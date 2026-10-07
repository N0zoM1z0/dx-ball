#!/usr/bin/env python3
"""Original mode-2 controller, hit regions and independent board-file outcomes."""
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

from target_oracle import ROOT, BANK, INDEX, FILE_SLOT
from test_gameover_differential import GameoverNative, GameoverTarget, GameoverHarness, GLOBALS
from test_device_differential import DeviceHarness
from test_runtime_differential import MODE_ENTRIES

ENTRIES={'initialize_editor':0x40C1A0,'redraw_editor':0x40C2B0,
    'editor_frame':0x40C3B0,'editor_key':0x40C740,'dispose_editor':0x40CF20,
    'draw_editor_choices':0x40C9C0,'draw_editor_status':0x40CA70,
    'initialize_hit_regions':0x401E10,'set_hit_region':0x401EB0,
    'find_hit_region':0x401F90}
BODIES={'initialize':'initialize_editor','redraw':'redraw_editor',
    'frame':'editor_frame','cleanup':'dispose_editor'}
REGIONS=0x4251A0
GLOBALS.update({0x421064:'hit_region_count',0x438AF0:'editor_selected_tile'})
FILE_DATA=bytes((i//400+i%400+7)%23 for i in range(20000))


class EditorNative(GameoverNative):
    def __init__(self,library):
        super().__init__(library)
        self.regions=(C.c_int32*500).in_dll(self.lib,'dxball_hit_regions')
        for op,group in enumerate(MODE_ENTRIES):
            self.mode_callbacks[op*5+2]=C.cast(getattr(self.lib,'dxball_'+BODIES[group]),C.c_void_p).value
        (C.c_void_p*5).in_dll(self.lib,'dxball_key_mode_ops')[2]=C.cast(self.lib.dxball_editor_key,C.c_void_p).value
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            f.restype=C.c_int32 if name=='find_hit_region' else None
            f.argtypes=[C.c_char] if name=='editor_key' else [C.c_int32]*5 if name=='set_hit_region' else [C.c_int32]*2 if name=='find_hit_region' else [C.c_int32] if name in ('initialize_hit_regions','dispose_editor') else []
    def file_role(self):
        value=self.file.value or 0
        return value if value in (0,0x1234) else 'file'


class EditorTarget(GameoverTarget):
    def __init__(self):
        super().__init__()
        for group in MODE_ENTRIES:self.uc.hook_del(self.mode_body_hooks[group,2])
        self.uc.hook_del(self.key_hooks[2])
    def file_api(self,name,args):
        if name=='open':
            path,mode=(self.string(v).decode() for v in args)
            if path=='default.bds':
                assert mode in ('rb','wb')
                self.board_open=mode
                opened=not self.board_blocked if mode=='wb' else path in self.board_files
                self.board_io.append((name,path,mode,opened))
                if opened and mode=='wb':self.board_files[path]=b''
                return self.FILE_HANDLE if opened else 0
        if self.board_open is not None and name in ('read','write','close'):
            if name=='close':
                assert args==(self.FILE_HANDLE,)
                self.board_io.append((name,));self.board_open=None;return 0
            pointer,size,count,handle=args
            assert (pointer,size,count,handle)==(BANK,1,20000,self.FILE_HANDLE)
            self.board_io.append((name,size,count))
            if name=='read':
                data=self.board_files['default.bds'][:size*count]
                self.put_bytes(pointer,data);return len(data)
            self.board_files['default.bds']=self.memory(pointer,size*count)
            return count
        return super().file_api(name,args)


class EditorHarness(GameoverHarness):
    def __init__(self,library):
        DeviceHarness.__init__(self,library,EditorNative,EditorTarget)
        self.cases=dict.fromkeys(ENTRIES,0);self.connected_checks=0
    def disk(self,data=FILE_DATA,blocked=False):
        path=Path('default.bds')
        if path.is_dir():path.rmdir()
        else:path.unlink(missing_ok=True)
        if blocked:path.mkdir()
        elif data is not None:path.write_bytes(data)
        self.t.board_files={} if data is None or blocked else {'default.bds':data}
        self.t.board_blocked=blocked;self.t.board_open=None;self.t.board_io=[]
    def seed(self,grid=None):
        super().seed(grid)
        self.disk()
        self.mode(2);self.setv('editor_selected_tile',1)
        self.n.regions[:]=[0]*500;self.t.write(REGIONS,bytes(2000))
    def index(self,index):
        self.n.index.value=index;self.t.write_u32(INDEX,index)
    def regions(self,data):
        assert len(data)==500
        self.n.regions[:]=data;self.t.write(REGIONS,bytes(self.n.regions))
    def compare(self,context):
        super().compare(context)
        assert bytes(self.n.regions)==self.t.read(REGIONS,2000),(context,'complete hit-region table')
        path=Path('default.bds')
        native={} if not path.is_file() else {'default.bds':path.read_bytes()}
        assert native==self.t.board_files,(context,'independent native/original board file')
    def call(self,name,*args):
        native_args=(bytes([args[0]&255]),) if name=='editor_key' else args
        nr=self.n.call('dxball_'+name,*native_args);tr=self.t.call(ENTRIES[name],*args)
        if nr is not None:assert nr==C.c_int32(tr).value,(name,args,nr,tr)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1
    def ready(self):
        self.n.call('dxball_initialize_hit_regions',23);self.t.call(ENTRIES['initialize_hit_regions'],23)
        self.n.call('dxball_draw_editor_choices');self.t.call(ENTRIES['draw_editor_choices'])
        self.compare('prepare actual toolbar')


def checks(library):
    fresh=C.CDLL(str(library));original=EditorTarget()
    table=(C.c_void_p*22).in_dll(fresh,'dxball_mode_ops')
    for op,group in enumerate(MODE_ENTRIES):
        assert table[op*5+2]==C.cast(getattr(fresh,'dxball_'+BODIES[group]),C.c_void_p).value
    assert (C.c_void_p*5).in_dll(fresh,'dxball_key_mode_ops')[2]==C.cast(fresh.dxball_editor_key,C.c_void_p).value
    for address,name in ((0x421064,'hit_region_count'),(0x438AF0,'editor_selected_tile')):
        assert source_global(C.c_int32, fresh,'dxball_'+name).value==original.read_u32(address)==0
    assert bytes((C.c_int32*500).in_dll(fresh,'dxball_hit_regions'))==original.read(REGIONS,2000)==bytes(2000)
    h=EditorHarness(library)
    for count in (-2,-1,0,1,23,50,98):
        h.seed();h.regions([0x17171717]*500);h.setv('clock_divisor',31337)
        h.call('initialize_hit_regions',count)
    for index in range(100):
        h.seed();h.regions([0x17171717]*500)
        h.call('set_hit_region',index,-index,index,100-index,index-100)
    # Inclusive edges, inactive records, index zero exclusion and last-match
    # precedence; counts stay within the physical 100-record array.
    for count,active,x,y in itertools.product((0,1,24,100),(0,1,2,-1),(-11,-10,0,10,11),(-21,-20,0,20,21)):
        h.seed();h.setv('hit_region_count',count)
        h.regions([-10,-20,10,20,active]*100);h.call('find_hit_region',x,y)
    print('Hit-region initialization, bounds and precedence passed.',flush=True)
    for primary,disabled in itertools.product((0,1),(0,1,2)):
        h.seed();h.setv('draw_to_primary',primary);h.setv('cursor_warp_disabled',disabled)
        h.call('initialize_editor')
    for primary,index,selected in itertools.product((0,1),(0,1,25,49),(0,1,8,22)):
        h.seed();h.index(index);h.setv('draw_to_primary',primary);h.setv('editor_selected_tile',selected)
        h.call('redraw_editor')
    for selected,index in itertools.product(range(23),(0,49)):
        h.seed();h.index(index);h.setv('editor_selected_tile',selected);h.call('draw_editor_status')
    for count in (0,24,100):
        h.seed();h.regions([0x17171717]*500);h.setv('hit_region_count',count);h.call('draw_editor_choices')
    print('Editor initialization, toolbar and redraw passed.',flush=True)
    for index,key in itertools.product((0,1,25,49),range(256)):
        h.seed(bytes([3])*400);h.index(index);h.call('editor_key',key)
    for key,length in itertools.product((ord('L'),ord('S')),(None,0,1,399,400,777,20000)):
        h.seed(bytes([3])*400);h.index(25);h.disk(None if length is None else FILE_DATA[:length])
        h.call('editor_key',key)
    h.seed();h.disk(None,blocked=True);h.call('editor_key',ord('S'))
    print('Every key byte, board switching and independent file outcomes passed.',flush=True)
    # Every board cell executes the actual draw/store dependencies for both
    # buttons. A high selected DWORD proves paint truncates to its low byte.
    for action,cell in itertools.product((1,2),range(400)):
        h.seed();h.ready();h.setv('mouse_action',action)
        h.setv('mouse_x',21+(cell%20)*30);h.setv('mouse_y',51+(cell//20)*15)
        h.setv('editor_selected_tile',0x101);h.index((cell*13)%50);h.call('editor_frame')
    for primary,control,action,x,y in itertools.product((0,1),(0,1,2,-1),(0,1,2,3),(-1,20,21,50,599,620,900),(-3,50,51,349,350,447,900)):
        # A bounded cross-section retains each axis/gate without multiplying
        # unrelated rendering cases already covered in the display owner.
        if (x+y+action)%7:continue
        h.seed();h.ready();h.setv('draw_to_primary',primary);h.setv('control_pressed',control)
        h.setv('mouse_action',action);h.setv('mouse_x',x);h.setv('mouse_y',y);h.call('editor_frame')
    for tile,dx,dy in itertools.product(range(1,23),(0,15,30,31),(0,15,16)):
        h.seed();h.ready();region=h.n.regions[(tile*5):(tile*5+5)]
        h.setv('mouse_action',1);h.setv('mouse_x',region[0]+dx);h.setv('mouse_y',region[1]+dy)
        h.call('editor_frame')
    for primary,fade,disabled in itertools.product((0,1),(0,1,2,-1),(0,1)):
        h.seed();h.setv('draw_to_primary',primary);h.setv('cursor_warp_disabled',disabled)
        h.call('dispose_editor',fade)
    print('Paint/erase, toolbar selection, CTRL and disposal passed.',flush=True)
    for primary in (0,1):
        h.seed();h.mode(0);h.points_ready();h.setv('draw_to_primary',primary)
        h.setv('control_pressed',1);h.phase('dispatch_key',0x403820,0x70)
        h.phase('dispatch_frame',0x403730);assert h.n.mode.value==2
        h.setv('mouse_x',21);h.setv('mouse_y',386);h.setv('mouse_action',1)
        h.phase('dispatch_frame',0x403730)
        for cell in (0,19,380,399):
            h.setv('mouse_x',21+cell%20*30);h.setv('mouse_y',51+cell//20*15)
            h.phase('dispatch_frame',0x403730)
        for key in (0xBB,0xBD,ord('S'),8,ord('L')):h.phase('dispatch_key',0x403820,key)
        h.phase('window_proc',0x40DA70,0x5678,0x100,0x1B,0)
        h.phase('dispatch_frame',0x403730);assert h.n.mode.value==0
        h.setv('control_pressed',0);h.setv('mouse_action',1)
        h.phase('dispatch_frame',0x403730);h.phase('dispatch_frame',0x403730)
        assert h.n.mode.value==1
    return h


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu();p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so');a=p.parse_args()
    library=a.library.resolve();previous=Path.cwd()
    try:
        with tempfile.TemporaryDirectory(prefix='dxball-editor-') as directory:
            os.chdir(directory);h=checks(library)
    finally:os.chdir(previous)
    report={'status':'pass','cases':h.cases,'total':sum(h.cases.values()),
        'connected_checks':h.connected_checks,'integration_checks_separate':True,
        'target_sha256':h.t.target_sha256,'library_sha256':hashlib.sha256(library.read_bytes()).hexdigest(),
        'scope':'Ten unmodified mode-2/hit-region entries with actual board bank, tile mapper, draw/store/load, mode/key/window routing and retained UI/dirty/palette/time bodies. Complete region, board, pixel and scalar storage, ordered render calls, independent actual-host-stdio versus original controlled-CRT board-file results. Counts and storage bounded; mapped tiles 0..22 and board indices 0..49. Resource reload/release, audio and Windows/COM hardware remain boundaries; no playable EXE claim.'}
    (ROOT/'build/reports/editor-differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()
