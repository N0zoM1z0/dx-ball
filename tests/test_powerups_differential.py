#!/usr/bin/env python3
"""Compare a connected bonus/paddle/board/ball family against original x86."""
import argparse
import ctypes as C
import hashlib
import itertools
import json
import math
from pathlib import Path
import random
import struct
import subprocess
import sys

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX, UC_X86_REG_FPCW, UC_X86_REG_FPTAG, UC_X86_REG_FPSW, UC_X86_REG_FP0
from target_oracle import ROOT, BANK, INDEX, TILES, AUX, MODE, ACTIVE_SURFACE
from resources_oracle import Bank, Sprite, BANKS, SPRITE_BANK
from test_gameplay_differential import Node, List, Ops, Allocate, signed, REMAINING, SCORE, PAN_SCALE
from test_entities_differential import EntitiesNative, EntitiesTarget, SHAPES, BonusNode, entity_type

BallNode, BallList = entity_type('BallNode', ('x', 'y', 'previous_x', 'previous_y', 'dx', 'dy', 'sprite', 'angle', 'speed', 'bounce_count', 'attached', 'attach_offset', 'wall_bounces'))
SHAPES.update(scratch=(0x43FAA8, Node, 12), balls=(0x43A8B8, BallNode, 52), clones=(0x43AAA8, BallNode, 52))
GLOBALS = {0x43A878:'paddle_x', 0x43A87C:'paddle_y', 0x43FA94:'paddle_width', 0x43A880:'paddle_sprite',
 0x43A904:'paddle_previous_x', 0x43A908:'paddle_previous_y', 0x438B0C:'mouse_x', 0x438B14:'mouse_y',
 0x422898:'cursor_warp_disabled', 0x43A888:'lives', 0x43A884:'life_score_limit',
 0x43A90C:'restart_requested', 0x422D1C:'level_changed', 0x425974:'end_requested', 0x425978:'return_to_menu',
 0x43A8D8:'bonus_3_active', 0x43A88C:'bonus_3_ticks', 0x43FAF4:'bonus_7_active',
 0x43A860:'bonus_8_active', 0x43A890:'bonus_9_active', 0x43A910:'bonus_12_active',
 0x43A864:'bonus_14_active', 0x43FAE0:'bonus_17_active', 0x43FAE8:'bonus_18_active', 0x43F8F0:'ball_count'}
ENTRIES = {'rectangles_overlap':0x402100, 'initialize_trig':0x402250, 'sine':0x402400, 'cosine':0x402490,
 'update_paddle_position':0x412DF0, 'advance_level':0x415B30, 'lose_life':0x415BB0,
 'clear_explosion_list':0x4153E0, 'spread_explosive_bricks':0x4150A0,
 'soften_special_bricks':0x415410, 'count_destructible_bricks':0x415A90,
 'append_ball':0x4106D0, 'begin_balls':0x4100F0, 'advance_ball':0x4101D0, 'remove_ball':0x411850,
 'clear_ball_list':0x415070, 'spawn_ball':0x4105D0, 'clone_balls':0x414DF0,
 'bounce_ball_from_paddle':0x411410, 'release_attached_balls':0x415820, 'update_bonuses':0x413E20}
Void = C.CFUNCTYPE(None)
Count = C.CFUNCTYPE(C.c_int32)
Cursor = C.CFUNCTYPE(C.c_int32, C.c_int32, C.c_int32)
class RoundOps(C.Structure):
    _fields_ = [('initialize_board', Void), ('count_bricks', Count)]

