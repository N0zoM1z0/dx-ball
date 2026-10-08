"""Investigate the original bitmap loader; no maintained-C acceptance is implied.

Only file/allocator/DirectDraw dependency boundaries are controlled. Original
header handling, row traversal, memory/string helpers and palette conversion
execute without instruction replacement. Stack bytes are explicit fixtures,
not an assumed palette-flags value for the reconstructed implementation.
"""
import hashlib
import json
from pathlib import Path
import struct
import sys

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_EDI,
    UC_X86_REG_EFLAGS, UC_X86_REG_EIP, UC_X86_REG_ESI, UC_X86_REG_ESP,
)

from resources_oracle import ResourceTarget

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from resource_limits import limit_cpu


class BitmapProbe(ResourceTarget):
    def __init__(self):
        super().__init__()
        callbacks = [
            (0x44127C, self.open_file), (0x441298, self.read_file),
            (0x441280, self.local_alloc), (0x44126C, self.local_free),
            (0x441264, self.close_file),
            (0x503400 + 5 * 4, self.create_palette),
            (self.VTABLE + 31 * 4, self.set_palette),
            (self.VTABLE + 25 * 4, self.lock_surface),
            (self.VTABLE + 32 * 4, self.unlock_surface),
        ]
        for index, (slot, callback) in enumerate(callbacks):
            address = 0x50C000 + index * 16
            self.write_u32(slot, address)
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, callback,
                                               begin=address, end=address))

    def fixture(self, width=3, height=2, pitch=5, fail='', fallback=False,
                path=b'fixture.bmp', prefix=b'controlled/', bits=8):
        self.reset()
        self.fail = fail
        self.fallback = fallback
        self.opens = self.reads = self.position = 0
        self.palette_bytes = None
        self.pixel_allocation = None
        self.write(self.PATH, path + b'\0')
        # This unresolved data dependency is a fixture, not a recovered prefix.
        self.write(0x422798, prefix + b'\0')
        header = bytearray(40)
        struct.pack_into('<IiiHH', header, 0, 40, width, height, 1, bits)
        self.input_palette = bytes((i * 17 + 9) & 255 for i in range(1024))
        self.input_pixels = bytes(range(1, width * height + 1))
        # An intentionally non-BM header distinguishes observed validation.
        self.data = b'\xC7' * 14 + header + self.input_palette + self.input_pixels
        self.surfaces[self.SURFACE] = dict(width=pitch, height=height, pitch=pitch,
            pixels=self.allocate(32 + pitch * height + 32) + 32, identity='bmp')
        self.model = self.surfaces[self.SURFACE]
        self.guard = self.model['pixels'] - 32
        self.total = pitch * height + 64

    def open_file(self, uc, address, size, userdata):
        path, access, share, security, disposition, attributes, template = self._args(7)
        assert (access, share, security, disposition, attributes, template) == (
            0x80000000, 1, 0, 3, 0x80, 0)
        self.opens += 1
        failed = self.fail == 'open' or (self.fallback and self.opens == 1)
        self.events.append(('open', self._cstring(path).decode('ascii'), int(failed)))
        self._return(0xFFFFFFFF if failed else self.FILE_HANDLE, pop=28)

    def read_file(self, uc, address, size, userdata):
        handle, output, count, transferred, overlapped = self._args(5)
        assert handle == self.FILE_HANDLE and overlapped == 0
        self.reads += 1
        failed = self.fail == 'read' + str(self.reads)
        self.events.append(('read', count, int(failed)))
        if not failed:
            data = self.data[self.position:self.position + count]
            assert len(data) == count
            self.write(output, data)
            self.write_u32(transferred, count)
            self.position += count
        self._return(int(not failed), pop=20)

    def local_alloc(self, uc, address, size, userdata):
        flags, count = self._args(2)
        assert flags == 0x40 and count == len(self.input_pixels)
        self.events.append(('allocate', flags, count))
        self.pixel_allocation = None if self.fail == 'allocate' else self.allocate(count)
        if self.pixel_allocation is not None:
            self.write(self.pixel_allocation, bytes(count))
        self._return(self.pixel_allocation or 0, pop=8)

    def local_free(self, uc, address, size, userdata):
        assert self._args(1) == (self.pixel_allocation,)
        self.events.append(('free',))
        self._return(pop=4)

    def close_file(self, uc, address, size, userdata):
        assert self._args(1) == (self.FILE_HANDLE,)
        self.events.append(('close',))
        self._return(0, pop=4)  # Its failure is ignored on this path.

    def lock_surface(self, uc, address, size, userdata):
        surface, rectangle, desc, flags, event = self._args(5)
        assert (surface, rectangle, flags, event) == (self.SURFACE, 0, 0, 0)
        assert self.read(desc, 108) == struct.pack('<I', 108) + bytes(104)
        failed = self.fail == 'lock'
        self.events.append(('lock', int(failed)))
        if not failed:
            self._fill_desc(surface, desc)
        self._return(int(failed), pop=20)

    def unlock_surface(self, uc, address, size, userdata):
        assert self._args(2) == (self.SURFACE, 0)
        self.events.append(('unlock',))
        self._return(1, pop=8)  # This result is also ignored.

    def create_palette(self, uc, address, size, userdata):
        draw, caps, entries, output, outer = self._args(5)
        assert (draw, caps, outer) == (self.DDRAW, 4, 0)
        self.palette_bytes = self.read(entries, 1024)
        self.events.append(('create_palette',))
        failed = self.fail == 'palette'
        if not failed:
            self.write_u32(output, self.PALETTE)
        self._return(int(failed), pop=20)

    def set_palette(self, uc, address, size, userdata):
        assert self._args(2) == (self.SURFACE, self.PALETTE)
        self.events.append(('set_palette',))
        self._return(1, pop=8)  # A nonzero HRESULT does not change return 1.

    def invoke(self, stack_seed):
        self.events = []
        self.write(self.STACK, bytes([stack_seed]) * self.STACK_SIZE)
        sp = self.STACK + self.STACK_SIZE - 0x100
        self.write(sp, struct.pack('<3I', self.RETURN, self.SURFACE, self.PATH))
        saved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_ESI: 0x23456789,
                 UC_X86_REG_EDI: 0x34567890, UC_X86_REG_EBP: 0x456789AB}
        for register, value in saved.items():
            self.uc.reg_write(register, value)
        self.uc.reg_write(UC_X86_REG_ESP, sp)
        self.uc.reg_write(UC_X86_REG_EFLAGS, 0x202)
        self.uc.emu_start(0x409F70, self.RETURN, count=1000000)
        assert self.uc.reg_read(UC_X86_REG_EIP) == self.RETURN
        assert self.uc.reg_read(UC_X86_REG_ESP) == sp + 4
        assert all(self.uc.reg_read(r) == v for r, v in saved.items())
        # Dependencies may write descriptors/output pointers, but target code
        # itself remains the original mapped executable.
        return self.uc.reg_read(UC_X86_REG_EAX)


