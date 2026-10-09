"""Compare missing/rejecting-handler exits in original and maintained owners.

Native children must reach real C exit1 and its registered exit observer.
Original children stop at the controlled exit entry without a fake return.
Neither path certifies the original CRT cleanup implementation.
"""
import argparse
import ast
import csv
from datetime import datetime, timezone
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
CONNECTOR = ROOT / 'tests/allocator_frame_oracle.py'
POSITIVE = ROOT / 'tests/test_allocator_frames.py'


def sha(path):
    with Path(path).open('rb') as handle:
        return hashlib.file_digest(handle, 'sha256').hexdigest()


def recipes():
    return [dict(name=name, handler=handler, failed_owner=owner)
            for name, owner in (('initialize_game', 'balls'), ('frame-shoot', 'projectiles'),
                                ('frame-death-restart', 'balls'), ('spawn_fire_effect', 'fire'),
                                ('spawn_particle', 'particles'), ('clone_balls', 'clones'))
            for handler in ('missing', 'zero')]


def prepare():
    for path in (Path(__file__), CONNECTOR, POSITIVE):
        ast.parse(path.read_text())
    with (ROOT / 'config/functions.csv').open() as handle:
        rows = list(csv.DictReader(handle))
    configured = {}
    for name in ('initialize_game', 'game_frame', 'spawn_fire_effect', 'spawn_particle', 'clone_balls'):
        matches = [row for row in rows if row['proposed_name'] == 'dxball_' + name]
        assert len(matches) == 1 and matches[0]['status'] in ('semantic', 'exact')
        configured[name] = int(matches[0]['address'], 16)
    return dict(status='source-only-not-execution', recipes=recipes(), configured_entries=configured,
                inputs={str(p): sha(p) for p in (Path(__file__).resolve(), CONNECTOR, POSITIVE,
                                                ROOT / 'config/functions.csv')},
                scope='Prepared missing/zero-handler fatal controls. No terminal allocation, frame or replay executed.')


def reject_live():
    for name in ('allocator-vc40-full-phase.json', 'allocator-mingw-full-phase.json'):
        path = ROOT / '.analysis' / name
        if path.exists() and json.loads(path.read_text())['status'] in ('starting', 'running'):
            raise RuntimeError('Campaign capture is pending; poll its existing handle before terminal controls: ' + str(path))


def execution_inputs():
    """Bind actual imported source/cache and mapped libraries, including libc."""
    paths = {Path(sys.executable).resolve(), Path('/proc/self/exe').resolve()}
    for module in tuple(sys.modules.values()):
        for attribute in ('__file__', '__cached__'):
            name = getattr(module, attribute, None)
            if name and Path(name).is_file():
                paths.add(Path(name).resolve())
    for line in Path('/proc/self/maps').read_text().splitlines():
        fields = line.split(maxsplit=5)
        if len(fields) == 6 and fields[5].startswith('/'):
            path = Path(fields[5])
            assert not fields[5].endswith(' (deleted)'), 'Mapped library was deleted'
            if path.is_file():
                paths.add(path.resolve())
    return {str(path): sha(path) for path in sorted(paths)}


def verify_frozen(frozen):
    for name, digest in frozen['inputs'].items():
        assert sha(name) == digest, name
    from windows_runtime import verified_originals
    assert verified_originals() == frozen['originals']


def verify_execution(frozen):
    actual = execution_inputs()
    for name, digest in actual.items():
        assert frozen['inputs'].get(name) == digest, ('Unbound child execution input', name)
    return actual


