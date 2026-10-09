#!/usr/bin/env python3
"""Compare recovered rotation C with unmodified original x86 and helpers."""
import argparse
import ctypes as C
import hashlib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from resources_oracle import BANKS, SPRITE_BANK, Sprite
from rotation_oracle import (RotationTarget, RotationNative, fixtures, source_pixels,
                             callback_fixtures, width_offset_fixtures)
from target_oracle import ACTIVE_SURFACE


def sha(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def immutable(target, native, records):
    """Each ABI's raw storage is compared with its own prior bytes."""
    sources = []
    for bank, slot, record in records:
        model = target.surfaces[target.read_u32(record)]
        host = native.banks[bank].sprites[slot]
        sources.append((target.read(record, 45), target.read(model['pixels'], model['pitch'] * model['height']),
                        C.string_at(host, C.sizeof(Sprite) + 1), bytes(native.surfaces[host.contents.surface]['pixels'])))
    return (target.read(BANKS, 3 * 1048), bytes(native.banks), sources,
            target.read(0x424650, 1444), target.read(0x424BF8, 1444),
            bytes((C.c_int32 * 361).in_dll(native.lib, 'dxball_sine_table')),
            bytes((C.c_int32 * 361).in_dll(native.lib, 'dxball_cosine_table')))


def destination(target, native, original_surface, host_surface, before, buffers):
    model = target.surfaces[original_surface]
    expected = target.read(model['pixels'] - 32, 35 * 24 + 64)
    actual = bytes(native.surfaces[host_surface]['guarded_storage'])
    assert actual == expected, 'Complete guarded destination differs'
    assert expected[:32] == expected[-32:] == b'\xA5' * 32
    for row in range(24):
        start, end = row * 35 + 32, (row + 1) * 35
        assert expected[32 + start:32 + end] == before[start:end], 'Row padding changed'
    key = hashlib.sha256(expected).hexdigest()
    assert key not in buffers or bytes.fromhex(buffers[key]) == expected
    buffers[key] = expected.hex()
    return key


def seed_pixels(target, native, bank, slot, width, height, pattern):
    record = target.seed(bank, slot, width=width, height=height)
    native.seed(bank, slot, width=width, height=height)
    source = target.read_u32(record)
    host = native.banks[bank].sprites[slot].contents.surface
    model = target.surfaces[source]
    data = source_pixels(width, height, model['pitch'], pattern)
    target.write(model['pixels'], data)
    C.memmove(C.addressof(native.surfaces[host]['pixels']), data, len(data))
    return record, source, host


def baseline(target, native, buffers):
    results = []
    for entry in ('render_rotated_sprite', 'draw_rotated_sprite'):
        for case in fixtures():
            target.reset()
            native.reset()
            bank, slot, width, height = (case[k] for k in ('bank', 'slot', 'width', 'height'))
            target.padding = native.padding = case['padding']
            record, source, host = seed_pixels(target, native, bank, slot, width, height, case['pattern'])
            target.surfaces[source]['identity'] = native.surfaces[host]['identity'] = 'source'
            target.write_u32(SPRITE_BANK, bank)
            native.bank.value = bank
            for identity, key in (('active', 'destination_retries'), ('source', 'source_retries')):
                target.lock_scripts[identity] = [-200] * case[key]
                native.lock_scripts[identity] = [-200] * case[key]
            before = bytes((i * 17 + 0x51) % 256 for i in range(35 * 24))
            target.write(target.surfaces[target.SURFACE]['pixels'], before)
            C.memmove(C.addressof(native.surfaces[native.active]['pixels']), before, len(before))
            saved = immutable(target, native, [(bank, slot, record)])
            if entry == 'render_rotated_sprite':
                arguments = (*case['center'], slot, case['angle'])
                target.call(0x4026A0, *arguments)
            else:
                arguments = (slot, *case['center'], case['angle'])
                target.call(0x404280, *arguments)
            getattr(native.lib, 'dxball_' + entry)(*arguments)
            assert target.events == native.events, (entry, case, target.events, native.events)
            assert target.events[-2:] == [('unlock', 'active'), ('unlock', 'source')]
            assert not any(target.lock_scripts.values()) and not any(native.lock_scripts.values())
            assert immutable(target, native, [(bank, slot, record)]) == saved, (entry, case, 'immutable storage')
            assert target.read_u32(SPRITE_BANK) == native.bank.value == bank
            assert target.read_u32(ACTIVE_SURFACE) == target.SURFACE
            assert native.active_binding.value == native.active
            key = destination(target, native, target.SURFACE, native.active, before, buffers)
            assert not target.io_events
            results.append(dict(entry=entry, case=case, guarded_destination=key, events=target.events))
    return results


def callbacks(target, native, buffers):
    results = []
    scenarios = callback_fixtures() + (
        ('destination changes during failed lock', 0, 'replacement-active', 'replacement-active', 0),
        ('bank changes during failed source lock', 2, 'active', 'active', 2),
    )
    for name, sampled_source, drawn_destination, unlocked_destination, unlocked_source in scenarios:
        target.reset()
        native.reset()
        alternate = target.surface(32, 24)
        target.surfaces[alternate].update(identity='replacement-active', pixels=target.allocate(35 * 24 + 64) + 32)
        host_alternate = native.surface(32, 24, 'replacement-active')
        native.guard_surface(host_alternate)
        records = []
        for bank, (width, height) in enumerate(((7, 5), (11, 8), (9, 7))):
            record, source, host = seed_pixels(target, native, bank, 1, width, height, 'solid')
            records.append((bank, 1, record))
            identity = 'source-' + str(bank)
            target.surfaces[source]['identity'] = native.surfaces[host]['identity'] = identity
            target.lock_scripts[identity] = native.lock_scripts[identity] = []
            model = target.surfaces[source]
            data = bytes(1 + ((byte - 1 + 53 * bank) % 254)
                         for byte in target.read(model['pixels'], model['pitch'] * model['height']))
            target.write(model['pixels'], data)
            C.memmove(C.addressof(native.surfaces[host]['pixels']), data, len(data))
        target.lock_scripts['replacement-active'] = native.lock_scripts['replacement-active'] = []
        roles = {'active': (target.SURFACE, native.active), 'replacement-active': (alternate, host_alternate)}
        before = {}
        for i, (role, (surface, host)) in enumerate(roles.items()):
            data = bytes((byte * (17 + 2*i) + 0x51 + i*29) % 256 for byte in range(35 * 24))
            before[role] = data
            target.write(target.surfaces[surface]['pixels'], data)
            C.memmove(C.addressof(native.surfaces[host]['pixels']), data, len(data))
        if drawn_destination == 'replacement-active' and name != 'destination changes during failed lock':
            target.after_desc['active'] = lambda o: o.write_u32(ACTIVE_SURFACE, alternate)
            native.after_desc['active'] = lambda o: setattr(o.active_binding, 'value', host_alternate)
        elif sampled_source and name != 'bank changes during failed source lock':
            target.after_desc['active'] = lambda o: o.write_u32(SPRITE_BANK, 1)
            native.after_desc['active'] = lambda o: setattr(o.bank, 'value', 1)
        if name == 'bank changes between source descriptor and lock':
            target.after_desc['source-1'] = lambda o: o.write_u32(SPRITE_BANK, 2)
            native.after_desc['source-1'] = lambda o: setattr(o.bank, 'value', 2)
        elif name == 'bank changes during destination unlock':
            target.after_unlock['active'] = lambda o: o.write_u32(SPRITE_BANK, 2)
            native.after_unlock['active'] = lambda o: setattr(o.bank, 'value', 2)
        elif name == 'destination changes again during source lock':
            target.after_lock['source-0'] = lambda o: o.write_u32(ACTIVE_SURFACE, o.SURFACE)
            native.after_lock['source-0'] = lambda o: setattr(o.active_binding, 'value', o.active)
        elif name == 'destination changes during failed lock':
            target.lock_scripts['active'] = [-200]
            native.lock_scripts['active'] = [-200]
            target.after_lock['active'] = lambda o: o.write_u32(ACTIVE_SURFACE, alternate)
            native.after_lock['active'] = lambda o: setattr(o.active_binding, 'value', host_alternate)
        elif name == 'bank changes during failed source lock':
            target.lock_scripts['source-0'] = [-200]
            native.lock_scripts['source-0'] = [-200]
            target.after_lock['source-0'] = lambda o: o.write_u32(SPRITE_BANK, 2)
            native.after_lock['source-0'] = lambda o: setattr(o.bank, 'value', 2)
        saved = immutable(target, native, records)
        target.call(0x4026A0, 16, 12, 1, 137)
        native.lib.dxball_render_rotated_sprite(16, 12, 1, 137)
        described_source = 1 if sampled_source and name != 'bank changes during failed source lock' else 0
        expected = [('desc', 'active', 108, 14), ('lock', drawn_destination, 0),
                    ('desc', 'source-' + str(described_source), 108, 14),
                    ('lock', 'source-' + str(sampled_source), 0),
                    ('unlock', unlocked_destination), ('unlock', 'source-' + str(unlocked_source))]
        if name == 'destination changes during failed lock':
            expected.insert(1, ('lock', 'active', -200))
        elif name == 'bank changes during failed source lock':
            expected.insert(3, ('lock', 'source-0', -200))
        assert target.events == native.events == expected, (name, target.events, native.events)
        assert not any(target.lock_scripts.values()) and not any(native.lock_scripts.values())
        assert immutable(target, native, records) == saved, (name, 'immutable storage')
        assert target.read_u32(SPRITE_BANK) == native.bank.value == unlocked_source
        assert target.read_u32(ACTIVE_SURFACE) == roles[unlocked_destination][0]
        assert native.active_binding.value == roles[unlocked_destination][1]
        outputs = {role: destination(target, native, surface, host, before[role], buffers)
                   for role, (surface, host) in roles.items()}
        assert not target.io_events
        results.append(dict(scenario=name, events=expected, guarded_destinations=outputs))
    return results


def offsets(target, native):
    results = []
    for bank, slot, width, angle in width_offset_fixtures():
        target.reset()
        native.reset()
        record, _, _ = seed_pixels(target, native, bank, slot, 7, 5, 'sparse')
        target.write_u32(record + 8, width)
        native.banks[bank].sprites[slot].contents.width = width
        target.write_u32(SPRITE_BANK, bank)
        native.bank.value = bank
        saved = immutable(target, native, [(bank, slot, record)])
        raw = target.call(0x402CD0, slot, angle)
        expected = raw if raw < 0x80000000 else raw - 0x100000000
        actual = native.lib.dxball_rotated_sprite_offset(slot, angle)
        assert actual == expected, (bank, slot, width, angle, actual, expected)
        assert immutable(target, native, [(bank, slot, record)]) == saved
        assert not target.events and not native.events and not target.io_events
        assert target.read_u32(SPRITE_BANK) == native.bank.value == bank
        results.append(dict(bank=bank, slot=slot, width=width, angle=angle, value=actual))
    assert next(x['value'] for x in results if x['width'] == 13 and x['angle'] == -45) == -9
    return results


def main():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    args = parser.parse_args()
    with session_lock():
        target, native = RotationTarget(), RotationNative(args.library.resolve())
        target.write_u32(0x42309C, 0)
        target.call(0x402250)
        native.lib.dxball_initialize_trig()
        tables = {}
        for name, address in (('sine', 0x424650), ('cosine', 0x424BF8)):
            original = target.read(address, 1444)
            assert original == bytes((C.c_int32 * 361).in_dll(native.lib, 'dxball_' + name + '_table'))
            tables[name] = hashlib.sha256(original).hexdigest()
        buffers = {}
        baseline_results = baseline(target, native, buffers)
        callback_results = callbacks(target, native, buffers)
        offset_results = offsets(target, native)
        native.reset()
        cases = dict(render_rotated_sprite=351, draw_rotated_sprite=344, rotated_sprite_offset=329)
        assert len(baseline_results) == 688 and len(callback_results) == 7 and len(offset_results) == 329
        inputs = sorted({str(p.relative_to(ROOT)) for p in (ROOT / 'src').glob('*') if p.suffix in ('.c', '.cpp', '.h')} |
                        {'CMakeLists.txt', 'config/target.toml', 'tests/test_rotation_differential.py',
                         'tests/rotation_oracle.py', 'tests/resources_oracle.py', 'tests/target_oracle.py'})
        report = dict(status='pass', target_sha256=target.target_sha256, cases=cases, total=sum(cases.values()),
                      inputs={name: sha(ROOT / name) for name in inputs}, library_sha256=sha(args.library),
                      trig_table_sha256=tables, baseline=baseline_results, callbacks=callback_results,
                      offsets=offset_results, guarded_destinations=buffers,
                      scope='Original x86 renderer, wrapper and offset; original initializer/trig/x87/conversion; controlled DirectDraw storage and finite locks; bounded geometry and representable offset arithmetic; normal CRT division branch')
        output = ROOT / 'build/reports/rotation-differential.json'
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS rotation differential:', report['total'], 'cases;', len(buffers), 'complete guarded buffers')


if __name__ == '__main__':
    main()
