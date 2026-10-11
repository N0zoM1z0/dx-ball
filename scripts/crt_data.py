"""Ground CRT definitions in complete code and independently placed data."""
import hashlib
import json
from pathlib import Path

import pefile

from coff import parse, region, _relocations
from crt_library import extract, function_section, members, relocate


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def verify_absolute_definitions(root, manifest, mapping):
    """Verify external COFF ABS values without placing target storage."""
    entries = manifest.get('absolute_definitions', [])
    selected = {entry['member_header_offset'] for entry in entries}
    library = root / manifest['library']
    raw_members = {offset: (name, raw) for offset, name, raw in members(library)
                   if offset in selected}
    exports, rows, inputs = {}, [], {}
    for entry in entries:
        if entry['symbol'] in exports:
            raise ValueError('duplicate absolute definition')
        name, raw = raw_members[entry['member_header_offset']]
        if name != entry['member'] or hashlib.sha256(raw).hexdigest() != entry['member_sha256']:
            raise ValueError('absolute member identity mismatch')
        obj = root / 'build/probes/crt-absolute' / f"{entry['member_header_offset']:08x}.obj"
        obj.parent.mkdir(parents=True, exist_ok=True)
        obj.write_bytes(raw)
        _, _, symbols = parse(obj)
        defined = [s for s in symbols.values() if s['name'] == entry['symbol']]
        if (len(defined) != 1 or defined[0]['section'] != -1 or
                defined[0]['storage'] != 2):
            raise ValueError('absolute binding requires one external COFF ABS definition')
        value = defined[0]['value']
        if value != entry['value']:
            raise ValueError('absolute definition value differs')
        established = {**mapping, **exports}
        if entry['symbol'] in established and established[entry['symbol']] != value:
            raise ValueError('absolute definition contradicts established binding')
        exports[entry['symbol']] = value
        inputs[str(obj.relative_to(root))] = digest(obj)
        rows.append(dict(**entry, status='same', section=-1, storage=2,
                         object=str(obj.relative_to(root)),
                         basis='external absolute definition in hash-verified COFF member'))
    return exports, rows, inputs


def verify_definitions(root, library, entries, mapping, base, loaded):
    exports, rows, inputs = {}, [], {}
    for entry in entries:
        address = int(entry['address'], 0)
        obj, identity = extract(library, entry['symbol'], root / 'build/probes/crt-definitions')
        code, relocations = function_section(obj, entry['symbol'])
        if len(code) != entry['size'] or not base <= address <= base + len(loaded) - len(code):
            raise ValueError('prior definition whole-section extent mismatch')
        linked = relocate(code, relocations, address, mapping)
        if linked != loaded[address - base:address - base + len(linked)]:
            raise ValueError('prior definition whole-section bytes differ')
        _, _, symbols = parse(obj)
        symbol = next(s for s in symbols.values() if s['name'] == entry['symbol'] and s['section'] > 0)
        if symbol['storage'] not in (2, 3) or symbol['value'] != 0:
            raise ValueError('prior definition is not a complete section-start function')
        if entry['symbol'] in mapping and mapping[entry['symbol']] != address:
            raise ValueError('prior definition contradicts established binding')
        if symbol['storage'] == 2:
            exports[entry['symbol']] = address
        inputs[str(obj.relative_to(root))] = digest(obj)
        rows.append(dict(**entry, **identity, object=str(obj.relative_to(root)),
                         status='same', external_definition=symbol['storage'] == 2,
                         code_sha256=hashlib.sha256(linked).hexdigest(),
                         relocations=relocations,
                         applied_bindings={r['symbol']: hex(mapping[r['symbol']]) for r in relocations}))
    return exports, rows, inputs


