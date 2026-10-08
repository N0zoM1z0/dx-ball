#!/usr/bin/env python3
"""Execute original projectile/fire queue entries and the ignition consumer."""
import argparse
import ctypes as C
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from test_core_differential import Harness, CoreNative, SHAPES
from test_gameplay_differential import Allocate, Ops
from unicorn.x86_const import UC_X86_REG_ECX
from windows_runtime import verified_originals, digest

ENTRIES = {'append_projectile':0x413410, 'begin_projectiles':0x410130,
           'advance_projectile':0x410230, 'remove_projectile':0x4134D0,
           'append_fire_effect':0x413670, 'begin_fire_effects':0x410030,
           'advance_fire_effect':0x413870, 'remove_fire_effect':0x413790,
           'retire_projectile':0x4134B0, 'ignite_balls':0x415630}
OWNERS = {'projectiles':('projectile','projectiles',4),
          'fire':('fire_effect','fire_effects',3)}


def cursor(h, owner, index):
    n, t = h.n, h.t
    node_type = SHAPES[owner][1]
    native = n.owners[owner].first
    target = t.read_u32(SHAPES[owner][0] + 4)
    if index is None:
        native = C.POINTER(node_type)()
        target = 0
    else:
        for _ in range(index):
            native = native.contents.next
            target = t.read_u32(target + SHAPES[owner][2])
    n.owners[owner].current = native
    t.write_u32(SHAPES[owner][0], target)


def seed(h, owner, length, position, salt):
    h.seed()
    count = 13 if owner == 'balls' else OWNERS[owner][2]
    for index in range(length):
        # Every payload field is distinct; helper entries must leave it intact.
        payload = [(-1 if field % 2 else 1) * (salt + 101 * index + field)
                   for field in range(count)]
        h.add(owner, payload)
    cursor(h, owner, position)
    h.n.events = []; h.t.events = []


def execute(h, name, owner=None):
    function = getattr(h.n.lib, 'dxball_' + name)
    if owner:
        result = function(C.byref(h.n.owners[owner]))
        h.t.uc.reg_write(UC_X86_REG_ECX, SHAPES[owner][0])
    else:
        result = function()
    target_result = h.t.call(ENTRIES[name])
    if name != 'ignite_balls':
        assert result == target_result, (name, result, target_result)
    h.compare(('core-queues', name))
    return dict(entry=name, result=result, queue=h.n.queue(owner or ('balls' if name=='ignite_balls' else 'projectiles')),
                events_sha256=hashlib.sha256(json.dumps(h.n.events,separators=(',',':')).encode()).hexdigest(),
                globals_sha256=hashlib.sha256(json.dumps(h.n.observed(),separators=(',',':')).encode()).hexdigest())


