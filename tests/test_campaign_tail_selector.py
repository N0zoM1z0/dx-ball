#!/usr/bin/env python3
"""Bounded original/native input-delay controls for the sparse-tail selector."""
import copy
import ctypes as C
import hashlib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from campaign_controller import choose_contact_mouse, choose_mouse_decision
from legacy_toolchain import session_lock, sha256
from resource_limits import limit_cpu
import core_native_loader
from test_campaign_contact import state
from test_core_differential import Harness, CoreNative
from test_entities_differential import SHAPES
from test_gameplay_differential import Ops, REMAINING


class ParticleNative(CoreNative):
    """Track particle provenance across creation and deletion within one frame."""
    def __init__(self, library):
        self.particle_depth = 0
        self.transient_particle_frees = 0
        super().__init__(library)
        signature = dict(Ops._fields_)['particle']
        address = C.cast(self.core_gameplay_table.particle, C.c_void_p).value
        assert address
        self.real_particle = signature(address)

        def particle(*args):
            self.particle_depth += 1
            try:
                self.real_particle(*args)
            except BaseException as error:
                self.errors.append(repr(error))
            finally:
                self.particle_depth -= 1
        self.particle_callback = signature(particle)
        assert C.cast(self.particle_callback, C.c_void_p).value != address
        self.core_gameplay_table.particle = self.particle_callback

    def allocate(self, size):
        address = super().allocate(size)
        if self.particle_depth:
            self.allocations[address]['producer'] = 'actual-particle-boundary'
        return address

    def free(self, address):
        row = self.allocations[address]
        if row['owner'] is None and row.get('producer') == 'actual-particle-boundary':
            assert row['size'] == C.sizeof(SHAPES['particles'][1])
            row['owner'] = 'particles'
            self.transient_particle_frees += 1
        return super().free(address)


def samples():
    # Reduced observed geometry, not a replay of unobserved live modifiers.
    grid = bytearray(400)
    for column, row, tile in ((4, 5, 3), (15, 5, 3), (14, 7, 9), (14, 8, 9)):
        grid[column + row * 20] = tile
    for x, y, dx, dy, angle, bounces, walls, paddle, phase in (
            (455, 364, -5, 7, 60, 30, 2, 428, 4),
            (421, 366, -7, 6, 135, 40, 3, 346, 0)):
        yield dict(grid=bytes(grid), paddle=paddle, phase=phase,
                   payload=[x, y, x-dx, y-dy, dx, dy, 61, angle, 9, bounces, 0, 0, walls])


def observe(h):
    result = state(h)
    result.update(board_tiles=bytes(h.n.tiles).hex(), remaining_bricks=h.n.state[REMAINING].value,
                  sprite_bank=0)
    pointer = h.n.owners['balls'].first
    for ball in result['balls']:
        ball.update(speed=pointer.contents.speed, sprite=pointer.contents.sprite)
        pointer = pointer.contents.next
    return result


def fallback_controls():
    sample = next(samples())
    baseline = dict(paddle_x=sample['paddle'], paddle_width=146, paddle_previous_y=450,
                    bonuses=[], bonus_3_ticks=0, sprite_bank=0, board_tiles=sample['grid'].hex(),
                    balls=[dict(x=455, y=364, dx=-5, dy=7, width=9, height=9,
                                speed=9, attached=0)])
    before = copy.deepcopy(baseline)
    decision = choose_mouse_decision(baseline, 400)
    assert decision['policy'] == 'tail-ray' and decision['phase'] == 5
    assert decision['scheduled_phase'] == 4 and baseline == before
    controls = []
    for label in ('missing-grid', 'malformed-grid', 'dense-grid', 'hard-tile',
                  'modifier', 'bonus', 'multi-ball', 'rising', 'slow', 'above-field', 'zero-width'):
        value = copy.deepcopy(baseline)
        if label == 'missing-grid': value.pop('board_tiles')
        if label == 'malformed-grid': value['board_tiles'] = 'not hex'
        if label == 'dense-grid': value['board_tiles'] = bytes([3]*400).hex()
        if label == 'hard-tile': value['board_tiles'] = (bytes([2])+sample['grid'][1:]).hex()
        if label == 'modifier': value['bonus_3_ticks'] = 1
        if label == 'bonus': value['bonuses'] = [dict(kind=11, x=300, y=410, dx=0, width=20, height=20)]
        if label == 'multi-ball': value['balls'].append(dict(value['balls'][0]))
        if label == 'rising': value['balls'][0]['dy'] = -7
        if label == 'slow': value['balls'][0]['speed'] = 8
        if label == 'above-field': value['balls'][0]['y'] = 349
        if label == 'zero-width': value['paddle_width'] = 0
        original = copy.deepcopy(value)
        row = choose_mouse_decision(value, 400)
        assert row['policy'] == 'contact' and row['phase'] == row['scheduled_phase'] == 4
        assert row['x'] == choose_contact_mouse(value, 400) and value == original
        controls.append(label)
    return controls


