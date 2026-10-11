#!/usr/bin/env python3
"""Verify bounded CRT origins by complete code sections and grounded relocations."""
import argparse
import hashlib
import json
import re
import struct
from importlib.util import spec_from_file_location, module_from_spec
from pathlib import Path

import pefile

from coff import parse, region, _relocations
from crt_library import members
from crt_data import verify_absolute_definitions, verify_definitions, verify_data_sections
from crt_scope import publish_section, relocate_section
from crt_coupled import verify_code_data_groups
from legacy_toolchain import Toolchain, session_lock
from resource_limits import limit_cpu

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verify_imports(original, manifest, base, loaded):
    image = pefile.PE(str(original))
    mapped = image.get_memory_mapped_image()
    offset = base - image.OPTIONAL_HEADER.ImageBase
    if offset < 0 or mapped[offset:offset + len(loaded)] != loaded:
        raise ValueError('retained original bytes differ from the pinned PE')
    named = {}
    for descriptor in image.DIRECTORY_ENTRY_IMPORT:
        for entry in descriptor.imports:
            if entry.name:
                key = (descriptor.dll.decode().casefold(), entry.name.decode())
                if key in named:
                    raise ValueError('ambiguous named PE import')
                named[key] = entry.address

    def cell(entry):
        address = named.get((entry['dll'].casefold(), entry['name']))
        if address is None or address != int(entry['cell'], 0):
            raise ValueError('named PE import cell mismatch')
        return address

    def thunk(address, import_cell):
        rva = address - image.OPTIONAL_HEADER.ImageBase
        section = image.get_section_by_rva(rva)
        code = image.get_data(rva, 6)
        if (section is None or not section.Characteristics & 0x20000000 or
                code != b'\xff\x25' + struct.pack('<I', import_cell)):
            raise ValueError('complete import thunk differs')
        return code

    bindings, records, inputs = {}, {}, {}
    for entry in manifest.get('import_bindings', []):
        import_cell = cell(entry)
        spelling = re.fullmatch(r'(__imp__|_)(.+)@\d+', entry['symbol'])
        if not spelling or spelling[2] != entry['name']:
            raise ValueError('COFF import spelling mismatch')
        address = int(entry['address'], 0)
        if entry['kind'] == 'iat' and spelling[1] == '__imp__':
            if address != import_cell:
                raise ValueError('IAT symbol does not bind its named cell')
            basis = 'named PE IAT cell'
        elif entry['kind'] == 'jump_thunk' and spelling[1] == '_':
            code = thunk(address, import_cell)
            if not base <= address <= base + len(loaded) - 6:
                raise ValueError('import thunk exceeds retained byte observation')
            if loaded[address - base:address - base + 6] != code:
                raise ValueError('retained import thunk bytes differ')
            basis = 'complete PE and retained-byte import thunk'
        else:
            raise ValueError('unsupported import binding kind')
        if entry['symbol'] in bindings:
            raise ValueError('duplicate import symbol binding')
        bindings[entry['symbol']] = address
        records[entry['symbol']] = dict(entry, basis=basis)

    thunks, observations = [], {}
    for entry in manifest.get('import_thunks', []):
        if entry['size'] != 6:
            raise ValueError('import thunk extent must be six bytes')
        address = int(entry['address'], 0)
        code = thunk(address, cell(entry))
        path = ROOT / entry['evidence_path']
        if path not in observations:
            observations[path] = json.loads(path.read_text())
            inputs[str(path.relative_to(ROOT))] = digest(path)
            inputs[str((path.parent / 'close.json').relative_to(ROOT))] = digest(path.parent / 'close.json')
        observation = observations[path]
        evidence = observation['evidence']
        if (observation['evidence_id'] != entry['evidence_id'] or
                evidence['subject']['digest']['sha256'] != manifest['target_sha256'] or
                evidence['provider'] != manifest['provider']):
            raise ValueError('import Evidence target/provider identity mismatch')
        result = observation['result']
        if entry['evidence_facet'] == 'bytes':
            first = int(result['address'], 0)
            observed = bytes.fromhex(result['bytes_hex'])
            if (not result['complete'] or not first <= address <= first + len(observed) - 6 or
                    observed[address - first:address - first + 6] != code):
                raise ValueError('retained complete thunk byte evidence differs')
        elif entry['evidence_facet'] == 'callee':
            matches = [p for p in result['callees']
                       if re.fullmatch(r'0x[0-9a-fA-F]+', p.get('address', ''))
                       and int(p['address'], 0) == address]
            if len(matches) != 1:
                raise ValueError('missing unique retained import callee')
            candidate = matches[0]
            body = candidate['body']
            dll, name = candidate['name'].split('::', 1)
            if (dll.casefold() != entry['dll'].casefold() or name != entry['name'] or
                    not candidate['classification']['thunk'] or not body['available'] or
                    body['total_bytes'] != 6 or body['span_bytes'] != 6 or
                    body['non_contiguous'] or not body['contains_entry'] or
                    body['ranges'] != [{'start': hex(address), 'end': hex(address + 5)}]):
                raise ValueError('retained import callee identity/extent mismatch')
        else:
            raise ValueError('unsupported retained import facet')
        thunks.append(dict(entry, status='same', bytes_hex=code.hex(),
                           code_sha256=hashlib.sha256(code).hexdigest()))
    return bindings, records, thunks, inputs


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--manifest', type=Path, default=ROOT / 'config/runtime-origin-sections.json')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/reports/runtime-origin-sections.json')
    args = parser.parse_args()
    with session_lock():
        Toolchain().verify()
        manifest_path = args.manifest.resolve()
        manifest = json.loads(manifest_path.read_text())
        original = ROOT / 'original/DXBALL.EXE'
        library = ROOT / manifest['library']
        if digest(original) != manifest['target_sha256'] or digest(library) != manifest['library_sha256']:
            raise ValueError('origin target/library identity mismatch')
        spec = spec_from_file_location('crt_provenance', ROOT / 'scripts/verify-crt-provenance.py')
        crt = module_from_spec(spec)
        spec.loader.exec_module(crt)
        _, observations, _ = crt.observations(ROOT / '.analysis/rea/runs', manifest['target_sha256'], manifest['provider'])
        requested = manifest['byte_observation']
        base = int(requested['address'], 0)
        evidence_path, observed, evidence_hash = observations[base, requested['size']]
        if observed['evidence_id'] != requested['evidence_id']:
            raise ValueError('unexpected original-byte Evidence ID')
        loaded = bytes.fromhex(observed['result']['bytes_hex'])
        prior_path = ROOT / manifest['prior_binding_manifest']
        prior = json.loads(prior_path.read_text())
        if prior['target_sha256'] != manifest['target_sha256'] or prior['provider'] != manifest['provider']:
            raise ValueError('prior relocation map belongs to another target/provider')
        fixed = {name: int(value, 0) for name, value in prior['relocations'].items()}
        prior_symbols = set(fixed)
        imported, import_records, import_thunks, import_inputs = verify_imports(original, manifest, base, loaded)
        if any(n in fixed and fixed[n] != a for n, a in imported.items()):
            raise ValueError('named import contradicts the reviewed prior CRT map')
        fixed.update(imported)
        absolute, absolute_rows, absolute_inputs = verify_absolute_definitions(ROOT, manifest, fixed)
        fixed.update(absolute)
        definitions, definition_rows, definition_inputs = ({}, [], {})
        if manifest.get('verify_prior_definitions'):
            definitions, definition_rows, definition_inputs = verify_definitions(
                ROOT, library, prior['entries'],
                {n: int(a, 0) for n, a in prior['relocations'].items()}, base, loaded)
        fixed.update(definitions)
        data_exports, data_rows, data_inputs = verify_data_sections(ROOT, manifest, fixed, original)
        fixed.update(data_exports)
        selected = {s['member_header_offset'] for s in manifest['sections']}
        raw_members = {offset: (name, raw) for offset, name, raw in members(library) if offset in selected}
        inputs = {str(p.relative_to(ROOT)): digest(p) for p in (
            manifest_path, prior_path, original, library, ROOT / 'scripts/verify-runtime-origin-sections.py',
            ROOT / 'scripts/verify-crt-provenance.py', ROOT / 'scripts/crt_library.py', ROOT / 'scripts/coff.py',
            ROOT / 'scripts/crt_data.py', ROOT / 'scripts/crt_scope.py',
            ROOT / 'scripts/crt_coupled.py',
            ROOT / 'scripts/legacy_toolchain.py', ROOT / 'scripts/resource_limits.py',
            ROOT / 'scripts/repo-python', ROOT / 'scripts/verify-python.py',
            ROOT / 'config/tools.lock.toml', ROOT / 'requirements-analysis.txt',
            evidence_path.parent / 'close.json')}
        inputs[str(evidence_path.relative_to(ROOT))] = evidence_hash
        inputs.update(import_inputs)
        inputs.update(absolute_inputs)
        inputs.update(definition_inputs)
        inputs.update(data_inputs)
        scoped = {}
        for row in definition_rows:
            obj = ROOT / row['object']
            _, sections, symbols = parse(obj)
            defined = [s for s in symbols.values()
                       if s['name'] == row['symbol'] and s['section'] > 0]
            if len(defined) != 1 or defined[0]['value'] != 0:
                raise ValueError('verified prior definition section is ambiguous')
            index = defined[0]['section']
            if sections[index - 1]['size'] != row['size']:
                raise ValueError('verified prior definition extent differs')
            publish_section(scoped, (row['header_offset'], digest(obj)), symbols,
                            index, int(row['address'], 0), row['size'])
        for row in data_rows:
            obj = ROOT / 'build/probes/crt-data' / f"{row['member_header_offset']:08x}.obj"
            if digest(obj) != row['member_sha256']:
                raise ValueError('verified data member identity differs')
            _, _, symbols = parse(obj)
            publish_section(scoped, (row['member_header_offset'], row['member_sha256']),
                            symbols, row['section_index'], int(row['address'], 0), row['size'])
        results = []
        verified_exports = {}
        export_origins = {}
        for entry in manifest['sections']:
            address = int(entry['address'], 0)
            name, raw = raw_members[entry['member_header_offset']]
            if name != entry['member'] or hashlib.sha256(raw).hexdigest() != entry['member_sha256']:
                raise ValueError('selected member identity changed')
            obj = ROOT / 'build/probes/runtime-origin-sections' / f"{entry['member_header_offset']:08x}.obj"
            obj.parent.mkdir(parents=True, exist_ok=True)
            obj.write_bytes(raw)
            data, sections, symbols = parse(obj)
            index = entry['section_index']
            if not 1 <= index <= len(sections):
                raise ValueError('missing code section')
            section = sections[index - 1]
            if not section['flags'] & 0x20 or not section['data'] or section['size'] != entry['size']:
                raise ValueError('whole code section identity/size mismatch')
            code = region(data, section['data'], section['size'])
            rels = _relocations(data, section, symbols, code)
            local = {s['name']: address + s['value'] for s in symbols.values() if s['section'] == index}
            if any(s['value'] > len(code) for s in symbols.values() if s['section'] == index):
                raise ValueError('defined symbol exceeds the selected code section')
            established = {**fixed, **verified_exports}
            if any(s['storage'] == 2 and s['section'] == index and
                   s['name'] in established and established[s['name']] != address + s['value']
                   for s in symbols.values()):
                raise ValueError('external local definition contradicts the prior relocation map')
            member_id = (entry['member_header_offset'], entry['member_sha256'])
            linked, rels, bindings = relocate_section(data, section, symbols, code,
                address, index, member_id, scoped, established)
            if not base <= address <= base + len(loaded) - len(linked):
                raise ValueError('whole section exceeds the complete REA read')
            target = loaded[address-base:address-base+len(linked)]
            if linked != target:
                raise ValueError('whole relocated code section differs: ' + entry['address'])
            for candidate in entry['entries']:
                if not address <= int(candidate, 0) < address + len(linked):
                    raise ValueError('claimed origin entry lies outside the matched section')
            inputs[str(obj.relative_to(ROOT))] = digest(obj)
            applied, scoped_bindings = {}, []
            for binding in bindings:
                symbol = binding['symbol']
                same_section = binding['section'] == index
                same_member = binding['basis'] == 'earlier complete verified section in the same archive member'
                if same_member:
                    authority = scoped[member_id][binding['symbol_index']]
                    scoped_bindings.append(dict(binding, address=hex(binding['address']),
                        member_header_offset=member_id[0], member_sha256=member_id[1],
                        source_section_address=hex(authority['section_address'])))
                basis = ('section-defined symbol' if same_section else
                         'earlier fully verified section in the same member' if binding['storage'] == 3 else
                         import_records[symbol]['basis'] if symbol in imported else
                         'verified COFF absolute definition' if symbol in absolute else
                         'reviewed prior CRT map' if symbol in prior_symbols else
                         'fully verified prior definition section' if symbol in definitions else
                         'fully verified independently placed data section' if symbol in data_exports else
                         'earlier fully verified section export')
                row = dict(address=hex(binding['address']), basis=basis)
                if not same_section and symbol not in fixed:
                    row['section_address'] = (hex(scoped[member_id][binding['symbol_index']]['section_address'])
                                              if same_member else export_origins[symbol])
                if symbol in applied and applied[symbol] != row:
                    raise ValueError('name-only report would hide distinct COFF-index bindings')
                applied[symbol] = row
            results.append(dict(**entry, status='same', difference_count=0,
                code_sha256=hashlib.sha256(linked).hexdigest(), relocations=rels,
                applied_bindings=applied,
                actual_COFF_symbol_indices=[b['symbol_index'] for b in bindings],
                same_member_bindings=scoped_bindings))
            # Publish object-local definitions only after the complete section
            # and every relocation pass. The key is member identity + COFF index.
            publish_section(scoped, member_id, symbols, index, address, len(code))
            # Publish only external definitions after every byte and relocation
            # in this section has passed. Static names are local to their object.
            for symbol in symbols.values():
                if symbol['section'] == index and symbol['storage'] == 2:
                    verified_exports[symbol['name']] = address + symbol['value']
                    export_origins[symbol['name']] = entry['address']
        grouped_code, grouped_data, _, grouped_inputs = verify_code_data_groups(
            ROOT, manifest, {**fixed, **verified_exports}, scoped, base, loaded, original)
        results.extend(grouped_code)
        data_rows.extend(grouped_data)
        inputs.update(grouped_inputs)
        for path, hashed in inputs.items():
            if digest(ROOT / path) != hashed:
                raise ValueError('origin input changed during verification: ' + path)
        report = dict(status='pass', target_sha256=manifest['target_sha256'],
            original_byte_evidence_id=observed['evidence_id'], inputs=inputs,
            complete_sections=len(results) + len(definition_rows),
            complete_section_bytes=sum(r['size'] for r in results + definition_rows),
            origin_entries=len({int(a, 0) for r in results for a in r['entries']} |
                               {int(r['address'], 0) for r in import_thunks + definition_rows}),
            section_origin_entries=len({int(a, 0) for r in results for a in r['entries']} |
                                       {int(r['address'], 0) for r in definition_rows}),
            verified_definitions=definition_rows, absolute_definitions=absolute_rows,
            data_sections=data_rows,
            member_scoped_definitions=[dict(member_header_offset=member[0], member_sha256=member[1], **row)
                                       for member, rows in scoped.items() for row in rows.values()],
            complete_data_bytes=sum(r['size'] for r in data_rows),
            import_thunk_entries=len(import_thunks), import_thunk_bytes=sum(r['size'] for r in import_thunks),
            import_bindings=import_records, import_thunks=import_thunks,
            results=results, limitations=manifest['limitations'])
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + '\n')
        print('runtime origin sections:', report['complete_sections'], 'complete sections;',
              report['complete_section_bytes'], 'bytes;', report['origin_entries'], 'entries')


if __name__ == '__main__':
    main()
