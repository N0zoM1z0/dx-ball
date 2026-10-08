"""Record original rotation outputs with controlled surfaces and finite locks.

This runs original trig initialization, lookup, x87 division and integer
conversion. It supplies no maintained rotation or host math replacement.
"""
import hashlib
import json
from fractions import Fraction
from pathlib import Path
import struct
import sys

from resources_oracle import BANKS, SPRITE_BANK
from rotation_oracle import RotationTarget, fixtures, source_pixels, width_offset_fixtures, callback_fixtures
from target_oracle import ACTIVE_SURFACE

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from resource_limits import limit_cpu


def sha256(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def probe_width_offset(target, cosine_table):
    """Check the instruction-derived candidate; backing divisor is independently confirmed through REA."""
    cosine = struct.unpack('<361i', cosine_table)
    divisor = Fraction.from_float(1.3)

    def term(width, angle):
        index = 360 - ((-angle) % 360) if angle < 0 else angle % 360
        return abs(int(Fraction(width * cosine[index], 1024) / divisor))

    cases = width_offset_fixtures()
    results = []
    for bank, slot, width, angle in cases:
        target.reset()
        record = target.seed(bank, slot, width=7, height=5)
        # Only the scalar record width is consumed on this path. The backing
        # source surface remains valid even for the signed scalar fixtures.
        target.write_u32(record + 8, width)
        target.write_u32(SPRITE_BANK, bank)
        record_before = target.read(record, 45)
        banks_before = target.read(BANKS, 3 * 1048)
        value = target.call(0x402CD0, slot, angle)
        actual = value if value < 0x80000000 else value - 0x100000000
        expected = -max(term(width, angle + 45), term(width, angle + 135))
        assert actual == expected, (bank, slot, width, angle, actual, expected)
        assert not target.events and not target.io_events
        assert target.read(record, 45) == record_before
        assert target.read(BANKS, 3 * 1048) == banks_before
        assert target.read_u32(SPRITE_BANK) == bank
        results.append(dict(bank=bank, slot=slot, width=width, angle=angle, value=actual))
    assert len(results) == 329
    # A double temporary would round 13/1.3 to ten before truncation. The
    # original extended division instead truncates the value below ten to nine.
    assert next(x['value'] for x in results if x['width'] == 13 and x['angle'] == -45) == -9
    return results


def probe_callback_changes(target, destinations):
    """Observe global reacquisition; compare pixels with stable original controls."""
    control = RotationTarget()
    control.write_u32(0x42309C, 0)
    control.call(0x402250)

    def setup(oracle):
        oracle.reset()
        alternate = oracle.surface(32, 24)
        oracle.surfaces[alternate].update(identity='replacement-active',
                                         pixels=oracle.allocate(35 * 24 + 64) + 32)
        records = []
        for bank, (width, height) in enumerate(((7, 5), (11, 8), (9, 7))):
            record = oracle.seed(bank, 1, width=width, height=height)
            records.append(record)
            source = oracle.surfaces[oracle.read_u32(record)]
            source['identity'] = 'source-' + str(bank)
            data = source_pixels(width, height, source['pitch'], 'solid')
            data = bytes(1 + ((byte - 1 + 53 * bank) % 254) for byte in data)
            oracle.write(source['pixels'], data)
            oracle.lock_scripts[source['identity']] = []
        oracle.lock_scripts['replacement-active'] = []
        for i, surface in enumerate((oracle.SURFACE, alternate)):
            model = oracle.surfaces[surface]
            data = bytes((byte * (17 + 2*i) + 0x51 + i*29) % 256 for byte in range(35 * 24))
            oracle.write(model['pixels'], data)
        oracle.write_u32(ACTIVE_SURFACE, oracle.SURFACE)
        return records, alternate

    rows = []
    for name, sampled_source, drawn_destination, unlocked_destination, unlocked_source in callback_fixtures():
        records, alternate = setup(target)
        control_records, control_alternate = setup(control)
        source_before = {bank: target.read(target.surfaces[target.read_u32(record)]['pixels'],
            target.surfaces[target.read_u32(record)]['pitch'] * target.surfaces[target.read_u32(record)]['height'])
            for bank, record in enumerate(records)}
        records_before = [target.read(record, 45) for record in records]
        banks_before = target.read(BANKS, 3 * 1048)
        destinations_before = {surface: target.read(target.surfaces[surface]['pixels'], 35 * 24)
                               for surface in (target.SURFACE, alternate)}
        if drawn_destination == 'replacement-active':
            target.after_desc['active'] = lambda oracle: oracle.write_u32(ACTIVE_SURFACE, alternate)
        elif sampled_source:
            target.after_desc['active'] = lambda oracle: oracle.write_u32(SPRITE_BANK, 1)
        if name == 'bank changes between source descriptor and lock':
            target.after_desc['source-1'] = lambda oracle: oracle.write_u32(SPRITE_BANK, 2)
        elif name == 'bank changes during destination unlock':
            target.after_unlock['active'] = lambda oracle: oracle.write_u32(SPRITE_BANK, 2)
        elif name == 'destination changes again during source lock':
            target.after_lock['source-0'] = lambda oracle: oracle.write_u32(ACTIVE_SURFACE, oracle.SURFACE)
        # The original captures dimensions before the first API boundary, but
        # later chooses the backing surface through current globals. The
        # stable original control uses the selected backing with the captured
        # record dimensions; its descriptor and pixel storage stay intact.
        control.write_u32(SPRITE_BANK, sampled_source)
        control.write_u32(control_records[sampled_source] + 8, 7)
        control.write_u32(control_records[sampled_source] + 12, 5)
        control.write_u32(ACTIVE_SURFACE, control_alternate if drawn_destination == 'replacement-active' else control.SURFACE)
        target.call(0x4026A0, 16, 12, 1, 137)
        control.call(0x4026A0, 16, 12, 1, 137)
        described_source = 1 if sampled_source else 0
        expected_calls = [('desc', 'active', 108, 14), ('lock', drawn_destination, 0),
            ('desc', 'source-' + str(described_source), 108, 14),
            ('lock', 'source-' + str(sampled_source), 0),
            ('unlock', unlocked_destination), ('unlock', 'source-' + str(unlocked_source))]
        assert target.events == expected_calls, (name, target.events)
        outputs = {}
        for role, surface, reference in (('active', target.SURFACE, control.SURFACE),
                                        ('replacement-active', alternate, control_alternate)):
            model = target.surfaces[surface]
            actual = target.read(model['pixels'] - 32, 35 * 24 + 64)
            expected = control.read(control.surfaces[reference]['pixels'] - 32, len(actual))
            assert actual == expected, (name, role)
            assert actual[:32] == actual[-32:] == b'\xA5' * 32
            for row in range(24):
                assert actual[32 + row*35 + 32:32 + (row+1)*35] == destinations_before[surface][row*35 + 32:(row+1)*35]
            digest = hashlib.sha256(actual).hexdigest()
            assert digest not in destinations or destinations[digest] == actual.hex()
            destinations[digest] = actual.hex()
            outputs[role] = digest
        assert [target.read(record, 45) for record in records] == records_before
        assert target.read(BANKS, 3 * 1048) == banks_before
        assert target.read_u32(SPRITE_BANK) == unlocked_source
        assert target.read_u32(ACTIVE_SURFACE) == (alternate if unlocked_destination == 'replacement-active' else target.SURFACE)
        for bank, record in enumerate(records):
            model = target.surfaces[target.read_u32(record)]
            assert target.read(model['pixels'], len(source_before[bank])) == source_before[bank]
        rows.append(dict(scenario=name, events=target.events, guarded_destinations=outputs,
            final_bank=target.read_u32(SPRITE_BANK), final_destination=unlocked_destination,
            comparison='Complete buffers equal stable original controls with captured geometry'))
    target.write_u32(ACTIVE_SURFACE, target.SURFACE)
    return rows


def run():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    target = RotationTarget()
    # Normal CRT division branch; initialization and its math helpers execute.
    target.write_u32(0x42309C, 0)
    allocation_state = (target.cursor, target.allocations.copy(), target.freed.copy())
    target.call(0x402250)
    assert not target.events and not target.io_events
    assert (target.cursor, target.allocations, target.freed) == allocation_state
    tables = {name: target.read(address, 361 * 4)
              for name, address in (('sine', 0x424650), ('cosine', 0x424BF8))}
    width_offsets = probe_width_offset(target, tables['cosine'])
    results, destinations = [], {}
    for case in fixtures():
        target.reset()
        bank, slot, width, height = (case[k] for k in ('bank', 'slot', 'width', 'height'))
        target.padding = case['padding']
        record = target.seed(bank, slot, width=width, height=height)
        source = target.read_u32(record)
        model = target.surfaces[source]
        model['identity'] = 'source'
        pixels = source_pixels(width, height, model['pitch'], case['pattern'])
        target.write(model['pixels'], pixels)
        target.write_u32(SPRITE_BANK, bank)
        record_before = target.read(record, 45)
        banks_before = target.read(BANKS, 3 * 1048)
        for identity, key in (('active', 'destination_retries'), ('source', 'source_retries')):
            target.lock_scripts[identity] = [-200] * case[key]
        destination = target.surfaces[target.SURFACE]
        before = bytes((i * 17 + 0x51) % 256 for i in range(35 * 24))
        target.write(destination['pixels'], before)
        target.call(0x4026A0, *case['center'], slot, case['angle'])
        actual = target.read(destination['pixels'], len(before))
        expected_calls = [('desc', 'active', 108, 14)]
        expected_calls += [('lock', 'active', -200)] * case['destination_retries']
        expected_calls += [('lock', 'active', 0), ('desc', 'source', 108, 14)]
        expected_calls += [('lock', 'source', -200)] * case['source_retries']
        expected_calls += [('lock', 'source', 0), ('unlock', 'active'), ('unlock', 'source')]
        assert target.events == expected_calls, (case, target.events)
        assert not any(target.lock_scripts.values())
        assert target.read(model['pixels'], len(pixels)) == pixels
        assert target.read(record, 45) == record_before
        assert target.read(BANKS, 3 * 1048) == banks_before
        assert target.read_u32(SPRITE_BANK) == bank
        guarded = target.read(destination['pixels'] - 32, len(before) + 64)
        assert guarded[:32] == guarded[-32:] == b'\xA5' * 32
        for row in range(24):
            assert actual[row*35 + 32:(row+1)*35] == before[row*35 + 32:(row+1)*35]
        if case['pattern'] == 'zero' or width == 0 or height == 0 or any(
                coordinate >= 0x80000000 for coordinate in case['center']):
            assert actual == before, case
        digest = hashlib.sha256(guarded).hexdigest()
        encoded = guarded.hex()
        assert digest not in destinations or destinations[digest] == encoded
        destinations[digest] = encoded
        results.append(dict(case=case, destination_sha256=digest,
            changed_bytes=sum(a != b for a, b in zip(actual, before)), events=target.events))
    assert len(results) == 344
    callback_changes = probe_callback_changes(target, destinations)
    for name, address in (('sine', 0x424650), ('cosine', 0x424BF8)):
        assert target.read(address, 361 * 4) == tables[name]
    inputs = ('tests/probe_rotation.py', 'tests/rotation_oracle.py', 'tests/resources_oracle.py',
        'tests/target_oracle.py', 'scripts/verify-target.py', 'scripts/resource_limits.py',
        'scripts/repo-python', 'scripts/verify-python.py', 'config/target.toml', 'config/tools.lock.toml')
    dossier = '.analysis/rea/runs/2026-10-07T10-33-32.118Z-interactive-2912559/03-analyze_function.json'
    width_dossier = '.analysis/rea/runs/2026-10-07T10-33-32.118Z-interactive-2912559/16-analyze_function.json'
    report = dict(scope='Original-machine investigation only; no maintained-C differential acceptance',
        target_sha256=target.target_sha256, inputs={name: sha256(ROOT / name) for name in inputs},
        rea_evidence_id='ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26',
        retained_dossier=dict(path=dossier, sha256=sha256(ROOT / dossier)),
        width_offset=dict(procedure='0x00402CD0', cases=len(width_offsets), results=width_offsets,
            candidate='-max(abs(trunc(width*cos(angle+45)/1.3)), abs(trunc(width*cos(angle+135)/1.3)))',
            comparison='Exact rational model of instruction-derived candidate; backing constant and C remain pending',
            rea_evidence_id='ev_274065db33e0f5af45f91e84ec3c68bf86d6b31f20e54434e568a1cca50290f5',
            retained_dossier=dict(path=width_dossier, sha256=sha256(ROOT / width_dossier))),
        original_trig=dict(initializer='0x00402250', entries=361,
            boundary_calls=[],
            table_sha256={name: hashlib.sha256(data).hexdigest() for name, data in tables.items()}),
        cases=len(results), results=results, guarded_destinations=destinations,
        callback_changes=callback_changes,
        limitations=['Controlled DirectDraw descriptors/storage and finite lock failures',
            'Normal CRT division branch with x87 control word 0x037F',
            'Bounded dimensions/nonnegative pitches; five explicit callback changes plus stable dependencies',
            'Constants/wrapper/reference REA requests and shared C implementation remain pending'])
    directory = ROOT / 'build/reports/rotation-investigation'
    directory.mkdir(parents=True, exist_ok=True)
    output = directory / 'original.json'
    output.write_text(json.dumps(report, indent=2) + '\n')
    print('Original rotation investigation:', len(results), 'renderer fixtures;', len(callback_changes),
          'callback scenarios;', len(width_offsets),
          'width-offset candidates;', len(destinations),
          'unique complete destination buffers;', output.stat().st_size, 'report bytes; no semantic promotion')


if __name__ == '__main__':
    run()
