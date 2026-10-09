#!/usr/bin/env python3
"""Execute the original ball and frame bosses with connected maintained owners."""
import argparse
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import random
import struct
import subprocess
import sys

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ECX
from target_oracle import ROOT, TILES, AUX, INDEX, MODE, ACTIVE_SURFACE, BANK
from resources_oracle import BANKS, SPRITE_BANK
from test_gameplay_differential import Allocate, Ops, signed, REMAINING, HARD, REDUCED, PENDING, SCORE, PAN_SCALE
from test_entities_differential import SHAPES, entity_type
from test_powerups_differential import FamilyNative, FamilyTarget, GLOBALS, BallNode

ProjectileNode, ProjectileList = entity_type('ProjectileNode', ('x', 'y', 'previous_x', 'previous_y'))
FireNode, FireList = entity_type('FireNode', ('x', 'y', 'ticks'))
SHAPES.update(projectiles=(0x43A898, ProjectileNode, 16), fire=(0x43A8E0, FireNode, 12))
GLOBALS.update({0x43A900:'projectile_count', 0x43FAB8:'launch_requested', 0x43A8FC:'attached_ball_cue',
                0x43FAE4:'paused', 0x4228D0:'draw_to_primary', 0x438B10:'mouse_action',
                0x43FAEC:'last_brick_deadline', 0x43F8D8:'palette_tick'})
ENTRIES = {'update_balls':0x410770, 'game_frame':0x40F8B0, 'hit_screen_point':0x4116C0,
           'retire_ball':0x411820, 'drop_bricks':0x415670, 'spawn_fire_effect':0x4135B0,
           'process_fire_effects':0x413710, 'update_projectiles':0x413170, 'fire_projectiles':0x4132C0}
FRAME_BOUNDARIES = [('current_time', 0x403450, 0), ('elapsed', 0x4034F0, 2),
    ('animate_palette', 0x40A970, 3), ('update_score', 0x415880, 0),
    ('wait_frames', 0x409610, 1), ('restore_regions', 0x408CC0, 0),
    ('draw_effect_sprite', 0x4082F0, 3), ('draw_paddle', 0x412EC0, 0),
    ('last_brick', 0x415F40, 0), ('draw_last_brick', 0x416370, 0),
    ('present', 0x409040, 0), ('restart_round', 0x415DF0, 0)]


