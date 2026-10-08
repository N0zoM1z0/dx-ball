#!/usr/bin/env python3
"""Execute eight unmodified original allocator bodies against maintained C.

Only HeapCreate/HeapAlloc/HeapFree and new-handler outcomes are controlled.
No original internal entry is replaced; requests/globals/effects and original
stack ABI compare. Host-width bridge controls are separately counted.
"""
import argparse
import ctypes as C
import hashlib
import json
from pathlib import Path
import signal
import sys
import tomllib
from unicorn import UC_HOOK_CODE
from target_oracle import ROOT, TargetOracle
sys.path.insert(0, str(ROOT/'scripts'))
from resource_limits import limit_cpu
HEAP, HANDLER, MODE = 0x440D70, 0x43FB10, 0x4234D4
ENTRIES = {'runtime_new': 0x416770, 'runtime_delete': 0x416760,
           'heap_release': 0x417750, 'allocate_with_handler': 0x417790,
           'heap_allocate': 0x4177D0, 'call_new_handler': 0x419EA0,
           'initialize_runtime_heap': 0x419E80, 'runtime_malloc': 0x417770}
Create = C.CFUNCTYPE(C.c_void_p, C.c_uint, C.c_size_t, C.c_size_t)
Allocate = C.CFUNCTYPE(C.c_void_p, C.c_void_p, C.c_uint, C.c_size_t)
Release = C.CFUNCTYPE(C.c_int, C.c_void_p, C.c_uint, C.c_void_p)
Handler = C.CFUNCTYPE(C.c_int, C.c_uint)
class HeapApi(C.Structure):
    _fields_ = [('create', Create), ('allocate', Allocate), ('release', Release)]
def digest(path):
    with Path(path).open('rb') as f: return hashlib.file_digest(f, 'sha256').hexdigest()

class Script:
    """Script only the external OS/callback responses, not the allocator rules."""
    def reset(self, fixture):
        self.plan = fixture
        self.alloc_index = self.handler_index = 0
        self.events, self.errors = [], []
        self.heap = fixture.get('heap', 0x12345000)
        self.handler = fixture.get('handler', 'primary')
        self.set_heap(self.heap)
        self.set_handler(self.handler)
        self.set_mode(fixture.get('mode', 0))

    def create_response(self, flags, initial, maximum):
        self.events.append(('HeapCreate', flags, initial, maximum))
        if 'create_result' not in self.plan:
            self.errors.append('Unexpected HeapCreate request')
        return self.plan.get('create_result', 0)

    def allocate_response(self, heap, flags, size):
        self.events.append(('HeapAlloc', heap, flags, size))
        responses = self.plan.get('allocations', [])
        if self.alloc_index >= len(responses):
            self.errors.append('Unexpected HeapAlloc response request')
            return 0
        result = responses[self.alloc_index]
        self.alloc_index += 1
        return result

    def release_response(self, heap, flags, memory):
        self.events.append(('HeapFree', heap, flags, memory))
        return self.plan.get('release_result', 1)

    def handler_response(self, identity, size):
        self.events.append(('new-handler', identity, size))
        responses = self.plan.get('handlers', [])
        if self.handler_index >= len(responses):
            self.errors.append('Unexpected new-handler response request')
            return 0
        action = responses[self.handler_index]
        self.handler_index += 1
        if 'heap' in action:
            self.heap = action['heap']
            self.set_heap(self.heap)
        if 'handler' in action:
            self.handler = action['handler']
            self.set_handler(self.handler)
        if 'mode' in action:
            self.set_mode(action['mode'])
        return action['result']