class FamilyNative(EntitiesNative):
    def __init__(self, library):
        super().__init__(library)
        self.owners.update(scratch=List.in_dll(self.lib,'dxball_explosive_sources'),
          balls=BallList.in_dll(self.lib,'dxball_balls'), clones=BallList.in_dll(self.lib,'dxball_duplicate_balls'))
        self.extra = {a:C.c_int32.in_dll(self.lib,'dxball_'+n) for a,n in GLOBALS.items()}
        self.banks = (Bank*3).in_dll(self.lib,'dxball_sprite_banks')
        self.sprites = [Sprite() for _ in range(255)]
        self.control_round, self.round_count = True, 123
        self.round_callbacks = [Void(self.initialize), Count(self.count_bricks), Cursor(self.cursor_position)]
        ops = RoundOps.in_dll(self.lib,'dxball_round_ops')
        ops.initialize_board, ops.count_bricks = self.round_callbacks[:2]
        C.c_void_p.in_dll(self.lib,'dxball_set_cursor_position').value = C.cast(self.round_callbacks[2],C.c_void_p).value
        for name in ENTRIES:
            f=getattr(self.lib,'dxball_'+name)
            if name in ('sine','cosine'): f.argtypes,f.restype=[C.c_int32],C.c_float
            elif name=='rectangles_overlap': f.argtypes,f.restype=[C.c_int32]*8,C.c_int32
            elif name in ('append_ball','begin_balls','advance_ball','remove_ball','clear_ball_list'):
                f.argtypes,f.restype=[C.POINTER(BallList)],C.c_int32
            elif name=='clear_explosion_list': f.argtypes,f.restype=[C.POINTER(List)],C.c_int32
            else: f.argtypes,f.restype=[],C.c_int32 if name=='count_destructible_bricks' else None
    def observed(self):
        result=super().observed()
        return result+tuple(v.value for v in self.extra.values())+(self.index.value,) if hasattr(self,'extra') else result
    def initialize(self):
        if self.control_round: self.events.append(('initialize-board',self.observed()))
        else: self.lib.dxball_initialize_board()
    def count_bricks(self):
        if self.control_round:
            self.events.append(('count-bricks',self.observed())); return self.round_count
        return self.lib.dxball_count_destructible_bricks()
    def cursor_position(self,x,y):
        self.events.append(('cursor',x,y,self.observed())); return 1
    def free(self,address):
        a=self.allocations[address]; assert a['live']
        if a['owner'] is None:
            payload=52 if a['size']==C.sizeof(BallNode) else 12
            assert a['size'] in (C.sizeof(BallNode),C.sizeof(Node))
        else: payload=SHAPES[a['owner']][2]
        self.events.append(('free-payload',C.string_at(address,payload).hex(),self.observed()))
        a['live']=False; C.memset(address,0xDD,a['size'])

class FamilyTarget(EntitiesTarget):
    def __init__(self):
        super().__init__()
        self.control_round,self.round_count=True,123
        self.write_u32(0x441350,0x50C000)
        self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,self.cursor_position,begin=0x50C000,end=0x50C000))
        for address,callback in ((0x411930,self.initialize),(0x415A90,self.count_bricks)):
            self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address))
    def observed(self):
        return super().observed()+tuple(signed(self.read_u32(a)) for a in GLOBALS)+(signed(self.read_u32(INDEX)),)
    def initialize(self,*unused):
        if self.control_round:
            self.events.append(('initialize-board',self.observed())); self._return()
    def count_bricks(self,*unused):
        if self.control_round:
            self.events.append(('count-bricks',self.observed())); self._return(self.round_count & 0xffffffff)
    def cursor_position(self,*unused):
        self.events.append(('cursor',*(signed(v) for v in self._args(2)),self.observed()));self._return(1,pop=8)
    def free(self,*unused):
        address=self._args(1)[0]; a=self.allocations[address]; assert a['live']
        payload=a['size']-8
        self.events.append(('free-payload',self.read(address,payload).hex(),self.observed()))
        a['live']=False; self.write(address,b'\xdd'*a['size']); self._return()
    def call(self,entry,*args):
        self.uc.reg_write(UC_X86_REG_FPCW,0x37f)
        self.uc.reg_write(UC_X86_REG_FPTAG,0xffff)
        return super().call(entry,*args)
    def floating_result(self):
        top=(self.uc.reg_read(UC_X86_REG_FPSW)>>11)&7
        mantissa,exponent=self.uc.reg_read(UC_X86_REG_FP0+top)
        value=math.ldexp(mantissa,(exponent&0x7fff)-16383-63) if mantissa else 0.0
        return -value if exponent&0x8000 else value


