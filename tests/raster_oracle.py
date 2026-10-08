"""Storage and API boundaries for original raster-controller execution."""
import ctypes as C
import struct

from unicorn import UC_HOOK_CODE
from resources_oracle import ResourceTarget


def normalized(data, role, edge_base, count, pointer_size):
    if role == 0:
        return data.hex()
    result = []
    for i in range(count):
        raw = data[i * pointer_size:(i + 1) * pointer_size]
        if raw == b'\xa5' * pointer_size:
            result.append('untouched')
            continue
        value = int.from_bytes(raw, 'little')
        index, offset = divmod(value - edge_base, 28)
        assert offset == 0 and 0 <= index < count, (role, i, value, edge_base)
        result.append(index)
    return result


def api_muldiv(number, numerator, denominator):
    # Controlled Win32 boundary, restricted to the sampled fixed-point domain.
    # These operands cannot produce half ties, denominator zero or overflow.
    assert denominator > 0 and numerator == 65536
    product = number * numerator
    quotient, remainder = divmod(abs(product), denominator)
    assert 2 * remainder != denominator
    if 2 * remainder > denominator:
        quotient += 1
    assert quotient <= 0x7fffffff
    return -quotient if product < 0 else quotient


class RasterTarget(ResourceTarget):
    callee_cleanup = 20

    def __init__(self):
        super().__init__()
        imported = [i for d in self.pe.DIRECTORY_ENTRY_IMPORT for i in d.imports
                    if i.address == 0x4412a8]
        assert len(imported) == 1 and imported[0].name == b'MulDiv'
        address = self.read_u32(0x4412a8)
        # A host callback at the unresolved import RVA supplies only MulDiv.
        # Neither original instructions nor the original IAT are rewritten.
        self.uc.mem_map(address & ~4095, 4096)
        self.uc.hook_add(UC_HOOK_CODE, self._muldiv, begin=address, end=address)
        self.uc.mem_map(0, 4096)
        self.write_u32(0, 0xffffffff)

    def _muldiv(self, *unused):
        args = tuple(C.c_int32(x).value for x in self._args(3))
        self.events.append(('MulDiv', *args))
        self._return(api_muldiv(*args) & 0xffffffff, pop=12)

    def fixture(self, points, pitch, mask):
        self.reset()
        self.points, self.mask = points, mask
        self.scratch, self.records, self.events, self.snapshots = [], {}, [], {}
        self.frame_base = self.allocate(pitch * 480 + 64)
        self.pixels = self.frame_base + 32
        self.point_base = self.allocate(len(points) * 8 + 64)
        self.points_address = self.point_base + 32
        self.point_bytes = b''.join(struct.pack('<ii', *p) for p in points)
        self.write(self.points_address, self.point_bytes)
        self.point_before = self.read(self.point_base, len(points) * 8 + 64)

    def _malloc(self, *unused):
        size = self._args(1)[0]
        role = len(self.scratch)
        expected = len(self.points) * (28 if role == 0 else 4)
        assert role < 3 and size == expected
        failed = bool(self.mask & (1 << role))
        self.events.append(('allocate', role, len(self.points), failed))
        pointer = None
        if not failed:
            base = self.allocate(size + 64)
            pointer = base + 32
            self.records[pointer] = dict(base=base, size=size, role=role)
        self.scratch.append(pointer)
        self._return(pointer or 0)

    def _free(self, *unused):
        pointer = self._args(1)[0]
        record = self.records[pointer]
        self.events.append(('free', record['role']))
        raw = self.read(record['base'], record['size'] + 64)
        assert raw[:32] == raw[-32:] == b'\xa5' * 32
        self.snapshots[record['role']] = normalized(
            raw[32:-32], record['role'], self.scratch[0] or 0, len(self.points), 4)
        self.write(pointer, b'\xd5' * record['size'])
        self._return()


class Point(C.Structure):
    _fields_ = [('x', C.c_int32), ('y', C.c_int32)]


