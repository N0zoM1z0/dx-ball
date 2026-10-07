#!/usr/bin/env python3
"""Execute thirteen original MDS/music bodies against one portable C owner.

Only Kernel32/WinMM imports and wrapper malloc/free are controlled on x86.
The RIFF parser, compact-event converter, controller and callback are original
instructions. Native allocation/header strides grow naturally with pointers;
import sizes and every logical field/payload/effect remain original contracts.
"""
import argparse
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import struct
import sys
from unicorn import UC_HOOK_CODE
from target_oracle import ROOT, TargetOracle

U=C.c_uint32; I=C.c_int32; P=C.c_void_p; Z=C.c_size_t
class Header(C.Structure):
    _fields_=[('data',P),('capacity',U),('recorded',U),('user',Z),('flags',U),
        ('next',P),('reserved',Z),('offset',U),('array',Z*8)]
class Context(C.Structure):
    _fields_=[('magic',U),('division',U),('capacity',U),('format',U),
        ('buffers',P),('stream',Z),('state',U),('count',I),('pending',I)]
class Input(C.Structure):_fields_=[('data',P),('length',U),('remaining',U)]
class Music(C.Structure):_fields_=[('context',P),('playing',I)]
ENTRIES={'open_mds':0x401000,'parse_mds':0x401210,'expand_mds_events':0x401580,
    'release_mds':0x4016e0,'play_mds':0x401780,'pause_mds':0x401990,
    'stop_mds':0x401a20,'midi_callback':0x401b10,'load_music':0x401b90,
    'resume_music':0x401c90,'pause_music':0x401ce0,'restart_music':0x401d30,'close_music':0x401da0}
# Return/argument declarations correspond to the owner's import boundary.
APIS=[('local_alloc','LocalAlloc',P,[U,Z]),('local_free','LocalFree',P,[P]),
 ('create_file','CreateFileA',Z,[P,U,U,P,U,U,Z]),('file_size','GetFileSize',U,[Z,P]),
 ('create_mapping','CreateFileMappingA',Z,[Z,P,U,U,U,P]),('map_view','MapViewOfFile',P,[Z,U,U,U,Z]),
 ('unmap_view','UnmapViewOfFile',I,[P]),('close_handle','CloseHandle',I,[Z]),
 ('global_alloc','GlobalAlloc',Z,[U,Z]),('global_lock','GlobalLock',P,[Z]),
 ('global_handle','GlobalHandle',Z,[P]),('global_unlock','GlobalUnlock',I,[Z]),
 ('global_free','GlobalFree',Z,[Z]),('stream_open','midiStreamOpen',U,[P,P,U,P,Z,U]),
 ('stream_property','midiStreamProperty',U,[Z,P,U]),
 ('prepare_header','midiOutPrepareHeader',U,[Z,P,U]),('stream_out','midiStreamOut',U,[Z,P,U]),
 ('stream_restart','midiStreamRestart',U,[Z]),('stream_pause','midiStreamPause',U,[Z]),
 ('out_reset','midiOutReset',U,[Z]),('unprepare_header','midiOutUnprepareHeader',U,[Z,P,U]),
 ('stream_close','midiStreamClose',U,[Z])]

def words(*values):return struct.pack('<'+'I'*len(values),*(v&0xffffffff for v in values))
def mds(capacity=64,compact=1,chunks=(words(7,0x903c7f),),division=480):
    payload=words(len(chunks))+b''.join(words(i,len(chunk))+chunk for i,chunk in enumerate(chunks))
    body=b'MIDSfmt '+words(12,division,capacity,compact)+b'data'+words(len(payload))+payload
    return b'RIFF'+words(len(body))+body

