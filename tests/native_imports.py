"""Bind external calls in one copied ELF image, without exporting libc symbols."""
import ctypes as C
import os
from pathlib import Path
import struct


class DlInfo(C.Structure):
    _fields_ = [('filename', C.c_char_p), ('base', C.c_void_p),
                ('symbol', C.c_char_p), ('address', C.c_void_p)]


def bind_imports(image, entry, callbacks):
    """Replace only this fixture's resolved PLT/GOT slots; retain page permissions."""
    path = image.path.resolve()
    data = path.read_bytes()
    if data[:6] != b'\x7fELF\x02\x01' or struct.unpack_from('<H', data, 18)[0] != 62:
        raise RuntimeError('Native import fixture requires little-endian x86-64 ELF')
    host = C.CDLL(None, use_errno=True)
    host.dladdr.argtypes = [C.c_void_p, C.POINTER(DlInfo)]
    host.dladdr.restype = C.c_int
    host.mprotect.argtypes = [C.c_void_p, C.c_size_t, C.c_int]
    host.mprotect.restype = C.c_int
    info = DlInfo()
    if (not host.dladdr(C.cast(entry, C.c_void_p), C.byref(info)) or
            Path(os.fsdecode(info.filename)).resolve() != path):
        raise RuntimeError('Native import entry belongs to a different image')
    sections_offset = struct.unpack_from('<Q', data, 40)[0]
    stride, count = struct.unpack_from('<HH', data, 58)
    sections = [struct.unpack_from('<IIQQQQIIQQ', data, sections_offset + i * stride)
                for i in range(count)]
    slots = {name: [] for name in callbacks}
    for section in sections:
        if section[1] != 4:  # SHT_RELA
            continue
        symbols = sections[section[6]]
        strings = sections[symbols[6]]
        for offset in range(section[4], section[4] + section[5], section[9]):
            address, relocation, addend = struct.unpack_from('<QQq', data, offset)
            if relocation & 0xffffffff not in (6, 7):  # GLOB_DAT / JUMP_SLOT
                continue
            symbol = symbols[4] + (relocation >> 32) * symbols[9]
            name_offset = strings[4] + struct.unpack_from('<I', data, symbol)[0]
            name = data[name_offset:data.index(b'\0', name_offset)].decode('ascii')
            if name in slots:
                if addend:
                    raise RuntimeError('Native function import has a nonzero addend')
                slots[name].append(info.base + address)
    if any(len(addresses) != 1 for addresses in slots.values()):
        raise RuntimeError('Native fixture must have one import slot per selected API')
    page_size = os.sysconf('SC_PAGE_SIZE')
    mappings = [line.split()[:2] for line in Path('/proc/self/maps').read_text().splitlines()]
    host_defaults = {name: C.cast(getattr(host, name), C.c_void_p).value for name in callbacks}
    for name, addresses in slots.items():
        address = addresses[0]
        mapping = next((permissions for bounds, permissions in mappings
                        if int(bounds.split('-')[0], 16) <= address < int(bounds.split('-')[1], 16)), None)
        if mapping is None or 'x' in mapping:
            raise RuntimeError('Native import slot is not mapped data')
        protection = sum(bit for permission, bit in [('r', 1), ('w', 2)] if permission in mapping)
        page = address & -page_size
        if host.mprotect(page, page_size, protection | 2):
            raise OSError(C.get_errno(), 'Cannot write native import page')
        try:
            C.c_void_p.from_address(address).value = callbacks[name]
        finally:
            if host.mprotect(page, page_size, protection):
                raise OSError(C.get_errno(), 'Cannot restore native import page permissions')
        if C.c_void_p.from_address(address).value != callbacks[name]:
            raise RuntimeError('Native import callback was not retained')
    if any(C.cast(getattr(host, name), C.c_void_p).value != address
           for name, address in host_defaults.items()):
        raise RuntimeError('Native fixture changed process-wide libc resolution')
    return slots