class CoreNative(FamilyNative):
    def __init__(self, library):
        from core_native_loader import fixture_image, bind_gameplay
        self.core_native_image = fixture_image(library)
        super().__init__(self.core_native_image.path)
        self.core_gameplay_table = Ops.in_dll(self.lib, 'dxball_gameplay_ops')
        bind_gameplay(self.core_native_image, self.lib, self.core_gameplay_table)
        self.owners.update(projectiles=ProjectileList.in_dll(self.lib, 'dxball_projectiles'),
                           fire=FireList.in_dll(self.lib, 'dxball_fire_effects'))
        for owner, singular, plural in ((ProjectileList, 'projectile', 'projectiles'),
                                       (FireList, 'fire_effect', 'fire_effects')):
            for name in ('append_' + singular, 'begin_' + plural,
                         'advance_' + singular, 'remove_' + singular):
                function = getattr(self.lib, 'dxball_' + name)
                function.argtypes, function.restype = [C.POINTER(owner)], C.c_int32
        self.now, self.timer_result = 1000, 0
        def checked(function, fallback=None):
            def callback(*args):
                try: return function(*args)
                except Exception as error:
                    self.errors.append(repr(error))
                    return fallback
            return callback
        callbacks = []
        for name, _, count in FRAME_BOUNDARIES:
            result = C.c_uint32 if name == 'current_time' else C.c_int32 if name == 'elapsed' else None
            argument = C.c_uint32 if name == 'elapsed' else C.c_int32
            signature = C.CFUNCTYPE(result, *([argument] * count))
            callbacks.append(signature(checked(lambda *a, name=name: self.frame_boundary(name, a), 0)))
        self.core_callbacks = callbacks
        table = (C.c_void_p * len(callbacks)).in_dll(self.lib, 'dxball_frame_ops')
        for i, callback in enumerate(callbacks): table[i] = C.cast(callback, C.c_void_p).value
        blt = C.CFUNCTYPE(C.c_int32, C.c_void_p, C.c_void_p, C.c_void_p, C.c_void_p, C.c_uint32, C.c_void_p)
        self.blt_callback = blt(checked(self.board_blt, -1))
        self.vtable[5] = C.cast(self.blt_callback, C.c_void_p).value
        for name in ENTRIES:
            function = getattr(self.lib, 'dxball_' + name)
            function.argtypes = [C.c_int32]*2 if name in ('hit_screen_point','spawn_fire_effect') else []
            function.restype = C.c_int32 if name == 'hit_screen_point' else None

    def observed(self):
        if hasattr(self, 'owners'):
            for owner in self.owners: self.queue(owner)
        return super().observed() + (self.hit_dx.value, self.hit_dy.value) if hasattr(self,'hit_dx') else super().observed()

    def frame_boundary(self, name, args):
        # Observe phase-entry state, not just final state: this detects order changes.
        self.events.append(('frame', name, *args, self.observed()))
        return self.now if name == 'current_time' else self.timer_result if name == 'elapsed' else None

    def board_blt(self, destination, rect, source, source_rect, flags, fx):
        assert destination == self.surface_pointer and source == CoreTarget.BACKGROUND and fx is None
        coordinates = struct.unpack('<4i',C.string_at(rect,16))
        assert coordinates == struct.unpack('<4i',C.string_at(source_rect,16))
        self.events.append(('board-blt',coordinates,flags,self.observed()))
        return 0

    def restore(self, destination, x, y, source, rect, flags):
        if destination == self.surface_pointer: destination = CoreTarget.SURFACE
        super().restore(destination, x, y, source, rect, flags)

    def free(self, address):
        allocation = self.allocations[address]
        if allocation['owner'] is None:
            assert allocation['size'] == C.sizeof(BallNode), 'unclassified deletion'
            payload = 52  # clone scratch can be produced and freed inside one call
        else: payload = SHAPES[allocation['owner']][2]
        assert allocation['live']
        self.events.append(('free-payload',C.string_at(address,payload).hex(),self.observed()))
        allocation['live'] = False
        C.memset(address,0xDD,allocation['size'])


class CoreTarget(FamilyTarget):
    def __init__(self):
        super().__init__()
        self.now, self.timer_result = 1000, 0
        self.frame_hooks = {}
        for name, address, count in FRAME_BOUNDARIES:
            def callback(*unused, name=name, count=count):
                args = self._args(count)
                if name != 'elapsed': args = tuple(signed(a) for a in args)
                self.events.append(('frame',name,*args,self.observed()))
                self._return(self.now if name == 'current_time' else self.timer_result if name == 'elapsed' else 0)
            hook = self.uc.hook_add(UC_HOOK_CODE,callback,begin=address,end=address)
            self.frame_hooks[name] = hook
            self._hooks.append(hook)
        self.write_u32(self.VTABLE+5*4,0x50D000)
        self._hooks.append(self.uc.hook_add(UC_HOOK_CODE,self.board_blt,begin=0x50D000,end=0x50D000))

    def observed(self):
        return super().observed() + (signed(self.read_u32(0x43A8A8)),signed(self.read_u32(0x43A8AC)))

    def board_blt(self,*unused):
        destination,rect,source,source_rect,flags,fx = self._args(6)
        assert (destination,source,fx) == (self.SURFACE,self.BACKGROUND,0)
        coordinates = struct.unpack('<4i',self.read(rect,16))
        assert coordinates == struct.unpack('<4i',self.read(source_rect,16))
        self.events.append(('board-blt',coordinates,flags,self.observed()))
        self._return(pop=24)