class Backend:
    def reset(self,fail=None,data=None,open_failure_handle=False):
        self.allocations={};self.retained=[];self.events=[];self.errors=[];self.fail=fail or {}
        self.calls={};self.file=data if data is not None else mds();self.open_failure_handle=open_failure_handle
        self.heap=0xa00000;self.current=0;self.buffer_base=0;self.buffer_count=0;self.buffer_capacity=0
        self.global_handle=0x8901;self.allocated_global=False;self.locked=False;self.freed_global=False
        self.ctx=self.alloc('context',self.context_size);self.current=self.ctx
        self.put_struct(self.ctx,'context',{'magic':0x4953444d,'division':480,'capacity':64})
        self.source=self.alloc('source',max(len(self.file)+512,4096));self.write(self.source,self.file)
        self.path=self.alloc('path',32);self.write(self.path,b'oracle.mds\0')
        self.output=self.alloc('output',self.pointer_size);self.put_pointer(self.output,0x1234)
        self.put_music(0)
    def alloc(self,name,size,fill=0):
        actual=max(size,1)
        if self.native:
            memory=C.create_string_buffer(actual);self.retained.append(memory);pointer=C.addressof(memory)
        else:
            pointer=self.heap;self.heap+=(actual+0xfff)&~0xfff
            assert self.heap<0x1900000
        self.allocations[pointer]=(name,actual)
        self.write(pointer,bytes([fill])*actual);return pointer
    def read_u32(self,p):return struct.unpack('<I',self.read(p,4))[0]
    def put_u32(self,p,v):self.write(p,words(v))
    def get_pointer(self,p):return int.from_bytes(self.read(p,self.pointer_size),'little')
    def put_pointer(self,p,v):self.write(p,int(v).to_bytes(self.pointer_size,'little'))
    def field(self,kind,name):
        if self.native:
            cls={'context':Context,'header':Header,'input':Input,'music':Music}[kind]
            typ=dict(cls._fields_)[name];return getattr(cls,name).offset,C.sizeof(typ)
        layouts={'context':('magic','division','capacity','format','buffers','stream','state','count','pending'),
            'header':('data','capacity','recorded','user','flags','next','reserved','offset','array'),
            'input':('data','length','remaining'),'music':('context','playing')}
        return layouts[kind].index(name)*4,32 if name=='array' else 4
    def get_struct(self,p,kind,name):
        off,size=self.field(kind,name);return int.from_bytes(self.read(p+off,size),'little')
    def put_struct(self,p,kind,values):
        for name,value in values.items():
            off,size=self.field(kind,name);self.write(p+off,int(value&((1<<(8*size))-1)).to_bytes(size,'little'))
    def role(self,p):
        if not p:return 0
        if p==0x1234:return p
        if self.buffer_base and self.buffer_base<=p<=self.buffer_base+(self.header_size+self.buffer_capacity)*max(1,self.buffer_count):
            index,offset=divmod(p-self.buffer_base,self.header_size+self.buffer_capacity)
            if index==self.buffer_count and offset==0 and self.buffer_count:
                return ('buffers',index-1,64+self.buffer_capacity)
            if offset>=self.header_size:offset=64+offset-self.header_size
            return ('buffers',index,offset)
        for address,(name,size) in self.allocations.items():
            if address<=p<address+size:return(name,p-address)
        raise AssertionError(('unknown pointer',hex(p)))
    def context(self,p=None):
        p=p or self.current
        if not p:return None
        values=[self.get_struct(p,'context',name) for name in ('magic','division','capacity','format','buffers','stream','state','count','pending')]
        values[4]=self.role(values[4]);return tuple(values)
    def header(self,p):
        values=[self.get_struct(p,'header',name) for name in ('data','capacity','recorded','user','flags','next','reserved','offset')]
        for i in (0,3,5):values[i]=self.role(values[i])
        arrayoff,arraysize=self.field('header','array');array=self.read(p+arrayoff,arraysize)
        values.append(tuple(int.from_bytes(array[i:i+self.pointer_size],'little') for i in range(0,len(array),self.pointer_size)))
        data=self.get_struct(p,'header','data');capacity=values[1]
        values.append(self.read(data,capacity) if data else b'');return tuple(values)
    def headers(self):
        if not self.buffer_base:return ()
        return tuple(self.header(self.buffer_base+i*(self.header_size+self.buffer_capacity)) for i in range(self.buffer_count))
    def buffers(self,count=3,capacity=64):
        self.buffer_count=count;self.buffer_capacity=capacity
        self.buffer_base=self.alloc('buffers',(self.header_size+capacity)*count)
        self.allocated_global=True
        self.put_struct(self.current,'context',{'capacity':capacity,'count':count,'buffers':self.buffer_base})
        for i in range(count):
            p=self.buffer_base+i*(self.header_size+capacity)
            self.put_struct(p,'header',{'data':p+self.header_size,'capacity':capacity,'recorded':12,'user':self.current})
            self.write(p+self.header_size,words(i,0,0x903c7f)+bytes([0x73])*(capacity-12))
    def music(self):
        p=self.get_music()
        if not p:return None
        context=self.get_struct(p,'music','context')
        return(self.role(context),self.get_struct(p,'music','playing'))
    def snapshot(self):
        return(self.context(),self.headers(),self.music(),self.allocated_global,self.locked,self.freed_global)
    def api(self,name,args):
        args=tuple(v or 0 for v in args);self.calls[name]=self.calls.get(name,0)+1
        failed=self.fail.get((name,self.calls[name]),self.fail.get(name,False))
        error=5 if failed else 0
        event=[name]
        result=0
        if name=='local_alloc':
            assert args==(0x40,self.context_size),args
            event += [0x40,36]
            if not failed:self.current=self.alloc('local_context',self.context_size);result=self.current
        elif name=='local_free':
            event += [self.role(args[0]),self.context(args[0])]
        elif name=='create_file':
            assert args[1:]==(0x80000000,1,0,3,0x80,0),args
            event += [self.string(args[0])];result=(1<<(8*self.pointer_size))-1 if failed else 0x7101
        elif name=='file_size':
            assert args==(0x7101,0);event+=list(args);result=len(self.file)
        elif name=='create_mapping':
            assert args==(0x7101,0,2,0,0,0);event+=list(args);result=0 if failed else 0x7102
        elif name=='map_view':
            assert args==(0x7102,4,0,0,0);event+=list(args);result=0 if failed else self.source
        elif name=='unmap_view':event += [self.role(args[0])];result=1
        elif name=='close_handle':event+=list(args);result=1
        elif name=='global_alloc':
            count=self.get_struct(self.current,'context','count');capacity=self.get_struct(self.current,'context','capacity')
            assert args==(0x2002,(self.header_size+capacity)*count),args
            self.buffer_count=count;self.buffer_capacity=capacity
            event += [0x2002,(64+capacity)*count]
            if not failed:
                self.buffer_base=self.alloc('buffers',args[1]);self.allocated_global=True;result=self.global_handle
        elif name=='global_lock':
            assert args==(self.global_handle if self.allocated_global else 0,),args
            event+=list(args)
            if args[0] and not failed:self.locked=True;result=self.buffer_base
        elif name=='global_handle':
            assert args==(self.buffer_base,);event += [self.role(args[0])];result=self.global_handle
        elif name=='global_unlock':
            assert args==(self.global_handle,);event+=list(args);self.locked=False
        elif name=='global_free':
            assert args==(self.global_handle,);event += [args[0],self.headers()];self.freed_global=True
        elif name=='stream_open':
            output,device,count,callback,instance,flags=args
            off,_=self.field('context','stream');assert output==self.current+off
            assert (self.read_u32(device),count,instance,flags)==(0xffffffff,1,0,0x30000)
            assert callback==(self.callback_address if self.native else ENTRIES['midi_callback'])
            event += [0xffffffff,count,'midi_callback',instance,flags,self.context()]
            if not failed or self.open_failure_handle:self.put_pointer(output,0x7123)
            result=error
        elif name=='stream_property':
            assert args[0]==0x7123 and args[2]==0x80000001
            assert self.read(args[1],8)==words(8,self.get_struct(self.current,'context','division'))
            event += [args[0],tuple(struct.unpack('<2I',self.read(args[1],8))),args[2],self.context()];result=error
        elif name in ('prepare_header','stream_out','unprepare_header'):
            stream,p,size=args;assert size==64 and stream==self.get_struct(self.current,'context','stream')
            event += [stream,self.role(p),size,self.header(p),self.context()]
            if not failed:
                flags=self.get_struct(p,'header','flags')
                flags=(flags|2) if name=='prepare_header' else (flags|4) if name=='stream_out' else flags&~2
                self.put_struct(p,'header',{'flags':flags})
            result=error
        else:
            assert name in ('stream_restart','stream_pause','out_reset','stream_close')
            assert args==(self.get_struct(self.current,'context','stream'),),args
            event += [*args,self.context()];result=error
        self.events.append(tuple(event));return result
    def string(self,p):
        data=bytearray()
        while self.read(p,1)!=b'\0':data.extend(self.read(p,1));p+=1
        return bytes(data)

