#!/usr/bin/env python3
"""Execute original lightning, dirty-region and presentation bodies together."""
import argparse
import ctypes as C
import hashlib
import itertools
import json
import os
from pathlib import Path
import random
import struct
import sys

from unicorn import UC_HOOK_CODE
from target_oracle import ROOT, TILES, MODE
from resources_oracle import Surface, BANKS, LIVE_PALETTE
from test_gameplay_differential import REMAINING, REDUCED, signed
from test_core_differential import GLOBALS, FRAME_BOUNDARIES
from test_runtime_differential import RuntimeNative, RuntimeTarget, RuntimeHarness, FRAME_FUNCTIONS

GLOBALS.update({0x4305D8:'present_count',0x4382EC:'dirty_page',0x42289C:'clip_regions',
                0x4228C8:'wait_vertical_blank',0x4228CC:'frame_wait_tick'})
ENTRIES={'last_brick':0x415F40,'draw_last_brick':0x416370,'reset_regions':0x408070,
    'queue_region':0x408990,'invalidate_region':0x408B70,'restore_effect_region':0x408A50,
    'bind_board_surface':0x409000,'bind_display_surface':0x409020,
    'draw_effect_sprite':0x4082F0,'draw_reduced_sprite':0x4085D0,'restore_regions':0x408CC0,
    'sort_present_regions':0x4094E0,'present_regions_now':0x409100,
    'present':0x409040,'wait_frames':0x409610,'animate_palette':0x40A970}
DIRTY,COUNTS,PRESENT,KEYS,LIGHTNING=0x4305E8,0x4305E0,0x426990,0x42E698,0x43A8C8
FX_SURFACE,RESTORE_SURFACE=0x42E690,0x4382E8
LOST,BUSY=0x887601C2,0x8876021C


