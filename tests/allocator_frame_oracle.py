"""Connect maintained allocation entries to original x86 frame ownership.

Importing this module does not instantiate an oracle, compile, or replay.
The parent must bind execution identities and acquire the single session lock
before constructing ConnectedHarness. Scope excludes external API implementations.
"""
import ast
import ctypes as C
import hashlib
import os
from pathlib import Path
import sys

from unicorn import UC_HOOK_CODE
from target_oracle import ROOT
from test_campaign_differential import Arena, Native as CampaignNative, Target as CampaignTarget
from test_display_differential import DisplayHarness
from test_gameplay_differential import Allocate as NodeAllocate, Ops
from test_effects_differential import EffectOps, Free
from test_core_differential import SHAPES
from test_allocator_differential import Create, Allocate, Release, Handler, HeapApi, ENTRIES, HEAP, HANDLER, MODE

HEAP_IDENTITY = 0x12345000
GAMEPLAY_SOURCE_SHA = 'd32db7d813d14070df68b649256a3dab7b7d331a3f7918b2b42a391aa575d684'
BOUNDARIES = ('target_oracle.py', 'test_gameplay_differential.py',
              'test_effects_differential.py', 'test_entities_differential.py',
              'test_powerups_differential.py', 'test_core_differential.py',
              'test_runtime_differential.py', 'test_display_differential.py',
              'test_allocator_differential.py')


class Ledger:
    def reset_connection(self):
        self.operations = {}
        self.next_operation = 0
        self.pending_operation = None
        self.remaining_failures = 0
        self.heap_events = []
        self.connection_phase = None

    def arm_failures(self, count):
        assert count >= 0 and self.pending_operation is None
        assert self.remaining_failures == 0
        self.remaining_failures = count

    def attempt(self, heap, flags, size):
        assert heap == HEAP_IDENTITY and flags == 0
        if self.pending_operation is None:
            self.pending_operation = self.next_operation
            self.next_operation += 1
            self.operations[self.pending_operation] = dict(size=size, allocation=None)
        operation = self.pending_operation
        assert self.operations[operation]['size'] == size
        success = self.remaining_failures == 0
        self.heap_events.append(('allocate', operation, heap, flags, size, success))
        if not success:
            self.remaining_failures -= 1
            return None
        memory = Arena.take(self, size)
        row = self.allocations[memory]
        row.update(address=memory, heap=heap, operation=operation, producer=self.connection_phase)
        self.operations[operation]['allocation'] = row
        self.pending_operation = None
        return memory

    def handler_result(self, size):
        operation = self.pending_operation
        assert operation is not None and size == self.operations[operation]['size']
        result = -7  # A negative callback result still requests a retry.
        self.heap_events.append(('handler', operation, size, result))
        return result

    def payload(self, row, native):
        if row['owner'] is not None:
            owner = row['owner']
            expected = C.sizeof(SHAPES[owner][1]) if native else SHAPES[owner][2] + 8
            assert row['size'] == expected
            return SHAPES[owner][2]
        # These reviewed top-level producers create only the declared temporary
        # queue family. A single scratch node may be unlinked before any other
        # external callback observes its published root. Do not infer a family
        # merely from its ambiguous host request size.
        exclusive = {'clone_balls': ('balls', 'clone-scratch'),
                     'spread_explosive_bricks': ('scratch', 'explosive-scratch')}
        assert self.connection_phase in exclusive
        assert row['producer'] == self.connection_phase
        owner, role = exclusive[self.connection_phase]
        expected = C.sizeof(SHAPES[owner][1]) if native else SHAPES[owner][2] + 8
        assert row['size'] == expected, 'Unclassified deletion outside a reviewed producer'
        row['transient'] = role
        return SHAPES[owner][2]

    def record_release(self, heap, flags, memory):
        row = self.allocations[memory]
        assert flags == 0 and row['live'] and row['heap'] == heap == HEAP_IDENTITY
        self.heap_events.append(('release', row['operation'], heap, flags, 1))
        return row

    def role(self, operation):
        row = self.operations[operation]['allocation']
        assert row is not None, 'A successful frame retained an unfinished request'
        return row['owner'] if row['owner'] is not None else row.get('transient')

    def heap_projection(self):
        result = []
        for event in self.heap_events:
            if event[0] == 'create':
                result.append(event)
                continue
            operation = event[1]
            role = self.role(operation)
            assert role is not None, 'Allocation was neither published nor known transient'
            if event[0] == 'allocate':
                _, _, heap, flags, raw_size, success = event
                result.append(('allocate', operation, heap, flags, role, success))
            elif event[0] == 'handler':
                result.append(('handler', operation, role, event[3]))
            else:
                result.append(event)
        return result

    def reset(self):
        if hasattr(self, 'operations'):
            assert self.pending_operation is None
            assert not any(a['live'] for a in self.allocations.values()), 'Fixture reset would hide live ownership'
        super().reset()
        self.reset_connection()
        self.start_arena()
        if hasattr(self, 'entry_calls'):
            self.entry_calls = dict.fromkeys(ENTRIES, 0)

    def ownership_snapshot(self):
        return dict(raw_heap_events=list(self.heap_events), operations={
            operation: dict(request_bytes=request['size'], allocation=dict(request['allocation']))
            for operation, request in self.operations.items()})