class Native(Backend):
    native=True;pointer_size=C.sizeof(P);header_size=C.sizeof(Header);context_size=C.sizeof(Context)
    def __init__(self,library):
        self.lib=C.CDLL(str(library));self.callbacks=[]
        self.slot=P.in_dll(self.lib,'dxball_music')
        self.callback_address=C.cast(self.lib.dxball_midi_callback,P).value
        table=(P*len(APIS)).in_dll(self.lib,'dxball_midi_api')
        for index,(name,_,result,args) in enumerate(APIS):
            def callback(*values,name=name):
                try:return self.api(name,values)
                except BaseException as exc:self.errors.append(exc);return 0
            fn=C.CFUNCTYPE(result,*args)(callback);self.callbacks.append(fn);table[index]=C.cast(fn,P).value
        argtypes={'open_mds':[P,P,U,C.c_ubyte],'parse_mds':[P,P,U],'expand_mds_events':[P,P],
            'play_mds':[P,C.c_ubyte],'midi_callback':[Z,U,Z,P,Z],'load_music':[P,I]}
        for name in ENTRIES:
            fn=getattr(self.lib,'dxball_'+name)
            fn.argtypes=argtypes.get(name,[P] if name in ('release_mds','pause_mds','stop_mds') else [])
            fn.restype=None if name in ('midi_callback','resume_music','pause_music','restart_music','close_music') else I
    def read(self,p,n):return C.string_at(p,n)
    def write(self,p,data):C.memmove(p,bytes(data),len(data))
    def get_music(self):return self.slot.value or 0
    def put_music(self,p):self.slot.value=p
    def call(self,name,args):
        result=getattr(self.lib,'dxball_'+name)(*args)
        if self.errors:raise self.errors[0]
        return result

