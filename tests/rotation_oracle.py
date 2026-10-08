"""Original-machine rotation fixtures; no maintained implementation is assumed."""
import ctypes as C
import itertools
import random

from resources_oracle import ResourceTarget, ResourceNative, Desc
from target_oracle import ACTIVE_SURFACE
from unicorn.x86_const import UC_X86_REG_FPCW, UC_X86_REG_FPTAG, UC_X86_REG_FPSW


class RotationTarget(ResourceTarget):
    instruction_limit = 2000000

    def reset(self):
        super().reset()
        self.lock_scripts = {'active': [], 'source': []}
        self.after_desc, self.after_lock, self.after_unlock = {}, {}, {}
        self.surfaces[self.SURFACE] = dict(width=32, height=24, pitch=35,
            pixels=self.allocate(35 * 24 + 64) + 32, identity='active')
        self.write_u32(ACTIVE_SURFACE, self.SURFACE)

    def _desc(self, *unused):
        surface, desc = self._args(2)
        assert self.read_u32(desc) == 108
        assert self.read_u32(desc + 4) == 14
        self.events.append(('desc', self.surfaces[surface]['identity'], 108, 14))
        self._fill_desc(surface, desc)
        callback = self.after_desc.get(self.surfaces[surface]['identity'])
        if callback:
            callback(self)
        self._return(0, pop=8)

    def _lock(self, *unused):
        surface, rect, desc, flags, event = self._args(5)
        assert rect == flags == event == 0
        identity = self.surfaces[surface]['identity']
        script = self.lock_scripts[identity]
        result = script.pop(0) if script else 0
        self.events.append(('lock', identity, result))
        if result == 0:
            self._fill_desc(surface, desc)
        callback = self.after_lock.get(identity)
        if callback:
            callback(self)
        self._return(result & 0xFFFFFFFF, pop=20)

    def _unlock(self, *unused):
        surface, pointer = self._args(2)
        assert pointer == 0
        identity = self.surfaces[surface]['identity']
        self.events.append(('unlock', identity))
        callback = self.after_unlock.get(identity)
        if callback:
            callback(self)
        self._return(pop=8)

    def call(self, entry, *arguments):
        self.uc.reg_write(UC_X86_REG_FPCW, 0x37F)
        self.uc.reg_write(UC_X86_REG_FPTAG, 0xFFFF)
        self.uc.reg_write(UC_X86_REG_FPSW, 0)
        return super().call(entry, *arguments)


def fixtures():
    base = dict(bank=0, slot=1, width=7, height=5, center=(16, 12), angle=0,
                padding=3, pattern='sparse', destination_retries=0, source_retries=0)
    for angle in range(-720, 721, 15):
        yield dict(base, angle=angle)
    for bank, slot, angle in itertools.product(range(3), (1, 127, 254), (-361, 0, 45, 270)):
        yield dict(base, bank=bank, slot=slot, angle=angle)
    for center, angle in itertools.product(((0, 0), (1, 1), (31, 23), (32, 24),
                                           (0xFFFFFFFF, 12), (16, 0xFFFFFFFF),
                                           (0x80000000, 0x80000000)),
                                          (-360, -1, 0, 1, 89, 90, 179, 180, 359, 360)):
        yield dict(base, center=center, angle=angle)
    for dimensions, pattern, padding in itertools.product(((0, 0), (0, 3), (1, 0),
                                                          (1, 1), (2, 3), (11, 8)),
                                                         ('zero', 'sparse', 'solid'), (0, 5)):
        yield dict(base, width=dimensions[0], height=dimensions[1], pattern=pattern,
                   padding=padding, angle=45)
    for destination, source in itertools.product((0, 1, 3), repeat=2):
        yield dict(base, destination_retries=destination, source_retries=source, angle=137)
    rng = random.Random(0x4026A0)
    for _ in range(96):
        yield dict(base, width=rng.randint(1, 16), height=rng.randint(1, 12),
                   center=(rng.randrange(36), rng.randrange(28)),
                   angle=rng.randint(-1080, 1080), padding=rng.randint(0, 7),
                   bank=rng.randrange(3), slot=rng.choice((1, 127, 254)))


