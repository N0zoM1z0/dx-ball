#!/usr/bin/env python3
"""Working-resource startup, score/board I/O, RNG calls and bank ownership."""
from source_state import source_global
import argparse
import ctypes as C
import hashlib
import itertools
import json
import os
from pathlib import Path
import struct
import sys
import tempfile

from unicorn import UC_HOOK_CODE
from target_oracle import ROOT, FILE_SLOT, BANK
from resources_oracle import ResourceNative, ResourceTarget, BANKS, FONT_BANK, SPRITE_BANK, Desc
from test_device_differential import DeviceNative, DeviceTarget, DeviceHarness
from test_core_differential import GLOBALS

ENTRIES={'initialize_device_state':0x403A00,'initialize_scores':0x406EE0,
    'read_scores':0x406CC0,'seed_random':0x403B90,
    'random_range':0x403B70,'release_sprite_banks':0x403CB0}
SCORES=0x4266A8
GLOBALS.update({0x4228D4:'software_only'})
FILE_APIS=[('open',0x417C20,C.c_void_p,[C.c_void_p]*2),
    ('read',0x417AA0,C.c_size_t,[C.c_void_p,C.c_size_t,C.c_size_t,C.c_void_p]),
    ('write',0x417E70,C.c_size_t,[C.c_void_p,C.c_size_t,C.c_size_t,C.c_void_p]),
    ('close',0x417A30,C.c_int32,[C.c_void_p]),
    ('access',0x417FF0,C.c_int32,[C.c_void_p,C.c_int32])]


class FileBoundaries:
    def file_state(self):
        return (self.score_bytes().hex(),self.read_bank().hex(),self.file_role())
    def file_api(self,name,args):
        if name=='open':
            path,mode=(self.string(v).decode() for v in args)
            self.file_events.append((name,path,mode,self.file_role()))
            self.open_path=path;return self.FILE_HANDLE if self.open_succeeds else 0
        if name=='access':
            path,mode=args;self.file_events.append((name,self.string(path).decode(),mode,self.file_role()))
            return self.access_result
        if name=='close':
            assert args==(self.FILE_HANDLE,)
            self.file_events.append((name,self.file_role()));return -1
        pointer,size,count,handle=args;assert handle==self.FILE_HANDLE
        assert (size,count)==(44,15)
        self.file_events.append((name,size,count,self.file_role()))
        if name=='read':
            data=self.files.get(self.open_path,b'')[:size*count];self.put_bytes(pointer,data)
            return len(data)//size
        data=self.memory(pointer,size*count);self.written_data=data
        self.file_events.append(('written',data.hex()))
        return self.write_result
    def random_seed(self,value):self.events.append(('srand',value,self.observed()))
    def random_next(self):
        self.events.append(('rand',self.random_value,self.observed()));return self.random_value
    def load_boards(self,path):
        self.events.append(('load-board-bank',self.string(path).decode(),self.observed()))