def verify_data_sections(root, manifest, mapping, original):
    library = root / manifest['library']
    selected = {e['member_header_offset'] for e in manifest.get('data_sections', [])}
    raw_members = {offset: (name, raw) for offset, name, raw in members(library) if offset in selected}
    image = pefile.PE(str(original))
    carrier = original.read_bytes()
    exports, rows, inputs = {}, [], {}
    for entry in manifest.get('data_sections', []):
        address = int(entry['address'], 0)
        name, raw = raw_members[entry['member_header_offset']]
        if name != entry['member'] or hashlib.sha256(raw).hexdigest() != entry['member_sha256']:
            raise ValueError('data member identity mismatch')
        obj = root / 'build/probes/crt-data' / f"{entry['member_header_offset']:08x}.obj"
        obj.parent.mkdir(parents=True, exist_ok=True)
        obj.write_bytes(raw)
        data, sections, symbols = parse(obj)
        index = entry['section_index']
        if not 1 <= index <= len(sections):
            raise ValueError('missing complete data section')
        section = sections[index - 1]
        if (not section['flags'] & 0x40 or section['flags'] & 0x20 or
                not section['data'] or section['size'] != entry['size']):
            raise ValueError('complete initialized data extent mismatch')
        content = region(data, section['data'], section['size'])
        relocations = _relocations(data, section, symbols, content)
        defined = {s['name']: s for s in symbols.values() if s['section'] == index}
        if any(s['value'] > len(content) for s in defined.values()):
            raise ValueError('data definition exceeds complete section')
        established = {**mapping, **exports}
        basis = entry['basis']
        if basis['kind'] == 'established_symbols':
            anchors = basis['symbols']
            if len(set(anchors)) < 2 or any(n not in established or n not in defined for n in anchors):
                raise ValueError('data placement requires multiple established symbols')
            bases = {established[n] - defined[n]['value'] for n in anchors}
            if bases != {address}:
                raise ValueError('established data anchors disagree with section placement')
            placement = {n: hex(established[n]) for n in anchors}
        elif basis['kind'] == 'unique_initialized_symbol':
            if basis['symbol'] not in defined:
                raise ValueError('missing initialized discovery symbol')
            start = defined[basis['symbol']]['value']
            end = start + basis['size']
            next_definition = min((s['value'] for s in defined.values() if s['value'] > start),
                                  default=len(content))
            if (basis['size'] < 16 or end != next_definition or
                    any(r['offset'] < end and r['offset'] + 4 > start for r in relocations)):
                raise ValueError('discovery symbol overlaps a relocation or incomplete extent')
            needle = content[start:end]
            first = carrier.find(needle)
            if first < 0 or carrier.find(needle, first + 1) >= 0:
                raise ValueError('initialized discovery symbol is not unique')
            located = image.OPTIONAL_HEADER.ImageBase + image.get_rva_from_offset(first) - start
            if located != address:
                raise ValueError('unique initialized symbol does not locate the declared section')
            placement = dict(symbol=basis['symbol'], complete_symbol_bytes=len(needle), file_offset=first)
        elif basis['kind'] in ('unique_initialized_section', 'unique_initialized_string'):
            if relocations or not any(content):
                raise ValueError('whole-section discovery requires nonzero relocation-free initialized data')
            if basis['kind'] == 'unique_initialized_string':
                literal = defined.get(basis['symbol'])
                if (literal is None or literal['value'] != 0 or
                        literal['storage'] != 2 or not literal['name'].startswith('??_C@') or
                        len(content) < 9 or content[-1:] != b'\0' or
                        any(c < 32 or c > 126 for c in content[:-1])):
                    raise ValueError('discovery requires a complete initialized ASCII string literal')
            elif len(content) < 16:
                raise ValueError('whole-section discovery requires at least sixteen initialized bytes')
            first = carrier.find(content)
            if first < 0 or carrier.find(content, first + 1) >= 0:
                raise ValueError('initialized discovery section is not unique')
            located = image.OPTIONAL_HEADER.ImageBase + image.get_rva_from_offset(first)
            if located != address:
                raise ValueError('unique initialized section does not locate the declared section')
            placement = dict(complete_section_bytes=len(content), file_offset=first)
        else:
            raise ValueError('unsupported independent data placement basis')
        local = {n: address + s['value'] for n, s in defined.items()}
        if any(n in established and established[n] != a for n, a in local.items()):
            raise ValueError('data definition contradicts an established symbol')
        linked = relocate(content, relocations, address, {**established, **local})
        path = root / entry['evidence_path']
        record = json.loads(path.read_text())
        evidence = record.get('evidence', record)
        if (record['evidence_id'] != entry['evidence_id'] or
                evidence['subject']['digest']['sha256'] != manifest['target_sha256'] or
                evidence['provider'] != manifest['provider']):
            raise ValueError('data Evidence target/provider identity mismatch')
        observed = record.get('result', record.get('raw_result'))
        if (observed is None or not observed['complete'] or int(observed['address'], 0) != address or
                observed['requested_bytes'] != len(linked) or observed['returned_bytes'] != len(linked)):
            raise ValueError('data Evidence complete extent mismatch')
        observed_bytes = bytes.fromhex(observed['bytes_hex'])
        if linked != observed_bytes or linked != image.get_data(address - image.OPTIONAL_HEADER.ImageBase, len(linked)):
            raise ValueError('whole relocated data differs from Evidence or PE')
        # No symbol becomes binding authority until its whole storage passes.
        actual_exports = {n: a for n, a in local.items() if defined[n]['storage'] == 2}
        exports.update(actual_exports)
        for p in (obj, path, path.parent / 'close.json'):
            inputs[str(p.relative_to(root))] = digest(p)
        rows.append(dict(**entry, status='same', placement=placement,
                         data_sha256=hashlib.sha256(linked).hexdigest(), relocations=relocations,
                         applied_bindings={r['symbol']: hex(({**established, **local})[r['symbol']]) for r in relocations},
                         exported_definitions={n: hex(a) for n, a in actual_exports.items()}))
    return exports, rows, inputs