def source_pixels(width, height, pitch, pattern):
    data = bytearray([0xE7] * (pitch * height))
    for y in range(height):
        for x in range(width):
            data[y * pitch + x] = (0 if pattern == 'zero' or
                                  (pattern == 'sparse' and (x + 2*y) % 3 == 0)
                                  else 1 + (x * 23 + y * 41) % 254)
    return bytes(data)


def width_offset_fixtures():
    cases = [(0, 1, width, angle)
             for width in (-127, -13, -1, 0, 1, 2, 3, 7, 13, 26, 31, 64, 127, 640)
             for angle in (-720, -405, -360, -135, -90, -45, -1, 0, 1, 45, 90, 135, 359, 360)]
    cases += [(0, 1, 13, angle) for angle in range(-720, 721, 15)]
    cases += [(bank, slot, 26, angle) for bank in range(3) for slot in (1, 127, 254)
              for angle in (-405, -45, 0, 135)]
    return cases


def callback_fixtures():
    return (
        ('destination changes after descriptor', 0, 'replacement-active', 'replacement-active', 0),
        ('bank changes after destination descriptor', 1, 'active', 'active', 1),
        ('bank changes between source descriptor and lock', 2, 'active', 'active', 2),
        ('bank changes during destination unlock', 0, 'active', 'active', 2),
        ('destination changes again during source lock', 0, 'replacement-active', 'active', 0),
    )


class RotationNative(ResourceNative):
    """Native DirectDraw fixture with the same controlled calls as the target."""
    def __init__(self, library):
        super().__init__(library)
        self.lib.dxball_render_rotated_sprite.argtypes = [C.c_uint32, C.c_uint32, C.c_int32, C.c_int32]
        self.lib.dxball_render_rotated_sprite.restype = None
        self.lib.dxball_draw_rotated_sprite.argtypes = [C.c_int32, C.c_uint32, C.c_uint32, C.c_int32]
        self.lib.dxball_draw_rotated_sprite.restype = None
        self.lib.dxball_rotated_sprite_offset.argtypes = [C.c_int32, C.c_int32]
        self.lib.dxball_rotated_sprite_offset.restype = C.c_int32
        self.active_binding = C.c_size_t.in_dll(self.lib, 'dxball_active_surface')

    def reset(self):
        super().reset()
        self.lock_scripts = {'active': [], 'source': []}
        self.after_desc, self.after_lock, self.after_unlock = {}, {}, {}
        self.guard_surface(self.active)

    def guard_surface(self, surface):
        model = self.surfaces[surface]
        model.update(width=32, height=24, pitch=35)
        storage = (C.c_ubyte * (35 * 24 + 64))(*([0xA5] * (35 * 24 + 64)))
        model['guarded_storage'] = storage
        model['pixels'] = (C.c_ubyte * (35 * 24)).from_buffer(storage, 32)

    def _desc(self, surface, pointer):
        desc = C.cast(pointer, C.POINTER(Desc)).contents
        assert (desc.size, desc.flags) == (108, 14)
        identity = self._identity(surface)
        self.events.append(('desc', identity, 108, 14))
        self._fill_desc(surface, pointer)
        callback = self.after_desc.get(identity)
        if callback:
            callback(self)
        return 0

    def _lock(self, surface, rect, pointer, flags, event):
        assert not rect and flags == 0 and not event
        identity = self._identity(surface)
        script = self.lock_scripts[identity]
        result = script.pop(0) if script else 0
        self.events.append(('lock', identity, result))
        if result == 0:
            self._fill_desc(surface, pointer)
        callback = self.after_lock.get(identity)
        if callback:
            callback(self)
        return result

    def _unlock(self, surface, pointer):
        assert not pointer
        identity = self._identity(surface)
        self.events.append(('unlock', identity))
        callback = self.after_unlock.get(identity)
        if callback:
            callback(self)
        return 0
