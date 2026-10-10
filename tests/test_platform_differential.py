#!/usr/bin/env python3
"""Original window/startup/input bodies with declared Windows and COM boundaries."""
from source_state import source_global
import argparse
import ctypes as C
import itertools
import json
import os
from pathlib import Path
import struct
import sys
import tempfile

from unicorn import UC_HOOK_CODE
from target_oracle import ROOT, MODE
from resources_oracle import BANKS, Surface, Desc
from test_gameplay_differential import signed
from test_core_differential import GLOBALS
from test_device_differential import DeviceNative, DeviceTarget, DeviceHarness

ENTRIES = {'win_main':0x40D930, 'window_proc':0x40DA70,
    'initialize_fullscreen':0x40CF70, 'initialize_compatible':0x40D4B0,
    'claim_instance':0x40DF10, 'close_instance':0x40DF80, 'detect_clock':0x403550,
    'dispatch_key':0x403820, 'game_key':0x410290,
    'dispose_working_surface':0x403BD0, 'initialize_sprite_banks':0x403C20}
GLOBALS.update({0x438B08:'application_active', 0x438B00:'shift_pressed',
    0x438B04:'control_pressed', 0x4228E0:'sound_suspended',
    0x4228D4:'software_only', 0x4228DC:'low_video_memory'})
HANDLES = {0x438B18:'main_window',0x4228A4:'instance_semaphore',
    0x4228B0:'direct_draw',0x4228B4:'primary_surface',0x4228B8:'secondary_surface',
    0x4228BC:'board_surface',0x4228C0:'direct_palette',0x4228C4:'direct_clipper',
    0x421070:'background_surface'}
KINDS = {'i':C.c_int32,'u':C.c_uint32,'h':C.c_size_t,'r':C.c_ssize_t,'p':C.c_void_p,'s':C.c_char_p,'v':None,'c':C.c_int8}
# API names, return type, argument types: imports and COM methods retain stdcall
# on original x86; reconstructed native callbacks use the host ABI.
APIS = [('load_icon','LoadIconA','h','hh'),('load_cursor','LoadCursorA','h','hh'),
    ('stock_object','GetStockObject','h','i'),('register_class','RegisterClassA','u','p'),
    ('create_window_ex','CreateWindowExA','h','ussuiiiihhhp'),
    ('show_window','ShowWindow','i','hi'),('update_window','UpdateWindow','i','h'),
    ('set_focus','SetFocus','h','h'),('destroy_window','DestroyWindow','i','h'),
    ('message_box','MessageBoxA','i','hssu'),('direct_draw_create','DirectDrawCreate','i','ppp'),
    ('get_cursor_pos','GetCursorPos','i','p'),('peek_message','PeekMessageA','i','phuuu'),
    ('wait_message','WaitMessage','i',''),('get_message','GetMessageA','i','phuu'),
    ('translate_message','TranslateMessage','i','p'),('dispatch_message','DispatchMessageA','r','p'),
    ('default_window_proc','DefWindowProcA','r','huhr'),('post_message','PostMessageA','i','huhr'),
    ('post_quit_message','PostQuitMessage','v','i'),('set_cursor','SetCursor','h','h'),
    ('set_capture','SetCapture','h','h'),('release_capture','ReleaseCapture','i',''),
    ('open_semaphore','OpenSemaphoreA','h','uis'),('create_semaphore','CreateSemaphoreA','h','piis'),
    ('close_handle','CloseHandle','i','h'),('get_version_ex','GetVersionExA','i','p')]
OPS = [('prepare_sound',0x4050F0,'h'),('initialize_sound',0x405120,'h'),
    ('pause_sound',0x4057D0,''),('resume_music',0x401C90,''),('pause_music',0x401CE0,''),
    ('close_music',0x401DA0,''),('release_audio',0x406270,''),('load_music',0x401B90,'si'),
    ('exit_process',0x417910,'i')]