class StartupNative(FileBoundaries,DeviceNative):
    FILE_HANDLE=0x504320
    def __init__(self,library):
        super().__init__(library);self.startup_callbacks=[]
        def bind(table,slot,result,kinds,function):
            def checked(*args):
                try:return function(*args)
                except Exception as error:print('Startup boundary failed:',repr(error),flush=True);os._exit(1)
            cb=C.CFUNCTYPE(result,*kinds)(checked);self.startup_callbacks.append(cb)
            table[slot]=C.cast(cb,C.c_void_p).value
        table=(C.c_void_p*5).in_dll(self.lib,'dxball_startup_file_ops')
        for slot,(name,_,result,kinds) in enumerate(FILE_APIS):
            bind(table,slot,result,kinds,lambda *a,name=name:self.file_api(name,a))
        table=(C.c_void_p*2).in_dll(self.lib,'dxball_random_ops')
        bind(table,0,None,[C.c_uint32],self.random_seed)
        bind(table,1,C.c_int32,[],self.random_next)
        bind((C.c_void_p*1).in_dll(self.lib,'dxball_startup_load_boards'),0,None,[C.c_void_p],self.load_boards)
        bind(self.ddraw_table,6,C.c_int32,[C.c_void_p]*4,self.create_background)
        bind((C.c_void_p*1).in_dll(self.lib,'dxball_process_exit_backend'),0,None,[C.c_int32],self.terminate)
        (C.c_void_p*22).in_dll(self.lib,'dxball_mode_ops')[20]=C.cast(self.lib.dxball_initialize_device_state,C.c_void_p).value
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name);f.restype=C.c_int32 if name=='random_range' else None
            f.argtypes=[C.c_int32] if name=='random_range' else []
    def memory(self,p,size):return C.string_at(p,size)
    def string(self,p):return C.string_at(p)
    def put_bytes(self,p,data):C.memmove(p,data,len(data))
    def score_bytes(self):return C.string_at(C.addressof((C.c_uint8*660).in_dll(self.lib,'dxball_scores')),660)
    def read_bank(self):return bytes(self.bank)
    def file_role(self):return 'file' if self.file.value==self.FILE_HANDLE else self.file.value or 0
    def create_background(self,ddraw,description,output,outer):
        d=Desc.from_address(description);assert ddraw==C.addressof(self.ddraw) and outer is None
        self.events.append(('background-create',d.size,d.flags,d.width,d.height,d.caps,self.create_result,self.null_background,self.observed()))
        C.c_void_p.from_address(output).value=None if self.null_background else C.addressof(self.background)
        return self.create_result
    def terminate(self,status):
        self.exit_file.write_text(json.dumps({'status':status,'events':self.events,
            'file_events':self.file_events,'state':self.file_state(),'observed':self.observed(),
            'background':self.normalize(C.c_void_p.in_dll(self.lib,'dxball_background_surface').value or 0)}))
        os._exit(status)


class StartupTarget(FileBoundaries,DeviceTarget):
    def __init__(self):
        super().__init__()
        for hook in self.file_hooks.values():self.uc.hook_del(hook)
        self.uc.hook_del(self.game_hooks[0x403B70]);self.uc.hook_del(self.mode_hooks['device'])
        def bind(address,count,function,stdcall=False):
            def callback(*unused):
                result=function(self._args(count));self._return(0 if result is None else result,pop=count*4 if stdcall else 0)
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address))
        for name,address,_,kinds in FILE_APIS:bind(address,len(kinds),lambda a,name=name:self.file_api(name,a))
        bind(0x4179F0,1,lambda a:self.random_seed(a[0]))
        bind(0x417A00,0,lambda a:self.random_next())
        bind(0x40CC30,1,lambda a:self.load_boards(a[0]))
        self.write_u32(0x506300+6*4,0x50E300);bind(0x50E300,4,self.create_background,True)
    def memory(self,p,size):return self.read(p,size)
    def string(self,p):return self._cstring(p)
    def put_bytes(self,p,data):self.write(p,data)
    def score_bytes(self):return self.read(SCORES,660)
    def read_bank(self):return self.read(BANK,20000)
    def file_role(self):
        value=self.read_u32(FILE_SLOT);return 'file' if value==self.FILE_HANDLE else value
    def create_background(self,args):
        ddraw,desc,output,outer=args;assert ddraw==self.DDRAW and outer==0
        self.events.append(('background-create',self.read_u32(desc),self.read_u32(desc+4),
            self.read_u32(desc+12),self.read_u32(desc+8),self.read_u32(desc+104),
            self.create_result,self.null_background,self.observed()))
        self.write_u32(output,0 if self.null_background else self.BACKGROUND);return self.create_result