class Native(Script):
    def __init__(self, library):
        self.lib = C.CDLL(str(library))
        self.heap_storage = C.c_void_p.in_dll(self.lib, 'dxball_runtime_heap')
        self.handler_storage = C.c_void_p.in_dll(self.lib, 'dxball_new_handler')
        self.mode_storage = C.c_int.in_dll(self.lib, 'dxball_malloc_mode')
        self.errors = []
        def protect(fn):
            def callback(*args):
                try: return fn(*args)
                except BaseException as exc: self.errors.append(exc); return 0
            return callback
        self.callbacks = {
            'primary': Handler(protect(lambda size: self.handler_response('primary', size))),
            'secondary': Handler(protect(lambda size: self.handler_response('secondary', size))),
        }
        self.allocate_callback = Allocate(
            protect(lambda heap, flags, size: self.allocate_response(heap or 0, flags, size)))
        self.release_callback = Release(
            protect(lambda heap, flags, memory: self.release_response(heap or 0, flags, memory or 0)))
        api = HeapApi.in_dll(self.lib, 'dxball_heap_api')
        self.create_callback = Create(protect(self.create_response))
        api.create = self.create_callback
        api.allocate, api.release = self.allocate_callback, self.release_callback
        for name in ENTRIES:
            function = getattr(self.lib, 'dxball_' + name)
            function.argtypes = ([] if name == 'initialize_runtime_heap'
                                 else [C.c_void_p] if name in ('runtime_delete', 'heap_release')
                                 else [C.c_uint, C.c_int] if name == 'allocate_with_handler'
                                 else [C.c_uint])
            function.restype = (None if name in ('runtime_delete', 'heap_release')
                                else C.c_int if name == 'call_new_handler' else C.c_void_p)

    def set_heap(self, value):
        self.heap_storage.value = value

    def set_mode(self, value):
        self.mode_storage.value = value

    def set_handler(self, identity):
        self.handler_storage.value = (C.cast(self.callbacks[identity], C.c_void_p).value
                                      if identity else None)

    def globals(self):
        identities = {C.cast(cb, C.c_void_p).value: name for name, cb in self.callbacks.items()}
        identities[None] = None
        assert self.handler_storage.value in identities, 'Unknown native handler pointer'
        return (self.heap_storage.value or 0, identities[self.handler_storage.value], self.mode_storage.value)

    def execute(self, name, args):
        result = getattr(self.lib, 'dxball_' + name)(*args)
        return result or 0


class Target(Script, TargetOracle):
    ALLOCATE, RELEASE, PRIMARY, SECONDARY = 0x509000, 0x509100, 0x509200, 0x509300
    CREATE = 0x509400

    def __init__(self):
        TargetOracle.__init__(self)
        # None of the eight original entries or their original internal calls
        # is hooked; remove unrelated inherited board/file service hooks.
        for hook in self._hooks:
            self.uc.hook_del(hook)
        self._hooks = []
        self.write_u32(0x441318, self.ALLOCATE)
        self.write_u32(0x441314, self.RELEASE)
        self.write_u32(0x441328, self.CREATE)
        for address, callback in ((self.ALLOCATE, self.allocate_hook),
                                  (self.RELEASE, self.release_hook),
                                  (self.PRIMARY, self.handler_hook),
                                  (self.SECONDARY, self.handler_hook),
                                  (self.CREATE, self.create_hook)):
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, callback, begin=address, end=address))
        section = next(s for s in self.pe.sections if s.Name.rstrip(b'\0') == b'.text')
        self.text_address = self.base + section.VirtualAddress
        self.text_bytes = self.read(self.text_address, section.Misc_VirtualSize)
        self.instruction_limit = 100000

    def set_heap(self, value):
        self.write_u32(HEAP, value)

    def set_mode(self, value):
        self.write_u32(MODE, value & 0xFFFFFFFF)

    def set_handler(self, identity):
        self.write_u32(HANDLER, {'primary': self.PRIMARY, 'secondary': self.SECONDARY, None: 0}[identity])

    def globals(self):
        return (self.read_u32(HEAP), {self.PRIMARY: 'primary', self.SECONDARY: 'secondary', 0: None}[self.read_u32(HANDLER)],
                C.c_int(self.read_u32(MODE)).value)

    def create_hook(self, uc, address, size, userdata):
        self._return(self.create_response(*self._args(3)), pop=12)

    def allocate_hook(self, uc, address, size, userdata):
        self._return(self.allocate_response(*self._args(3)), pop=12)

    def release_hook(self, uc, address, size, userdata):
        self._return(self.release_response(*self._args(3)) & 0xFFFFFFFF, pop=12)

    def handler_hook(self, uc, address, size, userdata):
        identity = 'primary' if address == self.PRIMARY else 'secondary'
        self._return(self.handler_response(identity, self._args(1)[0]) & 0xFFFFFFFF)

    def execute(self, name, args):
        result = self.call(ENTRIES[name], *args)
        # The inherited call checks original cdecl stack/callee-saved state.
        assert self.read(self.text_address, len(self.text_bytes)) == self.text_bytes
        return 0 if name in ('runtime_delete', 'heap_release') else result


