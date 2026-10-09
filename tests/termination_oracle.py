"""Controlled callback/ExitProcess boundary for the recovered CRT exit owner."""
import ctypes as C
import hashlib
import itertools
import struct

from unicorn import UC_HOOK_CODE
from target_oracle import TargetOracle

ENTRIES = {'crt_exit': 0x417910, 'crt_quick_exit': 0x417930,
           'crt_do_exit': 0x417950, 'crt_run_initializers': 0x4179D0}
WIDTHS = {'dxball_termination_done': 4, 'dxball_exit_flag': 1,
          'dxball_onexit_begin': 4, 'dxball_onexit_end': 4,
          'dxball_preterminators': 8, 'dxball_terminators': 4,
          'dxball_termination_ops': 4}
STORAGE = dict(zip(WIDTHS, (0x4230F0, 0x4230EC, 0x440D7C, 0x440D78,
                            0x421040, 0x42104C, 0x44131C)))
CALLBACK = C.CFUNCTYPE(None)
EXIT = C.CFUNCTYPE(None, C.c_uint)


def fixtures():
    # Exhaust every null/two-identity table through five slots, then valid
    # empty/reversed/interior subranges of a mixed six-slot table.
    for length in range(6):
        for values in itertools.product((0, 1, 2), repeat=length):
            yield dict(name='crt_run_initializers', helper=list(values), bounds=[0, length])
    for first in range(7):
        for last in range(7):
            yield dict(name='crt_run_initializers', helper=[1, 0, 2, 1, 0, 2], bounds=[first, last])
    layouts = [[], [0], [1], [1, 0, 2], [1, 2, 1, 3], [0, 0, 0, 0]]
    for status, quick, returning, values in itertools.product(
            (0, 1, 0xFFFFFFFF, 0x80000000, 0x7FFFFFFF),
            (0, 1, -1), (0, 1, -1, 256, -256, 0x7FFFFFFF), layouts):
        yield dict(name='crt_do_exit', args=[status, quick, returning], onexit=values,
                   pre=[1, 0], term=[2])
    for name, status, values in itertools.product(
            ('crt_exit', 'crt_quick_exit'), (0, 1, 0xFFFFFFFF, 0x80000000, 0x7FFFFFFF), layouts):
        yield dict(name=name, args=[status], onexit=values, pre=[1, 3], term=[2])
    # Null begin skips onexit regardless of end, and no done flag prevents a
    # second pass. Callback effects exercise local end/global begin ownership.
    for quick in (0, 1):
        yield dict(name='crt_do_exit', args=[7, quick, 1], onexit=[1, 2, 3],
                   null_begin=True, pre=[0, 3], term=[4], repeat=2)
    for action in ({'begin': 2}, {'begin': 0, 'end': 0}, {'onexit': [0, 4, 0, 3]},
                   {'pre': [4, 2]}, {'term': [4]}, {'done': 77, 'flag': 128}):
        yield dict(name='crt_do_exit', args=[19, 0, 256], onexit=[1, 2, 3],
                   pre=[1, 2], term=[3], mutations={'0': action})
    for action in ({'helper': [1, 4, 0, 2]}, {'done': 91, 'flag': 255}):
        yield dict(name='crt_run_initializers', helper=[1, 2, 3, 4], bounds=[0, 4],
                   mutations={'0': action})
    for name in ('crt_exit', 'crt_quick_exit', 'crt_do_exit'):
        yield dict(name=name, args=[23, 0, 1] if name == 'crt_do_exit' else [23],
                   onexit=[1, 2], pre=[1, 0], term=[3], repeat=2)


class Protocol:
    def reset(self, recipe):
        self.recipe, self.log, self.errors = recipe, [], []
        self.set_scalar('done', 0xDEADBEEF)
        self.set_scalar('flag', 0xEF)
        self.set_table('onexit', recipe.get('onexit', []))
        self.set_table('helper', recipe.get('helper', []))
        self.set_table('pre', recipe.get('pre', [0, 0]))
        self.set_table('term', recipe.get('term', [0]))
        self.set_bound('begin', None if recipe.get('null_begin') else 0)
        self.set_bound('end', len(recipe.get('onexit', [])))

    def callback(self, identity):
        index = len(self.log)
        self.log.append(dict(callback=identity, state=self.snapshot()))
        for name, value in self.recipe.get('mutations', {}).get(str(index), {}).items():
            if name in ('begin', 'end'):
                self.set_bound(name, value)
            elif name in ('done', 'flag'):
                self.set_scalar(name, value)
            else:
                self.set_table(name, value)

    def platform_exit(self, status):
        # Intentionally returning boundary for inspecting this finite owner;
        # neither native nor original physical process exit is simulated.
        self.log.append(dict(exit_process=status, state=self.snapshot()))

    def run(self):
        for _ in range(self.recipe.get('repeat', 1)):
            self.execute(self.recipe['name'], self.recipe.get('args', []))
        assert not self.errors, self.errors
        return dict(events=self.log, state=self.snapshot())


