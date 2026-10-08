#!/usr/bin/env python3
"""Bounded original-board episodes through all twelve original x86 frame phases.

Actual asset geometry, controlled dependency boundaries, and a reusable node
arena extend the display oracle beyond its small fixed fixtures. This remains
separate from full Windows campaign acceptance and direct owner case counts.
"""
import argparse
from collections import defaultdict
import ctypes as C
import json
from pathlib import Path
import struct
import sys
import time

from target_oracle import ROOT
from resources_oracle import BANKS, ResourceTarget
from test_display_differential import DisplayHarness, DisplayNative, DisplayTarget
from test_entities_differential import SHAPES
from test_gameplay_differential import REMAINING, SCORE
from test_core_differential import GLOBALS
from campaign_controller import choose_mouse
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import digest, verified_originals


class Arena:
    """Controlled malloc boundary; reuse only after compared free poisoning."""
    size = 0x200000

    def start_arena(self):
        self.available = defaultdict(list)
        self.offset = 0

    def take(self, size):
        if self.available[size]:
            address = self.available[size].pop()
        else:
            address = self.arena + self.offset
            self.offset += (size + 15) & ~15
            assert self.offset <= self.size, 'Controlled node arena exhausted'
        self.allocations[address] = dict(size=size, live=True, owner=None)
        return address

    def recycle(self):
        for address, row in self.allocations.items():
            if not row['live'] and not row.get('recycled'):
                self.available[row['size']].append(address)
                row['recycled'] = True


class Native(Arena, DisplayNative):
    def __init__(self, library):
        super().__init__(library)
        self.storage = C.create_string_buffer(self.size)
        self.arena = C.addressof(self.storage)
        self.start_arena()

    def allocate(self, size):
        assert size in {C.sizeof(shape[1]) for shape in SHAPES.values()}
        address = self.take(size)
        C.memset(address, 0xa5, size)
        self.events.append(('allocate', self.observed()))
        return address


class Target(Arena, DisplayTarget):
    def __init__(self):
        super().__init__()
        self.arena = 0x2000000
        self.uc.mem_map(self.arena, self.size)
        self.start_arena()

    def allocate(self, *unused):
        size = self._args(1)[0]
        assert size in {shape[2] + 8 for shape in SHAPES.values()}
        self.events.append(('allocate', self.observed()))
        address = self.take(size)
        self.write(address, b'\xa5' * size)
        self._return(address)


def seed_geometry(harness):
    # Execute the reviewed original loader; no hand-guessed sprite sizes.
    for bank, filename, mode in ((0, 'MBALL2.SBK', 1), (1, 'THEFONT.SBK', 0)):
        reader = ResourceTarget()
        reader.set_file(filename.lower(), (ROOT / 'original' / filename).read_bytes())
        reader.call(0x404610, bank, mode, reader.PATH)
        count, mode, name, records = reader.bank_snapshot(bank)
        harness.n.banks[bank].count = count
        harness.n.banks[bank].mode = mode
        harness.t.write_u32(BANKS + bank * 1048 + 1020, count)
        harness.t.write_u32(BANKS + bank * 1048 + 1024, mode)
        for slot, record in enumerate(records):
            if record is None:
                continue
            fields, code, baseline, pixels = record
            width, height, pitch, *rect = fields
            harness.sprite(slot, width, height, bank)
            sprite = harness.n.runtime_sprites[bank][slot]
            sprite.pitch = pitch
            sprite.rect.left, sprite.rect.top, sprite.rect.right, sprite.rect.bottom = rect
            harness.t.write(0x880000 + (bank * 255 + slot) * 48 + 16,
                            struct.pack('<5i', pitch, *rect))


def observed(harness):
    native = harness.n
    state = {name: native.extra[address].value for address, name in GLOBALS.items()}
    state.update(board_index=native.index.value, remaining_bricks=native.state[REMAINING].value,
                 score=native.state[SCORE].value)
    for owner in ('balls', 'bonuses'):
        nodes = []
        pointer = native.owners[owner].first
        while pointer:
            node = pointer.contents
            sprite = native.runtime_sprites[0][node.sprite]
            values = {field: getattr(node, field) for field in ('x', 'y', 'dx', 'dy')}
            values.update(width=sprite.width, height=sprite.height)
            values.update(attached=node.attached) if owner == 'balls' else values.update(kind=node.kind)
            nodes.append(values)
            pointer = node.next
        state[owner] = nodes
    return state


