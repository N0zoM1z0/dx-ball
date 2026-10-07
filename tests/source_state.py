"""Resolve source-owned fields through its compiler-emitted layout metadata."""
import ctypes as C

STORAGE_FIELDS = {'dxball_board_bank': 0, 'dxball_palette_tick': 1,
                  'dxball_explosions': 2, 'dxball_ball_count': 3,
                  'dxball_board_tiles': 4}


def source_global(kind, library, name):
    if name not in STORAGE_FIELDS:
        return kind.in_dll(library, name)
    offsets = (C.c_uint32 * 6).in_dll(library, 'dxball_board_storage_offsets')
    base = C.addressof(C.c_byte.in_dll(library, 'dxball_board_storage'))
    offset = offsets[STORAGE_FIELDS[name]]
    assert offsets[0] == 0 and offset + C.sizeof(kind) <= offsets[5]
    return kind.from_address(base + offset)
