#!/usr/bin/env python3
"""Check ordinary-input contact choices against the actual original rebound."""
import hashlib
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'scripts'), str(ROOT / 'tests')]
from campaign_controller import CONTACT_BIASES, DECISIONS_PER_CONTACT_BIAS, choose_greatest_y as choose_mouse
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from rotation_oracle import RotationTarget


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def main():
    if not __debug__:
        raise RuntimeError("Campaign aim comparisons require assertions; do not use -O.")
    limit_cpu()
    with session_lock():
        target = RotationTarget()
        code = target.read(0x401000, 0x1F000)
        target.write_u32(0x42309C, 0)
        target.call(0x402250)
        target.seed(0, 1, width=9, height=9)
        node = target.allocate(60)
        for address in (0x43A8B8, 0x43A8BC, 0x43A8C0):
            target.write_u32(address, node)
        target.write_u32(0x43A87C, 450)
        paths = ('tests/test_campaign_aim.py', 'scripts/campaign_controller.py',
                 'tests/rotation_oracle.py', 'tests/resources_oracle.py',
                 'tests/target_oracle.py', 'scripts/legacy_toolchain.py',
                 'scripts/verify-target.py', 'scripts/resource_limits.py',
                 'scripts/repo-python', 'scripts/verify-python.py',
                 'config/target.toml', 'config/tools.lock.toml')
        inputs = {name: digest(ROOT / name) for name in paths}
        rows = []
        for width in (43, 219):
            for x in (50, 320, 590):
                for dx in (-5, 0, 5):
                    for lookahead in (1, 2):
                        state = dict(paddle_width=width, paddle_x=320, bonuses=[],
                                     balls=[dict(x=x, y=430, dx=dx, dy=7,
                                                 width=9, height=9, attached=0)])
                        for phase in range(len(CONTACT_BIASES)):
                            mouse = choose_mouse(state, phase * DECISIONS_PER_CONTACT_BIAS, lookahead)
                            assert round(width / 2 + 21) <= mouse <= round(618 - width / 2)
                            collision_x = x + dx * lookahead
                            assert abs(mouse - (collision_x + 4.5)) <= width / 2 + 4.5 - 3
                            target.write_u32(0x43FA94, width)
                            target.write_u32(0x43A878, mouse)
                            target.write(node, struct.pack('<13i2I', collision_x, 440,
                                         x, 430, dx, 7, 1, 0, 9, 0, 0, 0, 0, 0, 0))
                            target.call(0x411410)
                            payload = struct.unpack('<13i', target.read(node, 52))
                            assert payload[5] < 0
                            assert not target.events and not target.io_events
                            rows.append(dict(width=width, x=x, incoming_dx=dx,
                                             lookahead=lookahead, phase=phase, mouse=mouse,
                                             angle=payload[7], dx=payload[4], dy=payload[5]))
        centered = [r for r in rows if r['width'] == 219 and r['x'] == 320
                    and r['incoming_dx'] == 5 and r['lookahead'] == 2]
        pairs = sorted({(r['dx'], r['dy']) for r in centered})
        assert pairs == [(-7, -6), (-5, -7), (-2, -8), (2, -8), (5, -7), (7, -6)]
        assert len(rows) == 216 and target.read(0x401000, 0x1F000) == code
        assert inputs == {name: digest(ROOT / name) for name in paths}
        report = dict(status='pass', target_sha256=target.target_sha256,
                      procedure='0x00411410', cases=len(rows), inputs=inputs,
                      immutable_code_sha256=hashlib.sha256(code).hexdigest(),
                      controlled_speed=9, centered_velocity_pairs=pairs, vectors=rows,
                      scope='Original rebound counterfactual for bounded contact positions; integration evidence, no direct owner-case or exact promotion.',
                      limitations=['No bonuses, physical input or live collision-prediction acceptance.',
                                   'Six phases are caller decision counts, not fixed game frames or seconds.',
                                   'Live SDK reads may mix frames; full-campaign completion requires a separate runtime control.'])
        output = ROOT / 'build/reports/campaign-aim.json'
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(report, indent=2) + '\n')
        print('Original rebound: 216 contact fixtures pass; six centered velocity pairs')


if __name__ == '__main__':
    main()