def load_runtime():
    sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
    import ctypes as C
    from unicorn.x86_const import UC_X86_REG_EIP
    from target_oracle import TILES, AUX
    from test_core_differential import SHAPES
    from test_display_differential import DisplayHarness
    from test_allocator_differential import HEAP, HANDLER, MODE
    from test_gameplay_differential import signed
    from resource_limits import limit_cpu
    limit_cpu()
    spec = importlib.util.spec_from_file_location('terminal_frame_connector', CONNECTOR)
    base = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = base
    spec.loader.exec_module(base)

    class Policy:
        def __init__(self, *args):
            self.terminal_active = False
            self.record_callback = None
            super().__init__(*args)

        def arm_terminal(self, recipe, record_callback):
            self.recipe = recipe
            self.record_callback = record_callback
            self.arm_failures(1)
            self.terminal_active = True
            if hasattr(self, 'heap_storage'):
                if recipe['handler'] == 'missing':
                    self.handler_storage.value = None
            elif recipe['handler'] == 'missing':
                self.write_u32(HANDLER, 0)

        def handler_result(self, size):
            if not self.terminal_active:
                return super().handler_result(size)
            assert self.recipe['handler'] == 'zero'
            assert self.pending_operation is not None
            assert self.operations[self.pending_operation]['size'] == size
            self.heap_events.append(('handler', self.pending_operation, size, 0))
            self.record_callback('handler-stop', self)
            return 0

    class Native(Policy, base.ConnectedNative):
        def heap_allocate(self, heap, flags, size):
            result = super().heap_allocate(heap, flags, size)
            if self.terminal_active:
                assert result is None and size == C.sizeof(SHAPES[self.recipe['failed_owner']][1])
                self.record_callback('allocation-failure', self)
            return result

    class Target(Policy, base.ConnectedTarget):
        def heap_allocate(self, *unused):
            requested = self._args(3)[2]
            super().heap_allocate(*unused)
            if self.terminal_active:
                assert requested == SHAPES[self.recipe['failed_owner']][2] + 8
                assert self.pending_operation is not None
                self.record_callback('allocation-failure', self)

        def exit(self, *unused):
            assert self.terminal_active and self._args(1) == (1,)
            assert self.uc.reg_read(UC_X86_REG_EIP) == 0x417910
            self.record_callback('terminal-exit', self)
            super().exit(*unused)

    class Harness(base.ConnectedHarness):
        def __init__(self, library):
            DisplayHarness.__init__(self, library, Native, Target)

    def snapshot(stage, oracle, harness):
        native = oracle is harness.n
        assert not harness.n.errors, harness.n.errors
        queues = {owner: oracle.queue(owner) for owner in SHAPES}
        game_state = dict(observed=oracle.observed(), queues=queues,
                          state={hex(a): v.value if native else signed(oracle.read_u32(a))
                                 for a, v in harness.n.state.items()},
                          tiles=(bytes(oracle.tiles) if native else oracle.read(TILES, 400)).hex(),
                          aux=(bytes(oracle.aux) if native else oracle.read(AUX, 400)).hex(),
                          events=list(oracle.events), display_state=oracle.display_observed(),
                          pixels_sha256=hashlib.sha256(C.string_at(oracle.pixels, C.sizeof(oracle.pixels))
                                                      if native else oracle.read(oracle.PIXELS, C.sizeof(harness.n.pixels))).hexdigest())
        heap = oracle.heap_storage.value if native else oracle.read_u32(HEAP)
        mode = oracle.mode_storage.value if native else signed(oracle.read_u32(MODE))
        handler = oracle.handler_storage.value if native else oracle.read_u32(HANDLER)
        assert heap == base.HEAP_IDENTITY and mode == 0
        assert bool(handler) == (oracle.recipe['handler'] == 'zero')
        if stage == 'prefix-ready':
            assert oracle.pending_operation is None and oracle.remaining_failures == 1
        else:
            assert oracle.pending_operation is not None and oracle.remaining_failures == 0
        heap_events = []
        for event in oracle.heap_events:
            if event[0] == 'allocate':
                heap_events.append((*event[:4], bool(event[5])))
            elif event[0] == 'handler':
                heap_events.append((event[0], event[1], event[3]))
            else:
                heap_events.append(event)
        if not native:
            assert oracle.read(oracle.text_address, len(oracle.text_bytes)) == oracle.text_bytes
        return dict(stage=stage, shared=dict(game=game_state, heap=heap, mode=mode,
                                            handler_present=bool(handler), heap_events=heap_events,
                                            pending_operation=oracle.pending_operation),
                    raw=dict(handler_pointer=handler or 0, heap_events=list(oracle.heap_events),
                             requests={op: r['size'] for op, r in oracle.operations.items()},
                             allocations={str(a): dict(row) for a, row in oracle.allocations.items()}),
                    original_entry_calls=None if native else dict(oracle.entry_calls),
                    original_exit_pc=None if native or stage != 'terminal-exit' else oracle.uc.reg_read(UC_X86_REG_EIP))

    return C, Harness, snapshot


