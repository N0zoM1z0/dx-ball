"""DirectDraw/CRT boundaries for executing the unmodified resource owner.

These boundaries allocate storage and report API results. They do not implement
SBK parsing, PCX decoding, sprite selection, row reversal, or glyph placement.
"""
import ctypes as C
import struct

from unicorn import UC_HOOK_CODE
from target_oracle import TargetOracle, ACTIVE_SURFACE

BANKS = 0x425980
SPRITE_BANK = 0x421088
FONT_BANK = 0x42108C
LIVE_PALETTE = 0x4386F0
SAVED_PALETTE = 0x4382F0


class ResourceTarget(TargetOracle):
    HEAP = 0x700000
    FILE_BUFFER = 0x3000000
    DDRAW = 0x503000
    PALETTE = 0x503100
    instruction_limit = 60000000

    def __init__(self):
        super().__init__()
        self.uc.hook_del(self._hooks[0])  # Execute real 0x404180 this time.
        self.uc.mem_map(self.HEAP, 0x2000000)
        self.uc.mem_map(self.FILE_BUFFER, 0x1000000)
        self.write_u32(self.DDRAW, 0x503400)
        self.write_u32(self.PALETTE, 0x503500)
        self.write_u32(0x4228B0, self.DDRAW)
        self.write_u32(0x4228C0, self.PALETTE)
        callbacks = {0x417770: self._malloc, 0x417750: self._free,
                     0x418220: self._filbuf, 0x418310: self._seek}
        slots = [(6, self._create, 0x503400), (6, self._palette, 0x503500),
                 (2, self._release, self.VTABLE), (5, self._blt, self.VTABLE),
                 (22, self._desc, self.VTABLE), (25, self._lock, self.VTABLE),
                 (29, self._key, self.VTABLE), (32, self._unlock, self.VTABLE)]
        for i, (slot, callback, table) in enumerate(slots):
            entry = 0x50B000 + i * 16
            self.write_u32(table + slot * 4, entry)
            callbacks[entry] = callback
        for address, callback in callbacks.items():
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, callback,
                                               begin=address, end=address))
        self.reset()

    def reset(self):
        self.cursor = self.HEAP
        self.surfaces = {}
        self.allocations = {}
        self.freed = []
        self.fail_create = False
        self.desc_failures = self.lock_failures = 0
        self.padding = 3
        self.write(BANKS, bytes(3 * 1048))
        self.write_u32(SPRITE_BANK, 0)
        self.write_u32(FONT_BANK, 0)
        self.write(LIVE_PALETTE, bytes([0xA5]) * 1024)
        self.write(SAVED_PALETTE, bytes([0xA5]) * 1024)
        self.surfaces[self.SURFACE] = self._surface_storage(640, 480, "active")

    def allocate(self, size):
        address = self.cursor
        self.cursor += (size + 15) & ~15
        assert self.cursor < self.HEAP + 0x2000000
        self.write(address, bytes([0xA5]) * size)
        self.allocations[address] = size
        return address

    def _surface_storage(self, width, height, identity):
        pitch = width + self.padding
        return dict(width=width, height=height, pitch=pitch,
                    pixels=self.allocate(pitch * height), identity=identity)

    def surface(self, width, height):
        address = self.allocate(4)
        self.write_u32(address, self.VTABLE)
        self.surfaces[address] = self._surface_storage(width, height, len(self.surfaces))
        return address

    def seed(self, bank, slot, code=65, width=7, height=5, baseline=2, null=False):
        address = self.allocate(45)
        surface = 0 if null else self.surface(width, height)
        self.write(address, struct.pack("<I8i", surface, 0x1234, width, height,
                                       width + self.padding, 1, 2, width + 1, height + 2))
        self.write(address + 36, bytes([code]))
        self.write_u32(address + 40, baseline)
        self.write_u32(BANKS + bank * 1048 + slot * 4, address)
        return address

    def set_file(self, name, data):
        self.file_data = data
        self.write(self.PATH, name.encode() + b"\0")
        self.write(self.FILE_BUFFER, data)

    def _file_position(self):
        return self.read_u32(self.FILE_HANDLE) - self.FILE_BUFFER

    def _position(self, position):
        self.write_u32(self.FILE_HANDLE, self.FILE_BUFFER + position)
        self.write_u32(self.FILE_HANDLE + 4, len(self.file_data) - position)

    def _open(self, uc, address, size, userdata):
        super()._open(uc, address, size, userdata)
        self._position(0)

    def _read(self, uc, address, size, userdata):
        destination, width, count, handle = self._args(4)
        assert handle == self.FILE_HANDLE and width != 0
        position = self._file_position()
        data = self.file_data[position:position + width * count]
        self.write(destination, data)
        self._position(position + len(data))
        self.io_events.append(("read", width, count))
        self._return(len(data) // width)

    def _filbuf(self, uc, address, size, userdata):
        assert self._args(1) == (self.FILE_HANDLE,)
        # All supplied streams are pre-buffered; a refill occurs only at EOF.
        assert self._file_position() >= len(self.file_data)
        self._return(0xFFFFFFFF)

    def _seek(self, uc, address, size, userdata):
        handle, offset, origin = self._args(3)
        assert handle == self.FILE_HANDLE and origin == 2
        offset = C.c_int32(offset).value
        self._position(len(self.file_data) + offset)
        self.io_events.append(("seek", offset, origin))
        self._return()

    def _malloc(self, uc, address, size, userdata):
        self._return(self.allocate(self._args(1)[0]))

    def _free(self, uc, address, size, userdata):
        pointer = self._args(1)[0]
        assert pointer in self.allocations and pointer not in self.freed
        self.freed.append(pointer)
        self._return()

    def _create(self, uc, address, size, userdata):
        draw, desc, output, outer = self._args(4)
        assert draw == self.DDRAW and outer == 0
        width, height = self.read_u32(desc + 12), self.read_u32(desc + 8)
        self.events.append(("create", width, height, self.read_u32(desc + 4),
                            self.read_u32(desc + 104)))
        self.write_u32(output, 0 if self.fail_create else self.surface(width, height))
        self._return(1 if self.fail_create else 0, pop=16)

    def _fill_desc(self, surface, desc):
        model = self.surfaces[surface]
        for offset, field in [(8, "height"), (12, "width"), (16, "pitch"), (36, "pixels")]:
            self.write_u32(desc + offset, model[field])

    def _desc(self, uc, address, size, userdata):
        surface, desc = self._args(2)
        result = int(self.desc_failures > 0)
        self.desc_failures -= result
        self.events.append(("desc", self.surfaces[surface]["identity"],
                            self.read_u32(desc + 4), result))
        if not result:
            self._fill_desc(surface, desc)
        self._return(result, pop=8)

    def _lock(self, uc, address, size, userdata):
        surface, rect, desc, flags, event = self._args(5)
        assert rect == event == flags == 0
        result = int(self.lock_failures > 0)
        self.lock_failures -= result
        self.events.append(("lock", self.surfaces[surface]["identity"], result))
        if not result:
            self._fill_desc(surface, desc)
        self._return(result, pop=20)

    def _key(self, uc, address, size, userdata):
        surface, flags, key = self._args(3)
        self.events.append(("key", self.surfaces[surface]["identity"], flags,
                            struct.unpack("<2I", self.read(key, 8))))
        self._return(pop=12)

    def _unlock(self, uc, address, size, userdata):
        surface, pointer = self._args(2)
        assert pointer == 0
        self.events.append(("unlock", self.surfaces[surface]["identity"]))
        self._return(pop=8)

    def _release(self, uc, address, size, userdata):
        surface, = self._args(1)
        self.events.append(("release", self.surfaces[surface]["identity"]))
        self._return(pop=4)

    def _restore(self, uc, address, size, userdata):
        dest, x, y, source, rect, flags = self._args(6)
        self.events.append(("fast", self.surfaces[dest]["identity"], x, y,
                            self.surfaces[source]["identity"],
                            struct.unpack("<4i", self.read(rect, 16)), flags))
        self._return(pop=24)

    def _blt(self, uc, address, size, userdata):
        dest, rect, source, source_rect, flags, fx = self._args(6)
        assert fx == 0
        self.events.append(("blt", self.surfaces[dest]["identity"],
                            struct.unpack("<4i", self.read(rect, 16)),
                            self.surfaces[source]["identity"],
                            struct.unpack("<4i", self.read(source_rect, 16)), flags))
        self._return(pop=24)

    def _palette(self, uc, address, size, userdata):
        palette, flags, start, count, entries = self._args(5)
        assert palette == self.PALETTE
        self.events.append(("palette", flags, start, count, self.read(entries, count * 4)))
        self._return(pop=20)

    def bank_snapshot(self, bank):
        base = BANKS + bank * 1048
        records = []
        for slot in range(255):
            address = self.read_u32(base + slot * 4)
            if not address:
                records.append(None)
                continue
            surface = self.read_u32(address)
            fields = struct.unpack("<7i", self.read(address + 8, 28))
            pixels = None
            if surface:
                model = self.surfaces[surface]
                pixels = self.read(model["pixels"], model["pitch"] * model["height"])
            records.append((fields, self.read(address + 36, 1),
                            C.c_int32(self.read_u32(address + 40)).value, pixels))
        return (self.read_u32(base + 1020), self.read_u32(base + 1024),
                self._cstring(base + 1028), records)


class Rect(C.Structure):
    _fields_ = [(name, C.c_int32) for name in ("left", "top", "right", "bottom")]


class Desc(C.Structure):
    _fields_ = [("size", C.c_uint32), ("flags", C.c_uint32),
                ("height", C.c_uint32), ("width", C.c_uint32), ("pitch", C.c_int32),
                ("ancillary", C.c_uint32 * 4), ("pixels", C.c_void_p),
                ("keys", C.c_uint32 * 8), ("format", C.c_uint32 * 8), ("caps", C.c_uint32)]


class Surface(C.Structure):
    _fields_ = [("vtable", C.POINTER(C.c_void_p))]


class Sprite(C.Structure):
    _fields_ = [("surface", C.c_void_p), ("opaque", C.c_int32), ("width", C.c_int32),
                ("height", C.c_int32), ("pitch", C.c_int32), ("rect", Rect),
                ("code", C.c_char), ("baseline", C.c_int32)]


class Bank(C.Structure):
    _fields_ = [("sprites", C.POINTER(Sprite) * 255), ("count", C.c_int32),
                ("mode", C.c_int32), ("filename", C.c_char * 20)]


class ResourceNative:
    def __init__(self, library):
        self.lib = C.CDLL(str(library))
        self.libc = C.CDLL(None)
        self.libc.malloc.argtypes = [C.c_size_t]
        self.libc.malloc.restype = C.c_void_p
        self.libc.free.argtypes = [C.c_void_p]
        self.banks = (Bank * 3).in_dll(self.lib, "dxball_sprite_banks")
        self.bank = C.c_int32.in_dll(self.lib, "dxball_sprite_bank")
        self.font = C.c_int32.in_dll(self.lib, "dxball_font_bank")
        self.live = (C.c_ubyte * 1024).in_dll(self.lib, "dxball_live_palette")
        self.saved = (C.c_ubyte * 1024).in_dll(self.lib, "dxball_saved_palette")
        self.callbacks = []
        self.table = (C.c_void_p * 33)()
        self.draw_table = (C.c_void_p * 7)()
        self.palette_table = (C.c_void_p * 7)()
        pointer, integer = C.c_void_p, C.c_uint32
        signatures = [(self.table, 2, self._release, [pointer]),
                      (self.table, 5, self._blt, [pointer] * 4 + [integer, pointer]),
                      (self.table, 7, self._fast, [pointer, integer, integer, pointer, pointer, integer]),
                      (self.table, 22, self._desc, [pointer, pointer]),
                      (self.table, 25, self._lock, [pointer, pointer, pointer, integer, pointer]),
                      (self.table, 29, self._key, [pointer, integer, pointer]),
                      (self.table, 32, self._unlock, [pointer, pointer]),
                      (self.draw_table, 6, self._create, [pointer] * 4),
                      (self.palette_table, 6, self._palette, [pointer, integer, integer, integer, pointer])]
        for table, slot, callback, arguments in signatures:
            wrapped = C.CFUNCTYPE(C.c_int32, *arguments)(callback)
            self.callbacks.append(wrapped)
            table[slot] = C.cast(wrapped, C.c_void_p).value
        self.draw = Surface(self.draw_table)
        self.palette = Surface(self.palette_table)
        C.c_void_p.in_dll(self.lib, "dxball_direct_draw").value = C.addressof(self.draw)
        C.c_void_p.in_dll(self.lib, "dxball_direct_palette").value = C.addressof(self.palette)
        self.lib.dxball_find_glyph.argtypes = [C.c_char]
        self.lib.dxball_draw_glyph.argtypes = [C.c_char, C.c_int32, C.c_int32]
        self.lib.dxball_load_sprite_bank.argtypes = [C.c_int32, C.c_int32, C.c_char_p]
        self.lib.dxball_load_pcx.argtypes = [C.c_void_p, C.c_char_p, C.c_int32, C.c_int32, C.c_int32]
        self.lib.dxball_load_live_palette.argtypes = [C.c_char_p]
        self.lib.dxball_load_saved_palette.argtypes = [C.c_char_p]
        self.surfaces = {}
        self.reset()

    def reset(self):
        for bank in self.banks:
            for record in bank.sprites:
                if record:
                    self.libc.free(record)
        C.memset(C.addressof(self.banks), 0, C.sizeof(self.banks))
        self.surfaces.clear()
        self.events = []
        self.padding = 3
        self.desc_failures = self.lock_failures = 0
        self.fail_create = False
        self.bank.value = self.font.value = 0
        C.memset(C.addressof(self.live), 0xA5, 1024)
        C.memset(C.addressof(self.saved), 0xA5, 1024)
        self.active = self.surface(640, 480, "active")
        C.c_size_t.in_dll(self.lib, "dxball_active_surface").value = self.active

    def surface(self, width, height, identity=None):
        pitch = width + self.padding
        pixels = (C.c_ubyte * (pitch * height))(*([0xA5] * (pitch * height)))
        surface = Surface(self.table)
        address = C.addressof(surface)
        self.surfaces[address] = dict(width=width, height=height, pitch=pitch,
                                     pixels=pixels, object=surface,
                                     identity=len(self.surfaces) if identity is None else identity)
        return address

    def seed(self, bank, slot, code=65, width=7, height=5, baseline=2, null=False):
        address = self.libc.malloc(C.sizeof(Sprite) + 1)
        C.memset(address, 0xA5, C.sizeof(Sprite) + 1)
        record = C.cast(address, C.POINTER(Sprite))
        record.contents.surface = None if null else self.surface(width, height)
        record.contents.opaque = 0x1234
        record.contents.width, record.contents.height = width, height
        record.contents.pitch = width + self.padding
        record.contents.rect = Rect(1, 2, width + 1, height + 2)
        record.contents.code, record.contents.baseline = bytes([code]), baseline
        self.banks[bank].sprites[slot] = record

    def _identity(self, address):
        return self.surfaces[address]["identity"]

    @staticmethod
    def _rect(address):
        return struct.unpack("<4i", C.string_at(address, 16))

    def _create(self, draw, description, output, outer):
        desc = C.cast(description, C.POINTER(Desc)).contents
        self.events.append(("create", desc.width, desc.height, desc.flags, desc.caps))
        C.cast(output, C.POINTER(C.c_void_p))[0] = None if self.fail_create else self.surface(desc.width, desc.height)
        return int(self.fail_create)

    def _fill_desc(self, surface, description):
        model = self.surfaces[surface]
        desc = C.cast(description, C.POINTER(Desc)).contents
        desc.height, desc.width, desc.pitch = model["height"], model["width"], model["pitch"]
        desc.pixels = C.addressof(model["pixels"])

    def _desc(self, surface, description):
        result = int(self.desc_failures > 0)
        self.desc_failures -= result
        desc = C.cast(description, C.POINTER(Desc)).contents
        self.events.append(("desc", self._identity(surface), desc.flags, result))
        if not result:
            self._fill_desc(surface, description)
        return result

    def _lock(self, surface, rect, description, flags, event):
        result = int(self.lock_failures > 0)
        self.lock_failures -= result
        self.events.append(("lock", self._identity(surface), result))
        if not result:
            self._fill_desc(surface, description)
        return result

    def _key(self, surface, flags, key):
        self.events.append(("key", self._identity(surface), flags, struct.unpack("<2I", C.string_at(key, 8))))
        return 0

    def _release(self, surface):
        self.events.append(("release", self._identity(surface)))
        return 0

    def _unlock(self, surface, pointer):
        self.events.append(("unlock", self._identity(surface)))
        return 0

    def _fast(self, dest, x, y, source, rect, flags):
        self.events.append(("fast", self._identity(dest), x, y, self._identity(source), self._rect(rect), flags))
        return 0

    def _blt(self, dest, rect, source, source_rect, flags, fx):
        self.events.append(("blt", self._identity(dest), self._rect(rect), self._identity(source), self._rect(source_rect), flags))
        return 0

    def _palette(self, palette, flags, start, count, entries):
        self.events.append(("palette", flags, start, count, C.string_at(entries, count * 4)))
        return 0

    def bank_snapshot(self, bank):
        records = []
        for record in self.banks[bank].sprites:
            if not record:
                records.append(None)
                continue
            sprite = record.contents
            rect = sprite.rect
            fields = (sprite.width, sprite.height, sprite.pitch, rect.left, rect.top, rect.right, rect.bottom)
            pixels = bytes(self.surfaces[sprite.surface]["pixels"]) if sprite.surface else None
            records.append((fields, sprite.code, sprite.baseline, pixels))
        owner = self.banks[bank]
        return owner.count, owner.mode, owner.filename, records
