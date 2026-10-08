"""Full bitmap effects with controlled original/native pre-entry stack storage."""
import argparse
import hashlib
import json
from pathlib import Path
import platform
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from probe_bmp_loader import BitmapProbe
from bitmap_oracle import NativeBitmap


def sha(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def fixtures():
    for seed in (0, 0x5a, 0xa5, 0xff):
        for pitch in (2, 3, 5):
            yield dict(pitch=pitch), seed
    for fail in ('open', 'read1', 'read2', 'bits', 'read3', 'allocate', 'read4', 'lock', 'palette'):
        yield dict(fail=fail, bits=24 if fail == 'bits' else 8), 0x5a
    for path in (b'fixture.bmp', b'P' * 160):
        yield dict(fallback=True, path=path), 0x5a
    shorts = ([(1, n) for n in range(14)] +
              [(2, n) for n in (0, 13, 14, 15, 16, 17, 23, 39)] +
              [(3, n) for n in (0, 1, 3, 4, 255, 256, 1023)] +
              [(4, n) for n in range(7)])
    for stage, returned in shorts:
        for seed in (0, 0x5a, 0xa5, 0xff):
            for pitch in (2, 3, 5):
                yield dict(pitch=pitch, short_read=(stage, returned)), seed
    for width in (0, 1, 2, 3, 4, 7, 13):
        for height in (0, 1, 2, 3, 5):
            for pitch in sorted(set((0, max(1, width - 1), width, width + 3))):
                for seed in (0, 0x5a, 0xa5, 0xff):
                    yield dict(width=width, height=height, pitch=pitch), seed


def vectors(target, native):
    rows, buffers = [], {}

    def intern(value):
        key = hashlib.sha256(value).hexdigest()
        assert key not in buffers or bytes.fromhex(buffers[key]) == value
        buffers[key] = value.hex()
        return key

    code = target.read(0x401000, 0x1f000)
    imports = dict(target.import_slots)
    for fixture, seed in fixtures():
        target.fixture(**fixture)
        native.fixture(target)
        path_before = target.read(target.PATH, len(target._cstring(target.PATH)) + 1)
        expected, actual = target.invoke(seed), native.call(seed)
        assert expected == actual, (fixture, seed, 'return')
        assert target.events == native.events, (fixture, seed, 'events')
        pixels = target.read(target.guard, target.total)
        assert pixels == bytes(native.pixels), (fixture, seed, 'pixels')
        assert target.palette_bytes == native.palette_bytes, (fixture, seed, 'full palette')
        assert target.read_buffers == native.read_buffers, (fixture, seed, 'full read buffers')
        assert target.read(target.PATH, len(path_before)) == path_before
        assert bytes(native.path) == path_before
        reads = {}
        for number, read in target.read_buffers.items():
            reads[str(number)] = {name: value for name, value in read.items()
                                  if name not in ('before', 'after')}
            for name in ('before', 'after'):
                reads[str(number)][name + '_sha256'] = intern(read[name])
        allocation = None
        if target.pixel_allocation:
            allocation = target.read(target.pixel_allocation, len(target.input_pixels))
            assert allocation == bytes(native.pixel_buffer), (fixture, seed, 'source pixels')
        rows.append(dict(fixture={k: v.decode('ascii') if isinstance(v, bytes) else v
                                  for k, v in fixture.items()}, stack_seed=seed,
                         result=actual, events=target.events, reads=reads,
                         destination_sha256=intern(pixels),
                         palette_sha256=intern(target.palette_bytes) if target.palette_bytes is not None else None,
                         allocation_sha256=intern(allocation) if allocation is not None else None))
    assert len(rows) == 975
    assert target.read(0x401000, len(code)) == code
    assert all(target.read_u32(slot) == value for slot, value in imports.items())
    return dict(vectors=rows, complete_buffers=buffers,
                immutable_code_sha256=hashlib.sha256(code).hexdigest(),
                immutable_import_slots={hex(k): hex(v) for k, v in imports.items()})


def build_stack_driver():
    assert platform.system() == 'Linux' and platform.machine() == 'x86_64'
    compiler = Path(shutil.which('gcc')).resolve()
    source = ROOT / 'tests/seed_stack_x86_64.S'
    output = ROOT / 'build/probes/bitmap-stack-driver.so'
    output.parent.mkdir(parents=True, exist_ok=True)
    before = sha(source)
    flags = ['-shared', '-fPIC', '-Wl,--no-undefined']
    subprocess.run([str(compiler), *flags, str(source), '-o', str(output)], check=True)
    assert sha(source) == before
    return output, dict(source_sha256=before, product_sha256=sha(output),
                        compiler=str(compiler), compiler_sha256=sha(compiler), flags=flags,
                        scope='Test-only SysV caller seeds 64 KiB before entering actual C; no production code or local memory replacement')


def main():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    parser = argparse.ArgumentParser()
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    args = parser.parse_args()
    with session_lock():
        names = {str(p.relative_to(ROOT)) for p in (ROOT / 'src').glob('*')
                 if p.suffix in ('.c', '.h')}
        names.update({'CMakeLists.txt', 'config/target.toml', 'config/tools.lock.toml',
                      'tests/test_bitmap_differential.py', 'tests/bitmap_oracle.py',
                      'tests/seed_stack_x86_64.S', 'tests/probe_bmp_loader.py',
                      'tests/resources_oracle.py', 'tests/target_oracle.py',
                      'scripts/verify-target.py', 'scripts/resource_limits.py',
                      'scripts/legacy_toolchain.py', 'scripts/repo-python', 'scripts/verify-python.py'})
        frozen = {n: sha(ROOT / n) for n in sorted(names)}
        library_sha = sha(args.library)
        helper, helper_record = build_stack_driver()
        target, native = BitmapProbe(), NativeBitmap(args.library, helper)
        try:
            result = vectors(target, native)
        finally:
            native.restore()
        for name, value in frozen.items():
            assert sha(ROOT / name) == value, name
        assert sha(args.library) == library_sha
        assert sha(helper) == helper_record['product_sha256']
        report = dict(status='pass', target_sha256=target.target_sha256,
                      cases=dict(load_bitmap=975), total=975, inputs=frozen,
                      library_sha256=library_sha, stack_driver=helper_record, **result,
                      scope='Complete guarded destinations, full palette including unwritten flags, full short-read buffers and allocation bytes, ordered controlled API effects. Pre-entry stack seeds, nonnegative bounded geometry/backing, zero-size allocation success supplied by API fixture, bounded fallback paths. No general BMP correctness, physical API or active gameplay claim.')
        out = ROOT / 'build/reports/bitmap-differential.json'
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS bitmap:', report['total'], 'full-byte cases;', len(result['complete_buffers']), 'complete buffers')


if __name__ == '__main__':
    main()
