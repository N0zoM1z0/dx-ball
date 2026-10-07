#!/usr/bin/env python3
"""Compare the complete x86 storage image, including overlapping terminal copies."""
import hashlib
import json
from pathlib import Path
import random
import shutil
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import Toolchain, session_lock, windows_path
from resource_limits import limit_cpu
from target_oracle import TargetOracle, BANK, AUX, INDEX

SIZE = 20432
SEED = 0x43AAB8
ENTRIES = (0x40CEA0, 0x40CEE0, 0x411930)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def main():
    if not __debug__:
        raise SystemExit('Assertions must remain enabled')
    limit_cpu()
    lock = session_lock()
    target = TargetOracle()
    directory = ROOT / 'build/probes/storage-copy'
    directory.mkdir(parents=True, exist_ok=True)
    driver = directory / 'storage-copy.exe'
    compiler = Path(shutil.which('i686-w64-mingw32-gcc')).resolve()
    flags = ['-std=c90', '-Wall', '-Wextra', '-Wpedantic', '-Werror', '-O0']
    subprocess.run([str(compiler), *flags, str(ROOT / 'tests/windows_storage_copy.c'),
                    '-o', str(driver)], check=True, timeout=60)
    rng = random.Random(SEED)
    patterns = [bytes(SIZE), bytes((i * 73 + 19) & 255 for i in range(SIZE)), rng.randbytes(SIZE)]
    rows = [(operation, board, board if operation == 2 else (board + 7) % 51,
             image, rng.randbytes(400))
            for image in patterns for board in range(51) for operation in range(3)]
    fixtures, results = directory / 'input.bin', directory / 'output.bin'
    with fixtures.open('wb') as stream:
        stream.write(struct.pack('<I', len(rows)))
        for operation, board, selected, image, auxiliary in rows:
            stream.write(struct.pack('<IIi', operation, board, selected) + image + auxiliary)
    library = ROOT / 'build/windows-i686/libdxball_core.dll'
    toolchain = Toolchain()
    with (directory / 'wine.log').open('w') as log:
        subprocess.run(['xvfb-run', '-a', 'wine', str(driver), windows_path(library),
                        windows_path(fixtures), windows_path(results)], env=toolchain.env,
                       stdout=log, stderr=subprocess.STDOUT, check=True, timeout=90)
    response = results.read_bytes()
    offsets = struct.unpack_from('<6I', response)
    assert offsets == (0, 20000, 20008, 20024, 20032, SIZE), offsets
    assert len(response) == 24 + len(rows) * (SIZE + 404)
    cases = {'load': 0, 'store': 0, 'initialize': 0}
    for row, (operation, board, selected, image, auxiliary) in enumerate(rows):
        target.write(BANK, image)
        target.write(AUX, auxiliary)
        target.write_u32(INDEX, selected)
        target.call(ENTRIES[operation], *(() if operation == 2 else (board,)))
        expected = target.read(BANK, SIZE) + target.read(AUX, 400) + target.read(INDEX, 4)
        actual = response[24 + row * (SIZE + 404):24 + (row + 1) * (SIZE + 404)]
        assert actual == expected, (row, operation, board,
            next(i for i, (a, b) in enumerate(zip(actual, expected)) if a != b))
        cases[('load', 'store', 'initialize')[operation]] += 1
    inputs = ['tests/test_windows_storage.py', 'tests/windows_storage_copy.c',
              'tests/target_oracle.py', 'scripts/legacy_toolchain.py',
              'scripts/resource_limits.py', 'CMakeLists.txt', 'config/mingw-i686.cmake']
    inputs += [str(p.relative_to(ROOT)) for p in sorted((ROOT / 'src').glob('*.[ch]'))]
    report = dict(status='pass', target_sha256=target.target_sha256, cases=cases,
        terminal_cases=sum(board == 50 for _, board, *_ in rows), seed=SEED,
        offsets=list(offsets), compared_region_bytes=SIZE, source_dll_sha256=digest(library),
        driver_sha256=digest(driver), compiler_sha256=digest(compiler), flags=flags,
        inputs={name: digest(ROOT / name) for name in inputs},
        fixture_sha256=digest(fixtures), result_sha256=digest(results),
        scope='Source-owned MinGW x86 DLL calls versus unmodified original x86 copy/initializer code; '
              'all 50 bank indices and overlapping index50, zero/ramp/random adjacent state. '
              'No game-process mutation or native-64 layout equivalence claim.')
    (ROOT / 'build/reports/windows-storage.json').write_text(json.dumps(report, indent=2) + '\n')
    # Deterministic fixtures can be reproduced from this test and seed; avoid retaining 18 MiB.
    fixtures.unlink()
    results.unlink()
    lock.close()
    print('PASS x86 storage:', sum(cases.values()), 'full-image cases;', report['terminal_cases'], 'terminal cases')


if __name__ == '__main__':
    main()