def main():
    assert __debug__, 'oracle assertions must stay enabled'
    sys.path.insert(0,str(ROOT/'scripts'))
    from resource_limits import limit_cpu
    limit_cpu()
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    parser.add_argument('--fail-allocator', choices=('append_ball', 'spawn_ball'))
    args=parser.parse_args()
    if args.fail_allocator:
        native = FamilyNative(args.library)
        failing_allocator = Allocate(lambda size: None)
        Ops.in_dll(native.lib, 'dxball_gameplay_ops').allocate_node = failing_allocator
        function = getattr(native.lib, 'dxball_' + args.fail_allocator)
        if args.fail_allocator == 'append_ball':
            function(C.byref(native.owners['balls']))
        else:
            function()
        raise AssertionError('failed allocation must terminate the process')
    n,t=FamilyNative(args.library),FamilyTarget()
    cases=dict.fromkeys(ENTRIES,0); integrations=0
    def setv(name,value):
        address=next(a for a,x in GLOBALS.items() if x==name)
        n.extra[address].value=value;t.write_u32(address,value)
    def sprite(slot,width,height,bank=0):
        n.sprites[slot].width,n.sprites[slot].height=width,height
        n.banks[bank].sprites[slot]=C.pointer(n.sprites[slot])
        address=0x805000+slot*48
        t.write(address,bytes(44));t.write(address+8,struct.pack('<2i',width,height))
        t.write_u32(BANKS+bank*1048+slot*4,address)
    def seed(tiles=None):
        n.reset();t.reset()
        for name in GLOBALS.values():setv(name,0)
        for a,v in n.state.items():v.value=123;t.write_u32(a,123)
        n.count.value=0;t.write_u32(0x43FA90,0)
        n.scale.value=1;t.write(PAN_SCALE,struct.pack('<d',1))
        n.index.value=0;t.write_u32(INDEX,0)
        n.mode.value=0;t.write_u32(MODE,0)
        n.active.value=0xAA;t.write_u32(ACTIVE_SURFACE,0xAA)
        n.cell=t.cell=85
        n.tiles[:]=tiles if tiles is not None else bytes(400);t.write(TILES,bytes(n.tiles))
        n.aux[:]=b'\xa5'*400;t.write(AUX,bytes(n.aux))
        for k,v in [('paddle_x',320),('paddle_y',450),('paddle_width',60),('paddle_sprite',68),
                    ('paddle_previous_x',320),('paddle_previous_y',450),('mouse_x',320),('mouse_y',477),
                    ('lives',3),('bonus_3_ticks',73),('return_to_menu',7)]:setv(k,v)
        C.c_int32.in_dll(n.lib,'dxball_sprite_bank').value=0;t.write_u32(SPRITE_BANK,0)
        for slot in [1,68]+list(range(35,54)):sprite(slot,60 if slot==68 else 10,8)
        n.control_round=t.control_round=False
        n.round_count=t.round_count=123
        t.write_u32(0x42309c,0)
    def compare(context):
        assert not n.errors,(context,n.errors)
        assert bytes(n.tiles)==t.read(TILES,400),(context,'tiles')
        assert bytes(n.aux)==t.read(AUX,400),(context,'aux')
        assert n.observed()==t.observed(),(context,n.observed(),t.observed())
        for a,v in n.state.items():assert v.value==signed(t.read_u32(a)),(context,hex(a))
        active=t.SURFACE if n.active.value==n.surface_pointer else n.active.value
        assert active==t.read_u32(ACTIVE_SURFACE),(context,'surface')
        assert n.events==t.events,(context,n.events[:12],t.events[:12])
        live=0
        for owner in SHAPES:
            nq,tq=n.queue(owner),t.queue(owner); assert nq==tq,(context,owner,nq,tq)
            live+=len(nq[0])
        for oracle in (n,t):
            assert sum(a['live'] for a in oracle.allocations.values())==live,(context,'lost allocation')
            for address,a in oracle.allocations.items():
                if not a['live']:
                    data=C.string_at(address,a['size']) if oracle is n else oracle.read(address,a['size'])
                    assert data==b'\xdd'*a['size'],(context,'write after free')
    def call(name,*args,owner=None,claim=True):
        if owner:
            nr=n.call('dxball_'+name,C.byref(n.owners[owner]));t.uc.reg_write(UC_X86_REG_ECX,SHAPES[owner][0]);tr=t.call(ENTRIES[name])
        else:
            nr=n.call('dxball_'+name,*args);tr=t.call(ENTRIES[name],*args)
        if name in ('sine','cosine'):tr=t.floating_result()
        if nr is not None:assert nr==tr,(name,args,nr,tr)
        compare((name,args,owner))
        if claim:cases[name]+=1
    def add(owner,payload):
        node=SHAPES[owner][1]
        function='append_ball' if owner in ('balls','clones') else 'append_explosion' if owner=='scratch' else 'append_bonus'
        entry=0x4106D0 if function=='append_ball' else 0x412470 if function=='append_explosion' else 0x413D80
        n.events=[];t.events=[]
        getattr(n.lib,'dxball_'+function)(C.byref(n.owners[owner]))
        t.uc.reg_write(UC_X86_REG_ECX,SHAPES[owner][0]);t.call(entry)
        address=C.cast(n.owners[owner].current,C.c_void_p).value
        target=t.read_u32(SHAPES[owner][0]);data=struct.pack('<'+'i'*len(payload),*payload)
        C.memmove(address,data,len(data));t.write(target,data)
        n.queue(owner);t.queue(owner)
    seed();call('initialize_trig')
    for name,address in [('sine',0x424650),('cosine',0x424BF8)]:
        values=(C.c_int32*361).in_dll(n.lib,'dxball_'+name+'_table')
        assert bytes(values)==t.read(address,1444),(name,'computed tables')
        for angle in range(-1080,1081):call(name,angle)
    rng=random.Random(0xDBA107)
    # Integer centers, touching/odd dimensions and inverted rectangles, no overflow.
    rectangles=[(x,y,x+w,y+h) for x,y,w,h in itertools.product((-3,0,3),(0,2),(-3,0,1,2,5),(-2,0,3))]
    for i in range(8000):
        a=rectangles[i%len(rectangles)];b=rectangles[rng.randrange(len(rectangles))]
        call('rectangles_overlap',*a,*b)
    for width,x,disabled in itertools.product((0,1,10,59,60,240,1200),(-100,0,20,21,50,320,587,618,900),(0,1,-1)):
        seed();setv('paddle_width',width);setv('mouse_x',x);setv('cursor_warp_disabled',disabled)
        call('update_paddle_position')
    boards=(ROOT/'original/DEFAULT.BDS').read_bytes()
    grids=[bytes([b])*400 for b in range(256)]+[boards[i*400:(i+1)*400] for i in range(50)]
    for grid in grids:
        seed(grid);setv('bonus_17_active',1);call('count_destructible_bricks');call('soften_special_bricks')
        seed(grid);call('spread_explosive_bricks')
    # Isolated boundary/interior sources and overlapping source neighborhoods.
    for x,y in itertools.product(range(20),range(20)):
        grid=bytearray(rng.randrange(256) for _ in range(400));grid[x+y*20]=8
        seed(grid);call('spread_explosive_bricks')
    for owner,name in [('scratch','clear_explosion_list'),('balls','clear_ball_list')]:
        for length in range(7):
            for current in range(-1,length):
                seed()
                for i in range(length):add(owner,[i+11]* (SHAPES[owner][2]//4))
                pointers=[];p=n.owners[owner].first
                while p:pointers.append(p);p=p.contents.next
                target_addresses=[];a=t.read_u32(SHAPES[owner][0]+4)
                while a:target_addresses.append(a);a=t.read_u32(a+SHAPES[owner][2])
                n.owners[owner].current=pointers[current] if current>=0 else C.POINTER(SHAPES[owner][1])()
                t.write_u32(SHAPES[owner][0],target_addresses[current] if current>=0 else 0)
                call(name,owner=owner)
                if owner=='balls':
                    for entry in ('begin_balls','advance_ball','remove_ball'):call(entry,owner=owner)
                    call('append_ball',owner=owner)
    # Exercise each list operation independently at every live cursor position.
    for name in ('append_ball', 'begin_balls', 'advance_ball', 'remove_ball'):
        for length in range(7):
            for current in range(-1, length):
                seed()
                for i in range(length):
                    add('balls', [i + 11] * 13)
                pointers, addresses = [], []
                pointer = n.owners['balls'].first
                address = t.read_u32(SHAPES['balls'][0] + 4)
                while pointer:
                    pointers.append(pointer)
                    pointer = pointer.contents.next
                while address:
                    addresses.append(address)
                    address = t.read_u32(address + 52)
                n.owners['balls'].current = pointers[current] if current >= 0 else C.POINTER(BallNode)()
                t.write_u32(SHAPES['balls'][0], addresses[current] if current >= 0 else 0)
                call(name, owner='balls')
    # The source and target both take the original fatal-allocation exit path.
    for name in ('append_ball', 'spawn_ball'):
        seed()
        result = subprocess.run([ROOT / 'scripts/repo-python', Path(__file__).resolve(),
                                 '--library', args.library.resolve(), '--fail-allocator', name],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        assert result.returncode == 1, (name, result.returncode, result.stderr)
        assert not result.stdout and not result.stderr, (name, result.stdout, result.stderr)
        t.fail_allocation, t.exit_status = True, None
        if name == 'append_ball':
            t.uc.reg_write(UC_X86_REG_ECX, SHAPES['balls'][0])
        try:
            t.call(ENTRIES[name])
        except AssertionError:
            assert t.exit_status == 1
        else:
            raise AssertionError('target allocation failure returned')
        assert t.read(SHAPES['balls'][0], 12) == bytes(12)
        assert signed(t.read_u32(0x43F8F0)) == (1 if name == 'spawn_ball' else 0)
        t.fail_allocation = False
        cases[name] += 1
    for width in (1,7,59,60,101,240):
        for offset in range(-20,width+21):
            seed();setv('paddle_width',width)
            add('balls',[320-width//2+offset,449,201,301,-4,7,1,17,5,43,0,4,23])
            call('bounce_ball_from_paddle')
    for width,x,speed in itertools.product((7,60,240),(20,50,320,590),(4,5,9)):
        seed();setv('paddle_width',width);setv('paddle_x',x);call('spawn_ball')
        for i,attached in enumerate((-1,0,1,2,1)):
            add('balls',[x-17+i*8,449,71,82,(-1)**i*speed,7,1,17,speed,43,attached,4,23])
        call('release_attached_balls');call('clone_balls')
    for length in (0,1,3,7):
        seed()
        for i in range(length):add('balls',[100+i*9,400,71,82,5,7,1,17,3+i,43,i%3,4,23])
        call('clone_balls');call('release_attached_balls')
    for lives,x in itertools.product((-1,0,1,3,99),(20,320,618)):
        seed();setv('lives',lives);setv('paddle_x',x);call('lose_life')
    for index,count in itertools.product((0,48,49,50),(-1,0,1,123)):
        seed();n.index.value=index;t.write_u32(INDEX,index)
        n.control_round=t.control_round=True;n.round_count=t.round_count=count
        call('advance_level')
    n.bank[:]=boards;t.write(BANK,boards)
    for index in range(49):
        seed();n.index.value=index;t.write_u32(INDEX,index);call('advance_level')
    # All kinds, default cases, width arithmetic and actual connected dependencies.
    for kind,width,base in itertools.product(tuple(range(19))+(-1,19,255),(20,60,120,240),(59,60)):
        seed(grids[256+kind%50]);setv('paddle_width',width);sprite(68,base,8)
        setv('bonus_8_active',1);setv('bonus_9_active',1)
        add('balls',[318,442,301,401,0,0,1,17,5,43,1,4,23])
        add('bonuses',[kind,35,315,446,0,0,0]);n.count.value=1;t.write_u32(0x43FA90,1)
        n.control_round=t.control_round=True
        call('update_bonuses')
    # Movement edges, simultaneous bounces, gravity threshold and removal skip.
    for x,y,dx,dy,ticks in itertools.product((19,20,609,610),(-1,0,449,470,471),(-4,0,4),(-3,0,3),(19,20,21)):
        seed();setv('paddle_previous_x',50)
        add('bonuses',[19,35,x,y,dx,dy,ticks]);n.count.value=1;t.write_u32(0x43FA90,1)
        call('update_bonuses')
    for kinds in ((0,13,10),(4,2,6),(10,11,16),(18,19,255)):
        seed(grids[270]);
        for i,kind in enumerate(kinds):add('bonuses',[kind,35,315,446,0,0,20])
        n.count.value=3;t.write_u32(0x43FA90,3)
        for frame in range(4):call('update_bonuses');integrations+=1
    for bank, width, height, cached_x, kind in itertools.product((0, 2), (1, 11, 31),
            (1, 9, 27), (50, 320), (0, 10, 11, 16, 19)):
        seed()
        C.c_int32.in_dll(n.lib, 'dxball_sprite_bank').value = bank
        t.write_u32(SPRITE_BANK, bank)
        sprite(35, width, height, bank)
        sprite(67, 91, 13, bank)
        setv('paddle_sprite', 67)
        setv('paddle_previous_x', cached_x)
        add('bonuses', [kind, 35, 315, 446, 0, 0, 0])
        n.count.value = 1
        t.write_u32(0x43FA90, 1)
        call('update_bonuses')
    report={'target_sha256':t.target_sha256,'cases':cases,'total':sum(cases.values()),'integration_cases':integrations,
      'scope':'original connected bonus/paddle/board-power/ball-list and quantized trig bodies; finite bounded arithmetic, valid sprite metadata, state-preserving audio/render/Win32 boundaries; terminal level initialization intercepted, full ball frame and playable game remain pending'}
    output=ROOT/'build/reports/powerups-differential.json';output.parent.mkdir(parents=True,exist_ok=True)
    output.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))

if __name__=='__main__':main()
