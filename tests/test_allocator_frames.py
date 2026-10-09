"""Compare allocation ownership over 21 fixtures / 564 original/native frames.

--source-check validates preparation without importing or constructing an oracle.
Execution writes a fresh directory under build/reports unless --output selects
another report directory. It does not compile or promote acceptance counters.
"""
import argparse
import ast
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
from pathlib import Path
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
CONNECTOR = ROOT / 'tests/allocator_frame_oracle.py'


def digest(path):
    with Path(path).open('rb') as handle:
        return hashlib.file_digest(handle, 'sha256').hexdigest()


def json_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def recipes():
    return ([dict(family='startup-launch', failures=n, frames=16) for n in (0, 1, 3)]
            + [dict(family='mixed-original-grid', board=b, failures=n, frames=40)
               for b in (0, 9, 24, 49) for n in (0, 1, 3)]
            + [dict(family='explosive-scratch', failures=n, frames=8) for n in (0, 1, 3)]
            + [dict(family='death-restart', failures=n, frames=4) for n in (0, 1, 3)])


def source_check():
    import csv
    for path in (CONNECTOR, Path(__file__)):
        ast.parse(path.read_text())
    with (ROOT / 'config/functions.csv').open() as handle:
        rows = list(csv.DictReader(handle))
    names = ('initialize_game', 'game_frame', 'spawn_fire_effect', 'spawn_particle',
             'spawn_brick_effect', 'queue_explosion_at', 'clone_balls',
             'spread_explosive_bricks', 'count_destructible_bricks', 'clear_all_entities')
    addresses = {}
    for name in names:
        matches = [row for row in rows if row['proposed_name'] == 'dxball_' + name]
        assert len(matches) == 1 and matches[0]['status'] in ('semantic', 'exact')
        addresses[name] = matches[0]['address']
    return dict(status='source-only-not-execution', recipes=recipes(),
                recipe_sha256=json_digest(recipes()),
                configured_entries=addresses,
                planned_game_frames=sum(recipe['frames'] for recipe in recipes()),
                connector_sha256=digest(CONNECTOR), runner_sha256=digest(__file__),
                pending=['Mixed fixture execution', 'Terminal allocation controls',
                         'Frozen cold replay', 'Review and acceptance update'])


def reject_live_capture():
    for name in ('allocator-vc40-full-phase.json', 'allocator-mingw-full-phase.json'):
        path = ROOT / '.analysis' / name
        if not path.exists():
            continue
        phase = json.loads(path.read_text())
        if phase['status'] in ('starting', 'running'):
            raise RuntimeError('Campaign capture is pending; poll its existing handle before frame execution: ' + str(path))