class Target(TargetOracle,Backend):
    native=False;pointer_size=4;header_size=64;context_size=36
    def __init__(self):
        TargetOracle.__init__(self);self.uc.mem_map(0xa00000,0xf00000)
        imports={item.name.decode():item.address for group in self.pe.DIRECTORY_ENTRY_IMPORT for item in group.imports if item.name}
        self.import_hooks=[]
        for index,(name,importname,_,args) in enumerate(APIS):
            address=0x50c000+index*16;self.write_u32(imports[importname],address)
            def callback(uc,address,size,user,name=name,count=len(args)):
                self._return(self.api(name,self._args(count)),pop=count*4)
            self.import_hooks.append(self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address))
        self.import_hooks.append(self.uc.hook_add(UC_HOOK_CODE,self.malloc,begin=0x416770,end=0x416770))
        self.import_hooks.append(self.uc.hook_add(UC_HOOK_CODE,self.free,begin=0x416760,end=0x416760))
    def malloc(self,uc,address,size,user):
        assert self._args(1)==(8,);self._return(self.alloc('wrapper',8))
    def free(self,uc,address,size,user):
        assert self.role(self._args(1)[0])[0]=='wrapper';self._return()
    def get_music(self):return self.read_u32(0x421060)
    def put_music(self,p):self.write_u32(0x421060,p)
    def call(self,name,args):
        self.callee_cleanup=20 if name=='midi_callback' else 0
        return TargetOracle.call(self,ENTRIES[name],*args)

