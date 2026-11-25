#!/usr/bin/env python3
"""Verify selected VC4 COFF bindings and state changes after an internal relink."""
from collections import defaultdict
import json
import os
from pathlib import Path
import random
import re
import struct
import tempfile

import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import UC_X86_REG_EFLAGS, UC_X86_REG_EIP, UC_X86_REG_ESP

from coff import _relocations, function, parse, region
from crt_library import relocate
from legacy_toolchain import ROOT, Toolchain, session_lock, sha256, windows_path


BUILD = ROOT / 'build/vc40-restored-crt'
BOARD_SIZE = 400
BOARD_OFFSETS = {
    '_dxball_board_storage': 0,
    '_dxball_palette_tick': 20000,
    '_dxball_unclassified_clock_tail': 20004,
    '_dxball_explosions': 20008,
    '_dxball_ball_count': 20024,
    '_dxball_unclassified_count_tail': 20028,
    '_dxball_board_tiles': 20032,
}
STORAGE_SIZE = BOARD_OFFSETS['_dxball_board_tiles'] + BOARD_SIZE
BOARD_CODE = ('_dxball_load_editor_board', '_dxball_store_editor_board',
              '_dxball_initialize_board')
CONVERSION_SETUP = '_dxball_crt_initialize_conversion_table'
CONVERSION_TARGETS = (
    '_dxball_crt_format_float', '_dxball_crt_crop_float_zeros',
    '_dxball_crt_assign_float', '_dxball_crt_force_decimal_point',
    '_dxball_crt_float_positive', '_dxball_crt_format_float',
)


class LinkedImage:
    def __init__(self, executable, link_map):
        self.pe = pefile.PE(str(executable))
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.symbols = defaultdict(set)
        for name, address in re.findall(
                r'^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}[ \t]+(\S+)[ \t]+([0-9A-Fa-f]{8})\b',
                link_map.read_text(), re.MULTILINE):
            self.symbols[name].add(int(address, 16))
        self.highlow = {
            item.rva for block in self.pe.DIRECTORY_ENTRY_BASERELOC
            for item in block.entries if item.type == pefile.RELOCATION_TYPE['IMAGE_REL_BASED_HIGHLOW']
        }

    def address(self, name):
        addresses = self.symbols.get(name, ())
        if len(addresses) != 1:
            raise ValueError(f'expected a unique map address for {name}')
        return next(iter(addresses))

    def rva(self, name):
        return self.address(name) - self.base

    def read(self, name, size):
        return self.pe.get_data(self.rva(name), size)


def initialized_data(path, name, size):
    data, sections, symbols = parse(path)
    definition, = [symbol for symbol in symbols.values()
                   if symbol['name'] == name and symbol['section'] > 0]
    section = sections[definition['section'] - 1]
    if not section['data']:
        raise ValueError(f'COFF definition for {name} has no initialized bytes')
    start = definition['value']
    contents = region(data, section['data'], section['size'])
    binding = []
    for row in _relocations(data, section, symbols, contents):
        offset = row['offset'] - start
        if -4 < offset < size:
            if not 0 <= offset <= size - 4:
                raise ValueError(f'relocation crosses the extent of {name}')
            binding.append(dict(row, offset=offset))
    return region(contents, start, size), binding


