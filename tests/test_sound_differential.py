#!/usr/bin/env python3
"""Run original DirectSound/file/RIFF bodies against the shared C sound owner.

Only imports, COM methods and CRT allocation/termination are controlled. Mock
freed blocks remain mapped as tombstones; this observes dangling pointers without
claiming subsequent dereferences are valid. No sound-controller model is used.
"""
from source_state import source_global
import argparse
import ctypes as C
import hashlib
import itertools
import json
import os
from pathlib import Path
import struct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_EFLAGS,
    UC_X86_REG_EBX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)
from target_oracle import ROOT, TargetOracle

U=C.c_uint32; I=C.c_int32; P=C.c_void_p; Z=C.c_size_t
class Sound(C.Structure):
    _fields_=[('buffer',P),('filename',C.c_char*20),('frequency',U),('pan',I),('volume',I)]
class Descriptor(C.Structure):
    _fields_=[('size',U),('flags',U),('bytes',U),('reserved',U),('format',P)]
ENTRIES={'initialize_sound':0x405120,'prepare_sound':0x4050f0,'pause_sound':0x4057d0,
    'release_audio':0x406270,'release_sounds':0x4058b0,'stop_all_sounds':0x405eb0,
    'load_sound':0x405990,'update_sound':0x405d80,'release_sound':0x4058f0,
    'play_sound':0x405c50,'stop_sound':0x405ef0,'restore_sounds':0x406180,
    'parse_wave':0x406290,'create_sound_buffer':0x4063a0,'load_binary_file':0x403320,
    'set_sound_frequency':0x405fa0,'set_sound_pan':0x406040,'set_sound_volume':0x4060e0}
APIS=[('create_device','DirectSoundCreate',I,[P,P,P]),
    ('create_file','CreateFileA',Z,[P,U,U,P,U,U,Z]),('file_size','GetFileSize',U,[Z,P]),
    ('read_file','ReadFile',I,[Z,P,U,P,P]),('close_handle','CloseHandle',I,[Z]),
    ('allocate',None,P,[Z]),('deallocate',None,None,[P]),
    ('message_box','MessageBoxA',I,[Z,P,P,U]),('exit',None,None,[I])]
DEVICE={2:('device_release',U,[P]),3:('create_buffer',I,[P,P,P,P]),
    6:('cooperate',I,[P,Z,U])}
BUFFER={2:('buffer_release',U,[P]),6:('get_volume',I,[P,P]),7:('get_pan',I,[P,P]),
    8:('get_frequency',I,[P,P]),9:('get_status',I,[P,P]),
    11:('lock',I,[P,U,U,P,P,P,P,U]),12:('play',I,[P,U,U,U]),
    13:('set_position',I,[P,U]),15:('set_volume',I,[P,I]),16:('set_pan',I,[P,I]),
    17:('set_frequency',I,[P,U]),18:('stop',I,[P]),19:('unlock',I,[P,P,U,P,U]),
    20:('restore',I,[P])}

def words(*xs):return struct.pack('<'+'I'*len(xs),*(x&0xffffffff for x in xs))
def json_bytes(value):
    if isinstance(value,bytes):return {'bytes_hex':value.hex()}
    raise TypeError(type(value).__name__)
def chunk(tag,data):return tag+words(len(data))+data+(b'\0' if len(data)&1 else b'')
def wave(data=bytes(range(31)),fmt=None,extras=()):
    fmt=fmt if fmt is not None else struct.pack('<HHIIHH',1,1,11025,11025,1,8)
    body=b'WAVE'+b''.join(extras)+chunk(b'fmt ',fmt)+chunk(b'data',data)
    return b'RIFF'+words(len(body))+body

