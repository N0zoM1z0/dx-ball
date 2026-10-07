#!/usr/bin/env python3
"""Original mode/lifecycle bodies, connected to maintained physics and rendering state."""
from source_state import source_global
import argparse
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import struct
import sys

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
from target_oracle import ROOT, BANK, TILES, AUX, MODE, ACTIVE_SURFACE
from resources_oracle import Sprite, Surface, BANKS, SPRITE_BANK, FONT_BANK, SAVED_PALETTE, LIVE_PALETTE
from test_gameplay_differential import signed, REMAINING, SCORE
from test_entities_differential import SHAPES
from test_core_differential import CoreNative, CoreTarget, Harness, GLOBALS, FRAME_BOUNDARIES

GLOBALS.update({0x421068:'high_resolution_clock',0x425970:'clock_divisor',0x43FAD8:'paddle_frame',
    0x43FADC:'paddle_tick',0x43FABC:'paddle_overlay_deadline',0x43A8F0:'paddle_overlay_sprite',
    0x43A8B0:'paddle_overlay_width',0x43FA88:'lightning_x',0x43FA8C:'lightning_y',
    0x43FAF0:'lightning_frames',
    0x4228A8:'device_reset_requested',0x4228AC:'surface_restore_requested',
    0x4228A0:'display_buffer_count',FONT_BANK:'font_bank'})
ENTRIES={'current_time':0x403450,'elapsed':0x4034F0,'redraw_mode':0x4036B0,
    'dispatch_frame':0x403730,'initialize_mode':0x4038D0,'cleanup_mode':0x403950,
    'initialize_game':0x40F4C0,'redraw_game':0x40F7A0,'draw_paddle':0x412EC0,
    'refresh_score':0x415880,'draw_score':0x4158D0,'finish_game':0x415C10,
    'reset_round':0x415C40,'restart_round':0x415DF0,'dispose_game':0x416430,'clear_all_entities':0x4164A0}
MODE_ENTRIES={'initialize':[0x40DFC0,0x40F4C0,0x40C1A0,0x406440,0x407420],
    'redraw':[0x40E0E0,0x40F7A0,0x40C2B0,0x406590,0x4075D0],
    'frame':[0x40E330,0x40F8B0,0x40C3B0,0x406730,0x407990],
    'cleanup':[0x40F010,0x416430,0x40CF20,0x407370,0x407AE0]}
# Argument kinds distinguish pointer-sized surfaces, literal paths and scalars.
RUNTIME_BOUNDARIES=[('load_saved_palette',0x4098F0,'s'),('palette_transition',0x40A340,'iiiii'),
    ('clear_surface',0x409F10,'pi'),('reset_regions',0x408070,''),
    ('load_pcx',0x409BB0,'psiii'),('load_sprite_bank',0x404610,'iis'),
    ('capture_sprite',0x4042B0,'iiiii'),('load_sound',0x405990,'is'),
    ('bind_board_surface',0x409000,'p'),('bind_display_surface',0x409020,'p'),
    ('draw_text',0x404EE0,'iiis'),('draw_centered_text',0x404F80,'iiis'),
    ('release_sounds',0x4058B0,''),('release_sprite_banks',0x403CB0,''),
    ('finalize_game_resources',0x401DA0,'')]
CounterSignature=C.CFUNCTYPE(C.c_int32,C.c_void_p)
TickSignature=C.CFUNCTYPE(C.c_uint32)
RESTORED_FRAME={'current_time','elapsed','update_score','draw_paddle','restart_round'}
FRAME_FUNCTIONS={'current_time':'current_time','elapsed':'elapsed','update_score':'refresh_score',
                 'draw_paddle':'draw_paddle','restart_round':'restart_round'}


def checked(oracle,function,fallback=None):
    def callback(*args):
        try:return function(*args)
        except Exception as error:
            oracle.errors.append(repr(error));return fallback
    return callback


