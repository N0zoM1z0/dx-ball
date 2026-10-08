#!/usr/bin/env python3
"""Probe the maintained Windows adapter/default allocator using built profiles."""
import hashlib
import json
import os
import re
from pathlib import Path
import shutil
import subprocess
import sys
import tomllib
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
from legacy_toolchain import Toolchain,session_lock,windows_path
from resource_limits import limit_cpu

def digest(p):
    with Path(p).open('rb') as f:return hashlib.file_digest(f,'sha256').hexdigest()

def main():
    if not __debug__:raise RuntimeError('Windows allocator probes require assertions')
    limit_cpu()
    with session_lock():
        tool=Toolchain();tool.verify(execute=True)
        output=ROOT/'build/probes/windows-allocator';output.mkdir(parents=True,exist_ok=True)
        probe=ROOT/'tests/windows_allocator_binding.c'
        inputs={}
        def bind(path, expected=None):
            path=Path(path).resolve(); name=str(path); value=digest(path)
            assert expected is None or expected==value,name
            assert name not in inputs or inputs[name]==value,('Changed bound input',name)
            inputs[name]=value
        for path in sorted((ROOT/'src').glob('*.[ch]')):bind(path)
        for p in (Path(__file__),probe,ROOT/'CMakeLists.txt',ROOT/'config/match-units.toml',ROOT/'config/tools.lock.toml',ROOT/'scripts/legacy_toolchain.py',ROOT/'scripts/resource_limits.py'):
            bind(p)
        meta=ROOT/'build/vc40/build.json';raw=meta.read_bytes();bind(meta,hashlib.sha256(raw).hexdigest());build=json.loads(raw)
        for n,h in build['inputs'].items():bind(ROOT/n,h)
        assert build['compiler_sha256']==tool.lock['compiler_sha256']
        vc_objects=[ROOT/'build/vc40'/(p.stem+'.obj') for p in sorted((ROOT/'src').glob('*.c')) if p.stem not in ('board_inspector','resource_inspector','windows_entry')]
        for p in vc_objects:bind(p)
        mingw=Path(shutil.which('i686-w64-mingw32-gcc')).resolve();bind(mingw)
        directory=ROOT/'build/windows-i686'
        archive=directory/'libdxball_core.dll.a';dll=directory/'libdxball_core.dll'
        adapter=directory/'CMakeFiles/dxball.dir/src/windows_adapter.c.obj'
        for p in (archive,dll,adapter):bind(p)
        runtime_tools={name:Path(shutil.which(name,path=tool.env.get('PATH'))).resolve() for name in ('xvfb-run','wine','Xvfb','xauth')}
        for path in runtime_tools.values():bind(path)
        # Bind actual compiler engine/header/link inputs before compiling. VC4
        # components and SDK trees are hash-attested by Toolchain.verify.
        for name in ('cc1','as','collect2','ld'):
            value=subprocess.check_output([str(mingw),'-print-prog-name='+name],text=True).strip()
            p=Path(value) if Path(value).is_file() else Path(shutil.which(value));p=p.resolve();bind(p)
        deps=subprocess.check_output([str(mingw),'-std=c90','-I'+str(ROOT/'src'),'-M',str(probe)],text=True)
        import shlex
        for name in shlex.split(deps.partition(':')[2].replace('\\\n',' ')):
            p=Path(name).resolve();bind(p)
        for name in ('crt2.o','crtbegin.o','crtend.o','libmingw32.a','libmingwex.a','libmoldname.a','libmsvcrt.a','libgcc.a','libgcc_eh.a','libpthread.dll.a','libuser32.a','libgdi32.a','libwinmm.a','libkernel32.a','libadvapi32.a','libshell32.a'):
            p=Path(subprocess.check_output([str(mingw),'-print-file-name='+name],text=True).strip()).resolve()
            if not p.is_file():raise RuntimeError('Missing link input: '+name)
            bind(p)
        def verify():
            for n,h in inputs.items():assert digest(n)==h,n
        verify();(output/'inputs-before.json').write_text(json.dumps(inputs,indent=2)+'\n')
        logs=[];products={};executables={};flags=tomllib.loads((ROOT/'config/match-units.toml').read_text())['builds']['boards']['flags']+['/I'+windows_path(ROOT/'src')]
        obj=output/'probe.obj';logs.append(tool.compile(probe,obj,flags).stdout);bind(obj)
        exe=output/'probe-vc40.exe';exe.unlink(missing_ok=True)
        args=['/NOLOGO','/MACHINE:IX86','/SUBSYSTEM:CONSOLE','/INCREMENTAL:NO','/PDB:NONE','/OUT:'+windows_path(exe),windows_path(obj),*map(windows_path,vc_objects),'user32.lib','gdi32.lib','winmm.lib']
        logs.append(tool.run('link.exe',args).stdout);executables['vc40']=exe
        exe=output/'probe-mingw.exe';exe.unlink(missing_ok=True)
        gccobj=output/'probe-mingw.o'
        flags=['-std=c90','-Wall','-Wextra','-Wpedantic','-Werror','-I'+str(ROOT/'src')]
        compiled=subprocess.run([str(mingw),*flags,'-c',str(probe),'-o',str(gccobj)],stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True)
        logs.append(compiled.stdout);(output/'compiler.log').write_text('\n'.join(logs))
        if compiled.returncode:print(compiled.stdout);compiled.check_returncode()
        bind(gccobj)
        linkmap=output/'mingw-link.map'
        command=[str(mingw),str(gccobj),str(adapter),str(archive),'-lwinmm','-luser32','-lgdi32','-static-libgcc','-Wl,-Map,'+str(linkmap),'-o',str(exe)]
        r=subprocess.run(command,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True);logs.append(r.stdout)
        (output/'compiler.log').write_text('\n'.join(logs))
        if r.returncode:print(r.stdout);r.check_returncode()
        synthetic=[]
        generated_name=re.compile(re.escape(exe.name.replace('-', '_').replace('.', '_'))+r'_e?rtr[0-9]{6}\.o')
        for line in linkmap.read_text().splitlines():
            if line.startswith('LOAD '):
                value=line[5:].strip()
                if value=='dll stuff':synthetic.append(value);continue
                # PE auto-import emits these in-memory pseudo-relocation records.
                # Bind the actual linker/map/PE, and never classify a real file
                # as synthetic solely because its name matches this pattern.
                if generated_name.fullmatch(value) and not Path(value).exists():
                    synthetic.append(value);continue
                path=Path(value).resolve();assert str(path) in inputs,('Unbound real link input',str(path))
        bind(linkmap)
        executables['mingw']=exe
        localdll=output/dll.name;shutil.copyfile(dll,localdll);assert digest(localdll)==inputs[str(dll)];bind(localdll,inputs[str(dll)])
        verify()
        for n,p in executables.items():products[str(p)]=digest(p)
        results={};env=dict(tool.env,PULSE_SINK='dxball_reconstruction_silent')
        for n,p in executables.items():
            verify();r=subprocess.run([str(runtime_tools['xvfb-run']),'-a',str(runtime_tools['wine']),str(p)],env=env,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True,timeout=60)
            logs.append(r.stdout);(output/'runtime.log').write_text('\n'.join(logs))
            if r.returncode:print(r.stdout);r.check_returncode()
            rows=[s for s in r.stdout.splitlines() if s.startswith('{')];assert len(rows)==1,(n,r.stdout)
            results[n]=json.loads(rows[0]);assert results[n]==dict(status='windows-allocator-binding-pass',pointer_bytes=4,heap_api_bytes=12,creates=1,allocations=4,successful_releases=4)
            assert products[str(p)]==digest(p)
        verify()
        report=dict(status='pass',results=results,inputs=inputs,products=products,compiler_sha256=tool.lock['compiler_sha256'],mingw_link_synthetic_inputs=synthetic,
                    limits=['Actual maintained Windows adapter callbacks and node/sound defaults under Wine; no whole-game or native Windows claim.',
                            'Observer callbacks forward to the saved physical table and confirm four successful releases per profile.',
                            'Listed linker-generated pseudo-relocation records have no independent file identity; their emitter, map and PE are bound.',
                            'HeapDestroy is fixture cleanup only; handler registration and game teardown remain unproved.'])
        p=ROOT/'build/reports/windows-allocator.json';p.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(results,indent=2))

if __name__=='__main__':main()
