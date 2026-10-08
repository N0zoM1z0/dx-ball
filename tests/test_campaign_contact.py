#!/usr/bin/env python3
"""Compare original/core contact timing and controlled mouse-delivery policies."""
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from campaign_controller import choose_mouse
from campaign_contact_candidate import choose_earliest_contact
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from test_core_differential import Harness, GLOBALS
from test_gameplay_differential import REMAINING
from windows_runtime import verified_originals, digest


def state(harness):
    n = harness.n
    result = {name: n.extra[address].value for address, name in GLOBALS.items()}
    result['bonuses'] = []
    result['balls'] = []
    pointer = n.owners['balls'].first
    while pointer:
        node = pointer.contents
        sprite = n.sprites[node.sprite]
        result['balls'].append({name: getattr(node, name) for name in ('x','y','dx','dy','attached')})
        result['balls'][-1].update(width=sprite.width, height=sprite.height)
        pointer = node.next
    return result


def seed(h, width, height):
    h.seed()
    h.setv('paddle_width', width)
    h.setv('cursor_warp_disabled', 1)
    h.sprite(1, height, height)
    h.sprite(68, width, 7)
    h.state(REMAINING, 2)


def advance(h, entry):
    h.n.events = []; h.t.events = []
    h.call(entry)
    summary = state(h)
    summary.update(normalized_roots=h.n.queue('balls'),
                   ordered_events_sha256=hashlib.sha256(json.dumps(h.n.events, separators=(',',':')).encode()).hexdigest(),
                   complete_globals_sha256=hashlib.sha256(json.dumps(h.n.observed(), separators=(',',':')).encode()).hexdigest())
    return summary