class RuntimeNative(CoreNative):
    def __init__(self,library):
        super().__init__(library)
        self.runtime_sprites=[[Sprite() for _ in range(255)] for _ in range(3)]
        self.primary,self.secondary=Surface(self.vtable),Surface(self.vtable)
        self.surface_names={self.surface_pointer:'board',C.addressof(self.primary):'primary',
                            C.addressof(self.secondary):'secondary',CoreTarget.BACKGROUND:'background'}
        self.saved=(C.c_uint8*1024).in_dll(self.lib,'dxball_saved_palette')
        self.live=(C.c_uint8*1024).in_dll(self.lib,'dxball_live_palette')
        self.runtime_callbacks=[]
        table=(C.c_void_p*15).in_dll(self.lib,'dxball_runtime_ops')
        for i,(name,_,kinds) in enumerate(RUNTIME_BOUNDARIES):
            signature=C.CFUNCTYPE(None,*[C.c_char_p if k=='s' else C.c_size_t if k=='p' else C.c_int32 for k in kinds])
            callback=signature(checked(self,lambda *a,name=name,kinds=kinds:self.runtime_boundary(name,kinds,a)))
            self.runtime_callbacks.append(callback);table[i]=C.cast(callback,C.c_void_p).value
        mode_table=(C.c_void_p*22).in_dll(self.lib,'dxball_mode_ops')
        for op,group in enumerate(MODE_ENTRIES):
            for mode in range(5):
                if mode==1:
                    function={'initialize':'initialize_game','redraw':'redraw_game','frame':'game_frame','cleanup':'dispose_game'}[group]
                    mode_table[op*5+mode]=C.cast(getattr(self.lib,'dxball_'+function),C.c_void_p).value
                else:
                    signature=C.CFUNCTYPE(None,*([C.c_int32] if group=='cleanup' else []))
                    callback=signature(checked(self,lambda *a,group=group,mode=mode:self.mode_boundary(group,mode,a)))
                    self.runtime_callbacks.append(callback);mode_table[op*5+mode]=C.cast(callback,C.c_void_p).value
        for i,group in enumerate(('device','synchronize'),20):
            callback=C.CFUNCTYPE(None)(checked(self,lambda group=group:self.mode_boundary(group,-1,())))
            self.runtime_callbacks.append(callback);mode_table[i]=C.cast(callback,C.c_void_p).value
        table=(C.c_void_p*12).in_dll(self.lib,'dxball_frame_ops')
        for i,(name,_,_) in enumerate(FRAME_BOUNDARIES):
            if name in RESTORED_FRAME:table[i]=C.cast(getattr(self.lib,'dxball_'+FRAME_FUNCTIONS[name]),C.c_void_p).value
        self.clock_callbacks=[TickSignature(checked(self,self.time_ms,0)),
            CounterSignature(checked(self,lambda p:self.counter_api('frequency',p),0)),
            CounterSignature(checked(self,lambda p:self.counter_api('counter',p),0))]
        table=(C.c_void_p*3).in_dll(self.lib,'dxball_clock_ops')
        for i,callback in enumerate(self.clock_callbacks):table[i]=C.cast(callback,C.c_void_p).value
        signature=C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_uint32,C.c_uint32,C.c_void_p,C.c_void_p,C.c_uint32)
        callback=signature(checked(self,self.blt_fast,-1));self.runtime_callbacks.append(callback)
        self.vtable[7]=C.cast(callback,C.c_void_p).value
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            f.argtypes=[C.c_uint32]*2 if name=='elapsed' else [C.c_int32] if name in ('cleanup_mode','dispose_game') else []
            f.restype=C.c_uint32 if name=='current_time' else C.c_int32 if name in ('elapsed','dispatch_frame') else None

    def normalize(self,surface):return self.surface_names.get(surface,surface)
    def runtime_boundary(self,name,kinds,args):
        args=tuple(self.normalize(a) if k=='p' else a.decode() if k=='s' else a for k,a in zip(kinds,args))
        self.events.append(('runtime',name,*args,self.observed(),bytes(self.saved).hex()))
    def mode_boundary(self,group,mode,args):
        self.events.append(('mode',group,mode,*args,self.observed()))
        if group=='device':
            self.mode.value=4;self.extra[0x425974].value=0;self.extra[0x425978].value=4
        elif group=='frame' and self.requested_next is not None:
            self.extra[0x425974].value=1;self.extra[0x425978].value=self.requested_next
    def time_ms(self):
        value=self.time_script.pop(0) if self.time_script else self.now
        self.events.append(('clock','time',value,self.observed()));return value
    def counter_api(self,name,pointer):
        low,high,result=self.frequency_value if name=='frequency' else self.counter_value
        C.memmove(pointer,struct.pack('<Ii',low,high),8)
        self.events.append(('clock',name,low,high,result,self.observed()));return result
    def board_blt(self,destination,rect,source,source_rect,flags,fx):
        assert fx is None
        coordinates=struct.unpack('<4i',C.string_at(rect,16))
        assert coordinates==struct.unpack('<4i',C.string_at(source_rect,16))
        self.events.append(('blt',self.normalize(destination),self.normalize(source),coordinates,flags,self.observed()))
        return 0
    def blt_fast(self,destination,x,y,source,rect,flags):
        self.events.append(('blt-fast',self.normalize(destination),x,y,self.normalize(source),
                            struct.unpack('<4i',C.string_at(rect,16)),flags,self.observed()))
        return 0
    def restore(self,destination,x,y,source,rect,flags):
        self.events.append(('restore',self.normalize(destination),x,y,self.normalize(source),
                           (rect.contents.left,rect.contents.top,rect.contents.right,rect.contents.bottom),flags))


