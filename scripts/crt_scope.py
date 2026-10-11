"""Bind actual COFF indices inside completely verified archive-member sections."""
import struct

from coff import _relocations, region
from crt_library import relocate


def publish_section(scoped, member_id, symbols, index, address, size):
    records = scoped.setdefault(member_id, {})
    for symbol_index, symbol in symbols.items():
        if symbol['section'] != index or symbol['storage'] not in (2, 3):
            continue
        if not 0 <= symbol['value'] <= size:
            raise ValueError('member definition exceeds the verified section')
        row = dict(symbol_index=symbol_index, symbol=symbol['name'], section=index,
                   storage=symbol['storage'], value=symbol['value'], type=symbol['type'],
                   address=address + symbol['value'], section_address=address)
        if symbol_index in records and records[symbol_index] != row:
            raise ValueError('member definition contradicts its verified section')
        records[symbol_index] = row


def relocate_section(data, section, symbols, code, address, index, member_id, scoped, external_bindings):
    relocations = _relocations(data, section, symbols, code)
    scoped_records = scoped.get(member_id, {})
    resolved, mapping, bindings = [], {}, []
    for ordinal, relocation in enumerate(relocations):
        offset, symbol_index, kind = struct.unpack('<IIH', region(
            data, section['relocations'] + ordinal * 10, 10))
        symbol = symbols[symbol_index]
        assert offset == relocation['offset'] and symbol['name'] == relocation['symbol']
        if symbol['section'] == index:
            if not 0 <= symbol['value'] <= len(code):
                raise ValueError('current member definition exceeds section')
            target = address + symbol['value']
            basis = 'current section definition by actual COFF symbol index'
        elif symbol_index in scoped_records:
            known = scoped_records[symbol_index]
            if any(known[k] != symbol[k] for k in ['section', 'storage', 'value', 'type']):
                raise ValueError('verified member symbol identity differs')
            if known['symbol'] != symbol['name']:
                raise ValueError('verified member symbol name differs')
            target = known['address']
            basis = 'earlier complete verified section in the same archive member'
        elif symbol['storage'] == 2 and symbol['name'] in external_bindings:
            target = external_bindings[symbol['name']]
            basis = 'independently verified external binding'
        else:
            raise ValueError('unresolved actual COFF symbol: ' + symbol['name'])
        if symbol['storage'] == 2 and symbol['name'] in external_bindings and external_bindings[symbol['name']] != target:
            raise ValueError('external member definition contradicts established binding')
        # The relocation engine receives a unique actual-index identity, so
        # same-name section/static symbols cannot overwrite one another.
        key = str(symbol_index)
        if key in mapping and mapping[key] != target:
            raise ValueError('one COFF symbol resolved to multiple addresses')
        mapping[key] = target
        resolved.append(dict(relocation, symbol=key))
        bindings.append(dict(relocation, symbol_index=symbol_index, section=symbol['section'],
                             storage=symbol['storage'], value=symbol['value'],
                             address=target, basis=basis))
    return relocate(code, resolved, address, mapping), relocations, bindings
