#!/usr/bin/env python3
"""Execute configured VC4 and MinGW allocator objects against original x86.

All object sections and relocations are loaded; the external typed heap API
is fixture storage. This is generated-code semantic evidence, not exactness.
"""
import hashlib,json,os,shlex,shutil,struct,subprocess,sys,tomllib
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(ROOT/'scripts'),str(ROOT/'tests')]
from resource_limits import limit_cpu
from legacy_toolchain import Toolchain,session_lock
from coff import parse,region
from test_allocator_differential import Target,ENTRIES,fixtures,producer_fixtures,digest

class CoffTarget(Target):
    """Load every generated section/relocation; preserve original target text."""
    BASE, API = 0x08000000,0x080FF000

    def __init__(self,path):
        super().__init__()
        data,sections,symbols = parse(path)
        self.object_sha256 = hashlib.sha256(data).hexdigest()
        assert len(sections) < 128
        self.uc.mem_map(self.BASE,0x100000)
        addresses = {i+1:self.BASE+i*0x2000 for i in range(len(sections))}
        globals_width = {'_dxball_runtime_heap':4,'_dxball_new_handler':4,
                         '_dxball_malloc_mode':4,'_dxball_heap_api':12}
        common = {name:self.API+i*0x20 for i,name in enumerate(globals_width)}
        def resolve(symbol):
            if symbol['section']==0 and symbol['name'] in common:
                assert symbol['storage']==2 and (symbol['value']==globals_width[symbol['name']] or (symbol['name']=='_dxball_heap_api' and symbol['value']==0)),symbol
                return common[symbol['name']]
            assert symbol['section'] > 0,('Unresolved generated-object dependency',symbol)
            assert symbol['value'] <= sections[symbol['section']-1]['size'],symbol
            return addresses[symbol['section']]+symbol['value']
        self.storage = {}
        for name,width in globals_width.items():
            matches=[s for s in symbols.values() if s['name']==name]
            assert len(matches)==1
            s=matches[0]
            if s['section']>0:assert s['value']+width<=sections[s['section']-1]['size']
            self.storage[name]=resolve(s)
        self.entries = {}
        for name,entry in ENTRIES.items():
            matches = [s for s in symbols.values() if s['name']=='_dxball_'+name and s['section']>0 and s['type']==0x20]
            assert len(matches)==1,(name,matches)
            self.entries[entry] = resolve(matches[0])
        self.sections = []
        for index,section in enumerate(sections,1):
            assert section['size'] <= 0x2000
            code = bytearray(region(data,section['data'],section['size'])) if section['data'] else bytearray(section['size'])
            occupied = set();relocations=[]
            for i in range(section['relocation_count']):
                offset,symbol_index,kind = struct.unpack('<IIH',region(data,section['relocations']+i*10,10))
                assert kind in (6,7,20) and symbol_index in symbols
                assert offset+4 <= len(code) and not any(j in occupied for j in range(offset,offset+4))
                occupied.update(range(offset,offset+4))
                symbol = symbols[symbol_index]
                addend = struct.unpack_from('<I',code,offset)[0]
                value = resolve(symbol)+addend
                if kind==20:value -= addresses[index]+offset+4
                elif kind==7:value -= self.BASE  # i386 DIR32NB image-relative debug data.
                struct.pack_into('<I',code,offset,value & 0xFFFFFFFF)
                relocations.append(dict(offset=offset,type={6:'DIR32',7:'DIR32NB',20:'REL32'}[kind],symbol=symbol['name'],addend=addend,resolved=value & 0xFFFFFFFF))
            if code:self.write(addresses[index],code)
            self.sections.append(dict(section=index,address=addresses[index],bytes=len(code),relocations=relocations,relocated_sha256=hashlib.sha256(code).hexdigest()))
        # Retain each object's actual BSS/common layout: GCC section-relative
        # relocations cannot be redirected by overriding named globals alone.
        assert self.globals()==(0,None,0)
        self.write(self.storage['_dxball_heap_api'],struct.pack('<III',self.CREATE,self.ALLOCATE,self.RELEASE))

    def set_heap(self,value):self.write_u32(self.storage['_dxball_runtime_heap'],value)

    def set_handler(self,identity):
        self.write_u32(self.storage['_dxball_new_handler'],{'primary':self.PRIMARY,'secondary':self.SECONDARY,None:0}[identity])

    def set_mode(self,value):self.write_u32(self.storage['_dxball_malloc_mode'],value & 0xFFFFFFFF)

    def globals(self):
        mode=self.read_u32(self.storage['_dxball_malloc_mode'])
        return (self.read_u32(self.storage['_dxball_runtime_heap']),
                {self.PRIMARY:'primary',self.SECONDARY:'secondary',0:None}[self.read_u32(self.storage['_dxball_new_handler'])],
                mode if mode<0x80000000 else mode-0x100000000)

    def call(self,entry,*args):
        return super().call(getattr(self,'entries',{}).get(entry,entry),*args)

