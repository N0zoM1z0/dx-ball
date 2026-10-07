#!/usr/bin/env python3
"""Original game-over controllers, name entry, rank insertion and score I/O."""
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

from unicorn import UC_HOOK_CODE
from target_oracle import ROOT
from test_intro_differential import IntroNative, IntroTarget, IntroHarness, GLOBALS
from test_device_differential import DeviceHarness
from test_startup_differential import FileBoundaries, FILE_APIS, SCORES, FILE_SLOT, BANK
from test_runtime_differential import MODE_ENTRIES

ENTRIES={'initialize_game_over':0x406440,'redraw_game_over':0x406590,
    'game_over_frame':0x406730,'dispose_game_over':0x407370,
    'game_over_key':0x4069F0,'draw_high_scores':0x406B20,
    'insert_high_score':0x406D20,'edit_score_name':0x4071C0}
GLOBALS.update({0x426698:'score_name_length',0x42669C:'score_blink_tick',
    0x4266A0:'selected_score_index',0x4266A4:'score_cursor_visible',
    0x42693C:'show_high_scores',0x426940:'entering_score_name'})
NAME=0x426948
BODIES={'initialize':'initialize_game_over','redraw':'redraw_game_over',
    'frame':'game_over_frame','cleanup':'dispose_game_over'}


def records(values=None):
    if values is None:values=[150-i*10 for i in range(15)]
    result=bytearray()
    for i,value in enumerate(values):
        text=('Player %02d'%i).encode()+bytes([0])
        result.extend(text+bytes([0xA0+i])*(40-len(text))+struct.pack('<I',value))
    assert len(result)==660
    return bytes(result)


class ScoreFiles(FileBoundaries):
    FILE_HANDLE=0x504320
    def file_api(self,name,args):
        self.file_events.append(('before',name,self.score_bytes().hex(),
            self.name_bytes().hex(),self.observed()))
        if name=='open' and self.open_sequence:self.open_succeeds=self.open_sequence.pop(0)
        return super().file_api(name,args)


class GameoverNative(ScoreFiles,IntroNative):
    def __init__(self,library):
        super().__init__(library);self.score_callbacks=[]
        self.names=(C.c_char*40).in_dll(self.lib,'dxball_score_name')
        self.score_storage=(C.c_uint8*660).in_dll(self.lib,'dxball_scores')
        table=(C.c_void_p*5).in_dll(self.lib,'dxball_startup_file_ops')
        for slot,(name,_,result,kinds) in enumerate(FILE_APIS):
            def checked(*args,name=name):
                try:return self.file_api(name,args)
                except Exception as error:print('Score boundary failed:',repr(error),flush=True);os._exit(1)
            callback=C.CFUNCTYPE(result,*kinds)(checked);self.score_callbacks.append(callback)
            table[slot]=C.cast(callback,C.c_void_p).value
        for op,group in enumerate(MODE_ENTRIES):
            self.mode_callbacks[op*5+3]=C.cast(getattr(self.lib,'dxball_'+BODIES[group]),C.c_void_p).value
        (C.c_void_p*5).in_dll(self.lib,'dxball_key_mode_ops')[3]=C.cast(self.lib.dxball_game_over_key,C.c_void_p).value
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            f.restype=C.c_int32 if name=='insert_high_score' else None
            f.argtypes=[C.c_char_p,C.c_uint32] if name=='insert_high_score' else [C.c_char] if name in ('edit_score_name','game_over_key') else [C.c_int32] if name=='dispose_game_over' else []
    def memory(self,p,size):return C.string_at(p,size)
    def score_bytes(self):return bytes(self.score_storage)
    def name_bytes(self):return bytes(self.names)
    def read_bank(self):return bytes(self.bank)
    def file_role(self):return 'file' if self.file.value==self.FILE_HANDLE else self.file.value or 0


class GameoverTarget(ScoreFiles,IntroTarget):
    def __init__(self):
        super().__init__()
        self.uc.mem_map(0x920000,0x1000)
        for group in MODE_ENTRIES:self.uc.hook_del(self.mode_body_hooks[group,3])
        self.uc.hook_del(self.key_hooks[3])
        for hook in self.file_hooks.values():self.uc.hook_del(hook)
        for name,address,_,kinds in FILE_APIS:
            def callback(*unused,name=name,count=len(kinds)):
                result=self.file_api(name,self._args(count));self._return(0 if result is None else result)
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address))
    def memory(self,p,size):return self.read(p,size)
    def score_bytes(self):return self.read(SCORES,660)
    def name_bytes(self):return self.read(NAME,40)
    def read_bank(self):return self.read(BANK,20000)
    def file_role(self):
        value=self.read_u32(FILE_SLOT);return 'file' if value==self.FILE_HANDLE else value