COM = [('get_attached', 'surface',12,'ppp'),('set_clipper','surface',28,'pp'),
    ('release','surface',2,'p'),('release','palette',2,'p'),
    ('create_clipper','ddraw',4,'pupp'),('create_surface','ddraw',6,'pppp'),
    ('get_caps','ddraw',11,'ppp'),('set_coop','ddraw',20,'phu'),
    ('set_display','ddraw',21,'puuu'),('clip_window','clipper',8,'puh')]
KEYS = [0x40E430,0x410290,0x40C740,0x4069F0,0x407AB0]

class Point(C.Structure):
    _fields_=[('x',C.c_int32),('y',C.c_int32)]
class Message(C.Structure):
    _fields_=[('window',C.c_size_t),('message',C.c_uint32),('wparam',C.c_size_t),
        ('lparam',C.c_ssize_t),('time',C.c_uint32),('point',Point)]
class WindowClass(C.Structure):
    _fields_=[('style',C.c_uint32),('procedure',C.c_void_p),('class_extra',C.c_int32),
        ('window_extra',C.c_int32),('instance',C.c_size_t),('icon',C.c_size_t),
        ('cursor',C.c_size_t),('background',C.c_size_t),('menu',C.c_char_p),('name',C.c_char_p)]
class Security(C.Structure):
    _fields_=[('length',C.c_uint32),('descriptor',C.c_void_p),('inherit',C.c_int32)]

class Boundaries:
    def text(self,p):
        return p.decode() if isinstance(p,bytes) else self.string(p).decode()
    def snapshot(self):
        return (tuple((n,self.norm(self.pointer(a,n))) for a,n in HANDLES.items()),
            tuple(self.scalar(a,n) for a,n in GLOBALS.items() if n in ('application_active',
                'control_pressed','shift_pressed','sound_suspended','software_only','low_video_memory')),
            self.scalar(0x438B10,'mouse_action'))
    def norm(self,p):
        p=p or 0
        for name,value in self.objects.items():
            if value==p:return name
        return self.normalize(p)
    def log(self,name,*args):
        self.window_events.append((name,*args,self.snapshot()))
    def status(self,name):return -1 if self.fail_stage==name else 0
    def boundary(self,name,args):
        args=list(args)
        if name in ('load_icon','load_cursor','stock_object'):
            self.log(name,*args);return {'load_icon':0x301,'load_cursor':0x302,'stock_object':0x303}[name]
        if name=='register_class':
            record=self.window_class(args[0]);self.log(name,*record);return self.register_result
        if name=='create_window_ex':
            args[1:3]=[self.text(v) for v in args[1:3]];args[-1]=args[-1] or 0
            self.log(name,*args);return 0 if self.fail_stage=='window' else 0x5678
        if name=='message_box':args[1:3]=[self.text(v) for v in args[1:3]]
        if name=='open_semaphore':
            args[2]=self.text(args[2]);self.log(name,*args);return self.open_result
        if name=='create_semaphore':
            args[0]=self.security(args[0]);args[3]=self.text(args[3]);self.log(name,*args);return self.semaphore_result
        if name=='direct_draw_create':
            assert not args[0] and not args[2]
            null=self.output_null and self.fail_stage=='draw'
            self.log(name,self.status('draw'),null)
            self.put_pointer(args[1],0 if null else self.objects['ddraw'])
            return self.status('draw')
        if name=='get_version_ex':
            assert self.u32(args[0])==148;self.log(name,148,self.platform_id,self.version_result)
            self.put_u32(args[0]+16,self.platform_id);return self.version_result
        if name=='get_cursor_pos':
            self.log(name,*self.window_cursor,self.cursor_result)
            self.put_bytes(args[0],struct.pack('<2i',*self.window_cursor));return self.cursor_result
        if name=='peek_message':
            assert args[1:]==[0,0,0,0]
            result=self.peek_script.pop(0) if self.peek_script else 1
            self.log(name,result);return result
        if name=='get_message':
            assert args[1:]==[0,0,0]
            result,fields=self.message_script.pop(0)
            self.put_message(args[0],fields);self.log(name,result,fields);return result
        if name in ('translate_message','dispatch_message'):
            self.log(name,self.message(args[0]));return -1
        if name=='wait_message':
            self.log(name)
            if self.activate_on_wait:self.set_scalar(0x438B08,'application_active',1)
            return -1
        if name=='default_window_proc':self.log(name,*args);return self.default_result
        self.log(name,*args)
        return None if name=='post_quit_message' else 0x7654 if name in ('set_focus','set_cursor','set_capture') else -1
    def com(self,name,args):
        a=list(args);role=self.norm(a[0])
        if name=='release':self.log(name,role);return 9
        assert role in ('ddraw','primary','secondary','clipper')
        if name=='get_caps':
            assert self.u32(a[1])==316 and not a[2]
            self.log(name,316,self.cap_bits,self.free_memory,self.caps_result)
            self.put_u32(a[1]+4,self.cap_bits);self.put_u32(a[1]+64,self.free_memory)
            return self.caps_result
        if name=='create_surface':
            assert not a[3]
            raw=self.desc_fields(a[1]);flags=raw[1]
            # DDSD flags define the consumed fields. Unwritten original stack
            # bytes are not an API argument or an accepted semantic claim.
            desc=(raw[0],flags,raw[-1],raw[2] if flags&2 else None,
                raw[3] if flags&4 else None,raw[5][0] if flags&0x20 else None)
            key='primary' if desc[2]&0x200 else 'board'
            null=self.output_null and self.fail_stage==key
            self.log(name,key,desc,self.status(key),null)
            self.put_pointer(a[2],0 if null else self.objects[key]);return self.status(key)
        if name=='get_attached':
            null=self.output_null and self.fail_stage=='attached'
            self.log(name,role,self.u32(a[1]),self.status('attached'),null)
            self.put_pointer(a[2],0 if null else self.objects['secondary']);return self.status('attached')
        if name=='create_clipper':
            assert a[1]==0 and not a[3]
            null=self.output_null and self.fail_stage=='clipper'
            self.log(name,0,self.status('clipper'),null)
            self.put_pointer(a[2],0 if null else self.objects['clipper']);return self.status('clipper')
        if name=='set_clipper':a[1]=self.norm(a[1]);key='clip-'+role
        else:key={'set_coop':'coop','set_display':'display','clip_window':'clip-window'}[name]
        self.log(name,role,*a[1:],self.status(key));return self.status(key)
    def platform(self,name,args):
        if name=='load_music':args=(self.text(args[0]),args[1])
        self.log(name,*args)
        if name=='exit_process':self.terminate(args[0])
    def key(self,mode,args):
        args=tuple(signed(v) if v<128 else v-256 for v in args)
        self.log('key-mode',mode,*args)

