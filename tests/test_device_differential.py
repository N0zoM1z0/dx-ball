#!/usr/bin/env python3
"""Original palette fade and lost-surface recovery, connected to game redraw."""
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
from target_oracle import ROOT, MODE
from resources_oracle import Surface, BANKS, SAVED_PALETTE, LIVE_PALETTE
from test_gameplay_differential import signed
from test_display_differential import DisplayNative, DisplayTarget, DisplayHarness, LOST

ENTRIES={'palette_transition':0x40A340,'initialize_palette':0x4096C0,
         'clear_surface':0x409F10,'restore_sprite_banks':0x403D30,
         'recover_surfaces':0x403640,'synchronize_surface':0x4035B0}


class DeviceNative(DisplayNative):
    def __init__(self,library):
        super().__init__(library)
        self.device_callbacks=[]
        self.background=Surface(self.vtable)
        self.surface_names[C.addressof(self.background)]='background'
        self.sprite_surfaces=[[Surface(self.vtable) for _ in range(255)] for _ in range(3)]
        for bank,objects in enumerate(self.sprite_surfaces):
            for slot,surface in enumerate(objects):self.surface_names[C.addressof(surface)]=('sprite',bank,slot)
        def bind(table,slot,signature,function):
            def checked(*args):
                try:return function(*args)
                except Exception as error:
                    print('Native device boundary failed:',repr(error),flush=True);os._exit(1)
            callback=signature(checked);self.device_callbacks.append(callback)
            table[slot]=C.cast(callback,C.c_void_p).value
        bind(self.vtable,13,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_uint32),self.blt_status)
        bind(self.vtable,27,C.CFUNCTYPE(C.c_int32,C.c_void_p),self.surface_restore)
        bind(self.vtable,31,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_void_p),self.set_palette)
        bind(self.ddraw_table,5,C.CFUNCTYPE(C.c_int32,C.c_void_p,C.c_uint32,C.c_void_p,C.c_void_p,C.c_void_p),self.create_palette)
        for symbol,length,functions in [
            ('dxball_runtime_ops',15,{1:'palette_transition',2:'clear_surface'}),
            ('dxball_display_ops',2,{1:'recover_surfaces'}),
            ('dxball_mode_ops',22,{21:'synchronize_surface'})]:
            table=source_global(C.c_void_p*length, self.lib,symbol)
            for slot,name in functions.items():table[slot]=C.cast(getattr(self.lib,'dxball_'+name),C.c_void_p).value
        for name in ENTRIES:
            function=getattr(self.lib,'dxball_'+name);function.restype=None
            function.argtypes=[C.c_size_t,C.c_int32] if name=='clear_surface' else [C.c_int32]*5 if name=='palette_transition' else []
    def blt_status(self,surface,flags):
        assert self.normalize(surface)=='primary' and flags==1
        self.events.append(('blt-status','primary',flags,signed(self.status_result),self.observed()))
        return signed(self.status_result)
    def surface_restore(self,surface):
        role=self.normalize(surface);script=self.restore_scripts.get(role,[])
        result=script.pop(0) if script else 0
        self.events.append(('surface-restore',role,signed(result),self.observed(),self.display_observed()))
        return signed(result)
    def set_palette(self,surface,palette):
        self.events.append(('set-palette',self.normalize(surface),'palette' if palette==C.addressof(self.palette) else palette,self.observed()))
        return -1
    def create_palette(self,ddraw,flags,entries,output,outer):
        assert ddraw==C.addressof(self.ddraw) and flags==4 and outer is None
        self.events.append(('create-palette',flags,C.string_at(entries,1024).hex(),signed(self.palette_result),self.observed()))
        C.c_void_p.from_address(output).value=None if self.palette_null else C.addressof(self.palette)
        return signed(self.palette_result)
    def board_blt(self,destination,rect,source,source_rect,flags,fx):
        if source is not None:return super().board_blt(destination,rect,source,source_rect,flags,fx)
        assert source_rect is None and flags==0x400 and fx is not None
        assert C.c_uint32.from_address(fx).value==100
        self.events.append(('color-fill',self.normalize(destination),struct.unpack('<4i',C.string_at(rect,16)),
            flags,C.c_uint32.from_address(fx+80).value,self.observed(),self.display_observed()))
        return -1