def child(args, prepared):
    reject_live()
    sys.path.insert(0, str(ROOT / 'scripts'))
    frozen = json.loads(args.frozen.read_text())
    assert frozen['prepared_inputs'] == prepared['inputs']
    # This gate precedes fixture and Unicorn imports, not just final reporting.
    verify_frozen(frozen)
    C, Harness, snapshot = load_runtime()
    from test_campaign_differential import seed_geometry
    from target_oracle import BANK
    from test_core_differential import SHAPES
    from windows_runtime import verified_originals
    initial_execution = verify_execution(frozen)
    identity_path = args.record.with_suffix('.identity.json')
    identity = dict(status='actual-child-identity', side=args.child, recipe=args.recipe,
                    frozen_sha256=sha(args.frozen), before_fixture=initial_execution)
    with identity_path.open('x') as stream:
        json.dump(identity, stream, indent=2)
        stream.write('\n')
    recipe = recipes()[args.recipe]
    library = Path(frozen['library'])
    assert sha(library) == frozen['library_sha256']
    assert verified_originals() == json.loads(args.originals.read_text())
    fd = os.open(args.record, os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o600)

    def emit(stage, oracle):
        if stage == 'terminal-exit':
            verify_frozen(frozen)
            identity['terminal_execution'] = verify_execution(frozen)
            identity_path.write_text(json.dumps(identity, indent=2) + '\n')
        observation = snapshot(stage, oracle, harness)
        data = (json.dumps(observation, sort_keys=True, separators=(',', ':')) + '\n').encode()
        offset = 0
        while offset < len(data):
            offset += os.write(fd, data[offset:])
        os.fsync(fd)

    harness = Harness(library)
    harness.seed()
    boards = (ROOT / 'original/DEFAULT.BDS').read_bytes()
    harness.n.bank[:] = boards
    harness.t.write(BANK, boards)
    seed_geometry(harness)
    harness.initialize_heap()
    addresses = prepared['configured_entries']
    if recipe['name'] != 'initialize_game':
        harness.phase('initialize_game', addresses['initialize_game'])
    if recipe['name'] == 'frame-shoot':
        harness.setv('bonus_8_active', 1)
        harness.setv('mouse_action', 1)
    elif recipe['name'] == 'frame-death-restart':
        node = harness.n.owners['balls'].current
        node.contents.y, node.contents.dy, node.contents.sprite, node.contents.attached = 474, 2, 1, 0
        target = harness.t.read_u32(SHAPES['balls'][0])
        for offset, value in ((4, 474), (20, 2), (24, 1), (40, 0)):
            harness.t.write_u32(target + offset, value)
        harness.phase('game_frame', addresses['game_frame'])
        assert not harness.n.owners['balls'].first
        assert harness.t.read(SHAPES['balls'][0], 12) == bytes(12)
        assert harness.t.entry_calls['runtime_delete'] == 1
        assert harness.t.entry_calls['runtime_new'] == 1
    function = 'game_frame' if recipe['name'].startswith('frame-') else recipe['name']
    values = ((100, 200) if function == 'spawn_fire_effect'
              else (100, 100, 2, 1, 35, 1) if function == 'spawn_particle' else ())
    oracle = harness.n if args.child == 'native' else harness.t
    oracle.arm_terminal(recipe, emit)
    emit('prefix-ready', oracle)
    if args.child == 'native':
        # glibc's observer runs only through actual C exit. Python failures and
        # unexpected returns take distinct _exit codes and cannot impersonate it.
        def observed_exit(context):
            try:
                emit('terminal-exit', harness.n)
            except BaseException as error:
                print('Terminal exit observation failed: ' + repr(error), file=sys.stderr, flush=True)
                os._exit(70)
        exit_observer = C.CFUNCTYPE(None, C.c_void_p)(observed_exit)
        libc = C.CDLL(None)
        register = libc.__cxa_atexit
        register.argtypes, register.restype = [C.c_void_p, C.c_void_p, C.c_void_p], C.c_int
        assert register(C.cast(exit_observer, C.c_void_p), None, None) == 0
        harness.n.call('dxball_' + function, *values)
        print('Fatal allocation returned unexpectedly', file=sys.stderr, flush=True)
        os._exit(72)
    else:
        try:
            harness.t.call(addresses[function], *values)
        except AssertionError:
            from unicorn.x86_const import UC_X86_REG_EIP
            assert harness.t.exit_status == 1 and harness.t.uc.reg_read(UC_X86_REG_EIP) == 0x417910
        else:
            raise AssertionError('Original fatal allocation returned')
        assert verified_originals() == json.loads(args.originals.read_text())
        os.close(fd)


