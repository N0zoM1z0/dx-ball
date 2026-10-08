#!/usr/bin/env python3
"""Compare controller decisions through complete original/native game frames."""
import ctypes as C
import gzip
import hashlib
import io
import itertools
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from campaign_controller import choose_greatest_y as choose_mouse, choose_contact_mouse
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from test_campaign_contact import advance, seed, state
from test_core_differential import Harness
from windows_runtime import digest, verified_originals


def observation(h):
    result = state(h)
    node = h.n.owners['bonuses'].first
    while node:
        value = node.contents
        sprite = h.n.sprites[value.sprite]
        result['bonuses'].append({name:getattr(value,name) for name in
                                  ('kind','x','y','dx','dy','gravity_ticks')})
        result['bonuses'][-1].update(width=sprite.width,height=sprite.height)
        node = value.next
    return result


def trace(h, policy, frames, interval=1, delay=0, step_base=98):
    tracked = []
    node = h.n.owners['balls'].first
    while node:
        tracked.append((C.addressof(node.contents),type(node.contents)))
        node = node.contents.next
    caught = [False] * len(tracked)
    previous_dy = [C.cast(address,C.POINTER(kind)).contents.dy for address,kind in tracked]
    pending, rows = {}, []
    for frame in range(frames):
        if frame % interval == 0:
            pending[frame+delay] = policy(observation(h),step_base+frame//interval)
        if frame in pending:
            h.setv('mouse_x',pending[frame])
        row = advance(h,'game_frame')
        for i,(address,kind) in enumerate(tracked):
            if h.n.allocations[address]['live']:
                dy = C.cast(address,C.POINTER(kind)).contents.dy
                caught[i] |= previous_dy[i] > 0 and dy < 0
                previous_dy[i] = dy
        row.update(frame=frame,requested=h.n.extra[0x438B0C].value,
                   bonuses=observation(h)['bonuses'])
        rows.append(row)
    return dict(trace=rows,tracked_caught=caught,
                tracked_surviving=[h.n.allocations[a]['live'] for a,_ in tracked],
                final_ball_count=len(rows[-1]['balls']),final_lives=rows[-1]['lives'])


def main():
    if not __debug__:
        raise RuntimeError('Campaign policy comparisons require assertions; do not use -O.')
    limit_cpu()
    with session_lock():
        originals=verified_originals()
        library=ROOT/'build/native/libdxball_core.so'
        library_sha256=digest(library)
        inputs={str(p.relative_to(ROOT)):digest(p) for p in sorted((ROOT/'src').glob('*.[ch]'))}
        for module in tuple(sys.modules.values()):
            filename=getattr(module,'__file__',None)
            if filename:
                p=Path(filename).resolve()
                if p.is_relative_to(ROOT) and p.suffix=='.py':inputs[str(p.relative_to(ROOT))]=digest(p)
        for n in ('config/target.toml','config/assets.csv','config/tools.lock.toml',
                  'requirements-analysis.txt','scripts/repo-python','scripts/verify-python.py'):
            inputs[n]=digest(ROOT/n)
        h=Harness(library);code=h.t.read(0x401000,0x1f000);vectors=[]
        policies=(('greatest-y',choose_mouse),('contact',choose_contact_mouse))
        # Nonzero kind-3 storage is a controlled counterfactual, not an observed producer.
        for width,height,dy,ticks,side in itertools.product((36,219),(5,6,9),(1,5,9),(0,73),('left','middle','right')):
            for label,policy in policies:
                seed(h,width,height);h.setv('bonus_3_ticks',ticks)
                lower=453-(7+height)//2-height//2
                x,dx={'left':(20,-5),'middle':(315,5),'right':(619-height,5)}[side]
                h.ball(x=x,y=lower-4*(dy+int(ticks!=0)),dx=dx,dy=dy,speed=9,angle=90)
                result=trace(h,policy,10)
                if label=='contact':assert result['tracked_caught']==[True],(width,height,dy,ticks,side,result)
                vectors.append(dict(family='kind3-wall-contact',policy=label,width=width,height=height,
                                    initial_dy=dy,initial_ticks=ticks,side=side,**result))
        # Moving rewards/hazards exercise actual collection, gravity and retirement.
        for width,kind,dx,y,urgent in itertools.product((36,219),(0,10,11,13,16),(-5,0,5),(397,440),(False,True)):
            for label,policy in policies:
                seed(h,width,9)
                h.ball(x=495,y=410 if urgent else 300,dx=0,dy=9 if urgent else -3,speed=9,angle=90)
                h.sprite(35+kind,12,12)
                h.add('bonuses',[kind,35+kind,490,y,dx,3,20])
                h.n.count.value=1;h.t.write_u32(0x43FA90,1)
                result=trace(h,policy,12)
                vectors.append(dict(family='moving-bonus',policy=label,width=width,kind=kind,
                                    initial_dx=dx,initial_y=y,urgent=urgent,**result))
        # All six rebound phases with bonus gravity boundaries and wall clamps.
        for width,kind,phase,gravity,side,urgent in itertools.product(
                (36,219),(11,13,16),range(6),(0,19,20),('left','right'),(False,True)):
            for label,policy in policies:
                seed(h,width,9)
                x,dx=(20,-5) if side=='left' else (610,5)
                h.ball(x=x,y=410 if urgent else 300,dx=dx,dy=9 if urgent else -3,speed=9,angle=90)
                h.sprite(35+kind,12,12)
                h.add('bonuses',[kind,35+kind,x,420,dx,3,gravity])
                h.n.count.value=1;h.t.write_u32(0x43FA90,1)
                result=trace(h,policy,12,step_base=phase*100)
                vectors.append(dict(family='bonus-phase-gravity-wall',policy=label,width=width,kind=kind,
                                    phase=phase,initial_gravity=gravity,side=side,urgent=urgent,**result))
        # Track every initially falling ball past both contacts, with explicit delivery controls.
        for width,height,interval,delay in itertools.product((36,73,146,219),(5,9),(1,2,3),(0,1,2)):
            for label,policy in policies:
                seed(h,width,height)
                h.ball(x=95,y=430,dx=0,dy=1,speed=9,angle=90)
                h.ball(x=495,y=410,dx=0,dy=9,speed=9,angle=90)
                result=trace(h,policy,40,interval,delay)
                vectors.append(dict(family='continued-multi-ball',policy=label,width=width,height=height,
                                    sample_interval_frames=interval,input_delay_frames=delay,**result))
        assert len(vectors)==1464 and sum(h.cases.values())==21168
        assert h.t.read(0x401000,0x1f000)==code and originals==verified_originals()
        assert library_sha256==digest(library)
        assert inputs=={n:digest(ROOT/n) for n in inputs}
        summaries=[]
        for family in ('kind3-wall-contact','moving-bonus','bonus-phase-gravity-wall','continued-multi-ball'):
            for label,_ in policies:
                rows=[r for r in vectors if r['family']==family and r['policy']==label]
                summaries.append(dict(family=family,policy=label,fixtures=len(rows),
                    all_tracked_caught=sum(all(r['tracked_caught']) for r in rows),
                    all_tracked_surviving=sum(all(r['tracked_surviving']) for r in rows),
                    round_has_ball=sum(r['final_ball_count']>0 for r in rows),
                    life_loss=sum(r['final_lives']<3 for r in rows)))
        report=dict(status='pass',target_sha256=h.t.target_sha256,library_sha256=library_sha256,
                    inputs=inputs,originals=originals,fixtures=len(vectors),compared_frames=sum(h.cases.values()),
                    immutable_code_sha256=hashlib.sha256(code).hexdigest(),summaries=summaries,vectors=vectors,
                    limitations=['Controlled empty-board original/native integration, not new direct owner cases.',
                                 'Nonzero kind-3 storage is injected symmetrically; no live producer is established.',
                                 'Finite traces and declared frame delays do not prove full campaigns or live latency.',
                                 'Incompatible simultaneous contacts and future brick trajectories remain unguaranteed.'])
        p=ROOT/'build/reports/campaign-policy-differential.json.gz'
        with p.open('wb') as out:
            with gzip.GzipFile(fileobj=out,mode='wb',mtime=0,compresslevel=6) as compressed:
                with io.TextIOWrapper(compressed,encoding='utf-8') as stream:
                    json.dump(report,stream,indent=2)
                    stream.write('\n')
        print(json.dumps(dict(fixtures=report['fixtures'],compared_frames=report['compared_frames'],summaries=summaries),indent=2))


if __name__=='__main__':main()