def main():
    if not __debug__:raise RuntimeError('Generated allocator comparisons require assertions')
    limit_cpu()
    with session_lock():
        tool=Toolchain();tool.verify(execute=True)
        manifest=ROOT/'config/match-units.toml';raw=manifest.read_bytes();config=tomllib.loads(raw.decode())['builds']['allocator']
        vc=ROOT/config['object'];compile_path=ROOT/'build/reports/allocator-compile.json';compile_raw=compile_path.read_bytes();compiled=json.loads(compile_raw)
        assert compiled['status']=='pass' and compiled['object_sha256']==digest(vc)
        assert compiled['manifest_sha256']==hashlib.sha256(raw).hexdigest()
        assert compiled['compiler_sha256']==tool.lock['compiler_sha256']
        assert compiled['flags']==config['flags']
        assert (ROOT/compiled['object']).resolve()==vc.resolve()
        inputs={str(manifest):hashlib.sha256(raw).hexdigest(),str(compile_path):hashlib.sha256(compile_raw).hexdigest(),str(vc):digest(vc)}
        def bind(p,value=None):
            p=Path(p).resolve();name=str(p);h=digest(p);assert value is None or h==value,name
            assert name not in inputs or inputs[name]==h,name
            inputs[name]=h
        for n,h in compiled['inputs'].items():bind(ROOT/n,h)
        for p in (Path(__file__),ROOT/'tests/test_allocator_differential.py',ROOT/'tests/target_oracle.py',ROOT/'scripts/coff.py',ROOT/'scripts/legacy_toolchain.py',ROOT/'scripts/resource_limits.py'):bind(p)
        gcc=Path(shutil.which('i686-w64-mingw32-gcc')).resolve();bind(gcc)
        for name in ('cc1','as'):
            value=subprocess.check_output([str(gcc),'-print-prog-name='+name],text=True).strip();p=Path(value) if Path(value).is_file() else Path(shutil.which(value));bind(p)
        flags=['-std=c90','-Wall','-Wextra','-Wpedantic','-Werror','-O2','-I'+str(ROOT/'src')]
        deps=subprocess.check_output([str(gcc),*flags,'-M',str(ROOT/'src/allocator.c')],text=True)
        for n in shlex.split(deps.partition(':')[2].replace('\\\n',' ')):bind(n)
        output=ROOT/'build/probes/allocator-coff';output.mkdir(parents=True,exist_ok=True)
        obj=output/'allocator-mingw.o';command=[str(gcc),*flags,'-c',str(ROOT/'src/allocator.c'),'-o',str(obj)]
        for n,h in inputs.items():assert digest(n)==h,n
        result=subprocess.run(command,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True);(output/'compiler.log').write_text(result.stdout)
        if result.returncode:print(result.stdout);result.check_returncode()
        bind(obj)
        original=Target();products={};vectors=list(fixtures())+list(producer_fixtures());assert len(vectors)==1433
        for profile,path in (('vc40',vc),('mingw',obj)):
            native=CoffTarget(path);assert native.target_sha256==original.target_sha256
            assert native.object_sha256==inputs[str(path.resolve())]
            counts=dict.fromkeys(ENTRIES,0);stream=hashlib.sha256()
            for f in vectors:
                native.reset(f);original.reset(f)
                for step in f.get('steps',[dict(name=f['name'],args=f['args'])] if 'args' in f else []):
                    native.events=[];original.events=[]
                    if 'mode' in step:native.set_mode(step['mode']);original.set_mode(step['mode'])
                    nr=native.execute(step['name'],step['args']);tr=original.execute(step['name'],step['args'])
                    assert not native.errors and not original.errors,(f,native.errors,original.errors)
                    assert (nr,native.events,native.globals())==(tr,original.events,original.globals()),(profile,f,nr,tr,native.events,original.events)
                    stream.update(json.dumps(dict(fixture=f,step=step,result=tr,events=original.events,globals=original.globals()),separators=(',',':')).encode()+b'\n');counts[step['name']]+=1
            assert sum(counts.values())==1437
            products[profile]=dict(object=str(path),object_sha256=native.object_sha256,cases=counts,total=1437,fixtures=1433,sections=native.sections,observations_sha256=stream.hexdigest())
        for n,h in inputs.items():assert digest(n)==h,n
        report=dict(status='pass',target_sha256=original.target_sha256,inputs=inputs,products=products,
                    compiler_sha256=tool.lock['compiler_sha256'],
                    limits=['Compiled shared C objects execute with controlled heap/new-handler providers and complete relocations.',
                            'External heap API has explicit twelve-byte fixture storage; other globals use actual BSS/common sections.',
                            'Two profiles replay the same1437 original calls; not additional direct cases or exact byte acceptance.'])
        path=ROOT/'build/reports/allocator-coff-differential.json';path.write_text(json.dumps(report,indent=2)+'\n')
        print('Allocator generated-object semantic replay:',{n:p['total'] for n,p in products.items()})
if __name__=='__main__':main()