class ConnectedNative(Ledger, CampaignNative):
    def __init__(self, library):
        super().__init__(library)
        self.reset_connection()
        self.heap_storage = C.c_void_p.in_dll(self.lib, 'dxball_runtime_heap')
        self.handler_storage = C.c_void_p.in_dll(self.lib, 'dxball_new_handler')
        self.mode_storage = C.c_int.in_dll(self.lib, 'dxball_malloc_mode')

        def protect(function):
            def callback(*args):
                try:
                    return function(*args)
                except BaseException as error:
                    print('Connected heap callback failed: ' + repr(error), file=sys.stderr, flush=True)
                    # Distinguish fixture exceptions from the real game's exit1.
                    os._exit(70)
            return callback

        self.heap_callbacks = (Create(protect(self.heap_create)),
                               Allocate(protect(self.heap_allocate)),
                               Release(protect(self.heap_release)),
                               Handler(protect(self.handler_result)))
        self.heap_api = HeapApi(*self.heap_callbacks[:3])
        self.lib.dxball_bind_heap_api.argtypes = [C.POINTER(HeapApi)]
        self.lib.dxball_bind_heap_api.restype = None
        self.lib.dxball_bind_heap_api(C.byref(self.heap_api))
        self.handler_storage.value = C.cast(self.heap_callbacks[3], C.c_void_p).value
        self.heap_storage.value = HEAP_IDENTITY
        self.mode_storage.value = 0
        self.lib.dxball_new_bytes.argtypes, self.lib.dxball_new_bytes.restype = [C.c_size_t], C.c_void_p
        self.lib.dxball_runtime_delete.argtypes, self.lib.dxball_runtime_delete.restype = [C.c_void_p], None
        self.lib.dxball_initialize_runtime_heap.argtypes = []
        self.lib.dxball_initialize_runtime_heap.restype = C.c_void_p
        self.owner_entries = (C.cast(self.lib.dxball_new_bytes, NodeAllocate),
                              C.cast(self.lib.dxball_runtime_delete, Free))
        Ops.in_dll(self.lib, 'dxball_gameplay_ops').allocate_node = self.owner_entries[0]
        EffectOps.in_dll(self.lib, 'dxball_effect_ops').deallocate_node = self.owner_entries[1]
        self.verify_connection()

    def verify_connection(self):
        assert C.cast(Ops.in_dll(self.lib, 'dxball_gameplay_ops').allocate_node, C.c_void_p).value == C.cast(self.lib.dxball_new_bytes, C.c_void_p).value
        assert C.cast(EffectOps.in_dll(self.lib, 'dxball_effect_ops').deallocate_node, C.c_void_p).value == C.cast(self.lib.dxball_runtime_delete, C.c_void_p).value
        assert self.heap_storage.value == HEAP_IDENTITY and self.mode_storage.value == 0
        assert self.handler_storage.value == C.cast(self.heap_callbacks[3], C.c_void_p).value

    def allocate(self, *unused):
        raise AssertionError('A node fixture callback replaced the maintained allocation chain')

    def free(self, *unused):
        raise AssertionError('A node fixture callback replaced the maintained deletion chain')

    def heap_create(self, flags, initial, maximum):
        assert (flags, initial, maximum) == (1, 0x1000, 0)
        self.heap_events.append(('create', flags, initial, maximum, HEAP_IDENTITY))
        return HEAP_IDENTITY

    def heap_allocate(self, heap, flags, size):
        assert size in {C.sizeof(shape[1]) for shape in SHAPES.values()}
        memory = self.attempt(heap or 0, flags, size)
        if memory is not None:
            C.memset(memory, 0xa5, size)
            self.events.append(('allocate', self.observed()))
        return memory

    def heap_release(self, heap, flags, memory):
        row = self.record_release(heap or 0, flags, memory)
        payload = self.payload(row, True)
        self.events.append(('free-payload', C.string_at(memory, payload).hex(), self.observed()))
        row['live'] = False
        C.memset(memory, 0xdd, row['size'])
        return 1