class Harness:
    def __init__(self,library):
        self.n=Native(library);self.t=Target();self.cases=dict.fromkeys(ENTRIES,0);self.connected_checks=0
    def reset(self,**kw):
        # Real native wrapper allocations are released between scenarios. Mocks
        # retain blocks until reset so failure paths/dangling pointers are visible.
        if getattr(self.n,'retained',None) and self.n.get_music():
            self.n.fail={};self.t.fail={};self.n.call('close_music',());self.t.call('close_music',())
        self.n.reset(**kw);self.t.reset(**kw)
    def call(self,name,na,ta,connected=False):
        self.n.events=[];self.t.events=[]
        nr=self.n.call(name,na);tr=self.t.call(name,ta)
        if nr is not None:assert (nr&0xffffffff)==tr,(name,nr,tr)
        ns=self.n.snapshot();ts=self.t.snapshot()
        assert ns==ts,(name,'state',ns,ts)
        assert self.n.events==self.t.events,(name,'events',self.n.events,self.t.events)
        if connected:self.connected_checks+=1
        else:self.cases[name]+=1
        return nr
    def contexts(self,**kw):
        for b in (self.n,self.t):b.put_struct(b.current,'context',kw)
    def controller(self,name,*args,connected=False):
        return self.call(name,(self.n.current,*args),(self.t.current,*args),connected)
    def wrapper(self,name,play=0,connected=False):
        return self.call(name,(self.n.path,play) if name=='load_music' else (),
            (self.t.path,play) if name=='load_music' else (),connected)
    def parse(self,data,length=None,fail=None,connected=False):
        self.reset(data=data,fail=fail)
        return self.call('parse_mds',(self.n.ctx,self.n.source,len(data) if length is None else length),
            (self.t.ctx,self.t.source,len(data) if length is None else length),connected)
    def open(self,mode,connected=False):
        return self.call('open_mds',(self.n.output,self.n.source if mode&2 else self.n.path,len(self.n.file),mode),
            (self.t.output,self.t.source if mode&2 else self.t.path,len(self.t.file),mode),connected)
    def callback(self,message=0x3c9,index=0,connected=False):
        pointers=[b.buffer_base+index*(b.header_size+b.buffer_capacity) if message==0x3c9 else 0 for b in (self.n,self.t)]
        return self.call('midi_callback',(0x7123,message,0xabc,pointers[0],0xdef),
            (0x7123,message,0xabc,pointers[1],0xdef),connected)