class PlatformNative(Boundaries,DeviceNative):
    def __init__(self,library):
        super().__init__(library);self.platform_callbacks=[]
        self.clipper_table=(C.c_void_p*9)();self.clipper=Surface(self.clipper_table)
        self.objects={'ddraw':C.addressof(self.ddraw),'primary':C.addressof(self.primary),
            'secondary':C.addressof(self.secondary),'board':self.surface_pointer,
            'palette':C.addressof(self.palette),'clipper':C.addressof(self.clipper),'background':C.addressof(self.background)}
        def bind(table,slot,result,kinds,function):
            def checked(*args):
                try:return function(*args)
                except Exception as error:print('Native platform boundary failed:',repr(error),flush=True);os._exit(1)
            cb=C.CFUNCTYPE(KINDS[result],*[KINDS[k] for k in kinds])(checked)
            self.platform_callbacks.append(cb);table[slot]=C.cast(cb,C.c_void_p).value
        shared_cells={'open_semaphore':'dxball_window_open_semaphore',
            'create_semaphore':'dxball_window_create_semaphore',
            'close_handle':'dxball_file_close',
            'load_icon':'dxball_window_load_icon',
            'load_cursor':'dxball_window_load_cursor',
            'stock_object':'dxball_window_stock_object',
            'register_class':'dxball_window_register_class',
            'create_window_ex':'dxball_window_create_window_ex',
            'show_window':'dxball_window_show_window',
            'update_window':'dxball_window_update_window',
            'set_focus':'dxball_window_set_focus',
            'destroy_window':'dxball_window_destroy_window',
            'message_box':'dxball_window_message_box',
            'direct_draw_create':'dxball_draw_factory_backend',
            'get_cursor_pos':'dxball_window_get_cursor_pos',
            'peek_message':'dxball_window_peek_message',
            'wait_message':'dxball_window_wait_message',
            'get_message':'dxball_window_get_message',
            'translate_message':'dxball_window_translate_message',
            'dispatch_message':'dxball_window_dispatch_message',
            'default_window_proc':'dxball_window_default_window_proc',
            'post_message':'dxball_window_post_message',
            'post_quit_message':'dxball_window_post_quit_message',
            'set_cursor':'dxball_window_set_cursor',
            'set_capture':'dxball_window_set_capture',
            'release_capture':'dxball_window_release_capture',
            'get_version_ex':'dxball_window_get_version_ex'}
        for name,_,result,kinds in APIS:
            if name in shared_cells:
                cell=(C.c_void_p*1).in_dll(self.lib,shared_cells[name])
                bind(cell,0,result,kinds,lambda *a,name=name:self.boundary(name,a))
        table=(C.c_void_p*len(OPS)).in_dll(self.lib,'dxball_platform_ops')
        for slot,(name,_,kinds) in enumerate(OPS):bind(table,slot,'v',kinds,lambda *a,name=name:self.platform(name,a))
        (C.c_void_p*15).in_dll(self.lib,'dxball_runtime_ops')[14]=table[5]
        tables={'surface':self.vtable,'ddraw':self.ddraw_table,'palette':self.palette_table,'clipper':self.clipper_table}
        for name,table,slot,kinds in COM:bind(tables[table],slot,'i',kinds,lambda *a,name=name:self.com(name,a))
        table=(C.c_void_p*5).in_dll(self.lib,'dxball_key_mode_ops')
        for mode in (0,2,3,4):
            bind(table,mode,'v','' if mode==4 else 'c',lambda *a,mode=mode:self.key(mode,tuple(v&255 for v in a)))
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            f.restype=C.c_size_t if name in ('win_main','claim_instance') else C.c_ssize_t if name=='window_proc' else C.c_int32 if name.startswith('initialize_') and name!='initialize_sprite_banks' else None
            f.argtypes={'win_main':[C.c_size_t]*3+[C.c_int32],'window_proc':[C.c_size_t,C.c_uint32,C.c_size_t,C.c_ssize_t],
                'initialize_fullscreen':[C.c_size_t,C.c_int32],'initialize_compatible':[C.c_size_t,C.c_int32],
                'dispatch_key':[C.c_int32],'game_key':[C.c_int32],'dispose_working_surface':[C.c_int32]}.get(name,[])
    def scalar(self,a,n):return source_global(C.c_int32, self.lib,'dxball_'+n).value
    def set_scalar(self,a,n,v):source_global(C.c_int32, self.lib,'dxball_'+n).value=signed(v)
    def pointer(self,a,n):return source_global(C.c_void_p, self.lib,'dxball_'+n).value or 0
    def set_pointer(self,a,n,v):source_global(C.c_void_p, self.lib,'dxball_'+n).value=v
    def u32(self,p):return C.c_uint32.from_address(p).value
    def put_u32(self,p,v):C.c_uint32.from_address(p).value=v&0xffffffff
    def put_bytes(self,p,b):C.memmove(p,b,len(b))
    def put_pointer(self,p,v):C.c_void_p.from_address(p).value=v
    def string(self,p):return C.string_at(p)
    def window_class(self,p):
        w=WindowClass.from_address(p)
        assert w.procedure==C.cast(self.lib.dxball_window_proc,C.c_void_p).value
        return (w.style,'window_proc',w.class_extra,w.window_extra,w.instance,w.icon,w.cursor,w.background,w.menu.decode(),w.name.decode())
    def security(self,p):
        s=Security.from_address(p);return (s.length,s.descriptor or 0,s.inherit)
    def desc_fields(self,p):
        d=Desc.from_address(p);return (d.size,d.flags,d.height,d.width,d.pitch,tuple(d.ancillary),d.pixels or 0,tuple(d.keys),tuple(d.format),d.caps)
    def message(self,p):
        m=Message.from_address(p);return (m.window,m.message,m.wparam,m.lparam,m.time,m.point.x,m.point.y)
    def put_message(self,p,fields):
        m=Message.from_address(p);m.window,m.message,m.wparam,m.lparam,m.time,m.point.x,m.point.y=fields
    def terminate(self,status):
        self.exit_file.write_text(json.dumps({'status':status,'events':self.window_events,'snapshot':self.snapshot()}));os._exit(status)