def verify_bindings(image, objects):
    blocks = [
        (name, *function(objects['src/boards.c'], name)) for name in BOARD_CODE
    ]
    blocks += [
        (name, *function(objects['src/runtime_initialization.c'], name))
        for name in ('_dxball_crt_initialize_runtime', CONVERSION_SETUP)
    ]
    blocks += [
        (name, *initialized_data(objects[source], name, size))
        for source, name, size in (
            ('src/boards.c', '_dxball_render_ops', 12),
            ('src/runtime_fp_initialization_state.c', '__FPinit', 4),
            ('src/runtime_fp_initialization_state.c', '__FPmtinit', 4),
            ('src/runtime_fp_initialization_state.c', '__FPmtterm', 4),
            ('src/runtime_float_format_state.c', '__cfltcvt_tab', 24),
            ('src/runtime_termination_tables.c', '_dxball_preterminators', 8),
        )
    ]
    for name, contents, bindings in blocks:
        targets = {row['symbol']: image.address(row['symbol']) for row in bindings}
        expected = relocate(contents, bindings, image.address(name), targets)
        if image.read(name, len(expected)) != expected:
            raise ValueError(f'linked bytes for {name} differ from its relocated COFF bytes')
        for row in bindings:
            site = image.rva(name) + row['offset']
            if (site in image.highlow) != (row['type'] == 'DIR32'):
                raise ValueError(f'unexpected PE base relocation for {name} at RVA {site:#x}')
    bank = image.address('_dxball_board_storage')
    for name, offset in BOARD_OFFSETS.items():
        if image.address(name) != bank + offset:
            raise ValueError(f'board storage offset changed for {name}')
    metadata = struct.pack('<6I', 0, 20000, 20008, 20024, 20032, STORAGE_SIZE)
    if image.read('_dxball_board_storage_offsets', len(metadata)) != metadata:
        raise ValueError('incorrect linked board storage metadata')
    return len(blocks), sum(len(bindings) for _, _, bindings in blocks)


def verify_execution(image):
    cpu = Uc(UC_ARCH_X86, UC_MODE_32)
    image_size = image.pe.OPTIONAL_HEADER.SizeOfImage
    cpu.mem_map(image.base, image_size)
    cpu.mem_write(image.base, image.pe.get_memory_mapped_image())
    stack = image.base + image_size + 0x1000
    cpu.mem_map(stack, 0x2000)
    return_address = stack + 0x1000

    def call(name, *args):
        sp = stack + 0x800
        words = (return_address, *args)
        cpu.mem_write(sp, struct.pack(f'<{len(words)}I', *words))
        cpu.reg_write(UC_X86_REG_ESP, sp)
        cpu.reg_write(UC_X86_REG_EFLAGS, 0x202)
        cpu.emu_start(image.address(name), return_address, count=10000)
        if (cpu.reg_read(UC_X86_REG_EIP) != return_address or
                cpu.reg_read(UC_X86_REG_ESP) != sp + 4 or
                cpu.reg_read(UC_X86_REG_EFLAGS) & 0x400):
            raise ValueError(f'incorrect return from {name}')

    call(CONVERSION_SETUP)
    conversion_table = image.address('__cfltcvt_tab')
    expected = struct.pack('<6I', *(image.address(name) for name in CONVERSION_TARGETS))
    if cpu.mem_read(conversion_table, len(expected)) != expected:
        raise ValueError('CRT conversion setup did not write the expected linked callbacks')

    bank = image.address('_dxball_board_storage')
    aux = image.address('_dxball_board_aux')
    index = image.address('_dxball_board_index')
    tiles = BOARD_OFFSETS['_dxball_board_tiles']
    rng = random.Random(0x43AAB8)
    patterns = (bytes(STORAGE_SIZE), bytes((17 + i * 73) % 256 for i in range(STORAGE_SIZE)),
                rng.randbytes(STORAGE_SIZE))
    cases = 0
    for data in patterns:
        for board in (0, 49, 50):
            for operation in BOARD_CODE:
                cpu.mem_write(bank, data)
                aux_before = rng.randbytes(BOARD_SIZE)
                cpu.mem_write(aux, aux_before)
                selected = struct.pack('<I', board)
                cpu.mem_write(index, selected)
                expected_storage = bytearray(data)
                offset = board * BOARD_SIZE
                if operation == '_dxball_store_editor_board':
                    expected_storage[offset:offset + BOARD_SIZE] = data[tiles:tiles + BOARD_SIZE]
                else:
                    expected_storage[tiles:tiles + BOARD_SIZE] = data[offset:offset + BOARD_SIZE]
                initializes = operation == '_dxball_initialize_board'
                call(operation, *(() if initializes else (board,)))
                expected_aux = bytes(BOARD_SIZE) if initializes else aux_before
                if (cpu.mem_read(bank, STORAGE_SIZE) != expected_storage or
                        cpu.mem_read(aux, BOARD_SIZE) != expected_aux or
                        cpu.mem_read(index, 4) != selected):
                    raise ValueError(f'incorrect storage after {operation}({board})')
                cases += 1
    return cases