Alloc = C.CFUNCTYPE(C.c_void_p, C.c_size_t)
Free = C.CFUNCTYPE(None, C.c_void_p)
MulDiv = C.CFUNCTYPE(C.c_int32, C.c_int32, C.c_int32, C.c_int32)


class Ops(C.Structure):
    _fields_ = [('allocate', Alloc), ('deallocate', Free), ('muldiv', MulDiv)]


class RasterNative:
    def __init__(self, library):
        self.lib = C.CDLL(str(library))
        self.errors = []
        self.ops = Ops.in_dll(self.lib, 'dxball_raster_ops')
        self.saved_ops = bytes(self.ops)
        self.default_muldiv = MulDiv(C.cast(self.ops.muldiv, C.c_void_p).value)
        self.alloc_callback = Alloc(self.allocate)
        self.free_callback = Free(self.free)
        self.muldiv_callback = MulDiv(self.muldiv)
        self.ops.allocate = self.alloc_callback
        self.ops.deallocate = self.free_callback
        self.ops.muldiv = self.muldiv_callback
        for name in ('dxball_fill_polygon', 'dxball_fill_polygon_clipped'):
            function = getattr(self.lib, name)
            function.argtypes = [C.c_void_p, C.c_int32, C.POINTER(Point), C.c_int32, C.c_uint8]
            function.restype = None
        self.lib.dxball_fill_triangle.argtypes = [C.c_void_p] + [C.c_int32] * 7 + [C.c_uint8]
        self.lib.dxball_fill_triangle.restype = None
        self.lib.dxball_fill_horizontal_span.argtypes = [C.c_void_p, C.c_int32, C.c_int32, C.c_uint8]
        self.lib.dxball_fill_horizontal_span.restype = None

    def restore(self):
        C.memmove(C.addressof(self.ops), self.saved_ops, len(self.saved_ops))

    def fixture(self, points, pitch, mask):
        self.mask, self.count = mask, len(points)
        self.scratch, self.records, self.events, self.snapshots = [], {}, [], {}
        self.errors = []
        self.frame = C.create_string_buffer(b'\xa5' * (pitch * 480 + 64), pitch * 480 + 64)
        self.pixels = C.addressof(self.frame) + 32
        self.point_storage = C.create_string_buffer(b'\xa5' * (self.count * 8 + 64), self.count * 8 + 64)
        self.points = (Point * self.count).from_buffer(self.point_storage, 32)
        for record, value in zip(self.points, points):
            record.x, record.y = value
        self.before = bytes(self.point_storage)

    def allocate(self, size):
        try:
            role = len(self.scratch)
            expected = self.count * (28 if role == 0 else C.sizeof(C.c_void_p))
            assert role < 3 and size == expected
            failed = bool(self.mask & (1 << role))
            self.events.append(('allocate', role, self.count, failed))
            pointer = None
            if not failed:
                buffer = C.create_string_buffer(b'\xa5' * (size + 64), size + 64)
                pointer = C.addressof(buffer) + 32
                self.records[pointer] = dict(buffer=buffer, size=size, role=role)
            self.scratch.append(pointer)
            return pointer
        except Exception as error:
            self.errors.append(repr(error))
            return None

    def muldiv(self, *args):
        try:
            self.events.append(('MulDiv', *args))
            value = api_muldiv(*args)
            # Exercise the maintained portable default independently of its
            # API trace bridge, on every sampled set of original arguments.
            assert self.default_muldiv(*args) == value
            return value
        except Exception as error:
            self.errors.append(repr(error))
            return -1

    def free(self, pointer):
        try:
            record = self.records[pointer]
            self.events.append(('free', record['role']))
            raw = bytes(record['buffer'])
            assert raw[:32] == raw[-32:] == b'\xa5' * 32
            self.snapshots[record['role']] = normalized(
                raw[32:-32], record['role'], self.scratch[0] or 0, self.count, C.sizeof(C.c_void_p))
            C.memset(pointer, 0xd5, record['size'])
        except Exception as error:
            self.errors.append(repr(error))