class Backend:
    def reset(self,data=None,fail=None,split=None,responses=(6,),device=True,primary=False,
              draw=False,status=0,partial_buffer=False):
        self.heap=0xa00000;self.retained=[];self.allocations={};self.freed=set()
        self.events=[];self.errors=[];self.counts={};self.buffers={};self.sequence=0
        self.fail=fail or {};self.split=split;self.responses=list(responses)
        self.status=status;self.partial_buffer=partial_buffer;self.terminal=None
        self.rebind_on_set=None
        self.file=data if data is not None else wave()
        self.file=self.file if len(self.file)>=64 else self.file+bytes(64-len(self.file))
        self.put_device(0);self.put_primary(0);self.put_draw(0xabc if draw else 0)
        for slot in range(50):self.put_slot(slot,0)
        self.device=self.object('device',self.device_table)
        self.put_device(self.device if device else 0)
        if primary:self.put_primary(self.buffer('primary',0))
        self.path=self.alloc('path',64);self.write(self.path,b'oracle.wav\0')
        self.source=self.alloc('source',max(4096,len(self.file)+512),0x63);self.write(self.source,self.file)
        self.output=self.alloc('output',max(32,3*self.pointer_size),0x41)
        self.new_heap_count=0
    def alloc(self,name,size,fill=0xa5):
        actual=max(size,1)
        if self.native:
            memory=C.create_string_buffer(actual+16);self.retained.append(memory);p=C.addressof(memory)
        else:
            p=self.heap;self.heap+=(actual+0x100f)&~0xfff
            assert self.heap<0x1900000
        self.allocations[p]=(name,actual)
        self.write(p,bytes([fill])*actual+b'\x97'*16);return p
    def object(self,name,table):
        p=self.alloc(name,self.pointer_size);self.put_pointer(p,table);return p
    def buffer(self,name,size,frequency=11025,pan=-77,volume=-123):
        p=self.object(name,self.buffer_table)
        payload=self.alloc(name+'_data',max(size,1),0x6b)
        self.buffers[p]=dict(name=name,size=size,data=payload,frequency=frequency,pan=pan,
            volume=volume,status=self.status,released=False,position=0x78)
        return p
    def record(self,slot,buffer=True,name=b'oracle.wav'):
        p=self.alloc('record'+str(slot),self.record_size+1)
        self.put_pointer(p,self.buffer('old'+str(slot),31) if buffer else 0)
        self.write(p+self.pointer_size,name+b'\0')
        for field,value in (('frequency',9000+slot),('pan',-slot),('volume',-99)):
            self.put_u32(p+self.field(field),value)
        self.put_slot(slot,p);return p
    def field(self,name):
        return getattr(Sound,name).offset if self.native else dict(frequency=24,pan=28,volume=32)[name]
    def get_pointer(self,p):return int.from_bytes(self.read(p,self.pointer_size),'little')
    def put_pointer(self,p,v):self.write(p,int(v).to_bytes(self.pointer_size,'little'))
    def read_u32(self,p):return int.from_bytes(self.read(p,4),'little')
    def put_u32(self,p,v):self.write(p,words(v))
    def role(self,p):
        if not p:return 0
        if p==int.from_bytes(b'\xa5'*self.pointer_size,'little'):return ('uninitialized',)
        if p in (0x1234,0xabc,0x7101):return p
        for base,(name,size) in self.allocations.items():
            if base<=p<=base+size:
                offset=p-base
                # Host pointers occupy eight bytes in the same logical record.
                if (name.startswith('record') or name.startswith('heap')) and size==self.record_size+1:
                    if offset>=self.pointer_size:offset=offset-self.pointer_size+4
                return(name,offset)
        raise AssertionError(('unknown pointer',hex(p)))
    def string(self,p):
        output=bytearray()
        for i in range(4096):
            x=self.read(p+i,1)
            if x==b'\0':return bytes(output)
            output.extend(x)
        raise AssertionError('unterminated fixture string')
    def record_state(self,p):
        if not p:return None
        return(self.role(p),self.role(self.get_pointer(p)),self.read(p+self.pointer_size,20),
            *(self.read_u32(p+self.field(f)) for f in ('frequency','pan','volume')),
            p in self.freed,self.read(p+self.record_size,1))
    def snapshot(self):
        return(self.role(self.get_device()),self.role(self.get_primary()),
            tuple(self.record_state(self.get_slot(i)) for i in range(50)),
            tuple((v['name'],v['size'],self.read(v['data'],max(v['size'],1)),v['frequency'],
                v['pan']&0xffffffff,v['volume']&0xffffffff,v['status'],v['released'],v['position'])
                for v in self.buffers.values()),tuple(sorted(self.role(p) for p in self.freed)))
    def outcome(self,name):
        self.counts[name]=self.counts.get(name,0)+1
        return self.fail.get((name,self.counts[name]),self.fail.get(name,0))
    def api(self,name,args):
        args=tuple(x or 0 for x in args);error=self.outcome(name);event=[name];result=error
        if name=='allocate':
            size=args[0];normalized=37 if size==self.record_size+1 else size
            event+=[normalized]
            result=0 if error else self.alloc('heap'+str(self.new_heap_count),size)
            self.new_heap_count+=1
        elif name=='deallocate':
            event+=[self.role(args[0])]
            if args[0]:self.freed.add(args[0])
        elif name=='create_device':
            assert args[0]==args[2]==0
            event+=[0,0];self.put_pointer(args[1],self.device);result=error
        elif name=='create_file':
            assert args[1:]==(0x80000000,1,0,3,0x80,0),args
            event+=[self.string(args[0]),*args[1:]]
            result=(1<<(8*self.pointer_size))-1 if error else 0x7101
        elif name=='file_size':
            assert args==(0x7101,0);event+=list(args);result=len(self.file)
        elif name=='read_file':
            assert args[0]==0x7101 and args[2]==len(self.file) and args[4]==0
            event += [args[0],self.role(args[1]),args[2],0]
            count=self.fail.get('short_read',len(self.file))
            if not error:self.write(args[1],self.file[:count]);self.put_u32(args[3],count)
            result=0 if error else 1
        elif name=='close_handle':
            assert args==(0x7101,);event+=list(args);result=0 if error else 1
        elif name=='message_box':
            event += [args[0],self.string(args[1]),self.string(args[2]),args[3]]
            assert self.responses,'unbounded retry fixture'
            result=self.responses.pop(0)
        elif name=='exit':
            self.events.append(('exit',args[0]));self.terminal=args[0]
            if self.native:
                assert self.exit_pipe is not None
                output=json.dumps(dict(events=self.events,state=self.snapshot(),code=args[0]),default=json_bytes).encode()
                while output:output=output[os.write(self.exit_pipe,output):]
                os._exit(args[0])
            self.uc.emu_stop();return 0
        elif name=='device_release':
            assert args==(self.device,);event+=['device'];result=0
        elif name=='cooperate':
            assert args==(self.device,0x777,1);event+=['device',*args[1:]]
        elif name=='create_buffer':
            device,desc,output,outer=args;assert device==self.device and outer==0
            size,flags,n,reserved=struct.unpack('<4I',self.read(desc,16))
            fmt=self.get_pointer(desc+16)
            assert size==20 and reserved==0 and flags in (1,0xe2)
            event += [size,flags,n,reserved,self.role(fmt),0]
            if not error or self.partial_buffer:
                frequency=self.read_u32(fmt+4) if fmt else 11025
                buffer=self.buffer(('new'+str(self.sequence)) if flags==0xe2 else 'primary',n,frequency)
                self.sequence+=1;self.put_pointer(output,buffer)
        else:
            buffer=args[0];v=self.buffers[buffer];event += [v['name']]
            if name=='buffer_release':v['released']=True;result=0
            elif name.startswith('get_'):
                field=name[4:];self.put_u32(args[1],v[field]);event+=[v[field]&0xffffffff]
            elif name=='lock':
                assert args[1:3]==(0,v['size']) and args[7]==0
                n=v['size'];first=n if self.split is None else min(n,self.split);second=n-first
                self.put_pointer(args[3],v['data']);self.put_u32(args[4],first)
                self.put_pointer(args[5],v['data']+first if second else 0);self.put_u32(args[6],second)
                event += [0,n,first,second,0]
            elif name=='unlock':
                assert args[1]==v['data'] and args[2]+args[4]==v['size']
                assert args[3]==(v['data']+args[2] if args[4] else 0)
                event += [args[2],args[4],self.read(v['data'],v['size']).hex()]
            elif name=='play':
                assert args[1:3]==(0,0) and args[3] in (0,1)
                event+=list(args[1:])
                if not error:v['status']=(v['status']&~4)|1|(4 if args[3] else 0)
            elif name=='restore':
                if not error:v['status']&=~2
            elif name=='stop':
                if not error:v['status']&=~5
            elif name.startswith('set_'):
                field=name[4:];event+=[args[1]&0xffffffff]
                if not error:v[field]=args[1]
                if self.rebind_on_set is not None:
                    slot,replacement=self.rebind_on_set
                    self.put_slot(slot,replacement)
                    event+=['rebind',slot,self.role(replacement)]
                    self.rebind_on_set=None
            else:raise AssertionError(name)
        self.events.append(tuple(event));return result or 0
    def guards(self):
        for p,(name,size) in self.allocations.items():
            assert self.read(p+size,16)==b'\x97'*16,(name,'allocation overrun')

