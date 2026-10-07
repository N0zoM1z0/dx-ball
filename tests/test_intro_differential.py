#!/usr/bin/env python3
"""Connected original splash/menu controllers, waves, point pixels and palettes."""
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
from target_oracle import ROOT, MODE
from resources_oracle import BANKS, FONT_BANK, Desc
from test_core_differential import GLOBALS
from test_platform_differential import PlatformNative, PlatformTarget, PlatformHarness
from test_runtime_differential import MODE_ENTRIES

ENTRIES={'initialize_intro':0x40DFC0,'redraw_intro':0x40E0E0,'intro_frame':0x40E330,
    'intro_key':0x40E430,'initialize_intro_points':0x40E570,'dispose_intro':0x40F010,
    'initialize_splash':0x407420,'redraw_splash':0x4075D0,'splash_frame':0x407990,
    'splash_key':0x407AB0,'dispose_splash':0x407AE0,'wave_x':0x402520,'wave_y':0x402560,
    'update_intro_points':0x40ED40,'raw_sine':0x402340,'raw_cosine':0x4023A0,
    'draw_scroller_wave':0x407BA0,'update_scroller':0x407C90,
    'draw_waving_credits':0x407D80,'pulse_splash_palette':0x407EF0}
GLOBALS.update({0x421084:'text_spacing',0x438B20:'intro_tick',
    0x438B24:'intro_cursor_x',0x438B28:'intro_cursor_y',0x426970:'scroller_length',
    0x426974:'credit_second_y',0x426978:'credit_first_y',0x42697C:'scroller_shift',
    0x426980:'scroller_index',0x426984:'scroller_reserved',0x426988:'credit_angle',
    0x42698C:'scroller_advance',0x4225C0:'splash_span',0x4225C4:'splash_offset',0x4225C8:'splash_phase'})
BODY_NAMES={'initialize':('initialize_intro','initialize_splash'),
    'redraw':('redraw_intro','redraw_splash'),'frame':('intro_frame','splash_frame'),
    'cleanup':('dispose_intro','dispose_splash')}
POINTS,OFFSETS,COLORS=0x438B30,0x439D20,0x4224B8


class IntroNative(PlatformNative):
    def __init__(self,library):
        super().__init__(library)
        self.points=(C.c_int32*(287*4)).in_dll(self.lib,'dxball_intro_points')
        self.offsets=(C.c_int32*720).in_dll(self.lib,'dxball_intro_offsets')
        self.colors=(C.c_int32*66).in_dll(self.lib,'dxball_splash_colors')
        self.mode_callbacks=(C.c_void_p*22).in_dll(self.lib,'dxball_mode_ops')
        for op,group in enumerate(MODE_ENTRIES):
            for mode,name in zip((0,4),BODY_NAMES[group]):
                self.mode_callbacks[op*5+mode]=C.cast(getattr(self.lib,'dxball_'+name),C.c_void_p).value
        table=(C.c_void_p*15).in_dll(self.lib,'dxball_runtime_ops')
        for slot,name in ((10,'draw_text'),(11,'draw_centered_text')):
            table[slot]=C.cast(getattr(self.lib,'dxball_'+name),C.c_void_p).value
        keys=(C.c_void_p*5).in_dll(self.lib,'dxball_key_mode_ops')
        for mode,name in ((0,'intro_key'),(4,'splash_key')):
            keys[mode]=C.cast(getattr(self.lib,'dxball_'+name),C.c_void_p).value
        def checked(surface,flags,key):
            try:
                self.events.append(('color-key',self.normalize(surface),flags,
                    struct.unpack('<2I',C.string_at(key,8)),self.observed()));return -1
            except Exception as e:print('Intro boundary failed:',repr(e),flush=True);os._exit(1)
        callback=C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_uint32,C.c_void_p)(checked)
        self.platform_callbacks.append(callback);self.vtable[29]=C.cast(callback,C.c_void_p).value
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            f.restype=C.c_int32 if name in ('raw_sine','raw_cosine','wave_x','wave_y') else None
            f.argtypes=[C.c_int32]*3 if name in ('wave_x','wave_y') else [C.c_int32] if name in ('raw_sine','raw_cosine','dispose_intro','dispose_splash') else [C.c_char] if name=='intro_key' else []
    def board_blt(self,destination,rect,source,source_rect,flags,fx):
        if source is None:return super().board_blt(destination,rect,source,source_rect,flags,fx)
        assert fx is None
        self.events.append(('scene-blt',self.normalize(destination),self.normalize(source),
            struct.unpack('<4i',C.string_at(rect,16)),struct.unpack('<4i',C.string_at(source_rect,16)),
            flags,self.observed(),self.display_observed()))
        return -1
    def fill_desc(self,pointer):
        # These newly observed callers specify the fixed DirectDraw record size
        # 108. The native bridge uses a typed host view to return its pixel pointer.
        desc=Desc.from_address(pointer);assert (desc.size,desc.flags)==(108,14)
        desc.width,desc.height,desc.pitch=640,480,self.pitch
        desc.pixels=C.addressof(self.pixels)