class PlatformTarget(Boundaries,DeviceTarget):
    CLIPPER=0x506500
    def __init__(self):
        super().__init__();self.objects={'ddraw':self.DDRAW,'primary':self.PRIMARY,
            'secondary':self.SECONDARY,'board':self.SURFACE,'palette':self.PALETTE,
            'clipper':self.CLIPPER,'background':self.BACKGROUND}
        self.write_u32(self.CLIPPER,0x506600)
        imports={i.name.decode():i.address for e in self.pe.DIRECTORY_ENTRY_IMPORT for i in e.imports if i.name}
        def bind(address,kinds,function,stdcall=True):
            def callback(*unused):
                args=tuple(signed(v) if k in ('i','r') else v for k,v in zip(kinds,self._args(len(kinds))))
                result=function(args);self._return(0 if result is None else result,pop=len(kinds)*4 if stdcall else 0)
            hook=self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
            self._hooks.append(hook)
            return hook
        for slot,(name,imported,_,kinds) in enumerate(APIS):
            address=0x509000+slot*16;self.write_u32(imports[imported],address)
            bind(address,kinds,lambda a,name=name:self.boundary(name,a))
        self.uc.hook_del(self.runtime_hooks['finalize_game_resources'])
        for name,address,kinds in OPS:
            if name!='exit_process':bind(address,kinds,lambda a,name=name:self.platform(name,a),False)
        tables={'surface':self.VTABLE,'ddraw':0x506300,'palette':0x506200,'clipper':0x506600}
        for i,(name,table,slot,kinds) in enumerate(COM):
            address=0x509300+i*16;self.write_u32(tables[table]+slot*4,address)
            bind(address,kinds,lambda a,name=name:self.com(name,a))
        self.key_hooks={mode:bind(KEYS[mode],'' if mode==4 else 'i',lambda a,mode=mode:self.key(mode,tuple(v&255 for v in a)),False) for mode in (0,2,3,4)}
    def exit(self,*unused):
        self.exit_status=self._args(1)[0];self.log('exit_process',self.exit_status);self.uc.emu_stop()
    def call(self,entry,*args):
        self.callee_cleanup=16 if entry in (ENTRIES['win_main'],ENTRIES['window_proc']) else 0
        try:return super().call(entry,*args)
        finally:self.callee_cleanup=0
    def scalar(self,a,n):return signed(self.read_u32(a))
    def set_scalar(self,a,n,v):self.write_u32(a,v)
    def pointer(self,a,n):return self.read_u32(a)
    def set_pointer(self,a,n,v):self.write_u32(a,v)
    def u32(self,p):return self.read_u32(p)
    def put_u32(self,p,v):self.write_u32(p,v)
    def put_bytes(self,p,b):self.write(p,b)
    def put_pointer(self,p,v):self.write_u32(p,v)
    def string(self,p):return self._cstring(p)
    def window_class(self,p):
        w=struct.unpack('<10I',self.read(p,40));assert w[1]==ENTRIES['window_proc']
        return (w[0],'window_proc',signed(w[2]),signed(w[3]),*w[4:8],self.text(w[8]),self.text(w[9]))
    def security(self,p):return struct.unpack('<IIi',self.read(p,12))
    def desc_fields(self,p):
        v=struct.unpack('<27I',self.read(p,108));return (*v[:4],signed(v[4]),tuple(v[5:9]),v[9],tuple(v[10:18]),tuple(v[18:26]),v[26])
    def message(self,p):
        v=struct.unpack('<7I',self.read(p,28));return (*v[:3],signed(v[3]),v[4],signed(v[5]),signed(v[6]))
    def put_message(self,p,fields):self.write(p,struct.pack('<7I',*(v&0xffffffff for v in fields)))