def run_case(h, sample, interval, delay, policy):
    h.seed(sample['grid'])
    for name in ('paddle_x', 'paddle_previous_x', 'mouse_x'):
        h.setv(name, sample['paddle'])
    h.setv('paddle_width', 146)
    h.setv('cursor_warp_disabled', 1)
    h.sprite(61, 9, 9)
    h.sprite(68, 146, 7)
    h.state(REMAINING, 4)
    h.add('balls', sample['payload'])
    h.setv('ball_count', 1)
    decisions = sample['phase'] * 100
    pending, trace = {}, []
    contact = change = None
    stop = 'frame-limit'
    for frame in range(160):
        decision = None
        if frame % interval == 0:
            current = observe(h)
            decision = (choose_mouse_decision(current, decisions) if policy == 'tail'
                        else dict(x=choose_contact_mouse(current, decisions), phase=(decisions//100)%6,
                                  scheduled_phase=(decisions//100)%6, policy='contact'))
            pending[frame + delay] = decision['x']
            decisions += 1
        if frame in pending:
            h.setv('mouse_x', pending[frame])
        h.n.events = []; h.t.events = []
        h.call('game_frame')
        current = observe(h)
        balls = current['balls']
        trace.append(dict(frame=frame, decision=decision, balls=balls,
                          requested=h.n.extra[0x438B0C].value, paddle=current['paddle_x'],
                          ordered_events_sha256=hashlib.sha256(json.dumps(h.n.events, separators=(',', ':')).encode()).hexdigest()))
        if contact is None and balls and balls[0]['dy'] < 0:
            contact = dict(frame=frame, ball=balls[0])
        if bytes(h.n.tiles) != sample['grid']:
            change = dict(frame=frame, cells=[dict(index=i, before=a, after=b)
                for i, (a, b) in enumerate(zip(sample['grid'], bytes(h.n.tiles))) if a != b])
            stop = 'grid-changed'
            break
        if not balls:
            stop = 'ball-retired'
            break
        if contact is not None and balls[0]['dy'] > 0 and balls[0]['y'] >= 350:
            stop = 'returned-below-field'
            break
    return dict(policy=policy, interval=interval, delay=delay, initial_phase=sample['phase'],
                contact=contact, grid_change=change, stop=stop, trace=trace)


def main():
    if not __debug__:
        raise RuntimeError('Original-frame assertions must remain enabled')
    limit_cpu()
    guards = fallback_controls()
    cached = core_native_loader._verified_identity(core_native_loader._recipe())
    assert cached is not None, 'Reuse the existing fixture; no implicit rebuild'
    library = ROOT / 'build/native/libdxball_core.so'
    identities = {n: sha256(ROOT / n) for n in ('scripts/campaign_controller.py',
        'tests/test_campaign_tail_selector.py', 'build/native/libdxball_core.so',
        'build/vc40-restored-crt/dxball.exe', 'config/match-units.toml', 'config/functions.csv')}
    rows = []
    with session_lock():
        h = Harness(library, native_type=ParticleNative)
        original_code = h.t.read(0x401000, 0x1F000)
        try:
            for sample in samples():
                for interval, delay in ((1, 0), (3, 0), (3, 2)):
                    for policy in ('contact', 'tail'):
                        row = run_case(h, sample, interval, delay, policy)
                        assert row['contact'] is not None and row['stop'] != 'ball-retired'
                        if policy == 'tail': assert row['grid_change'] is not None
                        rows.append(row)
            assert h.t.read(0x401000, 0x1F000) == original_code
        finally:
            h.n.core_gameplay_table.particle = h.n.real_particle
    assert all(sha256(ROOT / n) == digest for n, digest in identities.items())
    assert core_native_loader._verified_identity(core_native_loader._recipe()) == cached
    report = dict(status='pass', cases=len(rows), compared_frames=sum(len(r['trace']) for r in rows),
        fixture_sha256=cached['artifact_sha256'], inputs=identities, fallback_controls=guards,
        transient_particle_frees=h.n.transient_particle_frees, vectors=rows,
        compiler_runs=0, provider_queries=0, game_runs=0, full_replay=False,
        scope='Two reduced observed geometries; existing complete CoreHarness comparisons. Controlled frame sampling/input delays, not measured live latency. Other globals use fixture defaults. First grid change is not a brick clear or campaign speedup. Selector ray omits side/corner collisions; live verification remains separate.')
    output = ROOT / 'build/reports/campaign-tail-selector.json'
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + '\n')
    print(f'PASS {len(rows)} input-delay cases / {report["compared_frames"]} original/native frames; {len(guards)} fallback controls')


if __name__ == '__main__':
    main()