class DeviceTarget(DisplayTarget):
    BACKGROUND=0x506400
    def __init__(self):
        super().__init__()
        self.write_u32(self.BACKGROUND,self.VTABLE);self.surface_names[self.BACKGROUND]='background'
        self.uc.hook_del(self.display_hooks[0x403640]);self.uc.hook_del(self.mode_hooks['synchronize'])
        for name in ('palette_transition','clear_surface'):self.uc.hook_del(self.runtime_hooks[name])
        for bank in range(3):
            for slot in range(255):
                address=0x890000+(bank*255+slot)*8
                self.write_u32(address,self.VTABLE);self.surface_names[address]=('sprite',bank,slot)
        for table,slot,address,function in [(self.VTABLE,13,0x50E200,self.blt_status),
            (self.VTABLE,27,0x50E210,self.surface_restore),(self.VTABLE,31,0x50E220,self.set_palette),
            (0x506300,5,0x50E230,self.create_palette)]:
            assert address!=self.RETURN
            self.write_u32(table+slot*4,address)
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,function,begin=address,end=address))
    def blt_status(self,*unused):
        surface,flags=self._args(2);assert self.normalize(surface)=='primary' and flags==1
        self.events.append(('blt-status','primary',flags,signed(self.status_result),self.observed()))
        self._return(self.status_result,pop=8)
    def surface_restore(self,*unused):
        role=self.normalize(self._args(1)[0]);script=self.restore_scripts.get(role,[])
        result=script.pop(0) if script else 0
        self.events.append(('surface-restore',role,signed(result),self.observed(),self.display_observed()))
        self._return(result,pop=4)
    def set_palette(self,*unused):
        surface,palette=self._args(2)
        self.events.append(('set-palette',self.normalize(surface),'palette' if palette==self.PALETTE else palette,self.observed()))
        self._return(-1,pop=8)
    def create_palette(self,*unused):
        ddraw,flags,entries,output,outer=self._args(5);assert ddraw==self.DDRAW and flags==4 and outer==0
        self.events.append(('create-palette',flags,self.read(entries,1024).hex(),signed(self.palette_result),self.observed()))
        self.write_u32(output,0 if self.palette_null else self.PALETTE);self._return(self.palette_result,pop=20)
    def board_blt(self,*unused):
        destination,rect,source,source_rect,flags,fx=self._args(6)
        if source:return super().board_blt()
        assert source_rect==0 and flags==0x400 and fx!=0 and self.read_u32(fx)==100
        self.events.append(('color-fill',self.normalize(destination),struct.unpack('<4i',self.read(rect,16)),
            flags,self.read_u32(fx+80),self.observed(),self.display_observed()))
        self._return(-1,pop=24)