class Native(Backend):
    native=True;pointer_size=C.sizeof(P);record_size=C.sizeof(Sound)
    def __init__(self,library):
        self.lib=C.CDLL(str(library));self.callbacks=[];self.exit_pipe=None
        self.device_slot=P.in_dll(self.lib,'dxball_sound_device')
        self.primary_slot=P.in_dll(self.lib,'dxball_primary_sound')
        self.slots=(P*50).in_dll(self.lib,'dxball_sounds')
        self.draw_slot=P.in_dll(self.lib,'dxball_direct_draw')
        table=(P*3).in_dll(self.lib,'dxball_sound_api')
        sound_slots={'create_device':0,'allocate':1,'deallocate':2}
        file_cells={'create_file':'dxball_file_create','file_size':'dxball_file_size',
                    'read_file':'dxball_file_read','close_handle':'dxball_file_close'}
        for name,_,result,args in APIS:
            fn=self.callback(name,result,args)
            if name in sound_slots:table[sound_slots[name]]=C.cast(fn,P).value
            elif name in file_cells:P.in_dll(self.lib,file_cells[name]).value=C.cast(fn,P).value
            elif name=='message_box':(P*24).in_dll(self.lib,'dxball_window_api')[9]=C.cast(fn,P).value
            else:(P*9).in_dll(self.lib,'dxball_platform_ops')[8]=C.cast(fn,P).value
        self.heap_slot=P.in_dll(self.lib,'dxball_runtime_heap')
        P.in_dll(self.lib,'dxball_new_handler').value=None
        I.in_dll(self.lib,'dxball_malloc_mode').value=0
        heap=(P*3).in_dll(self.lib,'dxball_heap_api')
        for slot,name,result,arg in ((1,'allocate',P,Z),(2,'deallocate',I,P)):
            def bind(name,result,arg):
                def cb(heap,flags,value):
                    try:
                        assert (heap or 0)==(self.heap_slot.value or 0) and flags==0
                        response=self.api(name,(value,))
                        return 1 if name=='deallocate' else response
                    except BaseException as exc:
                        self.errors.append(exc);return 0
                fn=C.CFUNCTYPE(result,P,U,arg)(cb);self.callbacks.append(fn);return fn
            heap[slot]=C.cast(bind(name,result,arg),P).value
        self.tables=[]
        for methods,length in ((DEVICE,7),(BUFFER,21)):
            table=(P*length)();self.tables.append(table)
            for slot,(name,result,args) in methods.items():table[slot]=C.cast(self.callback(name,result,args),P).value
        self.device_table=C.addressof(self.tables[0]);self.buffer_table=C.addressof(self.tables[1])
        types={'initialize_sound':[Z],'prepare_sound':[Z],'load_sound':[I,P],
            'update_sound':[I,I,I,I],'play_sound':[I,I,I,I],'release_sound':[I],
            'stop_sound':[I],'parse_wave':[P,P,P,P],'create_sound_buffer':[P,P,P,U],
            'load_binary_file':[P,P,I], 'set_sound_frequency':[I,U],
            'set_sound_pan':[I,I],'set_sound_volume':[I,I]}
        for name in ENTRIES:
            fn=getattr(self.lib,'dxball_'+name);fn.argtypes=types.get(name,[])
            fn.restype=I if name in ('parse_wave','create_sound_buffer') else P if name=='load_binary_file' else None
    def callback(self,name,result,args):
        def cb(*values):
            try:return self.api(name,values)
            except BaseException as exc:
                if name=='exit':os._exit(254)
                self.errors.append(exc);return 0
        fn=C.CFUNCTYPE(result,*args)(cb);self.callbacks.append(fn);return fn
    def read(self,p,n):return C.string_at(p,n)
    def write(self,p,data):C.memmove(p,bytes(data),len(data))
    def get_device(self):return self.device_slot.value or 0
    def put_device(self,p):self.device_slot.value=p
    def get_primary(self):return self.primary_slot.value or 0
    def put_primary(self,p):self.primary_slot.value=p
    def get_slot(self,i):return self.slots[i] or 0
    def put_slot(self,i,p):self.slots[i]=p
    def put_draw(self,p):self.draw_slot.value=p
    def call(self,name,args):
        value=getattr(self.lib,'dxball_'+name)(*args)
        if self.errors:raise self.errors[0]
        self.guards();return value
    def terminating_call(self,name,args):
        reader,writer=os.pipe();pid=os.fork()
        if pid==0:
            os.close(reader);self.exit_pipe=writer
            exit_callback=self.callback('exit',None,[I,P])
            libc=C.CDLL(None);libc.on_exit.argtypes=[type(exit_callback),P];libc.on_exit.restype=I
            assert libc.on_exit(exit_callback,None)==0
            self.call(name,args);os._exit(255)
        os.close(writer);data=bytearray()
        while True:
            part=os.read(reader,65536)
            if not part:break
            data.extend(part)
        os.close(reader);_,status=os.waitpid(pid,0)
        assert os.WIFEXITED(status) and os.WEXITSTATUS(status) not in (254,255)
        result=json.loads(data);assert result['code']==os.WEXITSTATUS(status)
        return result