def fixtures():
    success = 0x81234567  # Full pointer result, including its high target bit.
    scenarios = [
        ('success', dict(allocations=[success])),
        ('missing-handler', dict(allocations=[0], handler=None)),
        ('handler-stop', dict(allocations=[0], handlers=[dict(result=0)])),
        ('retry-positive', dict(allocations=[0, success], handlers=[dict(result=7)])),
        ('retry-negative', dict(allocations=[0, success], handlers=[dict(result=-17)])),
        ('many-retries', dict(allocations=[0]*17+[success], handlers=[dict(result=(-3 if i % 2 else 8)) for i in range(17)])),
        ('remove-handler', dict(allocations=[0, 0], handlers=[dict(result=1, handler=None)])),
        ('replace-handler-heap', dict(allocations=[0, 0, success], handlers=[dict(result=5, handler='secondary', heap=0xABCDEF01), dict(result=-3, heap=0)])),
        ('stop-changes-heap', dict(allocations=[0], handlers=[dict(result=0, heap=0xFFFFFFFF)])),
    ]
    for name in ('runtime_new', 'allocate_with_handler'):
        for size in (0, 1, 8, 16, 32, 52, 60, 72, 128, 0x7FFFFFFF, 0x80000000, 0xFFFFFFE0, 0xFFFFFFE1, 0xFFFFFFFF):
            for enabled in ((1,) if name == 'runtime_new' else (0, 1, -1)):
                for scenario, script in scenarios:
                    # Disabled requests stop on their first failure; later
                    # responses are intentionally unused, not modeled loops.
                    yield dict(name=name, family=scenario, args=[size] if name == 'runtime_new' else [size, enabled], **script)
    for size in (0, 1, 60, 0xFFFFFFE0, 0xFFFFFFE1, 0xFFFFFFFF):
        for result in (0, success):
            yield dict(name='heap_allocate', family='direct-physical-forward', args=[size], allocations=[result])
        for result in (0, 1, -1, -2147483648, 2147483647):
            yield dict(name='call_new_handler', family='direct-handler', args=[size], handlers=[dict(result=result)])
        yield dict(name='call_new_handler', family='null-handler', args=[size], handler=None)
    for name in ('heap_release', 'runtime_delete'):
        for memory in (0, 1, success, 0xFFFFFFFF):
            for heap in (0, 0x12345000, 0xFFFFFFFF):
                for result in (0, 1, -1):
                    yield dict(name=name, family='release-null-or-bool', args=[memory], heap=heap, release_result=result)


def producer_fixtures():
    """Extend the saved six-entry controls without replacing their execution."""
    success = 0x81234567
    scenarios = [
        ('success', dict(allocations=[success])),
        ('missing-handler', dict(allocations=[0], handler=None)),
        ('handler-stop', dict(allocations=[0], handlers=[dict(result=0)])),
        ('retry-positive', dict(allocations=[0, success], handlers=[dict(result=7)])),
        ('retry-negative', dict(allocations=[0, success], handlers=[dict(result=-17)])),
        ('many-retries', dict(allocations=[0]*17+[success], handlers=[dict(result=(-3 if i % 2 else 8)) for i in range(17)])),
        ('remove-handler', dict(allocations=[0, 0], handlers=[dict(result=1, handler=None)])),
        ('replace-handler-heap', dict(allocations=[0, 0, success], handlers=[dict(result=5, handler='secondary', heap=0xABCDEF01), dict(result=-3, heap=0)])),
        ('stop-changes-heap', dict(allocations=[0], handlers=[dict(result=0, heap=0xFFFFFFFF)])),
        ('disable-mode-during-request', dict(allocations=[0, 0, success], handlers=[dict(result=1, mode=0), dict(result=-2)])),
        ('mutate-mode-during-request', dict(allocations=[0, 0, success], handlers=[dict(result=1, mode=-2147483648), dict(result=-2, mode=2147483647)])),
    ]
    for size in (0, 1, 8, 16, 32, 52, 60, 72, 128, 0x7FFFFFFF, 0x80000000, 0xFFFFFFE0, 0xFFFFFFE1, 0xFFFFFFFF):
        for mode in (0, 1, -1, -2147483648, 2147483647):
            for family, script in scenarios:
                yield dict(name='runtime_malloc', family=family, args=[size], mode=mode, **script)
    for heap in (0, 0x12345000, 0xFFFFFFFF):
        for result in (0, success, 0xFFFFFFFF):
            for handler in (None, 'primary'):
                for mode in (0, -1):
                    yield dict(name='initialize_runtime_heap', family='replace-heap-including-null', args=[],
                               heap=heap, handler=handler, mode=mode, create_result=result)
    yield dict(name='sequence', family='initialize-malloc-release', heap=0xFFFFFFFF,
               handler=None, mode=0, create_result=0xABCDEF01, allocations=[success],
               steps=[dict(name='initialize_runtime_heap', args=[]), dict(name='runtime_malloc', args=[0]),
                      dict(name='heap_release', args=[success])])
    yield dict(name='sequence', family='malloc-reloads-mode-between-calls', mode=0,
               allocations=[0, 0, success], handlers=[dict(result=-9)],
               steps=[dict(name='runtime_malloc', args=[8]), dict(name='runtime_malloc', args=[8], mode=-1)])
    yield dict(name='sequence', family='new-independent-of-malloc-mode', mode=0,
               allocations=[0, 0, success], handlers=[dict(result=-9)],
               steps=[dict(name='runtime_malloc', args=[8]), dict(name='runtime_new', args=[8])])


