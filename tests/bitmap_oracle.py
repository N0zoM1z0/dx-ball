"""Controlled native bitmap APIs; production source retains unwritten stack bytes."""
import ctypes as C
import struct
import traceback
from resources_oracle import Surface, Desc

class NativeBitmap:
 def __init__(self,library,stack_driver):
  self.core=self.lib=C.CDLL(str(library))
  self.stack_driver=C.CDLL(str(stack_driver))
  self.saved_draw=C.c_void_p.in_dll(self.core,'dxball_direct_draw').value
  self.callbacks=[];self.errors=[]
  self.table=(C.c_void_p*33)();self.draw_table=(C.c_void_p*7)()
  self.surface=Surface(self.table);self.draw=Surface(self.draw_table);self.palette=Surface(self.draw_table)
  C.c_void_p.in_dll(self.core,'dxball_direct_draw').value=C.addressof(self.draw)
  p,u=C.c_void_p,C.c_uint32
  signatures=[(self.table,25,C.c_int32,[p,p,p,u,p],self.lock),
   (self.table,32,C.c_int32,[p,p],self.unlock),
   (self.table,31,C.c_int32,[p,p],self.set_palette),
   (self.draw_table,5,C.c_int32,[p,u,p,p,p],self.create_palette)]
  for table,slot,ret,args,func in signatures:table[slot]=C.cast(self.wrap(ret,args,func),p).value
  self.ops={};self.saved_ops={}
  for name,ret,args,func in [
    ('dxball_file_create',C.c_size_t,[p,u,u,p,u,u,C.c_size_t],self.open),
    ('dxball_file_read',C.c_int32,[C.c_size_t,p,u,p,p],self.read),
    ('dxball_local_alloc',p,[u,C.c_size_t],self.allocate),
    ('dxball_local_free',p,[p],self.free),
    ('dxball_file_close',C.c_int32,[C.c_size_t],self.close)]:
   self.ops[name]=p.in_dll(self.lib,name)
   self.saved_ops[name]=self.ops[name].value
   self.ops[name].value=C.cast(self.wrap(ret,args,func),p).value
  self.invoke=self.stack_driver.dxball_test_invoke_seeded;self.invoke.argtypes=[p,p,p,u];self.invoke.restype=C.c_int32
  self.function=C.cast(self.lib.dxball_load_bitmap,p).value
 def wrap(self,ret,args,func):
  def guarded(*args):
   try:return func(*args)
   except BaseException:
    self.errors.append(traceback.format_exc());return 0
  f=C.CFUNCTYPE(ret,*args)(guarded);self.callbacks.append(f);return f
 def fixture(self,t):
  self.target=t;self.events=[];self.read_buffers={};self.opens=self.reads=self.position=0
  self.palette_bytes=None;self.pixel_allocation=None;self.pixel_buffer=None;self.errors=[]
  self.pixels=(C.c_ubyte*t.total)(*([0xa5]*t.total))
  self.path=C.create_string_buffer(t._cstring(t.PATH))
 def open(self,path,access,share,security,disposition,attributes,template):
  assert(access,share,security,disposition,attributes,template)==(0x80000000,1,None,3,0x80,0)
  self.opens+=1;failed=self.target.fail=='open' or(self.target.fallback and self.opens==1)
  self.events.append(('open',C.string_at(path).decode('ascii'),int(failed)))
  return C.c_size_t(-1).value if failed else self.target.FILE_HANDLE
 def read(self,handle,output,count,transferred,overlapped):
  assert handle==self.target.FILE_HANDLE and overlapped is None
  self.reads+=1;failed=self.target.fail=='read'+str(self.reads)
  self.events.append(('read',count,int(failed)))
  if not failed:
   returned=self.target.short_read[1] if self.target.short_read and self.reads==self.target.short_read[0] else count
   data=self.target.data[self.position:self.position+returned];assert len(data)==returned
   before=C.string_at(output,count)
   if data:C.memmove(output,data,len(data))
   C.cast(transferred,C.POINTER(C.c_uint32))[0]=returned;self.position+=returned
   self.read_buffers[self.reads]=dict(requested=count,returned=returned,before=before,after=C.string_at(output,count),file_position=self.position)
  return int(not failed)
 def allocate(self,flags,count):
  assert flags==0x40 and count==len(self.target.input_pixels)
  self.events.append(('allocate',flags,count))
  if self.target.fail=='allocate':return None
  self.pixel_buffer=(C.c_ubyte*count)();self.pixel_allocation=C.addressof(self.pixel_buffer)
  return self.pixel_allocation
 def free(self,address):
  assert address==self.pixel_allocation;self.events.append(('free',));return None
 def close(self,handle):
  assert handle==self.target.FILE_HANDLE;self.events.append(('close',));return 0
 def lock(self,surface,rect,description,flags,event):
  assert surface==C.addressof(self.surface) and rect is None and flags==0 and event is None
  assert C.string_at(description,C.sizeof(Desc))==struct.pack('<I',C.sizeof(Desc))+bytes(C.sizeof(Desc)-4)
  failed=self.target.fail=='lock';self.events.append(('lock',int(failed)))
  if not failed:
   d=C.cast(description,C.POINTER(Desc)).contents;t=self.target.model
   d.width=t['width'];d.height=t['height'];d.pitch=t['pitch'];d.pixels=C.addressof(self.pixels)+32
  return int(failed)
 def unlock(self,surface,pointer):
  assert surface==C.addressof(self.surface) and pointer is None
  self.events.append(('unlock',));return 1
 def create_palette(self,draw,caps,entries,output,outer):
  assert draw==C.addressof(self.draw) and caps==4 and outer is None
  self.palette_bytes=C.string_at(entries,1024);self.events.append(('create_palette',))
  failed=self.target.fail=='palette'
  if not failed:C.cast(output,C.POINTER(C.c_void_p))[0]=C.addressof(self.palette)
  return int(failed)
 def set_palette(self,surface,palette):
  assert surface==C.addressof(self.surface) and palette==C.addressof(self.palette)
  self.events.append(('set_palette',));return 1
 def call(self,seed):
  result=self.invoke(self.function,C.addressof(self.surface),C.addressof(self.path),seed)
  assert not self.errors,self.errors
  return result

 def restore(self):
  for name,value in self.saved_ops.items():self.ops[name].value=value
  C.c_void_p.in_dll(self.core,'dxball_direct_draw').value=self.saved_draw