class StartupHarness(DeviceHarness):
    def __init__(self,library):
        super().__init__(library,StartupNative,StartupTarget);self.cases=dict.fromkeys(ENTRIES,0);self.connected=0
    def seed(self,grid=None):
        super().seed(grid)
        for o in (self.n,self.t):
            o.file_events=[];o.files={};o.open_succeeds=True;o.access_result=0;o.open_path=None
            o.write_result=0;o.written_data=None;o.random_value=0;o.create_result=0;o.null_background=False;o.exit_status=None
        self.n.file.value=0x1234;self.t.write_u32(FILE_SLOT,0x1234)
        C.memset(C.addressof((C.c_uint8*660).in_dll(self.n.lib,'dxball_scores')),0xA7,660);self.t.write(SCORES,b'\xa7'*660)
    def compare(self,context):
        super().compare(context)
        assert self.n.file_state()==self.t.file_state(),(context,'score/board/FILE state')
        assert self.n.file_events==self.t.file_events,(context,'ordered file calls',self.n.file_events[:5],self.t.file_events[:5])
        assert self.n.written_data==self.t.written_data,(context,'file write data')
        pointer=C.c_void_p.in_dll(self.n.lib,'dxball_background_surface').value or 0
        assert self.n.normalize(pointer)==self.t.normalize(self.t.read_u32(0x421070)),(context,'background result')
    def call(self,name,*args):
        nr=self.n.call('dxball_'+name,*args);tr=self.t.call(ENTRIES[name],*args)
        if nr is not None:assert nr==C.c_int32(tr).value,(name,args,nr,tr)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1