def main():
    if not __debug__: raise RuntimeError('Allocator comparisons require assertions')
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path, default=ROOT/'build/native/libdxball_core.so')
    args = parser.parse_args()
    library = args.library.resolve(); library_sha = digest(library)
    owner = tomllib.loads((ROOT/'config/source-owners.toml').read_text())['owners']['allocator']
    names = [owner[k] for k in ('source','header','oracle','target_oracle')] + owner['additional_inputs']
    inputs = {n:digest(ROOT/n) for n in names}
    native, target = Native(library), Target()
    cases = dict.fromkeys(ENTRIES, 0); observations = hashlib.sha256(); observation_bytes = 0
    vectors = list(fixtures())+list(producer_fixtures()); assert len(vectors) == 1433
    signal.alarm(120)
    try:
        for fixture in vectors:
            native.reset(fixture); target.reset(fixture)
            for step in fixture.get('steps', [dict(name=fixture['name'], args=fixture['args'])] if 'args' in fixture else []):
                native.events = []; target.events = []
                if 'mode' in step: native.set_mode(step['mode']); target.set_mode(step['mode'])
                nr = native.execute(step['name'], step['args']); tr = target.execute(step['name'], step['args'])
                assert not native.errors and not target.errors, (fixture,native.errors,target.errors)
                assert (nr,native.events,native.globals()) == (tr,target.events,target.globals()), (fixture,nr,tr,native.events,target.events)
                raw = json.dumps(dict(fixture=fixture,step=step,result=tr,events=target.events,globals=target.globals()),separators=(',',':')).encode()+b'\n'
                observations.update(raw); observation_bytes += len(raw); cases[step['name']] += 1
        # Native-width pointer forwarding and typed size_t boundaries have no
        # corresponding x86 execution claim.
        memory, heap_object = C.create_string_buffer(1), C.create_string_buffer(1)
        pointer, heap = C.addressof(memory), C.addressof(heap_object)
        native.reset(dict(heap=heap,handler=None,allocations=[pointer]))
        assert native.execute('runtime_new',[1]) == pointer and not native.errors
        assert native.events == [('HeapAlloc',heap,0,1)]
        native.reset(dict(heap=heap,handler=None,release_result=0))
        native.execute('runtime_delete',[pointer]); assert not native.errors
        assert native.events == [('HeapFree',heap,0,pointer)]
        native.reset(dict(heap=0,handler=None,create_result=heap))
        assert native.execute('initialize_runtime_heap',[]) == heap and not native.errors
        assert native.globals() == (heap,None,0) and native.events == [('HeapCreate',1,0x1000,0)]
        host_controls = 3
        for name in ('dxball_malloc_bytes','dxball_new_bytes'):
            fn = getattr(native.lib,name); fn.argtypes=[C.c_size_t]; fn.restype=C.c_void_p
            native.reset(dict(heap=heap,handler=None,allocations=[pointer]))
            assert fn(0) == pointer and native.events == [('HeapAlloc',heap,0,1)] and not native.errors
            host_controls += 1
            if C.sizeof(C.c_size_t)>4:
                native.events=[]
                assert fn(1<<32) is None and native.events == []
                host_controls += 1
    finally: signal.alarm(0)
    assert inputs == {n:digest(ROOT/n) for n in names} and digest(library)==library_sha
    assert sum(cases.values()) == 1437
    report=dict(status='pass',cases=cases,fixtures=len(vectors),total=sum(cases.values()),
                inputs=inputs,library_sha256=library_sha,target_sha256=target.target_sha256,
                observations_sha256=observations.hexdigest(),observation_bytes=observation_bytes,
                native_only_controls=host_controls,
                limits=['Controlled heap/new-handler APIs; no physical Windows heap claim.',
                        'Original bodies and cdecl stack/callee-saved ABI execute unchanged.',
                        'Typed host-width controls are separate; exactness is not established.'])
    path=ROOT/'build/reports/allocator-differential.json';path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if __name__ == '__main__': main()
