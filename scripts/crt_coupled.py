"""Verify independently placed code/data groups before publishing definitions."""
import copy
import hashlib
import json

import pefile

from coff import parse, region, _relocations
from crt_library import members
from crt_scope import publish_section, relocate_section


def verify_code_data_groups(root, manifest, fixed, scoped, base, loaded, original):
    groups = manifest.get('code_data_groups', [])
    offsets = {g['member_header_offset'] for g in groups}
    raw_members = {o: (n, r) for o, n, r in members(root / manifest['library']) if o in offsets}
    image = pefile.PE(str(original))
    carrier = original.read_bytes()
    results, data_rows, exports, inputs = [], [], {}, {}

    for group in groups:
        offset, digest = group['member_header_offset'], group['member_sha256']
        name, raw = raw_members[offset]
        if name != group['member'] or hashlib.sha256(raw).hexdigest() != digest:
            raise ValueError('coupled member identity mismatch')
        obj = root / 'build/probes/crt-coupled' / f'{offset:08x}.obj'
        obj.parent.mkdir(parents=True, exist_ok=True)
        obj.write_bytes(raw)
        data, sections, symbols = parse(obj)
        key = (offset, digest)
        code, storage = group['code'], group['data']
        ci, di = code['section_index'], storage['section_index']
        if ci == di or not 1 <= ci <= len(sections) or not 1 <= di <= len(sections):
            raise ValueError('coupled sections must be distinct actual sections')
        cs, ds = sections[ci-1], sections[di-1]
        if (not cs['flags'] & 0x20 or not ds['flags'] & 0x40 or ds['flags'] & 0x20
                or not cs['data'] or not ds['data']
                or cs['size'] != code['size'] or ds['size'] != storage['size']):
            raise ValueError('coupled complete section extent/type mismatch')
        cb = region(data, cs['data'], cs['size'])
        db = region(data, ds['data'], ds['size'])
        cr, dr = _relocations(data, cs, symbols, cb), _relocations(data, ds, symbols, db)
        ca, da = int(code['address'], 0), int(storage['address'], 0)

        # Both locations come from independent literal bytes, never from an
        # observed relocation field. Contents are still provisional at this
        # point and cannot supply exports to another group or caller.
        def locate(content, rels, start, size, declared, executable):
            end = start + size
            if (size < 16 or not 0 <= start < end <= len(content)
                    or any(r['offset'] < end and r['offset']+4 > start for r in rels)):
                raise ValueError('coupled placement anchor overlaps a relocation or extent')
            needle = content[start:end]
            if not any(needle):
                raise ValueError('coupled placement anchor must be nonzero')
            first = carrier.find(needle)
            if first < 0 or carrier.find(needle, first+1) >= 0:
                raise ValueError('coupled placement anchor is not independently unique')
            address = image.OPTIONAL_HEADER.ImageBase + image.get_rva_from_offset(first) - start
            section = image.get_section_by_rva(address-image.OPTIONAL_HEADER.ImageBase)
            if (address != declared or section is None
                    or bool(section.Characteristics & 0x20000000) != executable):
                raise ValueError('coupled independent placement address/type differs')
            return dict(file_offset=first, section_offset=start, complete_anchor_bytes=size)

        basis = code['basis']
        if basis['kind'] != 'unique_nonrelocated_code':
            raise ValueError('unsupported coupled code placement basis')
        code_placement = locate(cb, cr, basis['offset'], basis['size'], ca, True)
        basis = storage['basis']
        if basis['kind'] != 'unique_initialized_symbol':
            raise ValueError('unsupported coupled data placement basis')
        anchors = [s for s in symbols.values() if s['section'] == di and s['name'] == basis['symbol']]
        if len(anchors) != 1:
            raise ValueError('coupled data anchor is not one actual definition')
        anchor = anchors[0]
        next_value = min((s['value'] for s in symbols.values()
                          if s['section'] == di and s['value'] > anchor['value']), default=len(db))
        if anchor['value'] + basis['size'] != next_value:
            raise ValueError('coupled initialized anchor is not a complete subobject')
        data_placement = locate(db, dr, anchor['value'], basis['size'], da, False)

        established = {**fixed, **exports}
        local = {key: copy.deepcopy(scoped.get(key, {}))}
        for index, address, content in [(ci, ca, cb), (di, da, db)]:
            for s in symbols.values():
                if (s['section'] == index and s['storage'] == 2
                        and s['name'] in established and established[s['name']] != address+s['value']):
                    raise ValueError('coupled definition contradicts established external binding')
            publish_section(local, key, symbols, index, address, len(content))
        linked_code, cr, code_bindings = relocate_section(data, cs, symbols, cb, ca, ci, key, local, established)
        linked_data, dr, data_bindings = relocate_section(data, ds, symbols, db, da, di, key, local, established)
        if (not base <= ca <= base+len(loaded)-len(cb)
                or linked_code != loaded[ca-base:ca-base+len(cb)]
                or linked_code != image.get_data(ca-image.OPTIONAL_HEADER.ImageBase, len(cb))):
            raise ValueError('coupled complete code differs from retained Evidence/PE')
        path = root / storage['evidence_path']
        record = json.loads(path.read_text())
        evidence = record.get('evidence', record)
        observed = record.get('result', record.get('raw_result'))
        if (record['evidence_id'] != storage['evidence_id']
                or evidence['subject']['digest']['sha256'] != manifest['target_sha256']
                or evidence['provider'] != manifest['provider']):
            raise ValueError('coupled data Evidence identity mismatch')
        if (not observed or not observed['complete'] or int(observed['address'], 0) != da
                or observed['requested_bytes'] != len(db) or observed['returned_bytes'] != len(db)
                or bytes.fromhex(observed['bytes_hex']) != linked_data
                or image.get_data(da-image.OPTIONAL_HEADER.ImageBase, len(db)) != linked_data):
            raise ValueError('coupled complete data differs from retained Evidence/PE')
        if any(not ca <= int(a, 0) < ca+len(cb) for a in code['entries']):
            raise ValueError('coupled origin entry exceeds complete code')

        identity = dict(member=name, member_header_offset=offset, member_sha256=digest,
                        code_data_group_complete=True)
        results.append(dict(**code, **identity, status='same', difference_count=0,
                            code_sha256=hashlib.sha256(linked_code).hexdigest(),
                            placement=code_placement, relocations=cr,
                            actual_COFF_symbol_indices=[r['symbol_index'] for r in code_bindings],
                            binding_records=code_bindings))
        data_rows.append(dict(**storage, **identity, status='same', placement=data_placement,
                              data_sha256=hashlib.sha256(linked_data).hexdigest(), relocations=dr,
                              actual_COFF_symbol_indices=[r['symbol_index'] for r in data_bindings],
                              binding_records=data_bindings,
                              exported_definitions={s['name']: hex(da+s['value']) for s in symbols.values()
                                                    if s['section'] == di and s['storage'] == 2}))
        # Retain the regular receipt fields alongside complete actual-index
        # bindings, with explicit group authority for cross-section references.
        for row, bindings in [(results[-1], code_bindings), (data_rows[-1], data_bindings)]:
            applied, member_rows = {}, []
            for binding in bindings:
                if binding['section'] in (ci, di) and binding['basis'] != 'current section definition by actual COFF symbol index':
                    binding['basis'] = 'same complete atomic code/data group'
                    member_rows.append(dict(binding, member_header_offset=offset, member_sha256=digest))
                record = dict(address=hex(binding['address']), basis=binding['basis'])
                if binding['symbol'] in applied and applied[binding['symbol']] != record:
                    raise ValueError('coupled name-only receipt would hide distinct bindings')
                applied[binding['symbol']] = record
            row['applied_bindings'] = applied
            row['same_member_bindings'] = member_rows
        for p in [obj, path, path.parent/'close.json']:
            inputs[str(p.relative_to(root))] = hashlib.sha256(p.read_bytes()).hexdigest()
        # Comparisons, receipt guards and complete input identities all pass.
        # Nothing from a failed group reaches the caller's binding authority.
        for index, address, content in [(ci, ca, cb), (di, da, db)]:
            publish_section(scoped, key, symbols, index, address, len(content))
            for s in symbols.values():
                if s['section'] == index and s['storage'] == 2:
                    exports[s['name']] = address+s['value']
    return results, data_rows, exports, inputs