def main():
    if not __debug__:
        raise RuntimeError('Contact comparisons require Python assertions; do not use -O.')
    limit_cpu()
    # Serialize complete original/native executions with other project writers.
    with session_lock():
        originals = verified_originals()
        library = ROOT / 'build/native/libdxball_core.so'
        library_sha256 = digest(library)
        inputs = {str(p.relative_to(ROOT)): digest(p) for p in sorted((ROOT / 'src').glob('*.[ch]'))}
        for module in tuple(sys.modules.values()):
            filename = getattr(module, '__file__', None)
            if filename:
                p = Path(filename).resolve()
                if p.is_relative_to(ROOT) and p.suffix == '.py': inputs[str(p.relative_to(ROOT))] = digest(p)
        for name in ('config/target.toml','config/assets.csv','config/tools.lock.toml',
                     'requirements-analysis.txt','scripts/repo-python',
                     'scripts/verify-python.py','scripts/verify-target.py','scripts/ghidra.py'):
            inputs[name] = digest(ROOT / name)
        h = Harness(library)
        assert digest(library) == library_sha256
        original_code = h.t.read(0x401000, 0x1f000)
        cases = []
        # Late input cannot change the cached position used by this impact.
        for width, height, offsets in itertools.product((36,73,146,219),(5,9),((0,0),(0,180),(180,0),(-180,180))):
            seed(h,width,height)
            previous, requested = (320 + offset for offset in offsets)
            h.setv('paddle_x',previous); h.setv('paddle_previous_x',previous); h.setv('mouse_x',requested)
            h.ball(x=320-height//2,y=450-height,dx=0,dy=9,speed=9,angle=90)
            trace = [advance(h,'game_frame') for _ in range(2)]
            assert (trace[0]['balls'][0]['dy'] < 0) == (offsets[0] == 0)
            assert trace[0]['paddle_previous_x'] == requested
            cases.append(dict(family='cached-impact',width=width,height=height,previous=previous,requested=requested,trace=trace))
        # Actual original wall handling clamps overshoot before reflection.
        for width,height,edge,dx in itertools.product((36,73,146,219),(5,9),('left-before','left','left-after','right-before','right','right-after'),(-9,9)):
            seed(h,width,height)
            bound = 619-height
            x = {'left-before':19,'left':20,'left-after':21,'right-before':bound-1,'right':bound,'right-after':bound+1}[edge]
            expected_x = max(20,min(bound,x+dx))
            paddle = max(width//2+21,min(618-width//2,expected_x+height//2))
            h.setv('paddle_x',paddle);h.setv('paddle_previous_x',paddle)
            h.ball(x=x,y=450-height-9,dx=dx,dy=9,speed=9,angle=90)
            frame = advance(h,'update_balls')
            assert frame['balls'][0]['x'] == expected_x
            cases.append(dict(family='wall-impact',width=width,height=height,x=x,dx=dx,frame=frame))
        # Fixed sampling/input delays are controlled frame units, not measured Wine latency.
        policy_results = []
        for width,height,interval,delay in itertools.product((36,73,146,219),(5,9),(1,2,3),(0,1,2)):
            for label,policy in (('frozen-greatest-y',choose_mouse),('earliest-contact-candidate',choose_earliest_contact)):
                seed(h,width,height)
                h.ball(x=95,y=430,dx=0,dy=1,speed=9,angle=90)
                h.ball(x=495,y=410,dx=0,dy=9,speed=9,angle=90)
                fast = h.n.owners['balls'].last
                fast_address = C.addressof(fast.contents)
                fast_type = type(fast.contents)
                pending = {}; decisions = 98; caught = False; trace = []
                for frame in range(14):
                    before = state(h)
                    if frame % interval == 0:
                        pending[frame+delay] = policy(before, decisions)
                        decisions += 1
                    if frame in pending: h.setv('mouse_x',pending[frame])
                    row = advance(h,'game_frame')
                    row.update(frame=frame,requested=h.n.extra[0x438B0C].value)
                    if h.n.allocations[fast_address]['live']:
                        fast_node = C.cast(fast_address,C.POINTER(fast_type)).contents
                        caught = caught or fast_node.dy < 0
                    trace.append(row)
                outcome = dict(family='multi-ball-delivery',policy=label,width=width,height=height,
                               sample_interval_frames=interval,input_delay_frames=delay,fast_ball_caught=caught,
                               fast_ball_retired=not h.n.allocations[fast_address]['live'],trace=trace)
                cases.append(outcome)
                policy_results.append({k:v for k,v in outcome.items() if k!='trace'})
        # A passed ball can hold greatest-Y priority while another is still catchable.
        for width,height in itertools.product((36,73,146,219),(5,9)):
            for label,policy in (('frozen-greatest-y',choose_mouse),('earliest-contact-candidate',choose_earliest_contact)):
                seed(h,width,height)
                h.ball(x=95,y=423,dx=0,dy=9,speed=9,angle=90)
                tracked=h.n.owners['balls'].first
                tracked_address=C.addressof(tracked.contents); tracked_type=type(tracked.contents)
                h.ball(x=495,y=461,dx=0,dy=9,speed=9,angle=90)
                caught=False;trace=[]
                for frame in range(8):
                    h.setv('mouse_x',policy(state(h),frame))
                    row=advance(h,'game_frame');row.update(frame=frame,requested=h.n.extra[0x438B0C].value)
                    if h.n.allocations[tracked_address]['live']:
                        node=C.cast(tracked_address,C.POINTER(tracked_type)).contents
                        caught=caught or node.dy<0
                    trace.append(row)
                outcome=dict(family='passed-ball-priority',policy=label,width=width,height=height,
                             viable_ball_caught=caught,viable_ball_retired=not h.n.allocations[tracked_address]['live'],trace=trace)
                cases.append(outcome);policy_results.append({k:v for k,v in outcome.items() if k!='trace'})
        # Compare the candidate's wall projection through actual full-frame input.
        for width,height,side in itertools.product((36,73,146,219),(5,9),('left','right')):
            for label,policy in (('frozen-greatest-y',choose_mouse),('earliest-contact-candidate',choose_earliest_contact)):
                seed(h,width,height)
                x,dx=(20,-5) if side=='left' else (619-height,5)
                h.ball(x=x,y=410,dx=dx,dy=7,speed=9,angle=90)
                pending={};trace=[];first_contact=None
                expected_contact_x=40 if side=='left' else 619-height-20
                for frame in range(8):
                    if frame%3==0:pending[frame+2]=policy(state(h),frame//3)
                    if frame in pending:h.setv('mouse_x',pending[frame])
                    row=advance(h,'game_frame');row.update(frame=frame,requested=h.n.extra[0x438B0C].value)
                    if first_contact is None and row['balls'][0]['dy']<0:
                        first_contact=dict(frame=frame,x=row['balls'][0]['x'])
                        assert first_contact==dict(frame=4,x=expected_contact_x)
                    trace.append(row)
                assert first_contact is not None
                outcome=dict(family='wall-policy-delivery',policy=label,width=width,height=height,side=side,
                             sample_interval_frames=3,input_delay_frames=2,first_contact=first_contact,trace=trace)
                cases.append(outcome);policy_results.append({k:v for k,v in outcome.items() if k!='trace'})
        assert len(cases) == 320 and sum(h.cases.values()) == 2560
        for outcome in policy_results:
            if outcome['policy'] == 'earliest-contact-candidate':
                if outcome['family'] == 'multi-ball-delivery': assert outcome['fast_ball_caught']
                if outcome['family'] == 'passed-ball-priority': assert outcome['viable_ball_caught']
        assert h.t.read(0x401000,0x1f000) == original_code
        assert originals == verified_originals()
        assert inputs == {name:digest(ROOT / name) for name in inputs}
        assert digest(library) == library_sha256
        report = dict(status='pass',target_sha256=h.t.target_sha256,library_sha256=library_sha256,
                      inputs=inputs,originals=originals,cases=len(cases),compared_frames=sum(h.cases.values()),
                      immutable_code_sha256=hashlib.sha256(original_code).hexdigest(),vectors=cases,policy_results=policy_results,
                      scope='Original/core controlled collision and ordinary-input counterfactual integration; no new direct owner or exact promotion.',
                      limitations=['Candidate is test-only; its complete campaign, bonuses and special movement remain unvalidated.',
                                   'Synthetic empty-board surface/dependency fixtures and known valid list/sprite metadata.',
                                   'Whole native/original state, list roots/cursors, ordered effects, pixels and free poisoning compared by reused Core Harness.',
                                   'No physical Windows input delivery, atomic SDK samples or full campaign acceptance.',
                                   'Known finite geometry; no active kind-3 movement or bonuses in these contact fixtures.',
                                   'Frame sampling/input delay values are declared controls, not measured live cadence.'])
        out=ROOT/'build/reports/campaign-contact.json';out.parent.mkdir(parents=True,exist_ok=True)
        out.write_text(json.dumps(report,indent=2)+'\n')
        print('Original/core contacts:',len(cases),'fixtures;',report['compared_frames'],'complete compared frames')


if __name__ == '__main__': main()
