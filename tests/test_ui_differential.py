#!/usr/bin/env python3
"""Text, inclusive line pixels and palette operations against original x86."""
import argparse
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import struct
import sys

from target_oracle import ROOT
from resources_oracle import ResourceNative, ResourceTarget, BANKS, FONT_BANK, LIVE_PALETTE

ENTRIES = {'draw_text':0x404EE0, 'draw_centered_text':0x404F80,
    'measure_text':0x404FD0, 'draw_line':0x403070, 'fill_rect':0x403230,
    'rotate_palette_right':0x40A880, 'rotate_rgb_colors':0x40AA60,
    'set_palette_rgb':0x40AB20}


class UiNative(ResourceNative):
    def __init__(self, library):
        super().__init__(library)
        self.spacing=C.c_int32.in_dll(self.lib,'dxball_text_spacing')
        self.disabled=C.c_int32.in_dll(self.lib,'dxball_cursor_warp_disabled')
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            f.restype=C.c_int32 if name=='measure_text' else None
            f.argtypes={'draw_text':[C.c_int32]*3+[C.c_void_p],
                'draw_centered_text':[C.c_int32]*3+[C.c_void_p],
                'measure_text':[C.c_int32,C.c_void_p],
                'draw_line':[C.c_size_t]+[C.c_int32]*4+[C.c_uint8],
                'fill_rect':[C.c_size_t]+[C.c_int32]*4+[C.c_uint32],
                'rotate_rgb_colors':[C.c_int32]*2+[C.c_void_p],
                'set_palette_rgb':[C.c_int32]+[C.c_uint8]*3}.get(name,[C.c_int32]*3)
    def _blt(self,dest,rect,source,source_rect,flags,fx):
        if source is not None:return super()._blt(dest,rect,source,source_rect,flags,fx)
        assert source_rect is None and flags==0x400 and C.c_uint32.from_address(fx).value==100
        self.events.append(('fill',self._identity(dest),self._rect(rect),flags,
            C.c_uint32.from_address(fx+80).value))
        return -1


class UiTarget(ResourceTarget):
    def _blt(self,*unused):
        dest,rect,source,source_rect,flags,fx=self._args(6)
        if source:return super()._blt(*unused)
        assert source_rect==0 and flags==0x400 and self.read_u32(fx)==100
        self.events.append(('fill',self.surfaces[dest]['identity'],
            struct.unpack('<4i',self.read(rect,16)),flags,self.read_u32(fx+80)))
        self._return(-1,pop=24)


def main():
    assert __debug__,'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'));from resource_limits import limit_cpu
    limit_cpu()
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    args=parser.parse_args();n,t=UiNative(args.library),UiTarget();cases=dict.fromkeys(ENTRIES,0)
    def reset():
        n.reset();t.reset();n.disabled.value=0;t.write_u32(0x422898,0)
        n.spacing.value=1;t.write_u32(0x421084,1)
    def compare(context):
        assert n.events==t.events,(context,'calls',n.events[:12],t.events[:12])
        assert bytes(n.live)==t.read(LIVE_PALETTE,1024),(context,'palette and flags')
        assert n.lock_failures==t.lock_failures and n.desc_failures==t.desc_failures
        for address,model in n.surfaces.items():
            target=next(x for x in t.surfaces.values() if x['identity']==model['identity'])
            assert bytes(model['pixels'])==t.read(target['pixels'],model['pitch']*model['height']),(context,'pixels and row padding',model['identity'])
    def call(name,nargs=(),targs=None):
        n.events=[];nr=getattr(n.lib,'dxball_'+name)(*nargs)
        tr=t.call(ENTRIES[name],*(nargs if targs is None else targs))
        if nr is not None:assert nr==C.c_int32(tr).value,(name,nr,tr)
        compare((name,cases[name]));cases[name]+=1
    # Actual glyph search and draw bodies execute on both sides. Slot count is
    # exclusive; misses, embedded NULs, duplicate codes and signed high bytes
    # retain the original half-width fallback and final-character spacing.
    for bank,spacing in itertools.product(range(3),(-2,0,1,3)):
        reset();n.font.value=bank;t.write_u32(FONT_BANK,bank)
        n.spacing.value=spacing;t.write_u32(0x421084,spacing)
        for slot,code in enumerate((65,0,0xE9,66,65,90),1):
            n.seed(bank,slot,code,width=slot*3+2,baseline=slot-3)
            t.seed(bank,slot,code,width=slot*3+2,baseline=slot-3)
        n.banks[bank].count=6;t.write_u32(BANKS+bank*1048+1020,6)
        for text in (b'',b'AB',b'A\0\xe9?',b'ZZA',b'\xffB\x00A'):
            memory=C.create_string_buffer(text);t.write(t.PATH,text+b'\0')
            for count in sorted(set((-1,0,len(text),max(0,len(text)-1)))):
                call('measure_text',(count,C.addressof(memory)),(count,t.PATH))
                call('draw_text',(-17,23,count,C.addressof(memory)),(-17,23,count,t.PATH))
                call('draw_centered_text',(101,-5,count,C.addressof(memory)),(101,-5,count,t.PATH))
    # Raster output is observed across every octant, both direction orderings,
    # equality boundaries, zero length, lock retries and padded scanlines.
    for dx,dy,color,retries in itertools.product(range(-4,5),range(-4,5),(0,200,255),(0,2)):
        reset();n.lock_failures=t.lock_failures=retries
        call('draw_line',(n.active,20,20,20+dx,20+dy,color),(t.SURFACE,20,20,20+dx,20+dy,color))
    for rect,color in itertools.product(((0,0,639,479),(17,-3,17,25),(5,6,-7,-8)),(0,255,256,0xffffffff)):
        reset();call('fill_rect',(n.active,*rect,color),(t.SURFACE,*rect,color))
    for disabled,wrap,bounds in itertools.product((0,1,2,-1),(0,1,2,-1),((0,0),(48,63),(0,255),(255,255))):
        reset();n.disabled.value=disabled;t.write_u32(0x422898,disabled)
        n.live[:]=bytes((i*37+11)%256 for i in range(1024));t.write(LIVE_PALETTE,bytes(n.live))
        call('rotate_palette_right',(*bounds,wrap))
    for disabled,entry,rgb in itertools.product((0,1,2,-1),(0,189,255),((0,0,0),(255,17,128),(1,2,3))):
        reset();n.disabled.value=disabled;t.write_u32(0x422898,disabled)
        call('set_palette_rgb',(entry,*rgb))
    for disabled,count in itertools.product((0,1,2,-1),(3,4,6,7,66)):
        reset();n.disabled.value=disabled;t.write_u32(0x422898,disabled)
        values=[-513,256,1025]+list(range(3,count))+[0x12345678]*3
        pool=(C.c_int32*len(values))(*values);t.write(t.PATH,bytes(pool))
        call('rotate_rgb_colors',(189,count,C.addressof(pool)),(189,count,t.PATH))
        assert bytes(pool)==t.read(t.PATH,C.sizeof(pool)),('RGB int pool and canary',count)
    report={'status':'pass','cases':cases,'total':sum(cases.values()),
        'target_sha256':t.target_sha256,'library_sha256':hashlib.sha256(args.library.read_bytes()).hexdigest(),
        'scope':'Eight unmodified original UI entries with actual glyph bodies; explicit COM outputs and call records, line pixel writes, row padding and palette flags. Valid pointers, palette bounds, count>=3 RGB pools and nonoverflowing arithmetic. No DirectDraw driver rasterization claim.'}
    (ROOT/'build/reports/ui-differential.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))


if __name__=='__main__':main()
