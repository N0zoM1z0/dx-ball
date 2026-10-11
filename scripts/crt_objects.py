"""Verify complete initialized objects without granting enclosing-section authority."""
import hashlib
import json
from pathlib import Path

import pefile

from coff import parse, region, _relocations
from crt_library import members


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verify_initialized_objects(root, manifest, original):
    groups = manifest.get('initialized_object_groups', [])
    selected = {g['member_header_offset'] for g in groups}
    library = root / manifest['library']
    raw_members = {o: (n, b) for o, n, b in members(library) if o in selected}
    carrier = original.read_bytes()
    image = pefile.PE(data=carrier)
    exports, results, inputs = {}, [], {}
    for entry in groups:
        name, raw = raw_members[entry['member_header_offset']]
        if name != entry['member'] or hashlib.sha256(raw).hexdigest() != entry['member_sha256']:
            raise ValueError('initialized object member identity mismatch')
        obj = root / 'build/probes/crt-objects' / f"{entry['member_header_offset']:08x}.obj"
        obj.parent.mkdir(parents=True, exist_ok=True)
        obj.write_bytes(raw)
        data, sections, symbols = parse(obj)
        index, start, size = entry['section_index'], entry['offset'], entry['size']
        if not 1 <= index <= len(sections):
            raise ValueError('initialized object section missing')
        section = sections[index - 1]
        if (not section['flags'] & 0x40 or section['flags'] & 0x20 or
                not section['data'] or start != 0 or size < 12 or size % 4 or size > section['size']):
            raise ValueError('initialized object group extent invalid')
        content = region(data, section['data'], section['size'])
        rels = _relocations(data, section, symbols, content)
        if any(r['offset'] < start + size and r['offset'] + 4 > start for r in rels):
            raise ValueError('initialized objects overlap a relocation')
        defined = {i: s for i, s in symbols.items()
                   if s['section'] == index and s['storage'] == 2}
        actual = sorted(((i, s) for i, s in defined.items() if start <= s['value'] < start + size),
                        key=lambda item: item[1]['value'])
        declared = entry['objects']
        if (len(actual) < 3 or len(declared) != len(actual) or
                [s['value'] for _, s in actual] != list(range(start, start + size, 4))):
            raise ValueError('initialized object group must cover every complete adjacent object')
        rows = []
        for (symbol_index, symbol), claim in zip(actual, declared):
            boundary = min((s['value'] for s in defined.values() if s['value'] > symbol['value']),
                           default=section['size'])
            if (claim['symbol_index'] != symbol_index or claim['symbol'] != symbol['name'] or
                    claim['size'] != 4 or boundary - symbol['value'] != 4 or symbol['type'] != 0):
                raise ValueError('initialized object identity or complete boundary differs')
            rows.append(dict(symbol_index=symbol_index, symbol=symbol['name'],
                             section=index, storage=symbol['storage'], type=symbol['type'],
                             value=symbol['value'], size=4))
        needle = content[start:start + size]
        pos = carrier.find(needle)
        if not any(needle) or pos < 0 or carrier.find(needle, pos + 1) >= 0:
            raise ValueError('complete initialized object group is not independently unique')
        address = image.OPTIONAL_HEADER.ImageBase + image.get_rva_from_offset(pos)
        if address != int(entry['address'], 0):
            raise ValueError('initialized object group independent placement differs')
        path = root / entry['evidence_path']
        record = json.loads(path.read_text())
        evidence = record.get('evidence', record)
        observed = record.get('result', record.get('raw_result'))
        if (record['evidence_id'] != entry['evidence_id'] or
                evidence['subject']['digest']['sha256'] != manifest['target_sha256'] or
                evidence['provider'] != manifest['provider'] or observed is None or not observed['complete']):
            raise ValueError('initialized object Evidence identity differs')
        raw_address = int(observed['address'], 0)
        raw_bytes = bytes.fromhex(observed['bytes_hex'])
        if (len(raw_bytes) != observed['requested_bytes'] or len(raw_bytes) != observed['returned_bytes'] or
                not raw_address <= address <= raw_address + len(raw_bytes) - size):
            raise ValueError('initialized objects exceed complete observed extent')
        if raw_bytes != image.get_data(raw_address - image.OPTIONAL_HEADER.ImageBase, len(raw_bytes)):
            raise ValueError('initialized object carrier differs from pinned PE')
        if needle != raw_bytes[address - raw_address:address - raw_address + size]:
            raise ValueError('complete initialized objects differ from Evidence')
        local = {}
        for row in rows:
            row['address'] = address + row['value'] - start
            local[row['symbol']] = row['address']
            if row['symbol'] in exports and exports[row['symbol']] != row['address']:
                raise ValueError('initialized object export contradicts earlier authority')
        result = dict(**entry, status='same', independent_file_offset=pos,
                      initialized_bytes_sha256=hashlib.sha256(needle).hexdigest(),
                      verified_objects=rows, enclosing_section_bytes=section['size'],
                      enclosing_section_complete=(size == section['size']),
                      authority='Only listed complete objects; no enclosing section/static/pointer authority')
        for p in (obj, path, path.parent / 'close.json'):
            inputs[str(p.relative_to(root))] = digest(p)
        # A failed group never leaks any exports or records.
        exports.update(local)
        results.append(result)
    return exports, results, inputs