def release_checks(library):
    # Run before DeviceHarness constructs Python-owned sprite records. These
    # resource fixtures are allocated by malloc and freed by the maintained C
    # release_sprite body, including NULL surfaces and bank boundary slots.
    n,t=ResourceNative(library),ResourceTarget();count=0
    n.lib.dxball_release_sprite_banks.restype=None;n.lib.dxball_release_sprite_banks.argtypes=[]
    for slots,modes in itertools.product(((),(0,1,254),tuple(range(255))),((0,0,0),(1,0,1),(2,-1,1))):
        n.reset();t.reset();n.font.value=1;t.write_u32(FONT_BANK,1)
        for bank in range(3):
            n.banks[bank].count=197;n.banks[bank].mode=modes[bank];n.banks[bank].filename=b'keep.sbk'
            t.write_u32(BANKS+bank*1048+1020,197);t.write_u32(BANKS+bank*1048+1024,modes[bank])
            t.write(BANKS+bank*1048+1028,b'keep.sbk\0'+bytes(11))
            for slot in slots:n.seed(bank,slot,null=slot%2==0);t.seed(bank,slot,null=slot%2==0)
        n.lib.dxball_release_sprite_banks();t.call(ENTRIES['release_sprite_banks'])
        assert n.events==t.events,('bank release calls',count)
        assert len(t.freed)==len(slots)*3 and n.bank.value==t.read_u32(SPRITE_BANK)==2
        assert n.font.value==t.read_u32(FONT_BANK)==1
        for bank in range(3):
            expected=list(t.bank_snapshot(bank));expected[1]=C.c_int32(expected[1]).value
            assert n.bank_snapshot(bank)==tuple(expected),('released bank',bank,count)
        count+=1
    return count


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu();p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so');a=p.parse_args()
    # Check fresh image defaults before any harness overwrites its state.
    fresh=C.CDLL(str(a.library));original=ResourceTarget()
    assert C.c_void_p.in_dll(fresh,'dxball_startup_load_boards').value==C.cast(fresh.dxball_read_board_bank,C.c_void_p).value
    for table,length,bindings in (
            ('dxball_mode_ops',22,{20:'initialize_device_state'}),
            ('dxball_runtime_ops',15,{10:'draw_text',11:'draw_centered_text',13:'release_sprite_banks'}),
            ('dxball_gameplay_ops',6,{4:'random_range'})):
        pointers=source_global(C.c_void_p*length, fresh,table)
        for slot,name in bindings.items():assert pointers[slot]==C.cast(getattr(fresh,'dxball_'+name),C.c_void_p).value,(table,slot,'production default')
    for address,name in ((0x4228A0,'display_buffer_count'),(0x4228A8,'device_reset_requested'),
            (0x4228D0,'draw_to_primary'),(0x4228D4,'software_only'),(0x421084,'text_spacing')):
        assert source_global(C.c_int32, fresh,'dxball_'+name).value==original.read_u32(address)==1,(name,'fresh default')
    released=release_checks(a.library);h=StartupHarness(a.library);h.cases['release_sprite_banks']=released
    for access,opened,written in itertools.product((-1,0,1),(False,True),(0,15)):
        h.seed()
        for o in (h.n,h.t):o.access_result=access;o.open_succeeds=opened;o.write_result=written
        h.call('initialize_scores')
    for name,capacity in (('read_scores',660),):
        for size,opened in itertools.product((0,1,43,44,capacity-1,capacity,capacity+17),(False,True)):
            h.seed();path='score.dat'
            for o in (h.n,h.t):o.open_succeeds=opened;o.files={path:bytes((i*71+5)%256 for i in range(size))}
            h.call(name)
    for now in (0,1,299,300,301,0x7fffffff,0x80000000,0xffffffff):
        h.seed()
        for o in (h.n,h.t):o.time_script=[now]
        h.call('seed_random')
    for value,limit in itertools.product((0,1,17,32767),(1,2,3,4,15,101,32767,-7)):
        h.seed();h.n.random_value=h.t.random_value=value;h.call('random_range',limit)
    for software,reduced,elapsed in itertools.product((0,1,2,-1),(0,1,2,-1),(0,399,400,401,1000)):
        h.seed();h.setv('software_only',software);h.state(0x4228D8,reduced)
        for o in (h.n,h.t):
            o.access_result=-1;o.files={'score.dat':bytes(range(256))*3,'default.bds':bytes(range(256))*80}
            o.time_script=[301,1000,1000+elapsed,123456]
        h.call('initialize_device_state')
    # Unsigned timer subtraction on wrap.
    h.seed()
    for o in (h.n,h.t):o.time_script=[42,0xfffffff0,20,33]
    h.call('initialize_device_state')
    # The real frame dispatcher enters the new device body before its declared
    # mode-4 initialize/frame boundary. This verifies production table wiring.
    h.seed();h.setv('device_reset_requested',1)
    for o in (h.n,h.t):o.tick_step=401
    h.n.call('dxball_dispatch_frame');h.t.call(0x403730);h.compare('connected device dispatch');h.connected+=1
    # Device failure must retain the COM output and terminate before I/O. Run
    # native exit in a child; original exit is intercepted without byte patches.
    for null in (False,True):
        h.seed()
        for o in (h.n,h.t):o.create_result=-1;o.null_background=null
        with tempfile.TemporaryDirectory() as directory:
            path=Path(directory)/'exit.json';h.n.exit_file=path
            child=os.fork()
            if child==0:h.n.call('dxball_initialize_device_state');os._exit(99)
            _,status=os.waitpid(child,0);assert os.waitstatus_to_exitcode(status)==1
            try:h.t.call(ENTRIES['initialize_device_state'])
            except AssertionError as error:assert str(error)=='instruction limit reached' and h.t.exit_status==1
            else:raise AssertionError('original startup failure returned')
            expected={'status':1,'events':h.t.events,'file_events':h.t.file_events,'state':h.t.file_state(),
                'observed':h.t.observed(),'background':h.t.normalize(h.t.read_u32(0x421070))}
            assert json.loads(path.read_text())==json.loads(json.dumps(expected)),('nonreturning startup',null)
        h.cases['initialize_device_state']+=1
    report={'status':'pass','cases':h.cases,'total':sum(h.cases.values()),'connected_checks':h.connected,
        'target_sha256':h.t.target_sha256,'library_sha256':hashlib.sha256(a.library.read_bytes()).hexdigest(),
        'scope':'Six unmodified original startup entries, actual palette/time/dispatcher and resource release bodies; controlled CRT file/access/RNG, previously accepted board-loader call, WinMM and DirectDraw outputs. Defined descriptor fields, valid storage, nonzero divisors, short reads, nonreturning exit and unsigned timing. Modes other than gameplay remain explicit boundaries; no playable executable claim.'}
    (ROOT/'build/reports/startup-differential.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