class ConnectedTarget(Ledger, CampaignTarget):
    ALLOCATE, RELEASE, NEW_HANDLER, CREATE = 0x509600, 0x509610, 0x509620, 0x509630

    def observed(self):
        # CoreNative.observed classifies every published root at each callback.
        # Give the original-side ledger the same observation timing; otherwise
        # a transient clone can be labeled published only on the native side.
        if hasattr(self, 'allocations'):
            for owner in SHAPES:
                self.queue(owner)
        return super().observed()

    def __init__(self):
        super().__init__()
        self.reset_connection()
        # Guard the anonymous delete registration using the reviewed immutable
        # source and its ordering after the named exit hook, rather than a bare
        # inherited-list index. Remove no other frame boundary.
        source = ROOT / 'tests/test_gameplay_differential.py'
        assert hashlib.sha256(source.read_bytes()).hexdigest() == GAMEPLAY_SOURCE_SHA
        hook = self._hooks[self._hooks.index(self.game_hooks[0x417910]) + 1]
        assert hook != self.game_hooks[0x416770]
        self.uc.hook_del(self.game_hooks[0x416770])
        self.uc.hook_del(hook)
        self.removed_allocator_hooks = (self.game_hooks[0x416770], hook)

        reserved = {self.RETURN}
        for filename in BOUNDARIES:
            tree = ast.parse((ROOT / 'tests' / filename).read_text())
            reserved.update(n.value for n in ast.walk(tree)
                            if isinstance(n, ast.Constant) and isinstance(n.value, int)
                            and self.SURFACE <= n.value < self.SURFACE + 0x10000)
        callbacks = (self.ALLOCATE, self.RELEASE, self.NEW_HANDLER, self.CREATE)
        assert len(set(callbacks)) == 4 and not reserved.intersection(callbacks)
        for table, length in ((self.VTABLE, 33), (0x506200, 7), (0x506300, 23)):
            assert not set(self.read_u32(table + i * 4) for i in range(length)).intersection(callbacks)
        for slot, address in ((0x441318, self.ALLOCATE), (0x441314, self.RELEASE), (0x441328, self.CREATE)):
            self.write_u32(slot, address)
        for address, callback in ((self.ALLOCATE, self.heap_allocate),
                                  (self.RELEASE, self.heap_release),
                                  (self.NEW_HANDLER, self.heap_handler),
                                  (self.CREATE, self.heap_create)):
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, callback, begin=address, end=address))
        self.write_u32(HEAP, HEAP_IDENTITY)
        self.write_u32(HANDLER, self.NEW_HANDLER)
        self.write_u32(MODE, 0)
        section = next(s for s in self.pe.sections if s.Name.rstrip(b'\0') == b'.text')
        self.text_address = self.base + section.VirtualAddress
        self.text_bytes = self.read(self.text_address, section.Misc_VirtualSize)
        self.entry_calls = dict.fromkeys(ENTRIES, 0)
        for name, address in ENTRIES.items():
            def observe(uc, address, size, userdata, name=name):
                self.entry_calls[name] += 1
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE, observe, begin=address, end=address))

    def allocate(self, *unused):
        raise AssertionError('A fixture hook replaced original operator new')

    def free(self, *unused):
        raise AssertionError('A fixture hook replaced original operator delete')

    def heap_create(self, *unused):
        flags, initial, maximum = self._args(3)
        assert (flags, initial, maximum) == (1, 0x1000, 0)
        self.heap_events.append(('create', flags, initial, maximum, HEAP_IDENTITY))
        self._return(HEAP_IDENTITY, pop=12)

    def heap_allocate(self, *unused):
        heap, flags, size = self._args(3)
        assert size in {shape[2] + 8 for shape in SHAPES.values()}
        memory = self.attempt(heap, flags, size)
        if memory is not None:
            self.write(memory, b'\xa5' * size)
            self.events.append(('allocate', self.observed()))
        self._return(memory or 0, pop=12)

    def heap_handler(self, *unused):
        self._return(self.handler_result(self._args(1)[0]) & 0xffffffff)

    def heap_release(self, *unused):
        heap, flags, memory = self._args(3)
        row = self.record_release(heap, flags, memory)
        payload = self.payload(row, False)
        self.events.append(('free-payload', self.read(memory, payload).hex(), self.observed()))
        row['live'] = False
        self.write(memory, b'\xdd' * row['size'])
        self._return(1, pop=12)

    def verify_connection(self):
        assert self.read_u32(HEAP) == HEAP_IDENTITY
        assert self.read_u32(HANDLER) == self.NEW_HANDLER and self.read_u32(MODE) == 0
        assert self.read(self.text_address, len(self.text_bytes)) == self.text_bytes