class DeviceHarness(DisplayHarness):
    def __init__(self,library,native_type=DeviceNative,target_type=DeviceTarget):
        super().__init__(library,native_type,target_type)
        self.cases=dict.fromkeys(ENTRIES,0);self.connected_checks=0
    def sprite(self,slot,width,height,bank=0):
        super().sprite(slot,width,height,bank)
        surface=C.addressof(self.n.sprite_surfaces[bank][slot])
        self.n.runtime_sprites[bank][slot].surface=surface
        self.t.write_u32(0x880000+(bank*255+slot)*48,0x890000+(bank*255+slot)*8)
    def seed(self,grid=None):
        super().seed(grid)
        C.c_void_p.in_dll(self.n.lib,'dxball_background_surface').value=C.addressof(self.n.background)
        self.t.write_u32(0x421070,self.t.BACKGROUND)
        for oracle in (self.n,self.t):
            oracle.restore_scripts={};oracle.status_result=0;oracle.palette_result=0;oracle.palette_null=False
        C.c_void_p.in_dll(self.n.lib,'dxball_direct_palette').value=C.addressof(self.n.palette)
        self.t.write_u32(0x4228C0,self.t.PALETTE)
        for bank in range(3):
            self.n.banks[bank].mode=0;self.n.banks[bank].filename=('bank%d.sbk'%bank).encode()
            self.t.write_u32(BANKS+bank*1048+1024,0)
            self.t.write(BANKS+bank*1048+1028,('bank%d.sbk'%bank).encode()+bytes(11))
        self.setv('cursor_warp_disabled',0)
    def bank_modes(self,modes):
        for bank,mode in enumerate(modes):
            self.n.banks[bank].mode=mode;self.t.write_u32(BANKS+bank*1048+1024,mode)
    def compare(self,context):
        super().compare(context)
        assert self.n.restore_scripts==self.t.restore_scripts,(context,'restore script consumption')
        pointer=C.c_void_p.in_dll(self.n.lib,'dxball_direct_palette').value
        assert ('palette' if pointer==C.addressof(self.n.palette) else pointer or 0)==('palette' if self.t.read_u32(0x4228C0)==self.t.PALETTE else self.t.read_u32(0x4228C0)),(context,'palette output')
        for bank in range(3):
            assert self.n.banks[bank].mode==signed(self.t.read_u32(BANKS+bank*1048+1024)),(context,'bank allocation mode',bank)
            assert bytes(self.n.banks[bank].filename)==self.t.read(BANKS+bank*1048+1028,20).split(b'\0')[0],(context,'bank filename',bank)
    def call(self,name,*args):
        self.n.call('dxball_'+name,*args);self.t.call(ENTRIES[name],*args)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1
    def scripts(self,primary=0,board=0):
        for oracle in (self.n,self.t):oracle.restore_scripts={'primary':[primary],'board':[board]}
    def phase(self,name,address,*args):
        self.n.call('dxball_'+name,*args);self.t.call(address,*args)
        self.compare((name,'connected'));self.connected_checks+=1


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu()
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    args=parser.parse_args();h=DeviceHarness(args.library)
    # Inclusive endpoints, both directions, flags preserved, terminal extra
    # SetEntries/wait, byte-sized step arithmetic, and original equality gates.
    for disabled,direction,step,bounds,timing in itertools.product((0,1,2,-1),(0,1,2,-1),
            (1,2,17,255,256,300),((0,0),(5,7),(0,255),(255,255)),((0,0),(1,1))):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.setv('wait_vertical_blank',timing[1])
        h.call('palette_transition',timing[0],step,*bounds,direction)
    for disabled,direction,step in itertools.product((1,),(0,1,2),(0,-1)):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.call('palette_transition',1,step,0,255,direction)
    print('PASS palette transition',h.cases['palette_transition'],flush=True)
    for result,null in ((0,False),(-1,False),(-1,True),(LOST,True)):
        h.seed();h.n.palette_result=h.t.palette_result=result;h.n.palette_null=h.t.palette_null=null
        h.call('initialize_palette')
    print('PASS palette creation',h.cases['initialize_palette'],flush=True)
    for role,color in itertools.product(('board','primary','secondary'),(0,1,255,256,-1,0x7fffffff)):
        h.seed();native={'board':h.n.surface_pointer,'primary':C.addressof(h.n.primary),'secondary':C.addressof(h.n.secondary)}[role]
        target={'board':h.t.SURFACE,'primary':h.t.PRIMARY,'secondary':h.t.SECONDARY}[role]
        h.n.call('dxball_clear_surface',native,color);h.t.call(ENTRIES['clear_surface'],target,color)
        h.compare(('clear_surface',role,color));h.cases['clear_surface']+=1
    print('PASS surface fill',h.cases['clear_surface'],flush=True)
    for modes in itertools.product((0,1,2,-1),repeat=3):
        h.seed();h.bank_modes(modes)
        for oracle in (h.n,h.t):oracle.restore_scripts={('sprite',bank,0):[-1] for bank in range(3)}
        for bank in range(3):
            for slot in range(255):
                h.n.banks[bank].sprites[slot]=C.POINTER(type(h.n.runtime_sprites[bank][slot]))()
                h.t.write_u32(BANKS+bank*1048+slot*4,0)
            for slot in (0,1,254):h.sprite(slot,10,8,bank)
            h.n.runtime_sprites[bank][1].surface=None
            h.t.write_u32(0x880000+(bank*255+1)*48,0)
        h.call('restore_sprite_banks')
    print('PASS sprite recovery',h.cases['restore_sprite_banks'],flush=True)
    for mode,primary,board in itertools.product((-1,0,1,2,3,4,5),(0,-1,LOST),(0,-1,LOST)):
        h.seed();h.n.mode.value=mode;h.t.write_u32(MODE,mode);h.scripts(primary,board)
        h.bank_modes((1,0,1));h.call('recover_surfaces')
    print('PASS surface recovery',h.cases['recover_surfaces'],flush=True)
    for disabled,request,status,primary,board in itertools.product((0,1,2,-1),(0,1,2,-1),(0,-1,LOST),(0,-1),(0,-1)):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.setv('surface_restore_requested',request)
        h.n.status_result=h.t.status_result=status;h.scripts(primary,board);h.call('synchronize_surface')
    print('PASS surface synchronization',h.cases['synchronize_surface'],flush=True)
    # Lost Flip -> actual recovery -> actual game redraw. BUSY followed by LOST
    # does not resume flipping after recovery. Integrations are counted separately.
    for flags,primary,board in itertools.product((0,1),(0,-1),(0,-1)):
        h.seed();h.setv('draw_to_primary',flags);h.setv('wait_vertical_blank',1);h.scripts(primary,board)
        h.n.flip_script=[0x8876021C,LOST]
        h.t.flip_script=[0x8876021C,LOST]
        h.phase('present',0x409040)
    for disabled,request,status in itertools.product((0,1,2),(0,1),(0,LOST)):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.setv('surface_restore_requested',request)
        h.n.status_result=h.t.status_result=status;h.phase('dispatch_frame',0x403730)
    for disabled in (0,1,2):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.setv('wait_vertical_blank',1)
        h.phase('initialize_game',0x40F4C0);h.phase('dispose_game',0x416430,1)
    report={'status':'pass','cases':h.cases,'total_cases':sum(h.cases.values()),
        'connected_checks':h.connected_checks,'integration_checks_separate':True,
        'target_sha256':hashlib.sha256((ROOT/'original/DXBALL.EXE').read_bytes()).hexdigest(),
        'library_sha256':hashlib.sha256(args.library.read_bytes()).hexdigest(),
        'scope':'Unmodified six original entries and maintained wait/redraw/frame bodies; controlled COM, sprite-bank reload, glyph, audio and platform boundaries. No driver rasterization or playable executable claim.'}
    directory=ROOT/'build/reports';directory.mkdir(parents=True,exist_ok=True)
    (directory/'device-differential.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
