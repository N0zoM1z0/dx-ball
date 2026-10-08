"""Strict i386 COFF reader for dedicated /Gy function sections.

Extent authority is the complete one-function COMDAT section, not a requested
prefix. Aux-less old VC4 symbols cannot hide additional emitted instructions.
"""
from pathlib import Path
import struct


def region(data, offset, length):
    if offset < 0 or length < 0 or offset + length > len(data):
        raise ValueError("truncated COFF range")
    return data[offset:offset + length]


def parse(path):
    data = Path(path).read_bytes()
    machine, count, _, symbol_offset, symbol_count, optional, _ = struct.unpack(
        "<HHIIIHH", region(data, 0, 20))
    if machine != 0x14C or optional != 0:
        raise ValueError("expected plain i386 COFF")
    sections = []
    for index in range(count):
        fields = struct.unpack("<8sIIIIIIHHI", region(data, 20 + index * 40, 40))
        sections.append({"size": fields[3], "data": fields[4],
                         "relocations": fields[5], "relocation_count": fields[7],
                         "flags": fields[9]})
    string_offset = symbol_offset + symbol_count * 18
    string_size = struct.unpack("<I", region(data, string_offset, 4))[0]
    strings = region(data, string_offset, string_size)
    symbols = {}
    index = 0
    while index < symbol_count:
        raw, value, section, kind, storage, aux = struct.unpack(
            "<8sIhHBB", region(data, symbol_offset + index * 18, 18))
        if raw[:4] == b"\0" * 4:
            offset = struct.unpack_from("<I", raw, 4)[0]
            if not 4 <= offset < len(strings):
                raise ValueError("bad COFF name offset")
            raw = strings[offset:]
        name = raw.split(b"\0", 1)[0].decode("ascii")
        symbols[index] = {"name": name, "value": value, "section": section,
                          "type": kind, "storage": storage}
        region(data, symbol_offset + index * 18, (1 + aux) * 18)
        index += 1 + aux
    if index != symbol_count:
        raise ValueError("auxiliary records exceed symbol count")
    return data, sections, symbols


def symbol_data(path, name, size):
    data, sections, symbols = parse(path)
    matches = [s for s in symbols.values() if s["name"] == name and s["section"] > 0]
    if len(matches) != 1:
        raise ValueError(f"expected one defined data symbol: {name}")
    symbol = matches[0]
    section = sections[symbol["section"] - 1]
    if symbol["value"] + size > section["size"] or not section["data"]:
        raise ValueError("mapped literal extends outside initialized object data")
    return region(data, section["data"] + symbol["value"], size)


def function(path, wanted):
    data, sections, symbols = parse(path)
    matches = [s for s in symbols.values() if s["name"] == wanted and s["section"] > 0]
    if len(matches) != 1:
        raise ValueError(f"expected one defined function symbol: {wanted}")
    symbol = matches[0]
    section = sections[symbol["section"] - 1]
    functions = [s for s in symbols.values() if s["section"] == symbol["section"]
                 and s["type"] == 0x20 and s["storage"] in (2, 3)]
    if (symbol["value"] != 0 or symbol["type"] != 0x20 or len(functions) != 1
            or symbol["storage"] not in (2, 3) or section["flags"] & 0x1020 != 0x1020):
        raise ValueError("function extent needs a dedicated code COMDAT section")
    code = bytearray(region(data, section["data"], section["size"]))
    relocations = []
    occupied = set()
    for index in range(section["relocation_count"]):
        offset, symbol_index, kind = struct.unpack(
            "<IIH", region(data, section["relocations"] + index * 10, 10))
        if kind not in (6, 20) or symbol_index not in symbols:
            raise ValueError("unsupported relocation or auxiliary target")
        if offset + 4 > len(code) or any(i in occupied for i in range(offset, offset + 4)):
            raise ValueError("relocation extends outside code or overlaps")
        occupied.update(range(offset, offset + 4))
        relocations.append({"offset": offset, "type": "DIR32" if kind == 6 else "REL32",
                            "symbol": symbols[symbol_index]["name"],
                            "addend": struct.unpack_from("<I", code, offset)[0]})
    return code, relocations