class Target(TargetOracle,Backend):
    native=False;pointer_size=4;record_size=36
    def __init__(self):
        TargetOracle.__init__(self);self.uc.mem_map(0xa00000,0xf00000)
        self.device_table=0x50a000;self.buffer_table=0x50a100
        imports={i.name.decode():i.address for g in self.pe.DIRECTORY_ENTRY_IMPORT for i in g.imports if i.name}
        self.boundary_hooks=[];index=0
        for name,importname,_,args in APIS:
            address=0x50c000+index*16;index+=1
            if importname:self.write_u32(imports[importname],address)
            else:address={'allocate':0x417770,'deallocate':0x417750,'exit':0x417910}[name]
            self.hook(address,name,len(args),len(args)*4 if importname else 0)
        for methods,table in ((DEVICE,self.device_table),(BUFFER,self.buffer_table)):
            for slot,(name,_,args) in methods.items():
                address=0x50c000+index*16;index+=1;self.write_u32(table+slot*4,address)
                self.hook(address,name,len(args),len(args)*4)
    def hook(self,address,name,count,pop):
        def cb(uc,address,size,user):
            value=self.api(name,self._args(count))
            if name!='exit':self._return(value&0xffffffff,pop=pop)
        self.boundary_hooks.append(self.uc.hook_add(UC_HOOK_CODE,cb,begin=address,end=address))
    def get_device(self):return self.read_u32(0x421098)
    def put_device(self,p):self.write_u32(0x421098,p)
    def get_primary(self):return self.read_u32(0x42109c)
    def put_primary(self,p):self.write_u32(0x42109c,p)
    def get_slot(self,i):return self.read_u32(0x4265d0+i*4)
    def put_slot(self,i,p):self.write_u32(0x4265d0+i*4,p)
    def put_draw(self,p):self.write_u32(0x4228b0,p)
    def call(self,name,args):
        value=TargetOracle.call(self,ENTRIES[name],*args);self.guards();return value
    def terminating_call(self,name,args):
        # Terminal execution is checked separately; there is no simulated return
        # from exit(), and no invented post-exit stack/register contract.
        self.write(self.STACK,b'\xa5'*self.STACK_SIZE)
        sp=self.STACK+self.STACK_SIZE-0x100
        self.write(sp,words(self.RETURN,*args))
        for reg,val in ((UC_X86_REG_EBX,0x12345678),(UC_X86_REG_ESI,0x23456789),
                (UC_X86_REG_EDI,0x34567890),(UC_X86_REG_EBP,0x456789ab)):
            self.uc.reg_write(reg,val)
        self.uc.reg_write(UC_X86_REG_ESP,sp);self.uc.reg_write(UC_X86_REG_EFLAGS,0x202)
        self.uc.emu_start(ENTRIES[name],self.RETURN,count=1000000)
        assert self.terminal is not None and self.uc.reg_read(UC_X86_REG_EIP)==0x417910
        self.guards();return dict(events=self.events,state=self.snapshot(),code=self.terminal)

