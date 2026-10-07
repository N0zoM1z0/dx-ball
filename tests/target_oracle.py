"""Execute unmodified target x86 functions with controlled dependency boundaries."""
import importlib.util
from pathlib import Path
import struct
import sys

import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE
from unicorn.x86_const import (
    UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI,
    UC_X86_REG_EDI, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EFLAGS,
)

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location("verify_target", ROOT / "scripts/verify-target.py")
verify_target = importlib.util.module_from_spec(spec)
spec.loader.exec_module(verify_target)

# Reviewed target globals; the maintained equivalents are separate host storage.
BANK = 0x0043AAB8
TILES = 0x0043F8F8
AUX = 0x0043A918
INDEX = 0x0043A8F8
MODE = 0x00421074
FILE_SLOT = 0x004265C8
ACTIVE_SURFACE = 0x004265CC
BOARD_SURFACE = 0x004228BC
BACKGROUND_SURFACE = 0x00421070


class TargetOracle:
    SURFACE = 0x00500000
    VTABLE = 0x00501000
    RESTORE = 0x00502000
    PATH = 0x00504000
    RETURN = 0x0050F000
    STACK = 0x00600000
    STACK_SIZE = 0x20000
    FILE_HANDLE = 0x00504320
    BACKGROUND = 0x00112233

    def __init__(self):
        path, manifest, data = verify_target.verify()
        self.target_sha256 = manifest["target"]["sha256"]
        self.pe = pefile.PE(data=data)
        self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.uc.mem_map(self.base, self.pe.OPTIONAL_HEADER.SizeOfImage)
        self.uc.mem_write(self.base, self.pe.get_memory_mapped_image())
        self.uc.mem_map(self.SURFACE, 0x10000)
        self.uc.mem_map(self.STACK, self.STACK_SIZE)
        self.write_u32(self.SURFACE, self.VTABLE)
        self.write_u32(self.VTABLE + 0x1C, self.RESTORE)
        self.write_u32(ACTIVE_SURFACE, self.SURFACE)
        self.write_u32(BOARD_SURFACE, self.SURFACE)
        self.write_u32(BACKGROUND_SURFACE, self.BACKGROUND)
        self.uc.mem_write(self.PATH, b"oracle.bds\0")
        self.events = []
        self.file_data = None
        self.written = None
        self.open_succeeds = True
        self.io_events = []
        self._hooks = []
        self.board_hooks = {}
        for address, callback in {
            0x00404180: self._sprite,
            0x00408B70: self._invalidate,
            self.RESTORE: self._restore,
            0x00417C20: self._open,
            0x00417AA0: self._read,
            0x00417E70: self._write,
            0x00417A30: self._close,
        }.items():
            hook = self.uc.hook_add(UC_HOOK_CODE, callback, begin=address, end=address)
            self._hooks.append(hook)
            if address in (0x404180, 0x408B70):
                self.board_hooks[address] = hook

    def read(self, address, size):
        return bytes(self.uc.mem_read(address, size))

    def write(self, address, data):
        self.uc.mem_write(address, bytes(data))

    def read_u32(self, address):
        return struct.unpack("<I", self.read(address, 4))[0]

    def write_u32(self, address, value):
        self.write(address, struct.pack("<I", value & 0xFFFFFFFF))

    def _args(self, count):
        sp = self.uc.reg_read(UC_X86_REG_ESP)
        return struct.unpack("<" + "I" * count, self.read(sp + 4, count * 4))

    def _return(self, value=0, pop=0):
        sp = self.uc.reg_read(UC_X86_REG_ESP)
        address = self.read_u32(sp)
        self.uc.reg_write(UC_X86_REG_EAX, value)
        self.uc.reg_write(UC_X86_REG_ESP, sp + 4 + pop)
        self.uc.reg_write(UC_X86_REG_EIP, address)

    def _cstring(self, address):
        result = bytearray()
        for i in range(4096):
            byte = self.read(address + i, 1)
            if byte == b"\0":
                return bytes(result)
            result.extend(byte)
        raise AssertionError("unterminated oracle string")

    def _sprite(self, uc, address, size, userdata):
        self.events.append(("sprite", *self._args(3)))
        self._return()

    def _invalidate(self, uc, address, size, userdata):
        self.events.append(("invalidate", *self._args(4)))
        self._return()

    def _restore(self, uc, address, size, userdata):
        destination, x, y, source, rect, flags = self._args(6)
        coordinates = struct.unpack("<4i", self.read(rect, 16))
        self.events.append(("restore", destination, x, y, source, coordinates, flags))
        self._return(pop=24)  # DirectDraw COM method uses stdcall.

    def _open(self, uc, address, size, userdata):
        path, mode = self._args(2)
        self.io_events.append(("open", self._cstring(path), self._cstring(mode)))
        self._return(self.FILE_HANDLE if self.open_succeeds else 0)

    def _read(self, uc, address, size, userdata):
        destination, element_size, count, handle = self._args(4)
        assert (destination, element_size, count, handle) == (BANK, 1, 20000, self.FILE_HANDLE)
        self.io_events.append(("read", element_size, count))
        data = (self.file_data or b"")[:element_size * count]
        if data:
            self.write(destination, data)
        self._return(len(data) // element_size)

    def _write(self, uc, address, size, userdata):
        source, element_size, count, handle = self._args(4)
        assert (source, element_size, count, handle) == (BANK, 1, 20000, self.FILE_HANDLE)
        self.io_events.append(("write", element_size, count))
        self.written = self.read(source, element_size * count)
        self._return(count)

    def _close(self, uc, address, size, userdata):
        assert self._args(1) == (self.FILE_HANDLE,)
        self.io_events.append(("close",))
        self._return()

    def call(self, entry, *args):
        self.events = []
        self.io_events = []
        self.written = None
        # Deterministic stack contents also expose uninitialized-return domains.
        self.write(self.STACK, b"\xa5" * self.STACK_SIZE)
        sp = self.STACK + self.STACK_SIZE - 0x100
        self.write(sp, struct.pack("<" + "I" * (1 + len(args)), self.RETURN,
                                   *(value & 0xFFFFFFFF for value in args)))
        saved = {UC_X86_REG_EBX: 0x12345678, UC_X86_REG_ESI: 0x23456789,
                 UC_X86_REG_EDI: 0x34567890, UC_X86_REG_EBP: 0x456789AB}
        for register, value in saved.items():
            self.uc.reg_write(register, value)
        self.uc.reg_write(UC_X86_REG_ESP, sp)
        self.uc.reg_write(UC_X86_REG_EFLAGS, 0x202)
        self.uc.emu_start(entry, self.RETURN, count=getattr(self, "instruction_limit", 1000000))
        assert self.uc.reg_read(UC_X86_REG_EIP) == self.RETURN, "instruction limit reached"
        assert self.uc.reg_read(UC_X86_REG_ESP) == sp + 4 + getattr(self, "callee_cleanup", 0), "stack imbalance"
        for register, value in saved.items():
            assert self.uc.reg_read(register) == value, "callee-saved register changed"
        return self.uc.reg_read(UC_X86_REG_EAX)