class ConnectedHarness(DisplayHarness):
    def __init__(self, library):
        super().__init__(library, ConnectedNative, ConnectedTarget)

    def compare(self, context):
        super().compare(context)
        self.n.verify_connection()
        self.t.verify_connection()
        assert self.n.pending_operation is None and self.t.pending_operation is None
        assert self.n.remaining_failures == self.t.remaining_failures == 0
        assert self.n.heap_projection() == self.t.heap_projection(), (context, 'heap effects')
        assert self.n.operations.keys() == self.t.operations.keys()
        for operation, native in self.n.operations.items():
            target = self.t.operations[operation]
            nrow, trow = native['allocation'], target['allocation']
            assert nrow is not None and trow is not None
            role = self.n.role(operation)
            assert role == self.t.role(operation)
            assert nrow['live'] == trow['live'] and nrow['heap'] == trow['heap']
            owner = {'clone-scratch': 'balls', 'explosive-scratch': 'scratch'}.get(role, role)
            node = SHAPES[owner]
            assert native['size'] == C.sizeof(node[1]) and target['size'] == node[2] + 8
        attempts = sum(e[0] == 'allocate' for e in self.t.heap_events)
        handlers = sum(e[0] == 'handler' for e in self.t.heap_events)
        releases = sum(e[0] == 'release' for e in self.t.heap_events)
        counts = self.t.entry_calls
        assert counts['runtime_new'] == counts['allocate_with_handler'] == len(self.t.operations)
        assert counts['heap_allocate'] == attempts
        assert counts['call_new_handler'] == handlers
        assert counts['runtime_delete'] == counts['heap_release'] == releases
        assert counts['runtime_malloc'] == 0
        assert counts['initialize_runtime_heap'] == sum(e[0] == 'create' for e in self.t.heap_events)

    def phase(self, name, address):
        self.phase_args(name, address)

    def phase_args(self, name, address, *args):
        self.n.connection_phase = self.t.connection_phase = name
        try:
            result = self.n.call('dxball_' + name, *args)
            target_result = self.t.call(address, *args)
            if result is not None:
                assert result == target_result, (name, 'return value', result, target_result)
            self.compare((name, 'allocator-connected', args))
            return result
        finally:
            self.n.connection_phase = self.t.connection_phase = None

    def initialize_heap(self):
        self.n.call('dxball_initialize_runtime_heap')
        self.t.call(ENTRIES['initialize_runtime_heap'])
        self.compare(('connected-runtime-heap-startup',))

    def recycle_compared(self):
        self.compare(('before-arena-reuse',))
        self.n.recycle()
        self.t.recycle()