def main():
    if not __debug__:
        raise RuntimeError('Frame comparisons require assertions')
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-check', action='store_true')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    parser.add_argument('--gold', type=Path, help='Optional private input/product acceptance manifest')
    args = parser.parse_args()
    if args.source_check:
        print(json.dumps(source_check(), indent=2))
        return
    if args.output is None:
        stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
        args.output = ROOT / 'build/reports/allocator-frames' / stamp
    reject_live_capture()
    sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
    from resource_limits import limit_cpu
    from legacy_toolchain import session_lock
    from windows_runtime import verified_originals
    limit_cpu()

    output = args.output.resolve()
    assert output.is_relative_to(ROOT / '.analysis') or output.is_relative_to(ROOT / 'build/reports')
    assert not output.is_relative_to(ROOT / '.analysis/checkpoints')
    with session_lock():
        reject_live_capture()
        output.mkdir(parents=True, exist_ok=False)
        spec = importlib.util.spec_from_file_location('allocator_frame_connector', CONNECTOR)
        connector = importlib.util.module_from_spec(spec)
        sys.modules[spec.name] = connector
        spec.loader.exec_module(connector)
        importlib.import_module('unicorn.unicorn_py3.arch.intel')
        importlib.import_module('ghidra')  # Pure PE mapping helper used by verify-target
        from target_oracle import BANK, AUX, INDEX
        from test_campaign_differential import seed_geometry, observed
        from test_core_differential import SHAPES
        from test_gameplay_differential import REMAINING
        import ctypes as C
        import csv
        import pefile
        import unicorn

        with (ROOT / 'config/functions.csv').open() as handle:
            rows = list(csv.DictReader(handle))
        entries = {row['proposed_name']: int(row['address'], 16)
                   for row in rows if row['proposed_name']}
        selected = ('initialize_game', 'game_frame', 'spawn_fire_effect',
                    'spawn_particle', 'spawn_brick_effect', 'queue_explosion_at',
                    'clone_balls', 'spread_explosive_bricks', 'count_destructible_bricks',
                    'clear_all_entities')
        addresses = {name: entries['dxball_' + name] for name in selected}
        assert all(sum(row['proposed_name'] == 'dxball_' + name for row in rows) == 1
                   for name in selected)
        library = args.library.resolve()
        gold_path = args.gold.resolve() if args.gold else None
        inputs = {str(p): digest(p) for p in sorted((ROOT / 'src').glob('*.[ch]'))}
        if gold_path:
            gold = json.loads(gold_path.read_text())
            assert digest(library) == gold['native_library_sha256']
            for group in ('semantic_inputs', 'final_inputs', 'rea_inputs', 'reports', 'exact_objects'):
                for name, expected in gold[group].items():
                    path = (ROOT / name).resolve()
                    assert digest(path) == expected, name
                    inputs[str(path)] = expected
        for module in tuple(sys.modules.values()):
            filename = getattr(module, '__file__', None)
            if filename:
                path = Path(filename).resolve()
                if path.is_relative_to(ROOT) and path.suffix == '.py':
                    inputs[str(path)] = digest(path)
                    cached = getattr(module, '__cached__', None)
                    if cached and Path(cached).is_file():
                        inputs[str(Path(cached).resolve())] = digest(cached)
        for package in (unicorn, pefile):
            directory = Path(package.__file__).resolve().parent
            # Also bind package code and shipped engines not yet imported.
            for path in directory.rglob('*') if package is unicorn else (Path(package.__file__).resolve(),):
                if path.is_file() and (path.suffix == '.py' or '.so' in path.name):
                    inputs[str(path)] = digest(path)
        if gold_path:
            inputs[str(gold_path)] = digest(gold_path)
        for path in (library, CONNECTOR, Path(__file__).resolve(),
                     ROOT / 'scripts/repo-python', ROOT / 'config/functions.csv',
                     ROOT / 'config/target.toml', Path(sys.executable).resolve()):
            inputs[str(path)] = digest(path)
        originals = verified_originals()
        boards = (ROOT / 'original/DEFAULT.BDS').read_bytes()
        prepared = source_check()
        (output / 'inputs-before.json').write_text(json.dumps(dict(inputs=inputs, originals=originals), indent=2) + '\n')
        (output / 'recipes.json').write_text(json.dumps(prepared, indent=2) + '\n')
        report = dict(status='running', source_count_promotion=False,
                      library_sha256=digest(library), recipe_sha256=prepared['recipe_sha256'],
                      fixture_results=[], compared_game_frames=0, compared_auxiliary_calls=0,
                      startup_connections=0, observed_roles=[],
                      limitations=['Controlled external Heap API and retained new handler; no physical heap claim.',
                                   'Original COM, resource/audio, glyph and non-game boundaries remain controlled.',
                                   'Actual asset geometry uses a separate controlled original resource reader.',
                                   'Fixture grids and ordinary differential input are separate from full Windows campaigns.',
                                   'This positive batch does not certify fatal allocations, full CRT startup or terminal index50.'])
        began = time.monotonic()
        harness = None
        destination = output / 'summary.json'
        try:
            # All loaded source, engine and product identities are recorded
            # before construction executes the maintained/original trig bodies.
            harness = connector.ConnectedHarness(library)
            report['target_sha256'] = harness.t.target_sha256
            phase_log = []

            def call(name, *values):
                result = harness.phase_args(name, addresses[name], *values)
                n, t = harness.n, harness.t
                projection = dict(state=observed(harness),
                                  queues={owner: n.queue(owner) for owner in SHAPES},
                                  game_events_sha256=json_digest(n.events),
                                  pixels_sha256=hashlib.sha256(C.string_at(n.pixels, C.sizeof(n.pixels))).hexdigest(),
                                  display_state=n.display_observed(),
                                  heap_effects=n.heap_projection(), original_entry_calls=dict(t.entry_calls))
                phase_log.append(dict(name=name, arguments=values, observation_sha256=json_digest(projection)))
                if name == 'game_frame':
                    report['compared_game_frames'] += 1
                else:
                    report['compared_auxiliary_calls'] += 1
                harness.recycle_compared()
                return result

            def finish_fixture(recipe):
                call('clear_all_entities')
                assert not any(row['live'] for row in harness.n.allocations.values())
                assert not any(row['live'] for row in harness.t.allocations.values())
                roles = sorted({harness.n.role(op) for op in harness.n.operations})
                report['fixture_results'].append(dict(recipe=recipe, phases=list(phase_log), roles=roles,
                                                      native=harness.n.ownership_snapshot(),
                                                      original=harness.t.ownership_snapshot(),
                                                      original_entry_calls=dict(harness.t.entry_calls)))
                phase_log.clear()
                destination.write_text(json.dumps(report, indent=2) + '\n')

            for recipe in recipes():
                grid = boards[recipe.get('board', 0) * 400:(recipe.get('board', 0) + 1) * 400]
                if recipe['family'] == 'explosive-scratch':
                    special = bytearray(400)
                    special[85] = 8
                    grid = bytes(special)
                harness.seed(grid)
                harness.n.bank[:] = boards
                harness.t.write(BANK, boards)
                seed_geometry(harness)
                harness.initialize_heap()
                report['startup_connections'] += 1
                failures = recipe['failures']
                if recipe['family'] == 'startup-launch':
                    harness.n.arm_failures(failures)
                    harness.t.arm_failures(failures)
                    call('initialize_game')
                else:
                    remaining = call('count_destructible_bricks')
                    harness.state(REMAINING, remaining)
                    harness.ball(x=314, y=330, dx=4, dy=-7, sprite=61, speed=7)
                    harness.compare(('seed-ball', recipe))
                    if recipe['family'] == 'mixed-original-grid':
                        harness.add('bonuses', [12, 47, 315, 446, 0, 0, 0])
                        harness.n.count.value = 1
                        harness.t.write_u32(0x43FA90, 1)
                        call('spawn_brick_effect', 3, 3, 1, 0)
                        # This producer takes board indices, unlike effects'
                        # pixel positions. Keep the synthetic request in bounds.
                        call('queue_explosion_at', 3, 3)
                        call('spawn_fire_effect', 100, 200)
                        call('spawn_particle', 100, 100, 2, 1, 35, 1)
                        call('clone_balls')
                        harness.n.arm_failures(failures)
                        harness.t.arm_failures(failures)
                        harness.setv('bonus_8_active', 1)
                    elif recipe['family'] == 'explosive-scratch':
                        harness.n.arm_failures(failures)
                        harness.t.arm_failures(failures)
                        call('spread_explosive_bricks')
                    else:
                        # Retire the seeded last ball in a complete frame;
                        # restart_round must allocate its replacement naturally.
                        pointer = harness.n.owners['balls'].current
                        pointer.contents.y = 474
                        pointer.contents.dy = 2
                        pointer.contents.sprite = 1
                        pointer.contents.attached = 0
                        target = harness.t.read_u32(SHAPES['balls'][0])
                        harness.t.write_u32(target + 4, 474)
                        harness.t.write_u32(target + 20, 2)
                        harness.t.write_u32(target + 24, 1)
                        harness.t.write_u32(target + 40, 0)
                for frame in range(recipe['frames']):
                    if recipe['family'] == 'death-restart' and frame == 1:
                        # The previous frame retires the last ball. Only this
                        # frame observes the empty list, loses a life and resets.
                        assert not harness.n.owners['balls'].first
                        assert harness.t.read(SHAPES['balls'][0], 12) == bytes(12)
                        assert harness.t.entry_calls['runtime_delete'] == 1
                        assert harness.t.entry_calls['runtime_new'] == 1
                        harness.n.arm_failures(failures)
                        harness.t.arm_failures(failures)
                    harness.setv('mouse_action', 1 if frame in (0, 2, 17) else 0)
                    call('game_frame')
                    assert harness.n.index.value < 50, 'Terminal native pointer ABI needs separate evidence'
                finish_fixture(recipe)
            report['observed_roles'] = sorted({role for row in report['fixture_results'] for role in row['roles']})
            expected = {'balls', 'clones', 'effects', 'explosions', 'particles', 'bonuses', 'projectiles', 'fire'}
            assert expected.issubset(report['observed_roles']), report['observed_roles']
            assert {'scratch', 'explosive-scratch'}.intersection(report['observed_roles'])
            for name, expected_sha in inputs.items():
                assert digest(name) == expected_sha, name
            assert verified_originals() == originals
            replay_projection = [dict(recipe=row['recipe'], phases=row['phases'], roles=row['roles'],
                                      original_entry_calls=row['original_entry_calls'])
                                 for row in report['fixture_results']]
            report['replay_projection'] = replay_projection
            report['replay_projection_sha256'] = json_digest(replay_projection)
            assert report['compared_game_frames'] == prepared['planned_game_frames']
            report['status'] = 'connected-positive-frame-pass'
        except BaseException as error:
            report.update(status='fail', error=repr(error))
            if harness is not None:
                report['last_original_entry_calls'] = dict(harness.t.entry_calls)
                report['last_native_ownership'] = harness.n.ownership_snapshot()
                report['last_original_ownership'] = harness.t.ownership_snapshot()
            raise
        finally:
            report['seconds'] = round(time.monotonic() - began, 3)
            report['finished_utc'] = datetime.now(timezone.utc).isoformat()
            destination.write_text(json.dumps(report, indent=2) + '\n')
        print(json.dumps(dict(status=report['status'], frames=report['compared_game_frames'],
                              fixtures=len(report['fixture_results']), report=str(destination),
                              report_sha256=digest(destination)), indent=2))


if __name__ == '__main__':
    main()