class RuntimeTarget(CoreTarget):
    PRIMARY,SECONDARY=0x505000,0x505100
    def __init__(self):
        super().__init__()
        for name in RESTORED_FRAME:self.uc.hook_del(self.frame_hooks[name])
        self.surface_names={self.SURFACE:'board',self.PRIMARY:'primary',self.SECONDARY:'secondary',self.BACKGROUND:'background'}
        for surface in (self.PRIMARY,self.SECONDARY):self.write_u32(surface,self.VTABLE)
        self.runtime_hooks={}
        for name,address,kinds in RUNTIME_BOUNDARIES:
            def callback(*unused,name=name,kinds=kinds):
                args=tuple(self.normalize(a) if k=='p' else self._cstring(a).decode() if k=='s' else signed(a)
                           for k,a in zip(kinds,self._args(len(kinds))))
                self.events.append(('runtime',name,*args,self.observed(),self.read(SAVED_PALETTE,1024).hex()))
                self._return()
            hook=self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
            self._hooks.append(hook);self.runtime_hooks[name]=hook
        self.mode_body_hooks={}
        for group,entries in MODE_ENTRIES.items():
            for mode,address in enumerate(entries):
                if mode==1:continue
                def callback(*unused,group=group,mode=mode):
                    args=tuple(signed(a) for a in self._args(1)) if group=='cleanup' else ()
                    self.mode_boundary(group,mode,args);self._return()
                hook=self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
                self._hooks.append(hook);self.mode_body_hooks[group,mode]=hook
        self.mode_hooks={}
        for group,address in [('device',0x403A00),('synchronize',0x4035B0)]:
            def callback(*unused,group=group):self.mode_boundary(group,-1,());self._return()
            hook=self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
            self._hooks.append(hook);self.mode_hooks[group]=hook
        self.clock_hooks={}
        for slot,address,name in [(0x4413A4,0x50E000,'time'),(0x4412A0,0x50E010,'frequency'),(0x44129C,0x50E020,'counter')]:
            self.write_u32(slot,address)
            def callback(*unused,name=name):
                if name=='time':
                    value=self.time_script.pop(0) if self.time_script else self.now
                    self.events.append(('clock','time',value,self.observed()));self._return(value)
                else:
                    low,high,result=self.frequency_value if name=='frequency' else self.counter_value
                    self.write(self._args(1)[0],struct.pack('<Ii',low,high))
                    self.events.append(('clock',name,low,high,result,self.observed()));self._return(result,pop=4)
            hook=self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
            self._hooks.append(hook);self.clock_hooks[name]=hook
    def normalize(self,surface):return self.surface_names.get(surface,surface)
    def mode_boundary(self,group,mode,args):
        self.events.append(('mode',group,mode,*args,self.observed()))
        if group=='device':self.write_u32(MODE,4);self.write_u32(0x425974,0);self.write_u32(0x425978,4)
        elif group=='frame' and self.requested_next is not None:
            self.write_u32(0x425974,1);self.write_u32(0x425978,self.requested_next)
    def board_blt(self,*unused):
        destination,rect,source,source_rect,flags,fx=self._args(6)
        assert fx==0
        coordinates=struct.unpack('<4i',self.read(rect,16))
        assert coordinates==struct.unpack('<4i',self.read(source_rect,16))
        self.events.append(('blt',self.normalize(destination),self.normalize(source),coordinates,flags,self.observed()))
        self._return(pop=24)
    def _restore(self,*unused):
        destination,x,y,source,rect,flags=self._args(6)
        # Slot 7 is shared by score/paddle BltFast and board restore boundaries.
        self.events.append(('blt-fast',self.normalize(destination),x,y,self.normalize(source),
                            struct.unpack('<4i',self.read(rect,16)),flags,self.observed()))
        self._return(pop=24)