def main():
    if not __debug__:
        raise RuntimeError('Terminal controls require assertions')
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source-check', action='store_true')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    parser.add_argument('--gold', type=Path, help='Optional private input/product acceptance manifest')
    parser.add_argument('--child', choices=('native', 'original'))
    parser.add_argument('--recipe', type=int, choices=range(len(recipes())))
    parser.add_argument('--record', type=Path)
    parser.add_argument('--originals', type=Path)
    parser.add_argument('--frozen', type=Path)
    args = parser.parse_args()
    prepared = prepare()
    if args.source_check:
        print(json.dumps(prepared, indent=2))
        return
    reject_live()
    if args.child:
        assert args.recipe is not None and args.record is not None and args.originals is not None and args.frozen is not None
        try:
            child(args, prepared)
        except BaseException as error:
            print('Terminal control child failed: ' + repr(error), file=sys.stderr, flush=True)
            os._exit(70)
        return
    if args.output is None:
        stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
        args.output = ROOT / 'build/reports/allocator-terminal' / stamp
    sys.path.insert(0, str(ROOT / 'scripts'))
    from legacy_toolchain import session_lock
    from resource_limits import limit_cpu
    from windows_runtime import verified_originals
    limit_cpu()
    with session_lock():
        reject_live()
        output = args.output.resolve()
        assert output.is_relative_to(ROOT / '.analysis') or output.is_relative_to(ROOT / 'build/reports')
        assert not output.is_relative_to(ROOT / '.analysis/checkpoints')
        output.mkdir(parents=True, exist_ok=False)
        original_path = output / 'originals-before.json'
        originals = verified_originals()
        original_path.write_text(json.dumps(originals, indent=2) + '\n')
        inputs = dict(prepared['inputs'])
        inputs.update({str(p): sha(p) for p in sorted((ROOT / 'src').glob('*.[ch]'))})
        for path in (ROOT / 'scripts/repo-python', ROOT / 'config/target.toml'):
            inputs[str(path)] = sha(path)
        library = args.library.resolve()
        if args.gold:
            gold_path = args.gold.resolve()
            gold = json.loads(gold_path.read_text())
            assert sha(library) == gold['native_library_sha256']
            inputs[str(gold_path)] = sha(gold_path)
            for group in ('semantic_inputs', 'final_inputs', 'rea_inputs', 'reports', 'exact_objects'):
                for name, digest in gold[group].items():
                    path = (ROOT / name).resolve()
                    assert sha(path) == digest, name
                    inputs[str(path)] = digest
        inputs[str(library)] = sha(library)
        # Import definitions only, without constructing a fixture/oracle. The
        # same closure is checked by each child before and after its imports.
        load_runtime()
        # Uc lazily imports the architecture implementation at construction.
        # Import its definitions now so the exact source/cache is frozen before
        # any child executes target code. No engine instance is constructed.
        importlib.import_module('unicorn.unicorn_py3.arch.intel')
        importlib.import_module('ghidra')  # verify-target's pure PE mapping helper
        inputs.update(execution_inputs())
        frozen = dict(inputs=inputs, originals=originals, prepared_inputs=prepared['inputs'],
                      library=str(library), library_sha256=sha(library))
        frozen_path = output / 'inputs-before.json'
        frozen_path.write_text(json.dumps(frozen, indent=2) + '\n')
        report = dict(status='running', controls=[], limitations=[
            'Controlled Heap API failure and missing/zero external handler; no physical heap exhaustion claim.',
            'Native C exit1 observed through glibc; original stops at the controlled exit entry0x417910.',
            'Original CRT exit cleanup and complete Windows startup/teardown remain unproved.'])
        began = time.monotonic()
        try:
            for index, recipe in enumerate(recipes()):
                records = {}
                for side in ('native', 'original'):
                    path = output / (str(index).zfill(2) + '-' + side + '.jsonl')
                    command = [ROOT / 'scripts/repo-python', Path(__file__).resolve(), '--child', side,
                               '--recipe', str(index), '--record', path, '--originals', original_path,
                               '--frozen', frozen_path]
                    result = subprocess.run(command, cwd=ROOT, capture_output=True, timeout=120)
                    (output / (path.stem + '.stdout')).write_bytes(result.stdout)
                    (output / (path.stem + '.stderr')).write_bytes(result.stderr)
                    expected_code = 1 if side == 'native' else 0
                    assert result.returncode == expected_code, (recipe, side, result.returncode, result.stderr)
                    assert not result.stdout and not result.stderr, (recipe, side, result.stdout, result.stderr)
                    observations = [json.loads(line) for line in path.read_text().splitlines()]
                    stages = ['prefix-ready', 'allocation-failure'] + (['handler-stop'] if recipe['handler'] == 'zero' else []) + ['terminal-exit']
                    assert [o['stage'] for o in observations] == stages
                    identity_path = path.with_suffix('.identity.json')
                    identity = json.loads(identity_path.read_text())
                    assert identity['side'] == side and identity['recipe'] == index
                    assert identity['frozen_sha256'] == sha(frozen_path)
                    for stage in ('before_fixture', 'terminal_execution'):
                        for name, digest in identity[stage].items():
                            assert inputs.get(name) == digest, name
                    records[side] = observations
                assert [o['shared'] for o in records['native']] == [o['shared'] for o in records['original']], recipe
                for side in records:
                    assert records[side][1]['shared']['game'] == records[side][-1]['shared']['game'], (recipe, side, 'Unexpected game effects after failed allocation')
                final = records['original'][-1]
                counts = final['original_entry_calls']
                baseline = records['original'][0]['original_entry_calls']
                delta = {name: count - baseline[name] for name, count in counts.items()}
                expected_delta = dict.fromkeys(counts, 0)
                for name in ('runtime_new', 'allocate_with_handler', 'heap_allocate', 'call_new_handler'):
                    expected_delta[name] = 1
                assert delta == expected_delta, (recipe, 'Terminal allocator entry delta', delta)
                assert final['original_exit_pc'] == 0x417910
                events = final['raw']['heap_events']
                assert counts['runtime_new'] == counts['allocate_with_handler'] == len(final['raw']['requests'])
                assert counts['heap_allocate'] == sum(e[0] == 'allocate' for e in events)
                assert counts['runtime_delete'] == counts['heap_release'] == sum(e[0] == 'release' for e in events)
                assert counts['initialize_runtime_heap'] == sum(e[0] == 'create' for e in events)
                assert sum(e[0] == 'handler' for e in events) == (recipe['handler'] == 'zero')
                assert counts['call_new_handler'] == 1 and counts['runtime_malloc'] == 0
                projection = [o['shared'] for o in records['original']]
                report['controls'].append(dict(recipe=recipe, native_exit=1, original_stop=1,
                                               observation_sha256=hashlib.sha256(json.dumps(projection, sort_keys=True).encode()).hexdigest(),
                                               original_entry_calls=counts, terminal_entry_delta=delta,
                                               original_prefix_entry_calls=baseline,
                                               child_identity_sha256={side: sha(output / (str(index).zfill(2) + '-' + side + '.identity.json'))
                                                                      for side in records}))
            for name, digest in inputs.items():
                assert sha(name) == digest, name
            assert verified_originals() == originals
            report['status'] = 'connected-terminal-controls-pass'
        except BaseException as error:
            report.update(status='fail', error=repr(error))
            raise
        finally:
            report['seconds'] = round(time.monotonic() - began, 3)
            report['finished_utc'] = datetime.now(timezone.utc).isoformat()
            (output / 'summary.json').write_text(json.dumps(report, indent=2) + '\n')
        print(json.dumps(dict(status=report['status'], controls=len(report['controls']),
                              report=str(output / 'summary.json'), report_sha256=sha(output / 'summary.json')), indent=2))


if __name__ == '__main__':
    main()
