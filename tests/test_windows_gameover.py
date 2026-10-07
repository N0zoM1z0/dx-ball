#!/usr/bin/env python3
"""Lose real balls through mouse input, then validate actual ranking persistence."""
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import digest, environment, launch, prepare, stop, verified_originals
from test_windows_runtime import command, game_window
from test_windows_play import (FLAGS, ORIGINAL, READER, Observer, capture_ready, click,
                               input_identities, reader_identity)

# Reused GAMEOVER_OWNER.md / test_gameover_differential.py state contracts.
FIELDS = dict(ORIGINAL, score_name_length=0x426698, selected_score_index=0x4266A0,
              show_high_scores=0x42693C, entering_score_name=0x426940,
              shift_pressed=0x438B00, scores=0x4266A8)


def score_file(runtime):
    matches = [p for p in runtime.iterdir() if p.name.casefold() == 'score.dat']
    if len(matches) != 1:
        raise AssertionError('Missing/ambiguous score file')
    return matches[0]


def expected_scores(before, score, name):
    """Independent file expectation: preserve tails after strcpy terminators."""
    assert len(before) == 660
    values = [struct.unpack_from('<I', before, index * 44 + 40)[0] for index in range(15)]
    assert score >= values[-1]
    rank = next((index for index, value in enumerate(values) if value <= score), 14)
    result = bytearray(before)
    for destination in range(14, rank, -1):
        source = before[(destination - 1) * 44:(destination - 1) * 44 + 40]
        source = source[:source.index(0) + 1]
        offset = destination * 44
        result[offset:offset + len(source)] = source
        struct.pack_into('<I', result, offset + 40, values[destination - 1])
    offset = rank * 44
    result[offset:offset + len(name) + 1] = name + b'\0'
    struct.pack_into('<I', result, offset + 40, score)
    return bytes(result), rank


def lose_game(observer, env):
    initial = observer.mode(1, 'game-ready')
    assert initial['lives'] == 3 and initial['balls']['attached'] == 1
    losses, releases, previous = [], 0, initial
    deadline = time.monotonic() + 90
    while time.monotonic() < deadline:
        state = observer.read('natural-life-loss')
        if state['lives'] < previous['lives']:
            losses.append({'before': previous['lives'], 'after': state['lives'],
                           'score': state['score'], 'mode': state['display_mode']})
        if state['display_mode'] == 3:
            break
        ball = state['balls']
        if state['display_mode'] == 1 and state['end_requested'] == 0:
            if ball is not None and ball['attached'] == 1:
                # Place each fresh attached ball under the first board, then release.
                command(['xdotool', 'mousemove', '200', '390', 'mousedown', '1'], env)
                observer.wait('natural-ball-release', lambda s: s['balls'] is not None
                              and s['balls']['attached'] == 0)
                command(['xdotool', 'mouseup', '1'], env)
                releases += 1
            elif ball is not None:
                # Ordinary player input deliberately misses the descending ball.
                target = 560 if ball['x'] < 320 else 80
                command(['xdotool', 'mousemove', str(target), '390'], env)
        previous = state
        time.sleep(0.05)
    else:
        raise AssertionError('Natural life-loss deadline exceeded')
    over = observer.mode(3, 'natural-game-over-ready')
    assert over['lives'] == 0 and over['ball_count'] == 0
    assert releases >= 3 and len(losses) >= 3
    assert all(row['before'] - row['after'] == 1 for row in losses)
    assert over['entering_score_name'] == 1 and over['score'] >= 10
    return over, losses, releases