def checked_objects(receipt):
    objects = {source: ROOT / row['object'] for source, row in receipt['objects'].items()}
    for source, path in objects.items():
        if sha256(path) != receipt['objects'][source]['object_sha256']:
            raise ValueError(f'build receipt does not match {path}')
    for member in receipt['original_members']:
        path = BUILD / 'members' / f"{member['header_offset']:08x}.obj"
        if sha256(path) != member['object_sha256']:
            raise ValueError(f'build receipt does not match {path}')
    for library in receipt['directx_imports']:
        if sha256(ROOT / library['library']) != library['library_sha256']:
            raise ValueError(f"build receipt does not match {library['library']}")
    return objects


def relink(receipt, objects, directory, base):
    arguments = receipt['link_arguments']
    paths = {windows_path(path) for path in objects.values()}
    if not paths.issubset(arguments):
        raise ValueError('receipt link arguments do not identify the local object files')
    movable = {windows_path(path) for path in objects.values()
               if not any(section['name'].startswith('.CRT$') for section in parse(path)[1])}
    reversed_objects = iter(reversed([arg for arg in arguments if arg in movable]))
    resource_args = [arg for arg in arguments if arg.lower().endswith('\\game-resources.obj')]
    if len(resource_args) != 1:
        raise ValueError('expected one game-resources.obj in the build receipt')
    retained = [
        next(reversed_objects) if arg in movable else arg
        for arg in arguments
        if not arg.upper().startswith(('/OUT:', '/MAP:', '/ENTRY:')) and arg not in resource_args
    ]
    executable, link_map = directory / 'layout.dll', directory / 'layout.map'
    with session_lock():
        toolchain = Toolchain()
        lock = toolchain.verify()
        if lock['linker_sha256'] != receipt['linker_sha256']:
            raise ValueError('current linker does not match the baseline receipt')
        toolchain.run('link.exe', [
            '/DLL', '/NOENTRY', '/INCLUDE:_dxball_windows_crt_startup',
            f'/BASE:{base:#x}', '/ALIGN:8192',
            '/OUT:' + windows_path(executable), '/MAP:' + windows_path(link_map), *retained,
        ])
    image = LinkedImage(executable, link_map)
    header = image.pe.OPTIONAL_HEADER
    if (header.AddressOfEntryPoint or image.base != base or header.SectionAlignment != 8192 or
            hasattr(image.pe, 'DIRECTORY_ENTRY_RESOURCE')):
        raise ValueError('unexpected entrypoint, base, section alignment, or resources in audit image')
    return image, len(movable)


def main():
    receipt = json.loads((BUILD / 'build.json').read_text())
    executable, link_map = BUILD / 'dxball.exe', BUILD / 'dxball.map'
    if (receipt['profile'] != 'vc40-restored-crt' or
            sha256(executable) != receipt['executable_sha256'] or
            sha256(link_map) != receipt['game_map_sha256']):
        raise ValueError('baseline PE and map must match the restored CRT build receipt')
    objects = checked_objects(receipt)
    regular = LinkedImage(executable, link_map)
    with tempfile.TemporaryDirectory(prefix='vc40-pi-', dir=ROOT / 'build') as directory:
        moved, count = relink(receipt, objects, Path(directory), regular.base)
        print(f'Reversed {count} source objects at the same image base ({regular.base:#010x})')
        shifts = set()
        for name in ('_dxball_load_editor_board', '_dxball_render_ops',
                     '_dxball_board_aux', '_dxball_board_storage', '__FPinit', '___xc_a'):
            rva_before, rva_after = regular.rva(name), moved.rva(name)
            if rva_before == rva_after:
                raise ValueError(f'layout trial did not move {name}')
            shifts.add(rva_after - rva_before)
            print(f'{name:28} RVA {rva_before:#08x} -> {rva_after:#08x}')
        if len(shifts) < 2:
            raise ValueError('layout trial preserved every checked relative position')
        for label, image in (('regular', regular), ('reordered', moved)):
            blocks, bindings = verify_bindings(image, objects)
            cases = verify_execution(image)
            print(f'{label}: {blocks} complete code/data spans, {bindings} COFF bindings, '
                  f'{cases} board cases and CRT conversion setup passed')


if __name__ == '__main__':
    os.environ.setdefault('PULSE_SINK', 'dxball_reconstruction_silent')
    main()
