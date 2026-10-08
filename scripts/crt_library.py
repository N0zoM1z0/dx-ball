"""Read pinned COFF library members for whole-section origin comparisons."""
from pathlib import Path
import struct

from coff import parse, region


def members(path):
    data = Path(path).read_bytes()
    if data[:8] != b'!<arch>\n':
        raise ValueError('expected a COFF archive')
    offset, names = 8, b''
    while offset < len(data):
        header = region(data, offset, 60)
        if header[58:] != b'`\n':
            raise ValueError('invalid archive member trailer')
        size = int(header[48:58])
        raw = region(data, offset + 60, size)
        field = header[:16].decode('ascii').strip()
        if field == '//':
            names = raw
        elif field != '/':
            if field.startswith('/'):
                index = int(field[1:])
                if not 0 <= index < len(names):
                    raise ValueError('invalid archive long-name offset')
                name = names[index:].split(b'\0', 1)[0].split(b'\n', 1)[0]
                name = name.decode('ascii').rstrip('/')
            else:
                name = field.rstrip('/')
            yield offset, name, raw
        offset += 60 + size + (size & 1)
    if offset != len(data):
        raise ValueError('missing archive member alignment byte')


def defines(raw, wanted):
    """Match requested ASCII symbols without decoding unrelated binary names."""
    if len(raw) < 20 or struct.unpack_from('<H', raw)[0] != 0x14C:
        return False
    _, _, _, start, count, optional, _ = struct.unpack_from('<HHIIIHH', raw)
    if optional:
        raise ValueError('expected a plain COFF library member')
    strings_start = start + count * 18
    length = struct.unpack('<I', region(raw, strings_start, 4))[0]
    if length < 4:
        raise ValueError('invalid COFF string table')
    strings = region(raw, strings_start, length)
    wanted = wanted.encode('ascii')
    found, index = False, 0
    while index < count:
        name, _, section, _, _, aux = struct.unpack(
            '<8sIhHBB', region(raw, start + index * 18, 18))
        if name[:4] == b'\0' * 4:
            offset = struct.unpack_from('<I', name, 4)[0]
            if not 4 <= offset < length:
                raise ValueError('invalid COFF symbol-name offset')
            name = strings[offset:]
        found |= section > 0 and name.split(b'\0', 1)[0] == wanted
        region(raw, start + index * 18, (1 + aux) * 18)
        index += 1 + aux
    if index != count:
        raise ValueError('COFF auxiliary records exceed the symbol table')
    return found


def extract(path, wanted, destination):
    selected = [(offset, name, raw) for offset, name, raw in members(path)
                if defines(raw, wanted)]
    if len(selected) != 1:
        raise ValueError('expected one defining library member: ' + wanted)
    offset, name, raw = selected[0]
    output = Path(destination) / (f'{offset:08x}.obj')
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(raw)
    return output, dict(member=name,header_offset=offset)


def function_section(path, wanted):
    """Require a complete single-function code section, including non-COMDAT asm."""
    data, sections, symbols = parse(path)
    selected = [s for s in symbols.values() if s['name'] == wanted and s['section'] > 0]
    if len(selected) != 1:
        raise ValueError('expected one defined function: ' + wanted)
    symbol = selected[0]
    if not 1 <= symbol['section'] <= len(sections):
        raise ValueError('function refers to a missing section')
    section = sections[symbol['section'] - 1]
    functions = [s for s in symbols.values() if s['section'] == symbol['section']
                 and s['type'] == 0x20 and s['storage'] in (2, 3)]
    if (symbol['value'] != 0 or symbol['type'] != 0x20 or symbol['storage'] not in (2, 3)
            or len(functions) != 1 or not section['flags'] & 0x20 or not section['data']
            or section['size'] <= 0):
        raise ValueError('origin comparison requires a whole single-function code section')
    code = bytearray(region(data, section['data'], section['size']))
    relocations, occupied = [], set()
    for index in range(section['relocation_count']):
        offset, target, kind = struct.unpack(
            '<IIH', region(data, section['relocations'] + index * 10, 10))
        if kind not in (6, 20) or target not in symbols:
            raise ValueError('unsupported COFF relocation')
        if offset + 4 > len(code) or any(i in occupied for i in range(offset, offset + 4)):
            raise ValueError('COFF relocation overlaps or exceeds the function')
        occupied.update(range(offset, offset + 4))
        relocations.append(dict(offset=offset, type='DIR32' if kind == 6 else 'REL32',
                                symbol=symbols[target]['name'],
                                addend=struct.unpack_from('<I', code, offset)[0]))
    return code, relocations


def relocate(code, relocations, address, mapping):
    result = bytearray(code)
    for relocation in relocations:
        offset, name = relocation['offset'], relocation['symbol']
        if relocation['type'] not in ('DIR32', 'REL32') or not 0 <= offset <= len(result) - 4:
            raise ValueError('invalid relocation kind or range')
        if name not in mapping:
            raise ValueError('unmapped relocation: ' + name)
        value = mapping[name] + relocation['addend']
        if relocation['type'] == 'REL32':
            value -= address + offset + 4
        struct.pack_into('<I', result, offset, value & 0xFFFFFFFF)
    return bytes(result)