def main():
    if not __debug__:
        raise RuntimeError("Campaign comparisons require assertions; do not use -O.")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--frames', type=int, default=40000)
    parser.add_argument('--boards', type=int, choices=range(1, 50), default=5,
                        help='Stop at this board index, before the host-pointer terminal ABI boundary')
    args = parser.parse_args()
    if not 1 <= args.frames <= 500000:
        parser.error('Frame budget must be 1..500000')
    limit_cpu()
    with session_lock():
        originals = verified_originals()
        library = ROOT / 'build/native/libdxball_core.so'
        harness = DisplayHarness(library.resolve(), Native, Target)
        seed_geometry(harness)
        inputs = {str(path.relative_to(ROOT)): digest(path) for path in sorted((ROOT / 'src').glob('*.[ch]'))}
        for module in tuple(sys.modules.values()):
            filename = getattr(module, '__file__', None)
            if filename:
                path = Path(filename).resolve()
                if path.is_relative_to(ROOT) and path.suffix == '.py':
                    inputs[str(path.relative_to(ROOT))] = digest(path)
        inputs.update({name: digest(ROOT / name) for name in
                       ('config/target.toml', 'config/assets.csv', 'requirements-analysis.txt',
                        'scripts/repo-python')})
        report = dict(status='running', frames=0, target_sha256=harness.t.target_sha256,
                      library_sha256=digest(library), inputs=inputs, originals=originals,
                      frame_budget=args.frames, goal_board_index=args.boards, transitions=[],
                      limitations=[
                          'Original x86 and native host C have controlled COM/audio/resource/glyph/non-game boundaries.',
                          'Actual asset dimensions/pitches/rectangles; synthetic surface identities and pixel fixtures.',
                          'Arena reuse occurs after complete state/event/pixel/free-poison comparison; malloc is controlled.',
                          'Direct fixture mouse requests; no Windows message-loop/input or hardware fidelity claim.',
                          'This bounded episode does not validate all 50 original boards or native terminal raw-pointer ABI.',
                          'Connected integration frames are separate from direct owner case counts.'])
        destination = ROOT / 'build/reports/campaign-differential.json'
        began = time.monotonic()
        previous = 0
        try:
            harness.phase('initialize_game', 0x40F4C0)
            for frame in range(args.frames):
                state = observed(harness)
                harness.setv('mouse_x', choose_mouse(state, frame, lookahead=1))
                harness.setv('mouse_action', 1)
                harness.phase('game_frame', 0x40F8B0)
                report['frames'] = frame + 1
                harness.n.recycle()
                harness.t.recycle()
                state = observed(harness)
                report['last_state'] = state
                index = state['board_index']
                if index != previous:
                    report['transitions'].append(dict(frame=frame, board_index=index, score=state['score'],
                                                     lives=state['lives'], remaining_bricks=state['remaining_bricks']))
                    previous = index
                    print('Original-x86 episode: board ' + str(index) + ' at frame ' + str(frame), flush=True)
                if index >= args.boards:
                    report['status'] = 'bounded-progression'
                    break
                if state['end_requested']:
                    report['status'] = 'bounded-game-over'
                    break
                if frame % 2000 == 0:
                    print('Compared frame ' + str(frame) + ', board ' + str(index), flush=True)
            else:
                report['status'] = 'bounded-frame-budget'
            assert verified_originals() == originals
        except Exception as error:
            report.update(status='fail', error=repr(error))
            raise
        finally:
            report['seconds'] = round(time.monotonic() - began, 3)
            destination.write_text(json.dumps(report, indent=2) + '\n')
        print('Original-x86 campaign episode: ' + report['status'] + ', ' + str(report['frames']) + ' compared frames')


if __name__ == '__main__':
    main()