class Native(Protocol):
    def __init__(self, library):
        self.lib = C.CDLL(str(library))
        self.tables = {name: (C.c_void_p * count)() for name, count in [('onexit', 8), ('helper', 8)]}
        self.tables.update(pre=(C.c_void_p * 2).in_dll(self.lib, 'dxball_preterminators'),
                           term=(C.c_void_p * 1).in_dll(self.lib, 'dxball_terminators'))
        self.scalars = {'done': C.c_uint.in_dll(self.lib, 'dxball_termination_done'),
                        'flag': C.c_ubyte.in_dll(self.lib, 'dxball_exit_flag')}
        self.bounds = {name: C.c_void_p.in_dll(self.lib, 'dxball_onexit_' + name)
                       for name in ('begin', 'end')}
        self.errors = []
        def protected(function):
            def call(*args):
                try:
                    function(*args)
                except BaseException as exc:
                    self.errors.append(str(exc))
            return call
        self.callbacks = {i: CALLBACK(protected(lambda i=i: self.callback(i))) for i in range(1, 5)}
        self.identities = {C.cast(cb, C.c_void_p).value: i for i, cb in self.callbacks.items()}
        self.identities[None] = 0
        self.exit_callback = EXIT(protected(self.platform_exit))
        C.c_void_p.in_dll(self.lib, 'dxball_termination_ops').value = C.cast(self.exit_callback, C.c_void_p).value
        for name in ENTRIES:
            fn = getattr(self.lib, 'dxball_' + name)
            fn.restype = None
            fn.argtypes = ([C.c_void_p, C.c_void_p] if name == 'crt_run_initializers'
                           else [C.c_uint, C.c_int, C.c_int] if name == 'crt_do_exit' else [C.c_uint])

    def set_scalar(self, name, value):
        self.scalars[name].value = value

    def set_bound(self, name, value):
        self.bounds[name].value = None if value is None else C.addressof(self.tables['onexit']) + value * C.sizeof(C.c_void_p)

    def set_table(self, name, values):
        for index in range(len(self.tables[name])):
            self.tables[name][index] = C.cast(self.callbacks[values[index]], C.c_void_p).value if index < len(values) and values[index] else None

    def snapshot(self):
        def bound(value):
            return None if value is None else (value - C.addressof(self.tables['onexit'])) // C.sizeof(C.c_void_p)
        return dict(done=self.scalars['done'].value, flag=self.scalars['flag'].value,
                    begin=bound(self.bounds['begin'].value), end=bound(self.bounds['end'].value),
                    tables={name: [self.identities[v] for v in values] for name, values in self.tables.items()})

    def execute(self, name, args):
        if name == 'crt_run_initializers':
            base = C.addressof(self.tables['helper'])
            args = [base + index * C.sizeof(C.c_void_p) for index in self.recipe['bounds']]
        getattr(self.lib, 'dxball_' + name)(*args)


class Target(Protocol, TargetOracle):
    ONEXIT, HELPER, CALLBACK_BASE, EXIT = 0x508000, 0x508100, 0x50A000, 0x50B000

    def __init__(self):
        TargetOracle.__init__(self)
        for hook in self._hooks:
            self.uc.hook_del(hook)
        self._hooks = []
        self.storage = dict(STORAGE)
        self.entries = dict(ENTRIES)
        self.uc.hook_add(UC_HOOK_CODE, self.callback_hook, begin=self.CALLBACK_BASE, end=self.CALLBACK_BASE + 0x40)
        self.uc.hook_add(UC_HOOK_CODE, self.exit_hook, begin=self.EXIT, end=self.EXIT)
        self.write_u32(self.storage['dxball_termination_ops'], self.EXIT)
        section = next(s for s in self.pe.sections if s.Name.rstrip(b'\0') == b'.text')
        self.text_address, self.text_size = self.base + section.VirtualAddress, section.Misc_VirtualSize
        self.text_sha256 = hashlib.sha256(self.read(self.text_address, self.text_size)).hexdigest()
        self.errors = []

    def table(self, name):
        return {'onexit': (self.ONEXIT, 8), 'helper': (self.HELPER, 8),
                'pre': (self.storage['dxball_preterminators'], 2),
                'term': (self.storage['dxball_terminators'], 1)}[name]

    def set_scalar(self, name, value):
        address = self.storage[{'done': 'dxball_termination_done', 'flag': 'dxball_exit_flag'}[name]]
        if name == 'done':
            self.write_u32(address, value)
        else:
            self.write(address, bytes([value & 255]))

    def set_bound(self, name, value):
        self.write_u32(self.storage['dxball_onexit_' + name], 0 if value is None else self.ONEXIT + value * 4)

    def set_table(self, name, values):
        address, count = self.table(name)
        self.write(address, struct.pack('<' + 'I' * count, *(self.CALLBACK_BASE + values[i] * 0x10 if i < len(values) and values[i] else 0 for i in range(count))))

    def snapshot(self):
        def bound(address):
            value = self.read_u32(address)
            return None if not value else (value - self.ONEXIT) // 4
        identities = {0: 0, **{self.CALLBACK_BASE + i * 0x10: i for i in range(1, 5)}}
        return dict(done=self.read_u32(self.storage['dxball_termination_done']),
                    flag=self.read(self.storage['dxball_exit_flag'], 1)[0],
                    begin=bound(self.storage['dxball_onexit_begin']), end=bound(self.storage['dxball_onexit_end']),
                    tables={name: [identities[self.read_u32(address + i * 4)] for i in range(count)]
                            for name in ('onexit', 'helper', 'pre', 'term') for address, count in [self.table(name)]})

    def callback_hook(self, uc, address, size, userdata):
        assert address in [self.CALLBACK_BASE + i * 0x10 for i in range(1, 5)]
        self.callback((address - self.CALLBACK_BASE) // 0x10)
        self._return()

    def exit_hook(self, uc, address, size, userdata):
        self.platform_exit(self._args(1)[0])
        self._return(pop=4)  # The real imported Windows API uses stdcall.

    def execute(self, name, args):
        if name == 'crt_run_initializers':
            args = [self.HELPER + index * 4 for index in self.recipe['bounds']]
        self.call(self.entries[name], *args)
        assert hashlib.sha256(self.read(self.text_address, self.text_size)).hexdigest() == self.text_sha256