class Harness:
    def __init__(self,library):
        lib=C.CDLL(str(library))
        for table,length,bindings in (
            ('dxball_platform_ops',9,{0:'prepare_sound',1:'initialize_sound',2:'pause_sound',6:'release_audio'}),
            ('dxball_runtime_ops',15,{7:'load_sound',12:'release_sounds'}),
            ('dxball_gameplay_ops',6,{2:'stop_sound',3:'play_sound'}),
            ('dxball_display_ops',2,{0:'update_sound'})):
            slots=source_global(P*length, lib,table)
            for slot,name in bindings.items():assert slots[slot]==C.cast(getattr(lib,'dxball_'+name),P).value
        self.n=Native(library);self.t=Target();self.cases=dict.fromkeys(ENTRIES,0);self.connected_checks=0
    def reset(self,**kw):self.n.reset(**kw);self.t.reset(**kw)
    def records(self,slots=(0,17,49),buffer=True):
        for b in (self.n,self.t):
            for slot in slots:b.record(slot,buffer)
    def call(self,name,na=(),ta=None,connected=False,terminal=False):
        self.n.events=[];self.t.events=[]
        if terminal:
            n=self.n.terminating_call(name,na);t=self.t.terminating_call(name,ta if ta is not None else na)
            assert n==json.loads(json.dumps(t,default=json_bytes)),(name,'terminal',n,t)
        else:
            nr=self.n.call(name,na);tr=self.t.call(name,ta if ta is not None else na)
            if name=='load_binary_file':assert self.n.role(nr)==self.t.role(tr)
            elif nr is not None:assert (nr&0xffffffff)==tr,(name,nr,tr)
            assert self.n.events==self.t.events,(name,'events',self.n.events,self.t.events)
            ns=self.n.snapshot();ts=self.t.snapshot();assert ns==ts,(name,'state',ns,ts)
        if connected:self.connected_checks+=1
        else:self.cases[name]+=1
    def load(self,slot=17,connected=False,terminal=False):
        self.call('load_sound',(slot,self.n.path),(slot,self.t.path),connected,terminal)
    def parse(self,data):
        self.reset(data=data)
        for b in (self.n,self.t):
            b.put_pointer(b.output,0x1234);b.put_pointer(b.output+b.pointer_size,0x1234)
            b.put_u32(b.output+2*b.pointer_size,0x76543210)
        self.call('parse_wave',(self.n.source,self.n.output,self.n.output+self.n.pointer_size,self.n.output+2*self.n.pointer_size),
            (self.t.source,self.t.output,self.t.output+4,self.t.output+8))
        for offset in (0,1):
            assert self.n.role(self.n.get_pointer(self.n.output+offset*self.n.pointer_size))==self.t.role(self.t.get_pointer(self.t.output+offset*4))
        assert self.n.read_u32(self.n.output+2*self.n.pointer_size)==self.t.read_u32(self.t.output+8)
        assert self.n.read(self.n.source,len(self.n.file))==self.t.read(self.t.source,len(self.t.file))