class Harness:
    def __init__(self,library,native_type=CoreNative,target_type=CoreTarget):
        self.n,self.t = native_type(library),target_type()
        self.cases = dict.fromkeys(ENTRIES,0)
        self.connected_frames = 0
        self.seed()
        self.n.lib.dxball_initialize_trig()
        self.t.call(0x402250)

    def setv(self,name,value):
        address = next(a for a,n in GLOBALS.items() if n == name)
        self.n.extra[address].value = signed(value)
        self.t.write_u32(address,value)

    def state(self,address,value):
        self.n.state[address].value = value; self.t.write_u32(address,value)

    def sprite(self,slot,width,height,bank=0):
        n,t = self.n,self.t
        n.sprites[slot].width,n.sprites[slot].height = width,height
        n.banks[bank].sprites[slot] = C.pointer(n.sprites[slot])
        # Keep metadata outside the pixel buffer, including for connected drawing.
        address = 0x880000+slot*48
        t.write(address,bytes(44)); t.write(address+8,struct.pack('<2i',width,height))
        t.write_u32(BANKS+bank*1048+slot*4,address)

    def seed(self,grid=None):
        n,t = self.n,self.t
        n.reset(); t.reset()
        for name in GLOBALS.values(): self.setv(name,0)
        for a in n.state: self.state(a,0)
        n.hit_dx.value,n.hit_dy.value = 17,-23
        t.write_u32(0x43A8A8,17);t.write_u32(0x43A8AC,-23)
        n.count.value=0; t.write_u32(0x43FA90,0)
        n.scale.value=1; t.write(PAN_SCALE,struct.pack('<d',1))
        n.index.value=0; t.write_u32(INDEX,0)
        n.mode.value=0; t.write_u32(MODE,0)
        n.active.value=0xAA; t.write_u32(ACTIVE_SURFACE,0xAA)
        n.cell=t.cell=85
        n.tiles[:] = grid if grid is not None else bytes(400); t.write(TILES,bytes(n.tiles))
        n.aux[:] = bytes(400); t.write(AUX,bytes(n.aux))
        for name,value in [('paddle_x',320),('paddle_y',450),('paddle_width',60),('paddle_sprite',68),
                           ('paddle_previous_x',320),('paddle_previous_y',450),
                           ('mouse_x',320),('mouse_y',477),('lives',3)]: self.setv(name,value)
        C.c_int32.in_dll(n.lib,'dxball_sprite_bank').value=0; t.write_u32(SPRITE_BANK,0)
        for slot in (1,32,55,61,68,*range(35,54)): self.sprite(slot,60 if slot==68 else 10,8)
        n.control_round=t.control_round=False
        C.c_size_t.in_dll(n.lib,'dxball_board_surface').value=n.surface_pointer
        C.c_size_t.in_dll(n.lib,'dxball_background_surface').value=t.BACKGROUND
        t.write_u32(0x4228BC,t.SURFACE);t.write_u32(0x421070,t.BACKGROUND)
        n.now=t.now=1000; n.timer_result=t.timer_result=0
        n.pitch=t.pitch=643; n.lock_failures=t.lock_failures=0
        C.memset(n.pixels,0xA7,C.sizeof(n.pixels)); t.write(t.PIXELS,b'\xa7'*C.sizeof(n.pixels))
        t.write_u32(0x42309C,0)

    def add(self,owner,payload):
        n,t = self.n,self.t
        n.events=[];t.events=[]
        if owner in ('fire','projectiles'):
            function = 'append_fire_effect' if owner == 'fire' else 'append_projectile'
            getattr(n.lib, 'dxball_' + function)(C.byref(n.owners[owner]))
            entry=0x413670 if owner=='fire' else 0x413410
        else:
            function='append_ball' if owner in ('balls','clones') else 'append_bonus' if owner=='bonuses' else 'append_explosion' if owner in ('explosions','scratch') else 'append_brick_effect'
            entry={'append_ball':0x4106D0,'append_bonus':0x413D80,'append_explosion':0x412470,'append_brick_effect':0x412690}[function]
            getattr(n.lib,'dxball_'+function)(C.byref(n.owners[owner]))
        t.uc.reg_write(UC_X86_REG_ECX,SHAPES[owner][0]);t.call(entry)
        data=struct.pack('<'+'i'*len(payload),*payload)
        C.memmove(n.owners[owner].current,data,len(data));t.write(t.read_u32(SHAPES[owner][0]),data)
        n.queue(owner);t.queue(owner)

    def ball(self,x=315,y=400,dx=3,dy=-5,sprite=1,speed=5,attached=0,offset=0,bounces=0,wall=0,angle=75):
        self.add('balls',[x,y,71,82,dx,dy,sprite,angle,speed,bounces,attached,offset,wall])
        self.setv('ball_count',self.n.extra[0x43F8F0].value+1)

    def compare(self,context):
        n,t = self.n,self.t
        assert not n.errors,(context,n.errors)
        assert bytes(n.tiles)==t.read(TILES,400),(context,'tiles')
        assert bytes(n.aux)==t.read(AUX,400),(context,'aux')
        assert n.observed()==t.observed(),(context,'globals',n.observed(),t.observed())
        for a,v in n.state.items(): assert v.value==signed(t.read_u32(a)),(context,hex(a))
        surface=t.SURFACE if n.active.value==n.surface_pointer else n.active.value
        assert surface==t.read_u32(ACTIVE_SURFACE),(context,'active-surface')
        assert C.string_at(n.pixels,C.sizeof(n.pixels))==t.read(t.PIXELS,C.sizeof(n.pixels)),(context,'pixels')
        if n.events != t.events:
            difference=next((i for i,(a,b) in enumerate(zip(n.events,t.events)) if a!=b),min(len(n.events),len(t.events)))
            raise AssertionError((context,'events',difference,n.events[difference:difference+2],t.events[difference:difference+2]))
        live=0
        for owner in SHAPES:
            nq,tq=n.queue(owner),t.queue(owner)
            assert nq==tq,(context,owner,nq,tq)
            live+=len(nq[0])
        for oracle in (n,t):
            assert sum(a['live'] for a in oracle.allocations.values())==live,(context,'lost allocation')
            for address,a in oracle.allocations.items():
                if not a['live']:
                    data=C.string_at(address,a['size']) if oracle is n else oracle.read(address,a['size'])
                    assert data==b'\xdd'*a['size'],(context,'write after free')

    def call(self,name,*args):
        nr=self.n.call('dxball_'+name,*args);tr=self.t.call(ENTRIES[name],*args)
        if nr is not None: assert nr==tr,(name,args,nr,tr)
        self.compare((name,args,self.cases[name]))
        self.cases[name]+=1