class PlatformHarness(DeviceHarness):
    def __init__(self,library):
        super().__init__(library,PlatformNative,PlatformTarget);self.cases=dict.fromkeys(ENTRIES,0)
    def seed(self,grid=None):
        super().seed(grid)
        for o in (self.n,self.t):
            o.window_events=[];o.fail_stage=None;o.output_null=False;o.open_result=0;o.semaphore_result=0x1357
            o.platform_id=2;o.version_result=1;o.register_result=0;o.cap_bits=0;o.free_memory=400000;o.caps_result=0
            o.window_cursor=(-321,765);o.cursor_result=1;o.default_result=-12345;o.activate_on_wait=False
            o.peek_script=[];o.message_script=[(0,(0x5678,0x12,0x89abcdef,-17,123,-19,23))]
            o.exit_status=None
            o.set_pointer(0x438B18,'main_window',0x2468);o.set_pointer(0x4228A4,'instance_semaphore',0x3579)
            o.set_pointer(0x4228C4,'direct_clipper',o.objects['clipper'])
            o.set_pointer(0x4228B0,'direct_draw',o.objects['ddraw'])
        C.c_int32.in_dll(self.n.lib,'dxball_cursor_point').value=17
        point=Point.in_dll(self.n.lib,'dxball_cursor_point');point.x,point.y=17,-23
        self.t.write(0x438AF8,struct.pack('<2i',17,-23))
    def compare(self,context):
        super().compare(context)
        assert self.n.snapshot()==self.t.snapshot(),(context,'platform state',self.n.snapshot(),self.t.snapshot())
        if self.n.window_events!=self.t.window_events:
            i=next((i for i,(n,t) in enumerate(zip(self.n.window_events,self.t.window_events)) if n!=t),min(len(self.n.window_events),len(self.t.window_events)))
            raise AssertionError((context,'Windows/COM events',i,self.n.window_events[i:i+1],self.t.window_events[i:i+1]))
        p=Point.in_dll(self.n.lib,'dxball_cursor_point');assert (p.x,p.y)==struct.unpack('<2i',self.t.read(0x438AF8,8))
        assert struct.pack('<d',self.n.scale.value)==self.t.read(0x4210A0,8),(context,'pan double')
        for bank in range(3):
            for slot in range(255):
                assert bool(self.n.banks[bank].sprites[slot])==bool(self.t.read_u32(BANKS+bank*1048+slot*4)),(context,'sprite slot',bank,slot)
        for attr in ('peek_script','message_script'):assert getattr(self.n,attr)==getattr(self.t,attr),(context,attr)
    def call(self,name,*args):
        nr=self.n.call('dxball_'+name,*args);tr=self.t.call(ENTRIES[name],*args)
        if nr is not None:assert nr==(signed(tr) if name=='window_proc' else tr),(name,args,nr,tr)
        self.compare((name,args,self.cases[name]));self.cases[name]+=1
    def pointer(self,name,role):
        address=next(a for a,n in HANDLES.items() if n==name)
        for o in (self.n,self.t):o.set_pointer(address,name,o.objects[role] if role else 0)
    def mode(self,value):self.n.mode.value=value;self.t.write_u32(MODE,value)


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu();p=argparse.ArgumentParser(description=__doc__);p.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    a=p.parse_args();h=PlatformHarness(a.library)
    for opened,created,old in itertools.product((0,1,0x100001),(0,1,0x1357),(0,0x3579)):
        h.seed()
        for o in (h.n,h.t):o.open_result=opened;o.semaphore_result=created;o.set_pointer(0x4228A4,'instance_semaphore',old)
        h.call('claim_instance')
    for handle in (0,1,0x3579,0xffffffff):
        h.seed()
        for o in (h.n,h.t):o.set_pointer(0x4228A4,'instance_semaphore',handle)
        h.call('close_instance')
    for platform,result in itertools.product((0,1,2,3,0xffffffff),(0,1)):
        h.seed();h.n.platform_id=h.t.platform_id=platform;h.n.version_result=h.t.version_result=result;h.call('detect_clock')
    print('PASS singleton and clock',flush=True)
    for mode,key in itertools.product((-1,0,1,2,3,4,5),range(256)):
        h.seed();h.mode(mode);h.setv('cursor_warp_disabled',1);h.call('dispatch_key',key)
    for paused,control,key in itertools.product((0,1,2,-1),(0,1,2,-1),(0x20,0x50,*range(0x70,0x7c),0xff)):
        h.seed();h.setv('paused',paused);h.setv('control_pressed',control)
        h.setv('cursor_warp_disabled',1);h.call('game_key',key)
    for disabled,fade,key in itertools.product((0,1,2),(0,1,2,-1),(0x50,0x20)):
        h.seed();h.mode(4);h.setv('cursor_warp_disabled',disabled);h.setv('restart_requested',fade);h.call('game_key',key)
    for bank,width,control,key in itertools.product((0,1,2),(1,7,59,120),(0,1,-1),(0x70,0x71,0x72,0x73)):
        h.seed();h.sprite(68,width,8,bank);h.setv('control_pressed',control)
        C.c_int32.in_dll(h.n.lib,'dxball_sprite_bank').value=bank;h.t.write_u32(0x421088,bank)
        h.call('game_key',key)
    for choice in range(6):
        h.seed();h.n.cursor=h.t.cursor=choice;h.call('game_key',0x74)
    for scale in (-3.5,-1.0,-0.0,0.0,0.125,7.25):
        h.seed();h.n.scale.value=scale;h.t.write(0x4210A0,struct.pack('<d',scale));h.call('game_key',0x7b)
    print('PASS key dispatch and game input',flush=True)
    for fade,reset,mode,background in itertools.product((-1,0,1),(0,1,2),(0,1,4),(False,True)):
        h.seed();h.mode(mode);h.setv('cursor_warp_disabled',1);h.setv('device_reset_requested',reset)
        if not background:h.pointer('background_surface',None)
        h.call('dispose_working_surface',fade)
    for modes,counts in [((0,1,-1),(0,1,255)),((2,-2,3),(17,254,2))]:
        h.seed();h.bank_modes(modes)
        for bank,count in enumerate(counts):h.n.banks[bank].count=count;h.t.write_u32(BANKS+bank*1048+1020,count)
        h.call('initialize_sprite_banks')
    messages=(0,1,7,8,0x14,0x1c,0x20,0x48,0x100,0x101,0x200,0x201,0x202,0x203,0x204,0x205,0x218,0x311,0xffffffff)
    for message,wp,mode,suspended in itertools.product(messages,(0,1,2,3,4,6,7,0x10,0x11,0x1b,0x50,0x171), (0,1,4), (0,1,2)):
        h.seed();h.mode(mode);h.setv('cursor_warp_disabled',1);h.setv('sound_suspended',suspended)
        h.setv('control_pressed',2);h.setv('shift_pressed',-1);h.call('window_proc',0x5678,message,wp,-17)
    for draw,primary,palette,board,background,reset in itertools.product((False,True),repeat=6):
        h.seed();h.mode(4);h.setv('cursor_warp_disabled',1);h.setv('device_reset_requested',int(reset))
        for name,present,role in [('direct_draw',draw,'ddraw'),('primary_surface',primary,'primary'),
            ('direct_palette',palette,'palette'),('board_surface',board,'board'),('background_surface',background,'background')]:
            if not present:h.pointer(name,None)
        h.call('window_proc',0x5678,2,0x1234,-17)
    for draw,primary,reset in itertools.product((False,True),(False,True),(0,1,2)):
        h.seed();h.setv('device_reset_requested',reset)
        if not draw:h.pointer('direct_draw',None)
        if not primary:h.pointer('primary_surface',None)
        h.call('window_proc',0x5678,0x311,99,-17)
    for message,wp in itertools.product((0x1c,0x100,0x101,0x200,0xffffffff),(0x80000000,0xffffffff)):
        h.seed();h.mode(4);h.call('window_proc',0x5678,message,wp,-2147483648)
    print('PASS window messages and shutdown',flush=True)
    for name in ('initialize_fullscreen','initialize_compatible'):
        stages=[None,'window','draw','coop','primary','board','clipper','clip-window','clip-primary']
        if name=='initialize_fullscreen':stages+=['display','attached','clip-secondary']
        for stage,null in itertools.product(stages,(False,True)):
            if null and stage not in ('window','draw','primary','board','clipper','attached'):continue
            h.seed();h.setv('display_buffer_count',1);h.setv('clip_regions',1)
            h.n.fail_stage=h.t.fail_stage=stage;h.n.output_null=h.t.output_null=null;h.call(name,0x1234,3)
        for buffers,clip,bits,free,old in itertools.product((0,1,2),(0,1,2),(0,0x2000000),(309999,310000,310001),(0,2)):
            h.seed();h.setv('display_buffer_count',buffers);h.setv('clip_regions',clip)
            h.state(0x4228D8,old);h.setv('low_video_memory',old)
            h.n.cap_bits=h.t.cap_bits=bits;h.n.free_memory=h.t.free_memory=free
            h.n.caps_result=h.t.caps_result=-1;h.call(name,0x1234,-1)
    print('PASS fullscreen and compatible creation',flush=True)
    for disabled,active,version,retval in itertools.product((0,1,2),(0,1,2),(1,2),(1,-1)):
        h.seed();h.mode(4);h.setv('cursor_warp_disabled',disabled);h.setv('application_active',active)
        h.n.platform_id=h.t.platform_id=version
        for o in (h.n,h.t):
            o.peek_script=[0,0,1,1]
            o.message_script=[(retval,(0x5678,0x1c,2,-7,101,11,-13)),(0,(0x5678,0x12,0x89abcdef,-17,123,-19,23))]
        h.call('win_main',0x1234,0,0,3)
    for disabled,stage in itertools.product((0,1,2),('window','draw','coop','primary','board','clipper')):
        h.seed();h.setv('cursor_warp_disabled',disabled);h.setv('clip_regions',1)
        h.n.fail_stage=h.t.fail_stage=stage;h.call('win_main',0x1234,0,0,3)
    # The singleton rejection is a non-returning CRT boundary, tested in a
    # forked native process; returning from an exit callback is never accepted.
    for opened,created in ((1,0x1357),(0,0)):
        h.seed();h.n.open_result=h.t.open_result=opened;h.n.semaphore_result=h.t.semaphore_result=created
        with tempfile.TemporaryDirectory() as directory:
            h.n.exit_file=Path(directory)/'exit.json';pid=os.fork()
            if pid==0:h.n.call('dxball_win_main',0x1234,0,0,3);os._exit(91)
            _,status=os.waitpid(pid,0);assert os.WIFEXITED(status) and os.WEXITSTATUS(status)==0
            native=json.loads(h.n.exit_file.read_text())
        try:h.t.call(ENTRIES['win_main'],0x1234,0,0,3)
        except AssertionError as error:assert str(error)=='instruction limit reached' and h.t.exit_status==0
        else:raise AssertionError('original process exit returned')
        assert native==json.loads(json.dumps({'status':h.t.exit_status,'events':h.t.window_events,'snapshot':h.t.snapshot()}))
        h.cases['win_main']+=1
    print('PASS WinMain lifecycle and stdcall ABI',flush=True)
    report={'cases':h.cases,'total':sum(h.cases.values()),'target_sha256':h.t.target_sha256,
        'scope':'unmodified original window/startup/input bodies; controlled Windows/DirectDraw/audio APIs, non-game modes and glyph/resource boundaries; maintained mode dispatch, game input, fades, game redraw and cleanup execute; not a playable game'}
    destination=ROOT/'build/reports/platform-differential.json';destination.parent.mkdir(parents=True,exist_ok=True)
    destination.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