class GameoverHarness(IntroHarness):
    def __init__(self,library):
        DeviceHarness.__init__(self,library,GameoverNative,GameoverTarget)
        self.cases=dict.fromkeys(ENTRIES,0);self.connected_checks=0
    def scores(self,data):
        assert len(data)==660
        self.n.score_storage[:]=data;self.t.write(SCORES,data)
    def name(self,text):
        assert len(text)<=39
        data=text+bytes([0])+bytes([0xAD])*(39-len(text))
        C.memmove(C.addressof(self.n.names),data,40);self.t.write(NAME,data)
        self.setv('score_name_length',len(text))
    def seed(self,grid=None):
        super().seed(grid)
        self.scores(records());self.name(b'')
        # Direct ranking draw requires a real selected surface, unlike the
        # generic harness sentinel used for isolated dependency traces.
        self.n.active.value=self.n.surface_pointer;self.t.write_u32(0x4265CC,self.t.SURFACE)
        self.n.file.value=0x1234;self.t.write_u32(FILE_SLOT,0x1234)
        for o in (self.n,self.t):
            o.file_events=[];o.files={'score.dat':records()};o.open_succeeds=True
            o.open_sequence=[];o.access_result=0;o.open_path=None
            o.write_result=0;o.written_data=None
    def compare(self,context):
        super().compare(context)
        assert self.n.file_state()==self.t.file_state(),(context,'score/board/FILE storage')
        assert self.n.name_bytes()==self.t.name_bytes(),(context,'name including poison tail')
        assert self.n.file_events==self.t.file_events,(context,'ordered score-file calls',self.n.file_events[:4],self.t.file_events[:4])
        assert self.n.written_data==self.t.written_data,(context,'complete written score records')
    def call(self,name,*args):
        if name=='insert_high_score':
            text,score=args;self.t.write(0x920000,text+bytes([0]));native_args=(text,score);target_args=(0x920000,score)
        elif name in ('edit_score_name','game_over_key'):
            native_args=(bytes([args[0]&255]),);target_args=args
        else:native_args=target_args=args
        nr=self.n.call('dxball_'+name,*native_args);tr=self.t.call(ENTRIES[name],*target_args)
        if nr is not None:assert nr==C.c_int32(tr).value,(name,args,nr,tr)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu();p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so');a=p.parse_args()
    lib=C.CDLL(str(a.library));raw=GameoverTarget()
    table=(C.c_void_p*22).in_dll(lib,'dxball_mode_ops')
    for op,group in enumerate(MODE_ENTRIES):assert table[op*5+3]==C.cast(getattr(lib,'dxball_'+BODIES[group]),C.c_void_p).value
    assert (C.c_void_p*5).in_dll(lib,'dxball_key_mode_ops')[3]==C.cast(lib.dxball_game_over_key,C.c_void_p).value
    for address,name in GLOBALS.items():
        if name in ('score_name_length','score_blink_tick','selected_score_index','score_cursor_visible','show_high_scores','entering_score_name'):
            assert source_global(C.c_int32, lib,'dxball_'+name).value==raw.read_u32(address)==0
    assert raw.read_u32(0x423658)==0 # original default C-locale branch
    h=GameoverHarness(a.library)
    # Every placement boundary, equal-score precedence and UINT_MAX use actual
    # score reload, strcpy and unsigned formatting on the original side.
    for score in (0,9,10,11,*range(20,151,10),151,0x7fffffff,0x80000000,0xffffffff):
        h.seed();h.call('insert_high_score',b'New player',score)
    for access,opened,readlen,written in itertools.product((-1,0,1),(False,True),(0,44,308,660),(0,7,15)):
        h.seed()
        for o in (h.n,h.t):o.access_result=access;o.open_sequence=[True,opened];o.files['score.dat']=records()[:readlen];o.write_result=written
        h.call('insert_high_score',b'X'*39,95)
    for failed in (False,True):
        h.seed()
        for o in (h.n,h.t):o.open_sequence=[not failed,True]
        h.call('insert_high_score',b'',10)
    # File contents differ from memory: skipping the reload or computing rank
    # before fread must change eligibility, placement or retained record tails.
    for values,readlen,score,opened in (([1000]*15,660,95,True),
            ([0]*15,660,5,True),([300-i*20 for i in range(15)],660,95,True),
            ([600,500,400]+[150-i*10 for i in range(3,15)],132,150,True),
            ([1000]*15,660,95,False),([100]*15,660,100,True)):
        h.seed()
        for o in (h.n,h.t):o.files['score.dat']=records(values)[:readlen];o.open_sequence=[opened,True]
        h.call('insert_high_score',b'Reloaded',score)
    print('Score insertion, file failures and poison tails passed.',flush=True)
    for shift,length,key in itertools.product((0,1,2,-1),(0,1,29,30,31),range(256)):
        h.seed();h.mode(3);h.name(b'a'*length);h.setv('shift_pressed',shift)
        h.setv('entering_score_name',1);h.state(0x422D18,75);h.call('edit_score_name',key)
        if key==255:print('Name key bytes passed:',shift,length,flush=True)
    for entering,key in itertools.product((0,1,2,-1),range(256)):
        h.seed();h.mode(3);h.name(b'Test');h.setv('entering_score_name',entering)
        h.state(0x422D18,75);h.call('game_over_key',key)
    print('Game-over key routing passed.',flush=True)
    for primary,score,readlen in itertools.product((0,1),(0,9,10,0xffffffff),(0,44,660)):
        h.seed();h.scores(records([500]*15));h.mode(3);h.name(b'Old');h.state(0x422D18,score);h.setv('draw_to_primary',primary)
        for o in (h.n,h.t):o.files['score.dat']=records()[:readlen]
        h.call('initialize_game_over')
    for selected in (-1,*range(15),15):
        h.seed();h.setv('selected_score_index',selected);h.call('draw_high_scores')
    for primary,show,entering,score in itertools.product((0,1),(0,1,2),(0,1,2),(0,0xffffffff)):
        h.seed();h.mode(3);h.setv('draw_to_primary',primary);h.setv('show_high_scores',show)
        h.setv('entering_score_name',entering);h.setv('selected_score_index',7);h.state(0x422D18,score)
        h.call('redraw_game_over')
    print('Initialization, ranking and redraw passed.',flush=True)
    for i,(primary,entering,show,action) in enumerate(itertools.product((0,1),(0,1,2,-1),(0,1,2),(0,1,2,3))):
        h.seed();h.mode(3);h.name(b'Tester');h.setv('draw_to_primary',primary)
        h.setv('entering_score_name',entering);h.setv('show_high_scores',show);h.setv('mouse_action',action)
        h.setv('score_cursor_visible',(0,1,2,-1)[i%4]);h.setv('mouse_x',(-99,8,599,900)[i%4]);h.setv('mouse_y',(-3,447,448,900)[i%4])
        h.n.now=h.t.now=(99,100,299,300)[i%4];h.call('game_over_frame')
    for primary,tick,now,entering in itertools.product((0,1),(0,1000,0xfffffff0),(0,99,100,299,300,1000,1300,0xffffffff),(0,1)):
        h.seed();h.mode(3);h.name(b'Clock');h.setv('draw_to_primary',primary)
        h.setv('score_blink_tick',tick);h.setv('entering_score_name',entering);h.setv('show_high_scores',1)
        h.setv('score_cursor_visible',1);h.n.now=h.t.now=now;h.call('game_over_frame')
    for primary,fade,disabled in itertools.product((0,1),(0,1,2,-1),(0,1)):
        h.seed();h.mode(3);h.setv('draw_to_primary',primary);h.setv('cursor_warp_disabled',disabled)
        h.call('dispose_game_over',fade)
    # Actual finish-game and mode/key controllers retain game-over bodies.
    # Successful/failed persistence are both observed before returning to menu.
    for primary,writable in itertools.product((0,1),(False,True)):
        h.seed();h.mode(1);h.setv('draw_to_primary',primary);h.state(0x422D18,175)
        for o in (h.n,h.t):o.access_result=0 if writable else -1
        h.phase('finish_game',0x415C10);h.phase('dispatch_frame',0x403730);assert h.n.mode.value==3
        for _ in range(4):h.phase('dispatch_frame',0x403730)
        for key in (0x41,0x42,0x08,0x43,0x20,0x39,0x0D):h.phase('dispatch_key',0x403820,key)
        assert C.c_int32.in_dll(h.n.lib,'dxball_show_high_scores').value==1
        assert C.c_int32.in_dll(h.n.lib,'dxball_entering_score_name').value==0
        for _ in range(4):h.phase('dispatch_frame',0x403730)
        h.setv('mouse_action',1);h.phase('dispatch_frame',0x403730);h.phase('dispatch_frame',0x403730)
        assert h.n.mode.value==0
    report={'status':'pass','cases':h.cases,'total':sum(h.cases.values()),
        'connected_checks':h.connected_checks,'integration_checks_separate':True,
        'target_sha256':h.t.target_sha256,'library_sha256':hashlib.sha256(a.library.read_bytes()).hexdigest(),
        'scope':'Eight unmodified game-over entries with actual mode/key routing, score reload/insertion, name editing, UI/glyph/line/dirty/palette/time bodies and original CRT default-locale conversion. Complete score/name/palette/pixel arrays, poison tails, file outputs and ordered calls. Valid terminating bounded storage and nonoverflowing arithmetic; resource reload/release on this edge, audio and Windows/driver effects remain boundaries. No playable EXE claim.'}
    (ROOT/'build/reports/gameover-differential.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