def observe(profile, env, reports):
    runtime, originals = prepare(profile, probe=True)
    output = reports / profile
    output.mkdir(parents=True, exist_ok=True)
    observer = Observer(profile, env, output / 'states.json', FIELDS)
    before = score_file(runtime).read_bytes()
    captures = {}
    with (output / 'wine.log').open('w') as log:
        process = launch(runtime, env, log)
        try:
            deadline = time.monotonic() + 30
            window = None
            while window is None and time.monotonic() < deadline:
                if process.poll() is not None:
                    raise AssertionError(profile + ': exited before game window: ' + str(process.returncode))
                window = game_window(env)
                time.sleep(0.1)
            assert window is not None
            observer.mode(4, 'opening-ready')
            capture_ready(output, 'opening', env)
            command(['xdotool', 'windowfocus', window, 'key', 'space'], env)
            observer.mode(0, 'menu-ready')
            assert bytes.fromhex(observer.read('initial-score-table')['scores']) == before
            click(env, 320, 390)
            over, losses, releases = lose_game(observer, env)
            # Original high-score content uses only two visible colors on this
            # 8-bit Wine/Xvfb palette. Keep the artifact; verify state/file below.
            captures['name-entry'], _ = capture_ready(output, 'name-entry', env, 2)
            command(['xdotool', 'key', 'r', 'e', 'x'], env)
            observer.wait('name-three-letters', lambda s: s['score_name_length'] == 3)
            command(['xdotool', 'key', 'BackSpace'], env)
            observer.wait('name-backspace', lambda s: s['score_name_length'] == 2)
            command(['xdotool', 'key', 'shift+a'], env)
            observer.wait('name-shift-released', lambda s: s['score_name_length'] == 3
                          and s['shift_pressed'] == 0)
            expected, rank = expected_scores(before, over['score'], b'reA')
            command(['xdotool', 'key', 'Return'], env)
            observer.wait('score-inserted', lambda s: s['entering_score_name'] == 0
                          and s['show_high_scores'] == 1 and s['selected_score_index'] == rank)
            # A later queued mouse event establishes that the ranking fade returned.
            command(['xdotool', 'mousemove', '330', '390'], env)
            observer.wait('ranking-input-processed', lambda s: s['mouse_x'] == 330)
            assert bytes.fromhex(observer.read('inserted-score-table')['scores']) == expected
            captures['ranking'], _ = capture_ready(output, 'ranking', env, 2)
            deadline = time.monotonic() + 20
            while score_file(runtime).read_bytes() != expected:
                if time.monotonic() >= deadline:
                    raise AssertionError(profile + ': full 660-byte ranking differs')
                time.sleep(0.1)
            (output / 'score-before.dat').write_bytes(before)
            actual = score_file(runtime).read_bytes()
            assert actual == expected
            (output / 'score-after.dat').write_bytes(actual)
            click(env, 330, 390)
            observer.mode(0, 'ranking-return-menu-ready')
            command(['xdotool', 'key', 'Escape'], env)
            code = process.wait(timeout=20)
            assert code == 0 and game_window(env) is None
            # A fresh process must read the persisted record, not a surviving table.
            process = launch(runtime, env, log)
            deadline = time.monotonic() + 30
            while game_window(env) is None and time.monotonic() < deadline:
                if process.poll() is not None:
                    raise AssertionError('Restart exited before window')
                time.sleep(0.1)
            observer.mode(4, 'restart-opening-ready')
            capture_ready(output, 'restart-opening', env)
            command(['xdotool', 'windowfocus', game_window(env), 'key', 'space'], env)
            observer.mode(0, 'restart-menu-ready')
            assert score_file(runtime).read_bytes() == expected
            assert bytes.fromhex(observer.read('restarted-score-table')['scores']) == expected
            command(['xdotool', 'key', 'Escape'], env)
            code = process.wait(timeout=20)
            assert code == 0 and game_window(env) is None
        finally:
            stop(process)
            assert verified_originals() == originals
    return {'profile': profile, 'losses': losses, 'releases': releases,
            'score': over['score'], 'rank': rank, 'name': 'reA',
            'score_file_sha256': digest(score_file(runtime)), 'captures': captures,
            'state_reads': len(observer.records), 'exit_code': code,
            'executable_sha256': digest(runtime / 'dxball.exe'),
            'originals_unchanged': len(originals)}


def main():
    limit_cpu()
    if os.environ.get('DXBALL_GAMEOVER_DISPLAY') != '1':
        lock = session_lock()
        READER.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_state_reader.c'),
                        '-o', str(READER)], check=True, timeout=60)
        lock.close()
        env = os.environ.copy(); env['DXBALL_GAMEOVER_DISPLAY'] = '1'
        subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                        str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve())],
                       env=env, check=True, timeout=450)
        return
    lock = session_lock()
    reports = ROOT / 'build/reports/windows-gameover'
    reports.mkdir(parents=True, exist_ok=True)
    observations = []
    for profile in ('original', 'vc40', 'windows-i686'):
        row = observe(profile, environment(), reports)
        observations.append(row)
        print(profile + ': natural life loss, name entry and full ranking persistence passed', flush=True)
    inputs = input_identities()
    for name in ('tests/test_windows_play.py', 'tests/test_windows_gameover.py',
                 'tests/test_gameover_differential.py'):
        inputs[name] = digest(ROOT / name)
    for name, value in inputs.items():
        assert digest(ROOT / name) == value, name
    report = {'status': 'pass', 'kind': 'real-Wine-natural-life-loss-ranking-runs',
              'observations': observations, 'inputs': inputs, 'original_addresses': FIELDS,
              **reader_identity(),
              'vc40_map_sha256': digest(ROOT / 'build/vc40/dxball.map'),
              'mingw_dll_sha256': digest(ROOT / 'build/windows-i686/libdxball_core.dll'),
              'originals': verified_originals(),
              'limitations': ['Real input only; observer never writes/patches/hooks target state.',
                              'Original high-score scene has only two visible colors on this Wine/Xvfb palette; captures are not pixel-fidelity acceptance.',
                              'Random scores/trajectories differ; each full ranking has its own independent byte expectation.',
                              'Sequential state reads are not atomic snapshots.',
                              'Complete in-memory ranking and file checked after a fresh process restart.',
                              'No full-level, physical audio or asynchronous MIDI claim.']}
    (ROOT / 'build/reports/windows-gameover.json').write_text(json.dumps(report, indent=2) + '\n')
    print('Natural game-over/ranking runs passed; complete file bytes and live state retained.')


if __name__ == '__main__':
    main()