def checks(library):
    h=Harness(library)
    assert h.n.header_size==120 and h.n.context_size==48
    assert not h.n.get_music() and not h.t.get_music()
    platform=(P*9).in_dll(h.n.lib,'dxball_platform_ops')
    for slot,name in ((3,'resume_music'),(4,'pause_music'),(5,'close_music')):
        assert platform[slot]==C.cast(getattr(h.n.lib,'dxball_'+name),P).value
    assert (P*15).in_dll(h.n.lib,'dxball_runtime_ops')[14]==C.cast(h.n.lib.dxball_close_music,P).value
    # Independent event input/output buffers include poison tails. Failure must
    # preserve recorded length and exactly the partial writes the original made.
    events=[b'',words(1),words(1,0x903c7f),words(1,0x903c7f,2,0x803c00),
        words(1,0x80000000),words(1,0x80000001)+b'abcd',
        words(1,0x80000005)+b'abcdefgh',words(1,0x80000009)+b'abcd',
        words(1,0x800000ff)+b'abcd',words(1,0x80000001)]
    for data,capacity in itertools.product(events,range(0,81,4)):
        for remaining in sorted(set((len(data),max(0,len(data)-1),max(0,len(data)-4)))):
            h.reset()
            arguments=[]
            for b in (h.n,h.t):
                source=b.alloc('events',max(64,len(data)+32),0x6b);b.write(source,data)
                destination=b.alloc('destination',128,0x91)
                header=b.alloc('converter_header',b.header_size)
                b.put_struct(header,'header',{'data':destination,'capacity':capacity,'recorded':0x9876})
                desc=b.alloc('descriptor',C.sizeof(Input) if b.native else 12)
                b.put_struct(desc,'input',{'data':source,'length':0x12345678,'remaining':remaining})
                arguments.append((desc,header,destination,source))
            h.call('expand_mds_events',arguments[0][:2],arguments[1][:2])
            assert h.n.header(arguments[0][1])==h.t.header(arguments[1][1])
            assert h.n.read(arguments[0][2],128)==h.t.read(arguments[1][2],128)
            assert h.n.read(arguments[0][3],max(64,len(data)+32))==h.t.read(arguments[1][3],max(64,len(data)+32))
            for b,args in ((h.n,arguments[0]),(h.t,arguments[1])):
                assert b.get_struct(args[0],'input','data')==args[3]
                assert b.get_struct(args[0],'input','length')==0x12345678
                assert b.get_struct(args[0],'input','remaining')==remaining
    print('Compact event partial writes, payload padding and capacity boundaries passed.',flush=True)
    valid=mds()
    for compact,count,capacity in itertools.product((0,1,2,3),(0,1,2,5),(16,24,64,4096)):
        h.parse(mds(capacity,compact,(words(7,0x903c7f),)*count))
    for length in range(len(valid)+1):h.parse(valid,length)
    for offset in (0,4,8,12,16,20,24,28,32,36,40,44,48):
        for value in (0,1,4,7,8,11,12,16,64,0xffffffff):
            # Keep count/capacity nonnegative and bounded; arithmetic overflow,
            # negative record counts and unmapped backing are outside the claim.
            if offset in (24,40) and value not in (0,1,4,8,12,16,64):continue
            data=bytearray(valid);data[offset:offset+4]=words(value)
            if offset==24 and value%8:continue
            if offset==40 and value>4:continue
            h.parse(bytes(data))
    for failure in ('global_alloc','global_lock'):
        h.parse(valid,fail={failure:True})
    for data in (mds(16,1,(words(1),)),mds(16,1,(words(1,0x80000008),)),mds(16,0,(bytes(17),))):h.parse(data)
    assets=sorted((ROOT/'original').rglob('*.MDS'))
    assert len(assets)==6,(len(assets),assets)
    for path in assets:h.parse(path.read_bytes())
    print('RIFF/MIDS chunk boundaries, allocation failures and all six original songs passed.',flush=True)
    for mode in range(256):
        h.reset();result=h.open(mode)
        for b in (h.n,h.t):
            output=b.get_pointer(b.output)
            assert output==(b.current if result==0 else 0x1234)
    for mode,data,failure in itertools.product((1,2),(valid,b'bad'),
            (None,'local_alloc','create_file','create_mapping','map_view','global_alloc','global_lock')):
        h.reset(data=data,fail={failure:True} if failure else None);result=h.open(mode)
        for b in (h.n,h.t):assert b.get_pointer(b.output)==(b.current if result==0 else 0x1234)
    print('Every open mode byte and ordered mapping/allocation cleanup passed.',flush=True)
    for name in ('play_mds','pause_mds','stop_mds','release_mds'):
        for magic,stream,state in itertools.product((0x4953444d,0,0x61746164),(0,0x7123),(*range(8),0x80000000,0x80000007)):
            flags_set=(0,1,2,3,255) if name=='play_mds' else (None,)
            for flags in flags_set:
                h.reset()
                for b in (h.n,h.t):b.buffers()
                h.contexts(magic=magic,stream=stream,state=state,pending=3)
                h.controller(name,*(() if flags is None else (flags,)))
    for name,failures in (('play_mds',('stream_open','stream_property','prepare_header','stream_out','stream_restart','out_reset')),
            ('pause_mds',('stream_pause',)),('stop_mds',('out_reset','unprepare_header','stream_close')),
            ('release_mds',('out_reset','unprepare_header','stream_close'))):
        for failure,index,existing,output in itertools.product(failures,(1,2,3),(False,True),(False,True)):
            h.reset(fail={(failure,index):True},open_failure_handle=output)
            for b in (h.n,h.t):b.buffers()
            h.contexts(stream=0x7123 if existing or name!='play_mds' else 0,state=4 if existing and name=='play_mds' else 0,pending=7)
            h.controller(name,*((1,) if name=='play_mds' else ()))
    for state,message,failed,pending in itertools.product(range(16),(0,0x3c9,0x3ca),(False,True),(0,3)):
        h.reset(fail={'stream_out':failed})
        for b in (h.n,h.t):b.buffers()
        h.contexts(stream=0x7123,state=state,pending=pending);h.callback(message)
    print('Stream creation, queueing, pause, stop, release and five-argument callback passed.',flush=True)
    for name in ('resume_music','pause_music','restart_music','close_music'):
        h.reset();h.wrapper(name)
    for play,data,failure in itertools.product((0,1,-1),(valid,b'bad'),
        (None,'local_alloc','create_file','create_mapping','map_view','global_alloc','global_lock',
         'stream_open','stream_property','prepare_header','stream_out','stream_restart')):
        h.reset(data=data,fail={failure:True} if failure else None);h.wrapper('load_music',play)
    for name,playing,failure in itertools.product(('resume_music','pause_music','restart_music','close_music'),(0,1),
            (None,'stream_open','stream_property','prepare_header','stream_out','stream_restart','stream_pause','out_reset','unprepare_header','stream_close')):
        h.reset();h.wrapper('load_music',playing,connected=True)
        for b in (h.n,h.t):b.fail={failure:True} if failure else {};b.calls={}
        h.wrapper(name)
    for path in assets:
        h.reset(data=path.read_bytes());h.wrapper('load_music',1,connected=True)
        for index in (0,h.n.buffer_count-1):h.callback(index=index,connected=True)
        h.wrapper('pause_music',connected=True);h.wrapper('resume_music',connected=True)
        h.wrapper('restart_music',connected=True);h.wrapper('load_music',0,connected=True)
        h.wrapper('resume_music',connected=True);h.wrapper('close_music',connected=True)
    h.reset()
    print('Music wrappers, replacement and connected lifecycles of all original songs passed.',flush=True)
    return h

def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu();parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so');a=parser.parse_args()
    library=a.library.resolve();h=checks(library)
    report={'status':'pass','cases':h.cases,'total':sum(h.cases.values()),
        'connected_checks':h.connected_checks,'integration_checks_separate':True,
        'target_sha256':h.t.target_sha256,'library_sha256':hashlib.sha256(library.read_bytes()).hexdigest(),
        'scope':'Thirteen unmodified MDS/music bodies. Original parser/converter/controller/callback execute; only Kernel32/WinMM and x86 wrapper malloc/free are controlled. Typed native headers/context grow to120/48 vs x86 64/36; original64-byte WinMM request checked independently. Complete logical records, payloads and ordered API effects, all256 open-mode bytes, bounded malformed RIFF/MIDS, partial converter writes, allocation/mapping/stream failures, callback RET20, all six original songs and separate connected lifecycles. Native wrapper malloc success only; nonnegative bounded counts/capacities, mapped backing, aligned header strides and no allocation/arithmetic overflow. Asynchronous hardware delivery and actual WinMM backend remain unimplemented; no playable EXE claim.'}
    output=ROOT/'build/reports/midi-differential.json';output.parent.mkdir(parents=True,exist_ok=True)
    output.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if __name__=='__main__':main()