class DisplayNative(RuntimeNative):
    def __init__(self,library):
        super().__init__(library)
        self.dirty=(C.c_int32*8000).in_dll(self.lib,'dxball_dirty_regions')
        self.counts=(C.c_int32*2).in_dll(self.lib,'dxball_dirty_counts')
        self.present_rects=(C.c_int32*8000).in_dll(self.lib,'dxball_present_regions')
        self.keys=(C.c_int32*2000).in_dll(self.lib,'dxball_present_keys')
        self.lightning=(C.c_int32*4).in_dll(self.lib,'dxball_lightning_rect')
        self.effect_value=C.c_size_t.in_dll(self.lib,'dxball_effect_surface')
        self.restore_value=C.c_size_t.in_dll(self.lib,'dxball_restore_surface')
        self.palette_table=(C.c_void_p*7)();self.ddraw_table=(C.c_void_p*23)()
        self.palette,self.ddraw=Surface(self.palette_table),Surface(self.ddraw_table)
        C.c_void_p.in_dll(self.lib,'dxball_direct_palette').value=C.addressof(self.palette)
        C.c_void_p.in_dll(self.lib,'dxball_direct_draw').value=C.addressof(self.ddraw)
        self.display_callbacks=[]
        def fatal(function):
            def callback(*args):
                try:return function(*args)
                except Exception as error:
                    # A failing HRESULT callback would make native retry loops
                    # run forever. Fail the oracle instead of retaining errors.
                    print('Native display boundary failed:',repr(error),flush=True)
                    os._exit(1)
            return callback
        def bind(table,slot,signature,function):
            callback=signature(fatal(function));self.display_callbacks.append(callback)
            table[slot]=C.cast(callback,C.c_void_p).value
        for slot,signature,function in [
            (22,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_void_p),self.desc),
            (25,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_void_p,C.c_void_p,C.c_uint32,C.c_void_p),self.lock),
            (32,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_void_p),self.unlock)]:
            bind(self.vtable,slot,signature,function)
        bind((C.c_void_p*3).in_dll(self.lib,'dxball_clock_ops'),0,C.CFUNCTYPE(C.c_uint32),self.time_ms)
        bind(self.vtable,11,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_void_p,C.c_uint32),self.flip)
        bind(self.palette_table,6,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_uint32,C.c_uint32,C.c_uint32,C.c_void_p),self.palette_entries)
        bind(self.ddraw_table,22,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_uint32,C.c_void_p),self.vertical_blank)
        bind((C.c_void_p*2).in_dll(self.lib,'dxball_display_ops'),0,C.CFUNCTYPE(None,*([C.c_int32]*4)),self.update_sound)
        bind((C.c_void_p*2).in_dll(self.lib,'dxball_display_ops'),1,C.CFUNCTYPE(None),self.recover)
        tables=[('dxball_frame_ops',12,{i:FRAME_FUNCTIONS.get(name,name) for i,(name,_,_) in enumerate(FRAME_BOUNDARIES)}),
                ('dxball_runtime_ops',15,{3:'reset_regions',8:'bind_board_surface',9:'bind_display_surface'}),
                ('dxball_render_ops',3,{0:'draw_sprite',1:'restore_board_region',2:'invalidate_region'}),
                ('dxball_effect_ops',5,{2:'draw_keyed_sprite',3:'draw_reduced_sprite',4:'restore_effect_region'})]
        for symbol,length,functions in tables:
            table=(C.c_void_p*length).in_dll(self.lib,symbol)
            for i,name in functions.items():table[i]=C.cast(getattr(self.lib,'dxball_'+name),C.c_void_p).value
        C.c_void_p.in_dll(self.lib,'dxball_particle_region').value=C.cast(self.lib.dxball_queue_region,C.c_void_p).value
        counts={'queue_region':4,'invalidate_region':4,'restore_effect_region':4,
                'draw_effect_sprite':3,'draw_reduced_sprite':3,'sort_present_regions':2,
                'wait_frames':1,'animate_palette':3,'bind_board_surface':1,'bind_display_surface':1}
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name);f.restype=None
            f.argtypes=[C.c_size_t] if name.startswith('bind_') else [C.c_int32]*counts.get(name,0)

    def display_observed(self):
        return (tuple(self.counts),self.extra[0x4382EC].value,self.extra[0x4305D8].value,
                self.extra[0x4228C8].value,self.extra[0x4228CC].value,self.extra[0x42289C].value)
    def time_ms(self):
        assert not self.errors,self.errors[:3]
        assert len(self.events)<10000,'clock callback budget exhausted'
        value=self.time_script.pop(0) if self.time_script else self.now
        if not self.time_script:self.now=(value+self.tick_step)&0xffffffff
        self.events.append(('clock','time',value,self.observed()));return value
    def desc(self,surface,pointer):
        assert self.normalize(surface) in ('board','primary','secondary')
        self.fill_desc(pointer);self.events.append(('get-desc',self.normalize(surface)));return 0
    def lock(self,surface,rect,pointer,flags,event):
        assert self.normalize(surface) in ('board','primary','secondary') and rect is None and flags==0 and event is None
        result=-1 if self.lock_failures else 0;self.lock_failures=max(0,self.lock_failures-1)
        self.fill_desc(pointer);self.events.append(('lock',self.normalize(surface),result));return result
    def unlock(self,surface,pointer):
        assert self.normalize(surface) in ('board','primary','secondary') and pointer is None
        self.events.append(('unlock',self.normalize(surface)));return 0
    def flip(self,surface,target,flags):
        assert target is None
        result=self.flip_script.pop(0) if self.flip_script else 0
        self.events.append(('flip',self.normalize(surface),flags,signed(result),self.observed(),self.display_observed()))
        return signed(result)
    def palette_entries(self,palette,flags,first,count,entries):
        assert palette==C.addressof(self.palette)
        self.events.append(('palette',flags,first,count,C.string_at(entries,count*4).hex(),self.observed(),self.display_observed()))
        return 0
    def vertical_blank(self,ddraw,flags,event):
        assert ddraw==C.addressof(self.ddraw) and event is None
        self.events.append(('vblank',flags,self.observed(),self.display_observed()));return 0
    def recover(self):self.events.append(('recover',self.observed(),self.display_observed()))
    def update_sound(self,*args):self.events.append(('sound-update',*args,self.observed(),self.display_observed()))
    def board_blt(self,*args):
        super().board_blt(*args);self.events[-1]+= (self.display_observed(),)
        return 0
    def blt_fast(self,*args):
        super().blt_fast(*args);self.events[-1]+= (self.display_observed(),)
        return 0