def checks(library):
    if not __debug__:
        raise RuntimeError('Oracle assertions must stay enabled')
    h=Harness(library)
    assert h.n.record_size==40 and C.sizeof(Descriptor)==24
    assets=sorted((ROOT/'original').rglob('*.WAV'));assert len(assets)==26
    for path in assets:h.parse(path.read_bytes())
    for fmt_size,databytes,junk in itertools.product(range(0,21),(0,1,2,3,31,32),range(0,6)):
        h.parse(wave(bytes(range(databytes)),bytes(fmt_size),(chunk(b'JUNK',bytes(junk)),)))
    for tag in (b'NOPE',b'RIFF'):
        for kind in (b'WAVE',b'NOPE'):
            for payload in (b'',chunk(b'data',b'123'),chunk(b'fmt ',bytes(14)),
                    chunk(b'fmt ',bytes(16))+chunk(b'fmt ',bytes(18))+chunk(b'data',b'x')):
                body=kind+payload;h.parse(tag+words(len(body))+body)
    print('RIFF parsing, odd chunks, output preservation and all 26 assets passed.',flush=True)
    for allocate,fail,short in itertools.product((0,1,7),(None,'allocate','read_file','close_handle'),(0,17,64)):
        h.reset(fail={fail:1,'short_read':short} if fail else {'short_read':short})
        n=h.n.alloc('destination',len(h.n.file));t=h.t.alloc('destination',len(h.t.file))
        h.call('load_binary_file',(h.n.path,n,allocate),(h.t.path,t,allocate))
        # Observe short-read poison tails independently of the returned pointer.
        blocks=[[(name,b.read(p,size)) for p,(name,size) in b.allocations.items()
            if name=='destination' or name.startswith('heap')] for b in (h.n,h.t)]
        assert blocks[0]==blocks[1]
    for fail in ({('create_file',1):1},{'create_file':1}):
        h.reset(fail=fail);h.call('load_binary_file',(h.n.path,0,1),(h.t.path,0,1))
    for bytes_,error in itertools.product((0,1,31,65536),(0,1,0x88780096)):
        h.reset(fail={'create_buffer':error})
        h.n.put_pointer(h.n.output,0x1234);h.t.put_pointer(h.t.output,0x1234)
        h.call('create_sound_buffer',(h.n.device,h.n.output,h.n.source+20,bytes_),
            (h.t.device,h.t.output,h.t.source+20,bytes_))
        assert h.n.role(h.n.get_pointer(h.n.output))==h.t.role(h.t.get_pointer(h.t.output))
    for path,device,split in itertools.product(assets,(False,True),(None,0,1,7)):
        h.reset(data=path.read_bytes(),device=device,split=split)
        for b in (h.n,h.t):b.write(b.path,path.name.encode()+b'\0')
        h.load()
    for failure in ('create_file','read_file','create_buffer','lock','unlock','get_frequency','get_pan','get_volume'):
        for error in (1,0x88780096):
            h.reset(fail={failure:error});h.records((17,));h.load()
    h.reset(data=b'NOPE'+bytes(80));h.records((17,));h.load()
    h.reset(fail={('allocate',2):1});h.load()
    h.reset(fail={('allocate',1):1});h.load(terminal=True)
    print('File loading, allocation failures, buffer splits and WAV upload passed.',flush=True)
    for name,device,record in itertools.product(('play_sound','update_sound'),(False,True),(False,True)):
        for frequency,pan,volume in itertools.product((0,8000,-1),(0,-10000,10000),(0,-10000,-1)):
            h.reset(device=device)
            if record:h.records((17,))
            h.call(name,(17,frequency,pan,volume))
    for name,error,restored in itertools.product(('play_sound','update_sound'),(0,1,2,0x88780096,0x88780032),(0,1,0x88780096)):
        h.reset(status=2,fail={'play':error,'restore':restored});h.records()
        h.call(name,(17,22050,-500,-1000))
    for name,device,status,error in itertools.product(('stop_sound','stop_all_sounds','restore_sounds'),
            (False,True),(0,1,2,3,4,6,0x102),(0,1,0x88780096)):
        h.reset(device=device,status=status,fail={'restore':error,'get_status':1});h.records()
        h.call(name,(17,) if name=='stop_sound' else ())
    for name,device,record,buffer in itertools.product(('release_sound','release_sounds'),(False,True),(False,True),(False,True)):
        h.reset(device=device)
        if record:h.records(buffer=buffer)
        h.call(name,(17,) if name=='release_sound' else ())
    for name,device,record,primary in itertools.product(('pause_sound','release_audio'),(False,True),(False,True),(False,True)):
        h.reset(device=device,primary=primary)
        if record:h.records(buffer=device or name=='release_audio')
        h.call(name)
    print('Playback, lost-buffer reload, stop and release lifecycles passed.',flush=True)
    controls=('set_sound_frequency','set_sound_pan','set_sound_volume')
    values=(-2147483648,-10000,-1,0,1,11025,2147483647,4294967295)
    # API-defined outputs are supplied even on failed GetStatus. Errors never
    # suppress the original's setter or its subsequent cached-parameter write.
    for name,slot,device,record,value in itertools.product(
            controls,(0,17,49),(False,True),(False,True),values):
        if device and record:continue
        h.reset(device=device)
        if record:h.records((slot,),buffer=False)
        h.call(name,(slot,value))
        assert not h.n.events and not h.t.events
    for name,slot,value,status,get_error,set_error in itertools.product(
            controls,(0,17,49),values,(0,2,4,6,0x100,0x102),
            (0,1,0x88780096),(0,1,0x88780096)):
        method=name.removeprefix('set_sound_')
        h.reset(status=status,fail={'get_status':get_error,'set_'+method:set_error})
        h.records()
        h.call(name,(slot,value))
        for b in (h.n,h.t):
            p=b.get_slot(slot)
            assert b.read_u32(p+b.field(method))==value&0xffffffff
        assert h.n.events[-1][0]=='set_'+method
        assert bool(any(e[0]=='restore' for e in h.n.events))==bool(status&2)
    # A rejected Restore leaves the old lost buffer in place. Each control
    # still attempts its setter and updates the cached request even on error.
    for name,slot,get_error,set_error,restore_error in itertools.product(
            controls,(0,17,49),(0,1),(0,0x88780096),(1,0x88780096)):
        field=name.removeprefix('set_sound_')
        h.reset(status=2,fail={'get_status':get_error,'set_'+field:set_error,
                              'restore':restore_error})
        h.records()
        old_records=(h.n.get_slot(slot),h.t.get_slot(slot))
        h.call(name,(slot,0))
        assert old_records==(h.n.get_slot(slot),h.t.get_slot(slot))
        for b in (h.n,h.t):
            assert b.read_u32(b.get_slot(slot)+b.field(field))==0
        assert not any(e[0]=='create_file' for e in h.n.events)
        assert h.n.events[-1][0]=='set_'+field
    # A synchronous setter callback can replace the record. The original loads
    # the current slot again for its final write, after using the old buffer.
    for name in controls:
        h.reset();h.records((17,49))
        for b in (h.n,h.t):b.rebind_on_set=(17,b.get_slot(49))
        h.call(name,(17,0))
        field=name.removeprefix('set_sound_')
        for b in (h.n,h.t):
            assert b.get_slot(17)==b.get_slot(49)
            assert b.read_u32(b.get_slot(49)+b.field(field))==0
    print('Persistent sound controls, ignored errors, recovery and callback rebinding passed.',flush=True)
    for name,device,draw,record in itertools.product(('initialize_sound','prepare_sound'),(False,True),(False,True),(False,True)):
        h.reset(device=device,draw=draw)
        if record:h.records(buffer=device)
        h.call(name,(0x777,))
    for draw,error,response in itertools.product((False,True),(1,0x88780078,0x8878000a),(0,3,4,5,6,7)):
        fail={'create_device':error}
        # Retrying occupied sound receives a success on the next factory call.
        if error==0x8878000a and response not in (3,5):fail={('create_device',1):error}
        h.reset(device=False,draw=draw,fail=fail,responses=(response,))
        terminal=not draw and ((error==0x8878000a and response==3) or (error!=0x8878000a and response==7))
        h.call('initialize_sound',(0x777,),terminal=terminal)
    for stage,draw,error,response,partial in itertools.product(('cooperate','create_buffer','play'),
            (False,True),(1,0x88780096),(0,6,7),(False,True)):
        h.reset(device=False,draw=draw,fail={stage:error},responses=(response,),partial_buffer=partial)
        h.call('initialize_sound',(0x777,),terminal=not draw and response==7)
    # Connected focus and lost-buffer sequence invokes every actual controller,
    # retaining filenames across pause and using newly reloaded buffer identities.
    for split in (None,0,7,31):
        h.reset(device=False,split=split)
        h.call('initialize_sound',(0x777,),connected=True)
        for slot in (0,17,49):h.load(slot,connected=True)
        for name,value in zip(controls,(0,-500,-1000)):
            h.call(name,(17,value),connected=True)
        h.call('update_sound',(17,22050,-500,-1000),connected=True)
        h.call('pause_sound',connected=True)
        h.call('initialize_sound',(0x777,),connected=True)
        for b in (h.n,h.t):
            for v in b.buffers.values():
                if not v['released'] and v['name']!='primary':v['status']|=2
            b.fail={('play',b.counts.get('play',0)+1):0x88780096}
        h.call('play_sound',(17,12000,500,-333),connected=True)
        h.call('release_audio',connected=True)
    print('Initialization dialogs, terminal exits and connected focus/recovery passed.',flush=True)
    return h

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    parser.add_argument('--report',type=Path,default=ROOT/'build/reports/sound-differential.json')
    args=parser.parse_args();h=checks(args.library.resolve())
    report=dict(status='pass',target_sha256=h.t.target_sha256,
        native_library_sha256=hashlib.sha256(args.library.read_bytes()).hexdigest(),
        direct_cases=sum(h.cases.values()),cases=h.cases,connected_checks=h.connected_checks,
        wav_assets=26,boundary='DirectSound COM, imports, CRT heap and terminal exit; no physical audio device')
    args.report.parent.mkdir(parents=True,exist_ok=True);args.report.write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report),flush=True)
if __name__=='__main__':main()
