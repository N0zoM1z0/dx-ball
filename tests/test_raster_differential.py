#!/usr/bin/env python3
"""Compare complete original/native raster effects with controlled APIs."""
import argparse
import base64
import ctypes as C
import gzip
import hashlib
import itertools
import json
from pathlib import Path
import random
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from raster_oracle import RasterTarget, RasterNative


def sha(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def capture(data, buffers):
    key = hashlib.sha256(data).hexdigest()
    if key in buffers:
        assert gzip.decompress(base64.b64decode(buffers[key])) == data
    else:
        buffers[key] = base64.b64encode(gzip.compress(data, compresslevel=1, mtime=0)).decode()
    return key


def contours():
    shapes = [[(2, 3), (17, 5), (11, 23)], [(0, 0), (639, 0), (639, 480), (0, 480)],
              [(10, 10), (20, 10), (20, 30), (10, 30)], [(10, 10), (30, 30), (10, 30), (30, 10)],
              [(10, 10), (25, 10), (25, 20), (15, 20), (15, 30), (10, 30)],
              [(5, 5), (20, 15), (5, 25), (10, 15)], [(10, 10), (10, 30)],
              [(5, 5), (5, 5), (20, 5), (20, 25), (5, 25)],
              [(13, 8), (24, 19), (8, 26), (1, 17)], [(10, 10), (12, 50), (30, 14), (50, 50), (30, 30)]]
    rng = random.Random(0x40b550)
    for _ in range(24):
        points = [(rng.randrange(1, 100), rng.randrange(1, 80)) for _ in range(rng.randrange(3, 12))]
        if len({p[1] for p in points}) > 1:
            shapes.append(points)
    return shapes


def compare_frame(target, native, pitch, buffers):
    assert not native.errors, native.errors
    assert target.events == native.events, (target.events, native.events)
    assert target.snapshots == native.snapshots, 'Scratch state differs'
    expected = target.read(target.frame_base, pitch * 480 + 64)
    assert expected == bytes(native.frame), 'Complete destination differs'
    assert expected[:32] == expected[-32:] == b'\xa5' * 32
    for y in range(480):
        assert expected[32 + y * pitch + 640:32 + (y + 1) * pitch] == b'\xa5' * (pitch - 640)
    assert target.read(target.point_base, len(target.points) * 8 + 64) == target.point_before
    assert bytes(native.point_storage) == native.before
    for pointer, record in target.records.items():
        assert target.read(pointer, record['size']) == b'\xd5' * record['size']
    return capture(expected, buffers)


def polygons(target, native, buffers):
    clipped = [[(-20, -10), (700, -10), (700, 510), (-20, 510)],
               [(-30, 10), (-3, 10), (-3, 30), (-30, 30)],
               [(650, 10), (700, 10), (700, 50), (650, 50)],
               [(10, -20), (30, -20), (30, -2), (10, -2)],
               [(10, 490), (30, 490), (30, 510), (10, 510)],
               [(-20, 30), (30, -20), (660, 25), (630, 490)],
               [(638, 478), (642, 478), (642, 482), (638, 482)]]
    rows = []
    target.callee_cleanup = 20
    for entry, symbol, extra in [(0x40b550, 'dxball_fill_polygon', []),
                                  (0x40bb60, 'dxball_fill_polygon_clipped', clipped)]:
        for shape in contours() + extra:
            for points in (shape, shape[1:] + shape[:1], list(reversed(shape))):
                for pitch, color in ((640, 0), (643, 127), (648, 255)):
                    for mask in range(8):
                        target.fixture(points, pitch, mask)
                        native.fixture(points, pitch, mask)
                        target.call(entry, target.pixels, pitch, target.points_address, len(points), color)
                        getattr(native.lib, symbol)(native.pixels, pitch, native.points, len(points), color)
                        pixels = compare_frame(target, native, pitch, buffers)
                        scratch = json.dumps(target.snapshots, sort_keys=True).encode()
                        rows.append(dict(entry=hex(entry), points=points, pitch=pitch, color=color,
                                         fail_mask=mask, events=target.events, guarded_destination_sha256=pixels,
                                         scratch_sha256=hashlib.sha256(scratch).hexdigest()))
        print('PASS raster polygons', hex(entry), len(rows), 'cumulative cases', flush=True)
    return rows


def triangles(target, native, buffers):
    shapes = [[(2, 3), (17, 5), (11, 23)], [(10, 10), (30, 10), (20, 30)],
              [(10, 10), (20, 30), (30, 30)], [(10, 10), (10, 20), (10, 30)],
              [(1, 10), (20, 10), (30, 10)], [(0, 0), (639, 0), (639, 480)],
              [(-20, 20), (20, -20), (660, 490)], [(638, 478), (642, 478), (642, 482)],
              [(-30, 10), (-3, 10), (-3, 30)], [(650, 10), (700, 10), (700, 50)],
              [(10, -20), (30, -20), (30, -2)], [(10, 490), (30, 490), (30, 510)],
              [(0, 0), (1, 1), (2, 2)], [(3, 3), (3, 3), (10, 10)]]
    rng = random.Random(0x40ab90)
    shapes += [[(rng.randrange(-30, 680), rng.randrange(-10, 500)) for _ in range(3)] for _ in range(24)]
    target.callee_cleanup = 0
    rows = []
    for shape in shapes:
        for points in itertools.permutations(shape):
            for pitch, color in ((640, 0), (643, 127), (648, 255)):
                target.fixture(points, pitch, 0)
                native.fixture(points, pitch, 0)
                arguments = [value for point in points for value in point]
                target.call(0x40ab90, target.pixels, pitch, *arguments, color)
                native.lib.dxball_fill_triangle(native.pixels, pitch, *arguments, color)
                pixels = compare_frame(target, native, pitch, buffers)
                assert target.read_u32(0) == 0xffffffff, 'Original SEH chain not restored'
                rows.append(dict(entry='0x40ab90', points=points, pitch=pitch, color=color,
                                 events=target.events, guarded_destination_sha256=pixels))
    return rows


def spans(target, native, buffers):
    rows = []
    target.callee_cleanup = 0
    for alignment, left, length, color in itertools.product(
            range(4), range(9), (-3, 0, 1, 2, 3, 4, 5, 6, 31, 639), (0, 127, 255)):
        target.reset()
        base = target.allocate(1088)
        storage = C.create_string_buffer(b'\xa5' * 1088, 1088)
        row = base + 32 + alignment
        native_row = C.addressof(storage) + 32 + alignment
        right = left + length - 1
        target.call(0x40b4c0, row, left, right, color)
        native.lib.dxball_fill_horizontal_span(native_row, left, right, color)
        expected = target.read(base, 1088)
        assert expected == bytes(storage)
        assert expected[:32] == expected[-32:] == b'\xa5' * 32
        assert target.events == []
        rows.append(dict(entry='0x40b4c0', alignment=alignment, left=left,
                         length=length, color=color, guarded_destination_sha256=capture(expected, buffers)))
    return rows


def vectors(target, native):
    buffers = {}
    result = dict(polygons=polygons(target, native, buffers),
                  triangles=triangles(target, native, buffers), spans=spans(target, native, buffers),
                  guarded_destinations_gzip_base64=buffers)
    assert len(result['polygons']) == 5400 and len(result['triangles']) == 684 and len(result['spans']) == 1080
    return result


def main():
    assert __debug__, 'Oracle assertions must stay enabled'
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path, default=ROOT / 'build/native/libdxball_core.so')
    args = parser.parse_args()
    with session_lock():
        inputs = sorted({str(p.relative_to(ROOT)) for p in (ROOT / 'src').glob('*')
                         if p.suffix in ('.c', '.cpp', '.h')} |
                        {'CMakeLists.txt', 'config/target.toml', 'tests/test_raster_differential.py',
                         'tests/raster_oracle.py', 'tests/resources_oracle.py', 'tests/target_oracle.py',
                         'scripts/verify-target.py', 'scripts/resource_limits.py'})
        frozen = {name: sha(ROOT / name) for name in inputs}
        library_sha = sha(args.library)
        target, native = RasterTarget(), RasterNative(args.library.resolve())
        code, iat = target.read(0x401000, 0x1f000), target.read(0x4412a8, 4)
        try:
            result = vectors(target, native)
        finally:
            native.restore()
        assert target.read(0x401000, len(code)) == code and target.read(0x4412a8, 4) == iat
        assert all(sha(ROOT / name) == value for name, value in frozen.items())
        assert sha(args.library) == library_sha
        cases = dict(fill_polygon=2448, fill_polygon_clipped=2952, fill_triangle=684, fill_horizontal_span=1080)
        report = dict(status='pass', target_sha256=target.target_sha256, cases=cases, total=sum(cases.values()),
                      inputs=frozen, library_sha256=library_sha, **result,
                      immutable_code_sha256=hashlib.sha256(code).hexdigest(),
                      scope='Original x86 and shared native source; complete pixels/guards/padding, immutable '
                            'point storage, scalar scratch bytes and normalized pointer entries; allocation/free '
                            'and MulDiv are controlled boundaries; portable math default checked on sampled calls; '
                            'nonhorizontal polygons, bounded coordinates/backing and representable arithmetic; '
                            'no driver, game-use or exact-emission claim')
        output = ROOT / 'build/reports/raster-differential.json'
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(report, indent=2) + '\n')
        print('PASS raster differential:', report['total'], 'cases;', len(result['guarded_destinations_gzip_base64']),
              'losslessly stored complete buffers', flush=True)


if __name__ == '__main__':
    main()