class IntroTarget(PlatformTarget):
    def __init__(self):
        super().__init__()
        for group in MODE_ENTRIES:
            for mode in (0,4):self.uc.hook_del(self.mode_body_hooks[group,mode])
        for name in ('draw_text','draw_centered_text'):self.uc.hook_del(self.runtime_hooks[name])
        for mode in (0,4):self.uc.hook_del(self.key_hooks[mode])
        self.write_u32(self.VTABLE+29*4,0x50E400)
        self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,self.color_key,begin=0x50E400,end=0x50E400))
    def color_key(self,*unused):
        surface,flags,key=self._args(3)
        self.events.append(('color-key',self.normalize(surface),flags,
            struct.unpack('<2I',self.read(key,8)),self.observed()));self._return(-1,pop=12)
    def fill_desc(self,pointer):
        assert (self.read_u32(pointer),self.read_u32(pointer+4))==(108,14)
        super().fill_desc(pointer)
    def board_blt(self,*unused):
        destination,rect,source,source_rect,flags,fx=self._args(6)
        if source==0:return super().board_blt(*unused)
        assert fx==0
        self.events.append(('scene-blt',self.normalize(destination),self.normalize(source),
            struct.unpack('<4i',self.read(rect,16)),struct.unpack('<4i',self.read(source_rect,16)),
            flags,self.observed(),self.display_observed()))
        self._return(-1,pop=24)