class DisplayTarget(RuntimeTarget):
    PALETTE,DDRAW=0x506000,0x506100
    # Original selection sort can exceed the old core budget after a full-board
    # redraw enqueues hundreds of rectangles. Keep a finite execution ceiling.
    instruction_limit=10000000
    def __init__(self):
        super().__init__()
        for name,hook in self.frame_hooks.items():
            if name not in FRAME_FUNCTIONS:self.uc.hook_del(hook)
        for name in ('reset_regions','bind_board_surface','bind_display_surface'):
            self.uc.hook_del(self.runtime_hooks[name])
        for hook in self.board_hooks.values():self.uc.hook_del(hook)
        self.uc.hook_del(self.region_hook)
        for name in ('keyed-sprite','reduced-sprite','region'):self.uc.hook_del(self.boundary_hooks[name])
        self.write_u32(self.PALETTE,0x506200);self.write_u32(self.DDRAW,0x506300)
        self.write_u32(0x4228C0,self.PALETTE);self.write_u32(0x4228B0,self.DDRAW)
        for table,slot,address,callback in [(self.VTABLE,11,0x50E100,self.flip),
                (0x506200,6,0x50E110,self.palette_entries),(0x506300,22,0x50E120,self.vertical_blank)]:
            assert address!=self.RETURN,'COM callback must not alias the oracle return sentinel'
            self.write_u32(table+slot*4,address)
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address))
        self.display_hooks={}
        for address,callback in [(0x403640,self.recover),(0x405D80,self.update_sound)]:
            hook=self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
            self._hooks.append(hook);self.display_hooks[address]=hook
    def display_observed(self):
        return (struct.unpack('<2i',self.read(COUNTS,8)),signed(self.read_u32(0x4382EC)),signed(self.read_u32(0x4305D8)),
                signed(self.read_u32(0x4228C8)),signed(self.read_u32(0x4228CC)),signed(self.read_u32(0x42289C)))
    def flip(self,*unused):
        surface,target,flags=self._args(3);assert target==0
        result=self.flip_script.pop(0) if self.flip_script else 0
        self.events.append(('flip',self.normalize(surface),flags,signed(result),self.observed(),self.display_observed()))
        self._return(result,pop=12)
    def palette_entries(self,*unused):
        palette,flags,first,count,entries=self._args(5);assert palette==self.PALETTE
        self.events.append(('palette',flags,first,count,self.read(entries,count*4).hex(),self.observed(),self.display_observed()))
        self._return(pop=20)
    def vertical_blank(self,*unused):
        ddraw,flags,event=self._args(3);assert ddraw==self.DDRAW and event==0
        self.events.append(('vblank',flags,self.observed(),self.display_observed()));self._return(pop=12)
    def recover(self,*unused):self.events.append(('recover',self.observed(),self.display_observed()));self._return()
    def update_sound(self,*unused):
        self.events.append(('sound-update',*(signed(a) for a in self._args(4)),self.observed(),self.display_observed()));self._return()
    def board_blt(self,*unused):
        super().board_blt();self.events[-1]+= (self.display_observed(),)
    def _restore(self,*unused):
        super()._restore();self.events[-1]+= (self.display_observed(),)
    def clock_tick(self):
        assert len(self.events)<10000,'clock callback budget exhausted'
        value=self.time_script.pop(0) if self.time_script else self.now
        if not self.time_script:self.now=(value+self.tick_step)&0xffffffff
        self.events.append(('clock','time',value,self.observed()));self._return(value)
    def desc(self,*unused):
        surface,pointer=self._args(2);assert self.normalize(surface) in ('board','primary','secondary')
        self.fill_desc(pointer);self.events.append(('get-desc',self.normalize(surface)));self._return(pop=8)
    def lock(self,*unused):
        surface,rect,pointer,flags,event=self._args(5)
        assert self.normalize(surface) in ('board','primary','secondary') and (rect,flags,event)==(0,0,0)
        result=-1 if self.lock_failures else 0;self.lock_failures=max(0,self.lock_failures-1)
        self.fill_desc(pointer);self.events.append(('lock',self.normalize(surface),result));self._return(result,pop=20)
    def unlock(self,*unused):
        surface,pointer=self._args(2);assert self.normalize(surface) in ('board','primary','secondary') and pointer==0
        self.events.append(('unlock',self.normalize(surface)));self._return(pop=8)