def main():
    if not __debug__:
        raise RuntimeError('Core comparisons require Python assertions; do not use -O.')
    sys.path.insert(0,str(ROOT/'scripts'))
    from resource_limits import limit_cpu
    limit_cpu()
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library',type=Path,default=ROOT/'build/native/libdxball_core.so')
    parser.add_argument('--fail-allocator', choices=('spawn_fire_effect','fire_projectiles'))
    args=parser.parse_args()
    if args.fail_allocator:
        n=CoreNative(args.library)
        failure=Allocate(lambda size: None)
        Ops.in_dll(n.lib,'dxball_gameplay_ops').allocate_node=failure
        if args.fail_allocator=='spawn_fire_effect':n.lib.dxball_spawn_fire_effect(100,200)
        else:
            n.sprites[32].width,n.sprites[32].height=10,8
            n.banks[0].sprites[32]=C.pointer(n.sprites[32])
            n.lib.dxball_fire_projectiles()
        raise AssertionError('failed allocation returned')
    h=Harness(args.library);rng=random.Random(0x410770)
    # Coordinate clamp and strict Y boundary, real hit constructors/score/fire queues.
    for x,y,tile,fire,hard in itertools.product((-1000,19,20,49,50,589,619,1000),
            (49,50,64,65,349,350),(0,1,2,8,21,22),(0,1),(0,1)):
        h.seed(bytes([tile])*400);h.ball(sprite=61 if fire else 1,speed=9)
        h.state(REMAINING,400);h.state(HARD,hard)
        h.call('hit_screen_point',x,y)
    # Fire placement and original remove+advance animation skipping.
    for x,y in itertools.product((-100,0,24,595,619,639,1000),(-100,0,23,436,459,479,1000)):
        h.seed();h.call('spawn_fire_effect',x,y)
    for name in ('spawn_fire_effect','fire_projectiles'):
        h.seed()
        result=subprocess.run([ROOT/'scripts/repo-python',Path(__file__).resolve(),
            '--library',args.library.resolve(),'--fail-allocator',name],capture_output=True)
        assert result.returncode==1 and not result.stdout and not result.stderr,(name,result)
        h.t.fail_allocation=True;h.t.exit_status=None
        try:h.t.call(ENTRIES[name],*([100,200] if name=='spawn_fire_effect' else []))
        except AssertionError:assert h.t.exit_status==1
        else:raise AssertionError('target failed allocation returned')
        for owner in ('fire','projectiles'):assert h.t.read(SHAPES[owner][0],12)==bytes(12)
        h.t.fail_allocation=False;h.cases[name]+=1
    for ticks in ((0,),(20,21,0),(21,21,21),(22,0,21,20)):
        h.seed()
        for i,tick in enumerate(ticks):h.add('fire',[20+i*40,200,tick])
        for _ in range(24):h.call('process_fire_effects')
    # Retire is count-gated, including count/cursor disagreement.
    for count,length in itertools.product((-1,0,1,3),(0,1,3)):
        h.seed()
        for i in range(length):h.ball(x=100+i*30)
        h.setv('ball_count',count);h.call('retire_ball')
    # Actual tile redraw and DirectDraw Blt parameters; aux stays in place.
    boards=(ROOT/'original/DEFAULT.BDS').read_bytes()
    for i in range(50):
        h.seed(boards[i*400:(i+1)*400]);h.n.aux[:]=b'\x85'*400;h.t.write(AUX,bytes(h.n.aux))
        h.call('drop_bricks')
    for tile in (0,1,2,8,21,22):
        h.seed(bytes([tile])*400);h.call('drop_bricks')
    # Moving balls: edges, exact death threshold, multiple simultaneous wall hits.
    for x,y,dx,dy in itertools.product((15,20,21,608,609,620),(-8,0,1,440,470,471,472),(-5,0,5),(-5,0,5)):
        h.seed();h.ball(x=x,y=y,dx=dx,dy=dy);h.call('update_balls')
    # Sticky offsets, speed threshold/cap, cached paddle differs from live paddle.
    for sticky,drop,width,x,speed,bounces,reduced in itertools.product((0,1),(0,1),(59,60),
            (288,295,315,339,346),(7,8,9),(40,41),(0,1)):
        h.seed(boards[400:800]);h.state(REMAINING,100)
        h.setv('paddle_width',width);h.setv('paddle_x',330)
        h.setv('bonus_9_active',sticky);h.setv('bonus_17_active',drop);h.state(REDUCED,reduced)
        h.ball(x=x,y=438,dx=0,dy=5,speed=speed,bounces=bounces,wall=300)
        h.call('update_balls')
    # Attached branch accepts every nonzero state; release keeps this frame attached to paddle.
    for attached,launch,offset in itertools.product((-1,1,2),(0,1,2),(-37,0,31)):
        h.seed();h.ball(attached=attached,offset=offset)
        h.setv('launch_requested',launch);h.call('update_balls')
    # Real board interactions, horizontal sample short-circuit, fire trail RNG order.
    for i in range(1400):
        h.seed(boards[(i%50)*400:(i%50+1)*400]);h.state(REMAINING,100)
        h.state(HARD,i%2);h.state(REDUCED,(i//2)%2);h.setv('bonus_3_ticks',i%3-1)
        h.ball(x=rng.randrange(15,625),y=rng.randrange(38,359),dx=rng.randrange(-10,11),
               dy=rng.randrange(-10,11),sprite=61 if i%3==0 else 1,speed=rng.randrange(4,10),wall=299+i%3)
        h.call('update_balls')
    for length in (0,1,3,6):
        h.seed()
        for i in range(length):h.ball(x=100+i*30,y=474 if i%2==0 else 400,dy=2)
        for _ in range(4):h.call('update_balls')
    # x87 truncation at the 15%/85% sampling boundaries, odd/large sprites,
    # alternate sprite banks and fire-specific lookup all use actual metadata.
    for bank,width,height,sprite in itertools.product((0,2),(1,7,31),(1,7,20,40),(1,55,61)):
        h.seed(boards[800:1200]);h.state(REMAINING,100)
        C.c_int32.in_dll(h.n.lib,'dxball_sprite_bank').value=bank;h.t.write_u32(SPRITE_BANK,bank)
        h.sprite(sprite,width,height,bank)
        h.ball(x=49,y=78,dx=-3,dy=-5,sprite=sprite,speed=5)
        h.call('update_balls')
    # Shooting and real projectile collision: includes successor skipping after deletion.
    for width in (1,7,59,60,120,240):
        h.seed();h.setv('paddle_width',width);h.call('fire_projectiles')
        for _ in range(3):h.call('update_projectiles')
    for tile,hard,y in itertools.product((0,1,2,8,21,22),(0,1),(0,7,8,49,50,57,58,350,359)):
        h.seed(bytes([tile])*400);h.state(REMAINING,400);h.state(HARD,hard)
        for i in range(3):h.add('projectiles',[100+i*30,y,123,234])
        h.setv('projectile_count',3);h.call('update_projectiles')
    # Pause bypasses every gameplay phase and preserves queued input.
    for paused,timer,action in itertools.product((1,0,2),(0,1),(0,1,2,3)):
        h.seed();h.ball();h.state(REMAINING,2);h.setv('paused',paused);h.setv('mouse_action',action)
        h.n.timer_result=h.t.timer_result=timer;h.call('game_frame')
    # All deferred power combinations are ordered AFTER drawing/explosion requests.
    powers=('bonus_3_active','bonus_14_active','bonus_18_active','bonus_12_active','bonus_7_active')
    for mask,dx,dy in itertools.product(range(32),(-3,0,3),(-5,0,5)):
        h.seed();h.state(REMAINING,2);h.ball(dx=dx,dy=dy,sprite=61 if mask%3==0 else 55,speed=8)
        for bit,name in enumerate(powers):h.setv(name,(mask>>bit)&1)
        h.call('game_frame')
    for restore,remaining,deadline,action,count in itertools.product((0,1),(-1,0,1,2),
            (0,789),(0,1,2,3),(0,5,6)):
        h.seed();h.ball(attached=1)
        h.setv('draw_to_primary',restore);h.state(REMAINING,remaining)
        h.setv('last_brick_deadline',deadline);h.setv('mouse_action',action)
        h.setv('bonus_8_active',1);h.setv('projectile_count',count)
        h.n.control_round=h.t.control_round=True;h.call('game_frame')
    # Finish waits for BOTH animation queues; begin checks retain their cursor side effects.
    for effect,fire in itertools.product((0,1),(0,1)):
        h.seed();h.state(REMAINING,0);h.ball(attached=1)
        if effect:
            h.add('effects',[1,22,20,50,8,8,0,0]);h.n.aux[0]=1;h.t.write(AUX,b'\x01')
        if fire:h.add('fire',[100,200,0])
        h.n.control_round=h.t.control_round=True;h.call('game_frame')
        assert h.n.index.value==(0 if effect or fire else 1),'must wait for both animation queues'
    # Connected multi-frame scenarios execute the original full frame: physics,
    # tile damage, effects, bonuses, particles and deferred powers stay unhooked.
    h.n.bank[:]=boards;h.t.write(BANK,boards)
    for board in (0,1,9,24,49):
        h.seed(boards[board*400:(board+1)*400]);h.state(REMAINING,200)
        h.ball(x=314,y=330,dx=4,dy=-7,sprite=61,speed=7)
        h.add('bonuses',[12,47,315,446,0,0,0]);h.n.count.value=1;h.t.write_u32(0x43FA90,1)
        for frame in range(40):
            h.setv('mouse_action',1 if frame in (2,17) else 0)
            h.setv('bonus_8_active',1 if frame>=10 else 0)
            h.n.now=h.t.now=1000+frame*20
            h.n.timer_result=h.t.timer_result=int(frame%3==0)
            h.call('game_frame');h.connected_frames+=1
    report={'target_sha256':hashlib.sha256((ROOT/'original/DXBALL.EXE').read_bytes()).hexdigest(),
            'cases':h.cases,'total':sum(h.cases.values()),'connected_frames':h.connected_frames,
            'connected_frames_are_subset':True,'frame_boundaries':[name for name,_,_ in FRAME_BOUNDARIES],
            'scope':'original full ball/frame bodies; configured time/render/score/last-brick/restart dependencies; maintained physics, projectiles, fire effects, tiles, powers and entity queues execute'}
    path=ROOT/'build/reports/core-differential.json';path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))


if __name__=='__main__':main()