def run():
    limit_cpu()
    target = BitmapProbe()
    rows = []
    for seed in (0, 0x5A, 0xA5, 0xFF):
        for pitch, expected in ((2, b'\x04\x05\x02\x03'),
                                (3, b'\x04\x05\x06\x01\x02\x03'),
                                (5, b'\x04\x05\x06\xA5\xA5\x01\x02\x03\xA5\xA5')):
            target.fixture(pitch=pitch)
            assert target.invoke(seed) == 1
            assert [event[0] for event in target.events] == [
                'open', 'read', 'read', 'read', 'allocate', 'read', 'lock',
                'unlock', 'free', 'close', 'create_palette', 'set_palette']
            assert target.read(target.guard, target.total) == b'\xA5' * 32 + expected + b'\xA5' * 32
            assert target.read(target.pixel_allocation, 6) == target.input_pixels
            palette = target.palette_bytes
            assert all(palette[i:i + 3] == target.input_palette[i:i + 3][::-1]
                       for i in range(0, 1024, 4))
            assert palette[3::4] == bytes([seed]) * 256
            rows.append(dict(stack_seed=seed, pitch=pitch, status='observed',
                             pixels=expected.hex(), events=target.events,
                             palette_flags_sha256=hashlib.sha256(palette[3::4]).hexdigest()))
    for failure, names in (
        ('open', ['open', 'open']),
        ('read1', ['open', 'read']),
        ('read2', ['open', 'read', 'read']),
        ('bits', ['open', 'read', 'read']),
        ('read3', ['open', 'read', 'read', 'read']),
        ('allocate', ['open', 'read', 'read', 'read', 'allocate']),
        ('read4', ['open', 'read', 'read', 'read', 'allocate', 'read', 'free']),
        ('lock', ['open', 'read', 'read', 'read', 'allocate', 'read', 'lock', 'free']),
        ('palette', ['open', 'read', 'read', 'read', 'allocate', 'read', 'lock',
                     'unlock', 'free', 'close', 'create_palette']),
    ):
        target.fixture(fail=failure, bits=24 if failure == 'bits' else 8)
        assert target.invoke(0x5A) == 0
        assert [event[0] for event in target.events] == names
        if failure != 'palette':
            assert target.read(target.guard, target.total) == b'\xA5' * target.total
        else:
            copied = b'\x04\x05\x06\xA5\xA5\x01\x02\x03\xA5\xA5'
            assert target.read(target.guard, target.total) == b'\xA5' * 32 + copied + b'\xA5' * 32
        rows.append(dict(failure=failure, events=target.events, status='observed'))
    for path in (b'fixture.bmp', b'P' * 160):
        target.fixture(fallback=True, path=path)
        assert target.invoke(0x5A) == 1
        assert target.events[:2] == [('open', path.decode(), 1),
                                    ('open', 'controlled/' + path.decode(), 0)]
        # The buffers begin 0x140 (320 decimal) bytes apart. These bounded
        # paths remain below that boundary; they leave palette flags alone.
        expected_flags = bytes([0x5A]) * 256
        assert target.palette_bytes[3::4] == expected_flags
        rows.append(dict(fallback_path_bytes=len(path), status='observed',
                         events=target.events,
                         palette_flags_sha256=hashlib.sha256(expected_flags).hexdigest()))
    inputs = ('tests/probe_bmp_loader.py', 'tests/resources_oracle.py',
              'tests/target_oracle.py', 'scripts/verify-target.py',
              'scripts/resource_limits.py', 'config/target.toml',
              'scripts/repo-python', 'scripts/verify-python.py', 'config/tools.lock.toml')
    dossier = '.analysis/rea/runs/2026-10-07T10-33-32.118Z-interactive-2912559/07-analyze_function.json'
    report = dict(scope='Original x86 investigation only; no C differential acceptance',
        target_sha256=target.target_sha256,
        rea_evidence_id='ev_e408e41080570698d5068c6aa811cbae0a93e65442822fc191ea85ea46c93cad',
        retained_dossier=dict(path=dossier, sha256=hashlib.sha256((ROOT / dossier).read_bytes()).hexdigest()),
        inputs={name: hashlib.sha256((ROOT / name).read_bytes()).hexdigest() for name in inputs},
        limitations=['Controlled file/allocator/COM dependencies; no physical DirectDraw execution',
                     'Fallback prefix is an unresolved controlled data dependency',
                     'Palette flags depend on caller stack storage; no deterministic C claim',
                     'Full reads, positive small dimensions/pitches and bounded paths only'],
        fixtures=rows)
    directory = ROOT / 'build/reports/bmp-investigation'
    directory.mkdir(parents=True, exist_ok=True)
    (directory / 'original.json').write_text(json.dumps(report, indent=2) + '\n')
    print('Original bitmap investigation:', len(rows), 'fixtures; no semantic promotion')


if __name__ == '__main__':
    run()