class DisplayHarness(RuntimeHarness):
    normalize_board_restores=False
    def __init__(self,library,native_type=DisplayNative,target_type=DisplayTarget):
        super().__init__(library,native_type,target_type)
        self.cases=dict.fromkeys(ENTRIES,0);self.connected_frames=0
        # Replace the controlled WinMM callback with the same advancing clock.
        self.t.uc.hook_del(self.t.clock_hooks['time'])
        self.t._hooks.append(self.t.uc.hook_add(UC_HOOK_CODE,lambda *a:self.t.clock_tick(),begin=0x50E000,end=0x50E000))
    def sprite(self,slot,width,height,bank=0):
        super().sprite(slot,width,height,bank)
        sprite=self.n.runtime_sprites[bank][slot]
        sprite.rect.left=0;sprite.rect.top=0
        sprite.rect.right=width;sprite.rect.bottom=height
        address=0x880000+(bank*255+slot)*48
        self.t.write(address+20,struct.pack('<4i',0,0,width,height))
    def seed(self,grid=None):
        super().seed(grid);n,t=self.n,self.t
        for oracle in (n,t):oracle.tick_step=20;oracle.flip_script=[]
        n.dirty[:]=[0]*8000;n.counts[:]=[0]*2;n.present_rects[:]=[0]*8000;n.keys[:]=[0]*2000;n.lightning[:]=[0]*4
        for address,length in [(DIRTY,32000),(COUNTS,8),(PRESENT,32000),(KEYS,8000),(LIGHTNING,16)]:t.write(address,bytes(length))
        n.restore_value.value=n.surface_pointer;t.write_u32(RESTORE_SURFACE,t.SURFACE)
        n.effect_value.value=C.addressof(n.secondary);t.write_u32(FX_SURFACE,t.SECONDARY)
        self.sprite(1,159,479,2)
    def compare(self,context):
        super().compare(context);n,t=self.n,self.t
        for data,address in [(n.dirty,DIRTY),(n.counts,COUNTS),(n.present_rects,PRESENT),(n.keys,KEYS),(n.lightning,LIGHTNING)]:
            assert C.string_at(data,C.sizeof(data))==t.read(address,C.sizeof(data)),(context,'display buffer',hex(address))
        assert n.normalize(n.effect_value.value)==t.normalize(t.read_u32(FX_SURFACE)),(context,'effect surface')
        assert n.normalize(n.restore_value.value)==t.normalize(t.read_u32(RESTORE_SURFACE)),(context,'restore surface')
        assert n.now==t.now,(context,'clock advancement',n.now,t.now)
        assert n.flip_script==t.flip_script,(context,'flip results')
    def call(self,name,*args):
        nr=self.n.call('dxball_'+name,*args);tr=self.t.call(ENTRIES[name],*args)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1
    def phase(self,name,address):
        self.n.call('dxball_'+name);self.t.call(address);self.compare((name,'connected'))
    def rects(self,rectangles,page=0,present=False):
        if present:
            self.setv('present_count',len(rectangles))
            for i,rect in enumerate(rectangles):
                self.n.present_rects[i*4:i*4+4]=rect;self.t.write(PRESENT+i*16,struct.pack('<4i',*rect))
        else:
            self.n.counts[page]=len(rectangles);self.t.write_u32(COUNTS+page*4,len(rectangles))
            for i,rect in enumerate(rectangles):
                self.n.dirty[i*8+page*4:i*8+page*4+4]=rect;self.t.write(DIRTY+i*32+page*16,struct.pack('<4i',*rect))


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu()
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    args=parser.parse_args();h=DisplayHarness(args.library);rng=random.Random(0xD8BA11)
    h.seed();h.n.dirty[:]=[19]*8000;h.t.write(DIRTY,C.string_at(h.n.dirty,32000))
    h.n.present_rects[:]=[23]*8000;h.t.write(PRESENT,C.string_at(h.n.present_rects,32000))
    h.n.keys[:]=[17]*2000;h.t.write(KEYS,C.string_at(h.n.keys,8000));h.call('reset_regions')
    for name,address,surface in [('bind_board_surface',RESTORE_SURFACE,'board'),('bind_display_surface',FX_SURFACE,'secondary')]:
        for native,target in [(h.n.surface_pointer,h.t.SURFACE),(C.addressof(h.n.secondary),h.t.SECONDARY)]:
            h.seed();h.n.call('dxball_'+name,native);h.t.call(ENTRIES[name],target)
            h.compare(name);h.cases[name]+=1
    rect_cases=[(-1,-1,10,10),(0,0,0,0),(640,480,640,480),(641,481,650,490),
                (-30,-20,-1,-1),(600,460,700,550),(20,50,50,65)]
    for page,reduced,restore,buffers,count,copy_count in itertools.product((0,1),(0,1,2),(0,1),(0,1),(0,999,1000),(0,1999,2000)):
        for name in ('queue_region','invalidate_region','restore_effect_region'):
            h.seed();h.setv('dirty_page',page);h.state(REDUCED,reduced);h.setv('draw_to_primary',restore)
            h.setv('display_buffer_count',buffers);h.setv('present_count',copy_count)
            h.n.counts[:]=[count,count];h.t.write(COUNTS,struct.pack('<2i',count,count))
            h.call(name,-1,50,45,65)
    for name,page,reduced,count,slot,x,y in itertools.product(('draw_effect_sprite','draw_reduced_sprite'),(0,1),(0,1,2),(0,999,1000),(31,38,68),(-1,20,639),(-1,50,479)):
        h.seed();h.setv('dirty_page',page);h.state(REDUCED,reduced);h.setv('present_count',1999)
        h.n.counts[page]=count;h.t.write_u32(COUNTS+page*4,count);h.call(name,slot,x,y)
    for page,clip,reduced,copy_count in itertools.product((0,1),(0,1,2),(0,1,2),(0,1998,2000)):
        h.seed();h.setv('dirty_page',page);h.setv('clip_regions',clip);h.state(REDUCED,reduced)
        h.setv('present_count',copy_count);h.rects(rect_cases,page);h.call('restore_regions')
    for count in (0,1,2,7,33):
        for trial in range(12):
            h.seed();rectangles=[tuple(rng.randrange(-40,700) for _ in range(4)) for _ in range(count)]
            h.rects(rectangles,present=True)
            keys=[rng.randrange(-50,50) for _ in range(count)]
            h.n.keys[:count]=keys;h.t.write(KEYS,struct.pack('<'+'i'*count,*keys))
            h.call('sort_present_regions',0,count-1)
    for clip,count in itertools.product((0,1,2),(0,1,2,7,33,128)):
        for trial in range(8):
            h.seed();h.setv('clip_regions',clip)
            rectangles=[]
            for i in range(count):
                x=rng.randrange(-40,680);y=rng.randrange(-40,520)
                rectangles.append((x,y,x+rng.randrange(0,90),y+rng.randrange(0,90)))
            h.rects(rectangles,present=True);h.call('present_regions_now')
    for clip in (0,1):
        h.seed();h.setv('clip_regions',clip);h.rects(rect_cases+[(20,50,51,65),(51,50,81,65)],present=True);h.call('present_regions_now')
    for disabled,first,last,rotate in itertools.product((0,1,2),(0,15,224),(0,15,231,255),(0,1,2)):
        if first>last:continue
        h.seed();h.setv('cursor_warp_disabled',disabled);h.call('animate_palette',first,last,rotate)
    for frames,vblank in itertools.product((-1,0,1,3,30),(0,1,2)):
        h.seed();h.setv('wait_vertical_blank',vblank);h.call('wait_frames',frames)
    for start,times in [(100,[100,116,117,119]),(0xfffffff0,[0xfffffff0,1]),(100,[99,103])]:
        h.seed();h.setv('frame_wait_tick',start)
        h.n.time_script=list(times);h.t.time_script=list(times);h.call('wait_frames',1)
    for page,reduced,vblank,results in itertools.product((0,1),(0,1,2),(0,1),([0],[BUSY,0],[BUSY,BUSY,0],[LOST],[1])):
        h.seed();h.setv('dirty_page',page);h.state(REDUCED,reduced);h.setv('wait_vertical_blank',vblank)
        if reduced==0:h.n.flip_script=list(results);h.t.flip_script=list(results)
        h.rects(rect_cases[:3],present=True);h.call('present')
    # Countdown wrap, inclusive expiry and half/divide rounding.
    for deadline,now in itertools.product((0,1,1000,0x7fffffff,0xfffffff0),(0,1,999,1000,1001,0x7fffffff,0xffffffff)):
        h.seed(bytes([2])*400);h.n.tiles[85]=8;h.t.write(TILES,bytes(h.n.tiles));h.n.now=h.t.now=now
        h.setv('last_brick_deadline',signed(deadline));h.call('last_brick')
    for x,y,reduced,width,height in itertools.product((0,10,19),(0,10,19),(0,1,2),(1,159,639),(1,479)):
        h.seed(bytes(400));h.n.tiles[x+y*20]=8;h.t.write(TILES,bytes(h.n.tiles));h.state(REDUCED,reduced)
        h.sprite(1,width,height,2);h.setv('last_brick_deadline',999);h.call('last_brick');h.call('draw_last_brick')
    h.seed(bytes(400));h.n.tiles[1]=8;h.n.tiles[380]=7;h.n.tiles[21]=1;h.t.write(TILES,bytes(h.n.tiles))
    h.setv('last_brick_deadline',999);h.call('last_brick')
    for frames in (-1,0,1,4,9):h.seed();h.setv('lightning_frames',frames);h.call('draw_last_brick')
    # All twelve original frame phases execute, through actual dirty rendering.
    for reduced,clip,vblank in itertools.product((0,1),(0,1),(0,1)):
        h.seed(bytes([2])*400);h.n.tiles[85]=8;h.t.write(TILES,bytes(h.n.tiles));h.state(REMAINING,1)
        h.state(REDUCED,reduced);h.setv('clip_regions',clip);h.setv('wait_vertical_blank',vblank)
        h.ball(attached=1);h.setv('last_brick_deadline',999)
        for frame in range(24):
            h.phase('game_frame',0x40F8B0);h.connected_frames+=1
    report={'target_sha256':hashlib.sha256((ROOT/'original/DXBALL.EXE').read_bytes()).hexdigest(),
            'cases':h.cases,'total':sum(h.cases.values()),'connected_frames':h.connected_frames,
            'integration_frames_separate':True,'scope':'unmodified lightning, dirty-region, merge/sort, palette, wait and presentation bodies; all twelve real gameplay phases; controlled COM/audio/recovery/resource/glyph/non-game boundaries'}
    p=ROOT/'build/reports/display-differential.json';p.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
