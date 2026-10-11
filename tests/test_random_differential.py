#!/usr/bin/env python3
"""Compare default random state, sequences and game wrappers with original x86."""
import argparse
import ctypes as C
import hashlib
import json
from pathlib import Path
import random
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from legacy_toolchain import session_lock, sha256
from resource_limits import limit_cpu
from target_oracle import TargetOracle


def main():
    if not __debug__:
        raise RuntimeError('Random comparisons require assertions.')
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    parser.add_argument('--report', type=Path, default=ROOT / 'build/reports/random-differential.json')
    args = parser.parse_args()
    limit_cpu()
    with session_lock():
        target = TargetOracle()
        native = C.CDLL(str(args.library.resolve()))
        native.dxball_crt_srand.argtypes = [C.c_uint32]
        native.dxball_crt_srand.restype = None
        native.dxball_crt_rand.argtypes = []
        native.dxball_crt_rand.restype = C.c_int32
        native.dxball_random_range.argtypes = [C.c_int32]
        native.dxball_random_range.restype = C.c_int32
        state = C.c_uint32.in_dll(native, 'dxball_random_state')
        cell = 0x4230F4
        neighbors = target.read(cell - 8, 8), target.read(cell + 4, 8)
        observations = []

        def compare_next(context):
            expected = target.call(0x417A00)
            actual = native.dxball_crt_rand()
            assert actual == expected, (context, actual, expected)
            assert state.value == target.read_u32(cell), context
            assert 0 <= actual <= 32767
            assert neighbors == (target.read(cell - 8, 8), target.read(cell + 4, 8))
            observations.append((context, actual, state.value))

        assert state.value == target.read_u32(cell) == 1
        for step in range(16):
            compare_next(('default', step))
        seeds = [0, 1, 2, 299, 300, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFE, 0xFFFFFFFF]
        seeds += [1 << bit for bit in range(32)]
        fixture_random = random.Random(0x417A00)
        seeds += [fixture_random.getrandbits(32) for _ in range(128)]
        for index, seed in enumerate(seeds):
            target.call(0x4179F0, seed)
            native.dxball_crt_srand(seed)
            assert state.value == target.read_u32(cell) == seed
            for step in range(16):
                compare_next((index, step))

        # The actual game wrapper consumes the same state and preserves signed remainder.
        wrapper_cases = 0
        for seed in seeds[:9]:
            target.call(0x4179F0, seed)
            native.dxball_crt_srand(seed)
            for limit in (1, 2, 3, 20, 300, 32768, 0x7FFFFFFF, -1, -3, -32768):
                expected = target.call(0x403B70, limit)
                assert native.dxball_random_range(limit) == expected
                assert state.value == target.read_u32(cell)
                wrapper_cases += 1

        clock_type = C.CFUNCTYPE(C.c_uint32)
        ticks = 0
        clock = clock_type(lambda: ticks)
        clock_cell = C.c_void_p.in_dll(native, 'dxball_time_get_time')
        old_clock = clock_cell.value
        native.dxball_seed_random.argtypes = []
        native.dxball_seed_random.restype = None
        clock_cases = 0
        try:
            clock_cell.value = C.cast(clock, C.c_void_p).value
            for ticks in (0, 1, 299, 300, 301, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
                native.dxball_seed_random()
                target.call(0x4179F0, ticks % 300)
                assert state.value == target.read_u32(cell) == ticks % 300
                compare_next(('clock seed', ticks))
                clock_cases += 1
        finally:
            clock_cell.value = old_clock

        report = dict(status='pass', target_sha256=target.target_sha256,
                      library_sha256=sha256(args.library), seed_cases=len(seeds),
                      next_cases=len(observations), wrapper_cases=wrapper_cases,
                      clock_seed_cases=clock_cases,
                      observation_sha256=hashlib.sha256(json.dumps(observations).encode()).hexdigest(),
                      inputs={name: sha256(ROOT / name) for name in (
                          'src/random.c', 'src/random.h', 'src/startup.c', 'src/state_types.h',
                          'tests/test_random_differential.py', 'tests/target_oracle.py')},
                      scope='Unmodified original srand/rand and random_range, full state after every call, '
                            'initial state, reseeding and adjacent original bytes; fresh maintained defaults. '
                            'Clock transport controlled only for game seed modulo300; nonzero limits.')
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS original/default RNG:', len(observations), 'next calls,',
              len(seeds), 'seeds,', wrapper_cases, 'range calls,', clock_cases, 'clock seeds')


if __name__ == '__main__':
    main()