class IntroHarness(PlatformHarness):
    def __init__(self,library):
        # Preserve the platform harness's pointer/message/COM comparisons.
        from test_device_differential import DeviceHarness
        DeviceHarness.__init__(self,library,IntroNative,IntroTarget)
        self.cases=dict.fromkeys(ENTRIES,0);self.connected_checks=0
    def seed(self,grid=None):
        super().seed(grid)
        for data,address in ((self.n.points,POINTS),(self.n.offsets,OFFSETS)):
            C.memset(data,0xA7,C.sizeof(data));self.t.write(address,b'\xa7'*C.sizeof(data))
        colors=[]
        for green in (*range(20,241,20),*range(220,39,-20)):colors.extend((0,green,240))
        assert len(colors)==66;self.n.colors[:]=colors;self.t.write(COLORS,bytes(self.n.colors))
        for name,value in (('text_spacing',1),('splash_span',120),('splash_phase',1),
                ('scroller_length',3480),('scroller_advance',15)):
            self.setv(name,value)
        for bank in range(3):
            self.n.banks[bank].count=180;self.t.write_u32(BANKS+bank*1048+1020,180)
            for slot in range(1,180):
                sprite=self.n.runtime_sprites[bank][slot]
                sprite.code=bytes([slot]);sprite.baseline=0
                self.t.write(0x880000+(bank*255+slot)*48+36,bytes([slot]))
                self.t.write_u32(0x880000+(bank*255+slot)*48+40,0)
        # Existing glyph bodies always consult the actual font-bank global.
        C.c_int32.in_dll(self.n.lib,'dxball_font_bank').value=1;self.t.write_u32(FONT_BANK,1)
    def compare(self,context):
        super().compare(context)
        for data,address in ((self.n.points,POINTS),(self.n.offsets,OFFSETS),(self.n.colors,COLORS)):
            assert bytes(data)==self.t.read(address,C.sizeof(data)),(context,'intro buffer',hex(address))
        assert C.c_int32.in_dll(self.n.lib,'dxball_font_bank').value==self.t.read_u32(FONT_BANK),(context,'font bank')
    def call(self,name,*args):
        if name=='intro_key':native_args=(bytes([args[0]&255]),)
        else:native_args=args
        nr=self.n.call('dxball_'+name,*native_args);tr=self.t.call(ENTRIES[name],*args)
        if nr is not None:assert nr==C.c_int32(tr).value,(name,args,nr,tr)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1
    def phase(self,name,address,*args):
        self.n.call('dxball_'+name,*args);self.t.call(address,*args)
        self.compare((name,'connected',self.connected_checks));self.connected_checks+=1
    def points_ready(self):
        self.n.call('dxball_initialize_intro_points');self.t.call(ENTRIES['initialize_intro_points'])
        self.compare('prepare intro points')


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu();p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so');a=p.parse_args()
    # Verify untouched production tables and readonly/default data before any
    # oracle installs controlled platform/resource/audio providers.
    lib=C.CDLL(str(a.library));raw=IntroTarget()
    modes=(C.c_void_p*22).in_dll(lib,'dxball_mode_ops');keys=(C.c_void_p*5).in_dll(lib,'dxball_key_mode_ops')
    for op,group in enumerate(MODE_ENTRIES):
        for mode,name in zip((0,4),BODY_NAMES[group]):assert modes[op*5+mode]==C.cast(getattr(lib,'dxball_'+name),C.c_void_p).value
    for mode,name in ((0,'intro_key'),(4,'splash_key')):assert keys[mode]==C.cast(getattr(lib,'dxball_'+name),C.c_void_p).value
    text=C.string_at(C.addressof((C.c_char*3481).in_dll(lib,'dxball_welcome_text')))
    assert text==raw._cstring(0x421718) and len(text)==3480
    assert bytes((C.c_int32*66).in_dll(lib,'dxball_splash_colors'))==raw.read(COLORS,264)
    assert C.c_int32.in_dll(lib,'dxball_splash_span').value==raw.read_u32(0x4225C0)==120
    assert C.c_int32.in_dll(lib,'dxball_splash_phase').value==raw.read_u32(0x4225C8)==1
    h=IntroHarness(a.library)
    for angle in range(-720,721):
        h.call('raw_sine',angle);h.call('raw_cosine',angle)
    for angle,amplitude in itertools.product(range(-720,721,13),(-31,-4,0,3,99)):
        h.call('wave_x',17,angle,amplitude);h.call('wave_y',-17,angle,amplitude)
    h.seed();h.call('initialize_intro_points')
    for tick,now,retries in itertools.product((0,1000,0xfffffff0),(0,49,50,1000,1049,1050),(0,2)):
        h.seed();h.points_ready();h.setv('intro_tick',tick)
        h.n.now=h.t.now=now;h.n.lock_failures=h.t.lock_failures=retries
        h.call('update_intro_points')
    for disabled,span,phase in itertools.product((0,1,2,-1),(0,2,6,120,160),(0,1,89,179,359,360)):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.setv('splash_span',span);h.setv('splash_phase',phase)
        h.n.live[:]=bytes((i*11+1)%256 for i in range(1024));h.t.write(0x4386F0,bytes(h.n.live))
        h.call('pulse_splash_palette')
    for reduced,angle in itertools.product((0,1,2,-1),range(0,1081,17)):
        h.seed();h.state(0x4228D8,reduced);h.setv('credit_angle',angle);h.call('draw_waving_credits')
    for reduced in (0,1,2,-1):
        h.seed();h.state(0x4228D8,reduced);h.call('draw_scroller_wave')
    for index,shift,advance in itertools.product((0,1,20,3479),(0,11,12,15),(0,15,16)):
        h.seed();h.setv('scroller_index',index);h.setv('scroller_shift',shift);h.setv('scroller_advance',advance)
        h.call('update_scroller')
    for control,key in itertools.product((0,1,2,-1),range(256)):
        h.seed();h.setv('control_pressed',control);h.call('intro_key',key)
    h.seed();h.call('splash_key')
    for primary,last in itertools.product((0,1,2),(0,1,0xffffffff)):
        h.seed();h.mode(0);h.setv('draw_to_primary',primary);h.state(0x422D18,last)
        h.call('redraw_intro')
    for primary,software,low,wait in itertools.product((0,1),(0,1),(0,1),(0,1)):
        h.seed();h.mode(4);h.setv('draw_to_primary',primary);h.setv('software_only',software)
        h.setv('low_video_memory',low);h.setv('wait_vertical_blank',wait);h.call('redraw_splash')
    for primary,disabled in itertools.product((0,1),(0,1,2)):
        for mode,name in ((0,'initialize_intro'),(4,'initialize_splash')):
            h.seed();h.mode(mode);h.setv('draw_to_primary',primary);h.setv('cursor_warp_disabled',disabled);h.call(name)
    for primary,fade,disabled in itertools.product((0,1),(0,1,2,-1),(0,1)):
        for mode,name in ((0,'dispose_intro'),(4,'dispose_splash')):
            h.seed();h.mode(mode);h.setv('draw_to_primary',primary);h.setv('cursor_warp_disabled',disabled);h.call(name,fade)
    for primary,action,mouse in itertools.product((0,1),(0,1,2,3),((-99,-3),(8,447),(599,448),(900,900))):
        for mode,name in ((0,'intro_frame'),(4,'splash_frame')):
            h.seed();h.mode(mode);h.points_ready();h.setv('draw_to_primary',primary)
            h.setv('mouse_action',action);h.setv('mouse_x',mouse[0]);h.setv('mouse_y',mouse[1]);h.call(name)
    # Both modes' original bodies remain connected through actual mode dispatch
    # and key routing. File parsing/audio/COM driver effects are declared seams.
    for primary in (0,1):
        h.seed();h.mode(4);h.setv('draw_to_primary',primary)
        h.phase('initialize_mode',0x4038D0)
        for _ in range(12):h.phase('dispatch_frame',0x403730)
        h.phase('dispatch_key',0x403820,0x20);h.phase('dispatch_frame',0x403730)
        assert h.n.mode.value==0
        for _ in range(12):h.phase('dispatch_frame',0x403730)
        h.setv('control_pressed',1);h.phase('dispatch_key',0x403820,0x70)
        h.phase('dispatch_frame',0x403730);assert h.n.mode.value==2
    report={'status':'pass','cases':h.cases,'total':sum(h.cases.values()),
        'connected_checks':h.connected_checks,'integration_checks_separate':True,
        'target_sha256':h.t.target_sha256,'library_sha256':hashlib.sha256(a.library.read_bytes()).hexdigest(),
        'scope':'Twenty unmodified splash/menu/math entries with actual UI/glyph/point/line/palette/dirty/time bodies and connected mode/key dispatch. Compare full point/wave/RGB arrays, controlled pixel buffers and every ordered COM/resource/audio call. Valid terminating storage/arithmetic domains; resource reload, bank-release on this edge, audio and Windows/driver effects remain boundaries. No playable executable claim.'}
    (ROOT/'build/reports/intro-differential.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