def main():
    if not __debug__:
        raise RuntimeError('Core queue comparisons require Python assertions; do not use -O.')
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fail-allocator', choices=('projectiles','fire'))
    args = parser.parse_args()
    library = ROOT / 'build/native/libdxball_core.so'
    if args.fail_allocator:
        n = CoreNative(library)
        failure = Allocate(lambda size: None)
        Ops.in_dll(n.lib,'dxball_gameplay_ops').allocate_node = failure
        singular = OWNERS[args.fail_allocator][0]
        getattr(n.lib,'dxball_append_' + singular)(C.byref(n.owners[args.fail_allocator]))
        raise AssertionError('failed allocation returned')
    with session_lock():
        originals = verified_originals()
        library_sha256 = digest(library)
        inputs = {str(p.relative_to(ROOT)):digest(p) for p in sorted((ROOT/'src').glob('*.[ch]'))}
        for module in tuple(sys.modules.values()):
            filename = getattr(module,'__file__',None)
            if filename:
                p = Path(filename).resolve()
                if p.is_relative_to(ROOT) and p.suffix=='.py': inputs[str(p.relative_to(ROOT))]=digest(p)
        for name in ('config/target.toml','config/assets.csv','config/tools.lock.toml',
                     'requirements-analysis.txt','scripts/repo-python','scripts/verify-python.py',
                     'scripts/verify-target.py','scripts/ghidra.py'):
            inputs[name]=digest(ROOT/name)
        h = Harness(library)
        for name in ('retire_projectile','ignite_balls'):
            function=getattr(h.n.lib,'dxball_'+name)
            function.argtypes=[];function.restype=None if name=='ignite_balls' else C.c_int32
        code=h.t.read(0x401000,0x1f000)
        counts=dict.fromkeys(ENTRIES,0);vectors=[];connected=[]
        for owner,(singular,plural,_) in OWNERS.items():
            names=('append_'+singular,'begin_'+plural,'advance_'+singular,'remove_'+singular)
            for length in range(6):
                for position in (None,*range(length)):
                    for salt in (7,2147480000):
                        for name in names:
                            seed(h,owner,length,position,salt)
                            row=execute(h,name,owner)
                            row.update(owner=owner,length=length,cursor=position,payload_seed=salt)
                            vectors.append(row);counts[name]+=1
            # Actual target exit, plus native subprocess: no allocator body is replaced by source claims.
            seed(h,owner,0,None,7)
            child=subprocess.run([ROOT/'scripts/repo-python',Path(__file__).resolve(),
                                  '--fail-allocator',owner],capture_output=True)
            assert child.returncode==1 and not child.stdout and not child.stderr,(owner,child)
            h.t.fail_allocation=True;h.t.exit_status=None
            h.t.uc.reg_write(UC_X86_REG_ECX,SHAPES[owner][0])
            try:h.t.call(ENTRIES[names[0]])
            except AssertionError:assert h.t.exit_status==1
            else:raise AssertionError('target failed allocation returned')
            assert h.t.read(SHAPES[owner][0],12)==bytes(12)
            h.t.fail_allocation=False;counts[names[0]]+=1
            vectors.append(dict(entry=names[0],owner=owner,failure='allocation',exit_status=1))
            # Connected topology/cursor transitions include removal followed by advance.
            for position in (None,0,1,2):
                seed(h,owner,3,position,7)
                trace=[]
                for name in (names[3],names[2],names[0],names[1],names[3],names[2],names[3],names[2]):
                    h.n.events=[];h.t.events=[]
                    trace.append(execute(h,name,owner))
                connected.append(dict(owner=owner,initial_cursor=position,trace=trace))
        for length in range(6):
            for position in (None,*range(length)):
                for salt in (7,2147480000):
                    for count in (-1,0,1,5,100):
                        seed(h,'projectiles',length,position,salt);h.setv('projectile_count',count)
                        row=execute(h,'retire_projectile');assert h.n.extra[0x43A900].value==count-1
                        row.update(length=length,cursor=position,count_before=count,payload_seed=salt)
                        vectors.append(row);counts['retire_projectile']+=1
                    seed(h,'balls',length,position,salt)
                    row=execute(h,'ignite_balls')
                    node=h.n.owners['balls'].first
                    while node:
                        assert node.contents.sprite==61
                        node=node.contents.next
                    row.update(length=length,cursor=position,payload_seed=salt)
                    vectors.append(row);counts['ignite_balls']+=1
        assert sum(counts.values())==590 and len(vectors)==590
        assert len(connected)==8 and sum(len(x['trace']) for x in connected)==64
        assert h.t.read(0x401000,0x1f000)==code
        assert originals==verified_originals()
        assert inputs=={name:digest(ROOT/name) for name in inputs}
        assert digest(library)==library_sha256
        report=dict(status='pass',target_sha256=h.t.target_sha256,library_sha256=library_sha256,
                    inputs=inputs,originals=originals,cases=counts,total=sum(counts.values()),
                    connected_calls=64,connected_calls_are_separate=True,vectors=vectors,connected=connected,
                    immutable_code_sha256=hashlib.sha256(code).hexdigest(),
                    scope='Complete unmodified original entries versus maintained native C; valid typed roots, untouched payload, lifetime, cursor, globals and full integer returns.',
                    limitations=['Host allocation/release callbacks are dependency bridges; original CRT bodies are outside these helper claims.',
                                 'Finite count decrement excludes signed overflow; malformed lists and invalid backing are outside scope.',
                                 'Connected transition calls are separate from direct acceptance; no full campaign or physical API claim.'])
        out=ROOT/'build/reports/core-queues-differential.json';out.parent.mkdir(parents=True,exist_ok=True)
        out.write_text(json.dumps(report,indent=2)+'\n')
        print('Core queue entries:',report['total'],'direct cases;',report['connected_calls'],'separate connected calls')


if __name__=='__main__':main()