class RuntimeHarness(Harness):
    normalize_board_restores=True

    def __init__(self,library,native_type=RuntimeNative,target_type=RuntimeTarget):
        self.boards=(ROOT/'original/DEFAULT.BDS').read_bytes()
        super().__init__(library,native_type,target_type)
        self.cases=dict.fromkeys(ENTRIES,0);self.connected_frames=0
        self.n.bank[:]=self.boards;self.t.write(BANK,self.boards)
    def sprite(self,slot,width,height,bank=0):
        n,t=self.n,self.t
        sprite=n.runtime_sprites[bank][slot];sprite.width,sprite.height=width,height
        sprite.surface=0x900000+bank*0x1000+slot*4
        n.banks[bank].sprites[slot]=C.pointer(sprite)
        address=0x880000+(bank*255+slot)*48
        t.write(address,bytes(44));t.write_u32(address,sprite.surface)
        t.write(address+8,struct.pack('<2i',width,height));t.write_u32(BANKS+bank*1048+slot*4,address)
    def seed(self,grid=None):
        super().seed(self.boards[:400] if grid is None else grid)
        n,t=self.n,self.t
        n.mode.value=1;t.write_u32(MODE,1)
        self.state(REMAINING,100)
        for oracle in (n,t):
            oracle.time_script=[];oracle.frequency_value=(1000000,0,1);oracle.counter_value=(1000000,0,1)
            oracle.requested_next=None
        n.saved[:]=bytes((i*31+7)%256 for i in range(1024));t.write(SAVED_PALETTE,bytes(n.saved))
        n.live[:]=b'\x9a'*1024;t.write(LIVE_PALETTE,bytes(n.live))
        for name,value,address in [('primary_surface',C.addressof(n.primary),0x4228B4),('secondary_surface',C.addressof(n.secondary),0x4228B8)]:
            source_global(C.c_size_t, n.lib,'dxball_'+name).value=value;t.write_u32(address,t.PRIMARY if name=='primary_surface' else t.SECONDARY)
        for bank in range(3):
            n.banks[bank].count=0;n.banks[bank].mode=0
            t.write(BANKS+bank*1048+1020,bytes(8))
            for slot in range(1,180):self.sprite(slot,60 if slot==68 else 10,18 if slot>=64 else 8,bank)
        n.bank[:]=self.boards;t.write(BANK,self.boards)
    def compare(self,context):
        n,t=self.n,self.t
        assert not n.errors,(context,n.errors)
        assert bytes(n.tiles)==t.read(TILES,400),(context,'tiles')
        assert bytes(n.aux)==t.read(AUX,400),(context,'aux')
        assert bytes(n.saved)==t.read(SAVED_PALETTE,1024),(context,'saved palette')
        assert bytes(n.live)==t.read(LIVE_PALETTE,1024),(context,'live palette')
        for bank in range(3):
            assert (n.banks[bank].count,n.banks[bank].mode)==struct.unpack('<2i',t.read(BANKS+bank*1048+1020,8)),(context,'bank metadata',bank)
        assert n.observed()==t.observed(),(context,'globals',n.observed(),t.observed())
        for a,v in n.state.items():assert v.value==signed(t.read_u32(a)),(context,hex(a))
        assert n.mode.value==signed(t.read_u32(MODE)),(context,'mode')
        assert C.c_int32.in_dll(n.lib,'dxball_sprite_bank').value==signed(t.read_u32(SPRITE_BANK)),(context,'sprite bank')
        assert n.normalize(n.active.value)==t.normalize(t.read_u32(ACTIVE_SURFACE)),(context,'active surface')
        assert C.string_at(n.pixels,C.sizeof(n.pixels))==t.read(t.PIXELS,C.sizeof(n.pixels)),(context,'pixels')
        # Board cell restores use the rendering bridge in C and BltFast in the
        # target. Normalize this declared dependency, retaining every argument.
        target_events=[]
        for event in t.events:
            if self.normalize_board_restores and event[0]=='blt-fast' and event[6]==0x10 and event[5][2]-event[5][0]==30 and event[5][3]-event[5][1]==15:
                target_events.append(('restore',*event[1:7]))
            else:target_events.append(event)
        if n.events!=target_events:
            i=next((i for i,(a,b) in enumerate(zip(n.events,target_events)) if a!=b),min(len(n.events),len(target_events)))
            raise AssertionError((context,'events',i,n.events[i:i+1],target_events[i:i+1]))
        live=0
        for owner in SHAPES:
            nq,tq=n.queue(owner),t.queue(owner);assert nq==tq,(context,owner,nq,tq);live+=len(nq[0])
        for oracle in (n,t):
            assert sum(a['live'] for a in oracle.allocations.values())==live,(context,'lost allocation')
            assert not oracle.time_script,(context,'unused time script')
            for address,a in oracle.allocations.items():
                if not a['live']:
                    data=C.string_at(address,a['size']) if oracle is n else oracle.read(address,a['size'])
                    assert data==b'\xdd'*a['size'],(context,'write after free')
    def call(self,name,*args):
        nr=self.n.call('dxball_'+name,*args);tr=self.t.call(ENTRIES[name],*args)
        if nr is not None:assert nr==tr,(name,args,nr,tr)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1
    def populate(self,length=2,current=-1):
        for owner in SHAPES:
            for i in range(length):
                if owner=='particles':
                    self.n.lib.dxball_spawn_particle(100+i,200,1,-2,95,0);self.t.call(0x4148A0,100+i,200,1,-2,95,0)
                    self.n.queue(owner);self.t.queue(owner)
                else:self.add(owner,[i+10]*(SHAPES[owner][2]//4))
            pointers=[];pointer=self.n.owners[owner].first
            addresses=[];address=self.t.read_u32(SHAPES[owner][0]+4)
            while pointer:pointers.append(pointer);pointer=pointer.contents.next
            while address:addresses.append(address);address=self.t.read_u32(address+SHAPES[owner][2])
            cursor=(length-1 if current==-1 else current)
            self.n.owners[owner].current=pointers[cursor] if cursor>=0 and length else C.POINTER(SHAPES[owner][1])()
            self.t.write_u32(SHAPES[owner][0],addresses[cursor] if cursor>=0 and length else 0)


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu()
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    args=parser.parse_args();h=RuntimeHarness(args.library)
    # Clock uses only LowPart, frequency truncation and an ignored counter result.
    for enabled,divisor,failure,low,high in itertools.product((0,1,-1),(0,1000),(0,1),
            (0,1,999,1000,0x7fffffff,0xffffffff),(-3,0,7)):
        h.seed();h.setv('high_resolution_clock',enabled);h.setv('clock_divisor',divisor)
        h.n.frequency_value=h.t.frequency_value=(1000123,7,1-failure)
        h.n.counter_value=h.t.counter_value=(low,high,failure);h.n.now=h.t.now=0xfffffff1
        h.call('current_time')
    for now,start,interval in itertools.product((0,1,20,32,64,1000,0xffffffff),
            (0,1,20,1000,0xfffffff0,0xffffffff),(0,1,20,32,64,0x80000000)):
        h.seed();h.n.now=h.t.now=now;h.call('elapsed',start,interval)
    # Frame selection happens before the timer advances; raw overlay time is separate.
    for width,frame,attached,laser,now in itertools.product((30,59,60,120,240),range(4),(0,1),(0,1),(32,64,65,1000)):
        h.seed();h.setv('paddle_width',width);h.setv('paddle_frame',frame)
        h.setv('attached_ball_cue',attached);h.setv('bonus_8_active',laser)
        h.n.now=h.t.now=now;h.setv('paddle_overlay_deadline',now)
        h.setv('paddle_overlay_width',width);h.setv('paddle_overlay_sprite',128)
        h.call('draw_paddle')
    for laser,width in itertools.product((0,1),(1,7,59,60,120,240)):
        h.seed();h.setv('attached_ball_cue',1);h.setv('bonus_8_active',laser);h.setv('paddle_width',width)
        h.n.time_script=[0xfffffff0,0xfffffff1,0xfffffff2,0xfffffff3]
        h.t.time_script=list(h.n.time_script);h.call('draw_paddle')
    for score,lives in itertools.product((-1,0,1,99,999999999,1000000000,2147483647),(-10,0,1,3,10,11,20,21,30)):
        h.seed();h.state(SCORE,score);h.setv('lives',lives);h.call('draw_score')
        h.setv('displayed_score',score if lives%2 else score-1);h.call('refresh_score')
    for paused,buffers,restore in itertools.product((0,1,2),(-1,0,1,2),(0,1)):
        h.seed();h.setv('paused',paused);h.setv('display_buffer_count',buffers);h.setv('draw_to_primary',restore)
        h.call('redraw_game')
    # Every owner and cursor; counters are NOT reset by queue cleanup.
    for length in range(4):
        for current in [-2]+list(range(length)):
            h.seed();h.populate(length,current)
            h.setv('ball_count',77);h.setv('projectile_count',88);h.call('clear_all_entities')
    for board,width,mouse in itertools.product(range(50),(59,120),(20,320,618)):
        h.seed(h.boards[board*400:(board+1)*400]);h.setv('paddle_width',width);h.setv('mouse_x',mouse)
        for name in ('bonus_3_active','bonus_7_active','bonus_8_active','bonus_9_active','bonus_12_active',
                     'bonus_14_active','bonus_17_active','bonus_18_active','bonus_3_ticks','restart_requested','level_changed'):
            h.setv(name,17)
        h.call('reset_round');assert h.n.owners['balls'].current.contents.attached==1
    for restart,changed,lives in itertools.product((0,1,2),(0,1,2),(-1,0,1,3)):
        h.seed();h.populate();h.setv('restart_requested',restart);h.setv('level_changed',changed);h.setv('lives',lives)
        h.n.aux[:]=b'\xb1'*400;h.t.write(AUX,bytes(h.n.aux));h.call('restart_round')
    for fade,restart in itertools.product((-1,0,1),(0,1,2)):
        h.seed();h.populate();h.setv('restart_requested',restart);h.call('dispose_game',fade)
    h.seed();h.call('finish_game')
    for restore,width,mouse in itertools.product((0,1),(30,60,120),(20,320,618)):
        h.seed();h.setv('draw_to_primary',restore);h.setv('paddle_width',width);h.setv('mouse_x',mouse)
        h.call('initialize_game')
    for mode in (-3,0,1,2,3,4,5):
        for name in ('initialize_mode','redraw_mode','cleanup_mode'):
            h.seed();h.n.mode.value=mode;h.t.write_u32(MODE,mode)
            h.call(name,*([1] if name=='cleanup_mode' else []))
    for mode,device,end,next_mode in itertools.product((-1,0,1,2,3,4,5),(0,1),(0,1),(0,1,3,5)):
        h.seed();h.ball(attached=1);h.n.mode.value=mode;h.t.write_u32(MODE,mode)
        h.setv('device_reset_requested',device);h.setv('surface_restore_requested',1)
        h.setv('end_requested',end);h.setv('return_to_menu',next_mode);h.call('dispatch_frame')
    for mode,next_mode in itertools.product((0,2,3,4),(0,1,3,5)):
        h.seed();h.n.mode.value=mode;h.t.write_u32(MODE,mode)
        h.n.requested_next=h.t.requested_next=next_mode;h.call('dispatch_frame')
    # Actual new-game -> launch -> death -> reset, followed by terminal cleanup.
    h.seed();h.call('initialize_game')
    for frame in range(36):
        if frame==2:h.setv('mouse_action',1)
        if frame in (10,20,30):
            p=h.n.owners['balls'].first;a=h.t.read_u32(SHAPES['balls'][0]+4)
            p.contents.y=478;p.contents.attached=0;h.t.write_u32(a+4,478);h.t.write_u32(a+40,0)
        h.n.now=h.t.now=1000+frame*20
        h.call('dispatch_frame');h.connected_frames+=1
    assert h.n.mode.value==3,'last life must leave gameplay through the real reset/dispatcher bodies'
    report={'target_sha256':hashlib.sha256((ROOT/'original/DXBALL.EXE').read_bytes()).hexdigest(),
        'cases':h.cases,'total':sum(h.cases.values()),'connected_frames':h.connected_frames,
        'connected_frames_are_subset':True,'restored_frame_dependencies':sorted(RESTORED_FRAME),
        'scope':'unmodified lifecycle/mode/clock/paddle/score bodies; connected game frame and entity owners; resource/backend and non-game modes remain explicit controlled boundaries'}
    p=ROOT/'build/reports/runtime-differential.json';p.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
