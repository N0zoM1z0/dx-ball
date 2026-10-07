#!/usr/bin/env python3
"""Real board completion; optional focus-recovery diagnostic without target writes."""
import json
import argparse
import os
from pathlib import Path
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import digest, environment, launch, prepare, stop, verified_originals
from test_windows_runtime import command, game_window
from test_windows_play import (FLAGS, ORIGINAL, READER, Observer, board_file, capture_ready,
                               click, input_identities, reader_identity)

# Retained gameplay/runtime/power-up/board REA state contracts; no new addresses guessed.
FIELDS = dict(ORIGINAL, remaining_bricks=0x43A8F4, restart_requested=0x43A90C,
              level_changed=0x422D1C, surface_restore_requested=0x4228AC,
              cursor_warp_disabled=0x422898, last_brick_deadline=0x43FAEC)
CELL = 18 * 20 + 6


def wait_window(process, env, title='^DX-Ball$'):
    deadline = time.monotonic() + 30
    while time.monotonic() < deadline:
        if process.poll() is not None:
            raise AssertionError('Exited before window: ' + title + ' code ' + str(process.returncode))
        if title == '^DX-Ball$':
            window = game_window(env)
        else:
            result = subprocess.run(['xdotool', 'search', '--onlyvisible', '--name', title],
                                    env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                    text=True, timeout=10)
            assert result.returncode in (0, 1)
            windows = result.stdout.split()
            window = windows[0] if windows else None
        if window is not None:
            return window
        time.sleep(0.1)
    raise AssertionError('Window deadline: ' + title)


def attached(observer, phase):
    return observer.wait(phase, lambda s: s['display_mode'] == 1 and s['end_requested'] == 0
                         and s['restart_requested'] == 0 and s['device_reset_requested'] == 0
                         and s['balls'] is not None and s['balls']['attached'] == 1)


def release(observer, env, x, phase):
    command(['xdotool', 'mousemove', str(x), '390'], env)
    observer.wait(phase + '-paddle', lambda s: s['paddle_x'] == x)
    command(['xdotool', 'mousedown', '1'], env)
    state = observer.wait(phase, lambda s: s['balls'] is not None and s['balls']['attached'] == 0)
    command(['xdotool', 'mouseup', '1'], env)
    return state


def focus_cycle(observer, env, output):
    peer = None
    with (output / 'peer.log').open('w') as log:
        try:
            peer = subprocess.Popen(['wine', str(READER), 'peer'], env=env,
                                    stdout=log, stderr=log, start_new_session=True)
            target = wait_window(peer, env, '^DX-Ball Focus Probe$')
            command(['xdotool', 'windowraise', target, 'windowfocus', target], env)
            inactive = observer.wait('focus-inactive', lambda s: s['application_active'] == 0
                                    and s['surface_restore_requested'] == 1)
            assert inactive['paused'] == 0 and inactive['balls'] is not None
            assert inactive['balls']['attached'] == 0
            time.sleep(0.5)
            frozen = observer.read('focus-inactive-stability')
            assert frozen['application_active'] == 0 and frozen['balls'] == inactive['balls']
            assert frozen['score'] == inactive['score'] and frozen['lives'] == inactive['lives']
            # The foreground peer restores/activates the game through ordinary
            # SDK APIs. X input focus alone need not restore an iconified game.
            command(['xdotool', 'key', 'Return'], env)
            active = observer.wait('focus-resumed', lambda s: s['application_active'] == 1
                                  and s['surface_restore_requested'] == 0 and s['balls'] is not None
                                  and s['balls'] != frozen['balls'])
            time.sleep(0.5)
            sustained = observer.read('focus-sustained-motion')
            assert sustained['application_active'] == 1 and sustained['balls'] != active['balls']
            capture_ready(output, 'focus-return', env)
            return {'inactive_restore_request': inactive['surface_restore_requested'],
                    'active_restore_request': active['surface_restore_requested'],
                    'frozen_seconds': 0.5,
                    'cursor_warp_disabled': active['cursor_warp_disabled']}, peer, target
        except Exception:
            if peer is not None:
                stop(peer)
            raise


def observe(profile, env, reports, focus_recovery=False):
    runtime, originals = prepare(profile, probe=True)
    output = reports / profile
    output.mkdir(parents=True, exist_ok=True)
    observer = Observer(profile, env, output / 'states.json', FIELDS, {'board_tiles': ':board'})
    bank_input = (runtime / 'DEFAULT.BDS').read_bytes()
    edited = bytearray(400); edited[CELL] = 1
    bank_expected = bytes(edited) + bank_input[400:]
    focus = {'status': 'not-requested'}
    with (output / 'wine.log').open('w') as log:
        process = launch(runtime, env, log)
        peer = None
        try:
            window = wait_window(process, env)
            observer.mode(4, 'opening-ready')
            capture_ready(output, 'opening', env)
            command(['xdotool', 'windowfocus', window, 'key', 'space'], env)
            observer.mode(0, 'menu-ready')
            command(['xdotool', 'key', 'ctrl+F1'], env)
            observer.mode(2, 'editor-ready')
            observer.wait('editor-control-released', lambda s: s['control_pressed'] == 0)
            command(['xdotool', 'key', 'BackSpace'], env)
            observer.wait('editor-completely-empty', lambda s: bytes.fromhex(s['board_tiles']) == bytes(400))
            click(env, 37, 392)
            observer.wait('editor-tile1-selected', lambda s: s['editor_selected_tile'] == 1)
            click(env, 215, 327)
            observer.wait('editor-single-brick', lambda s: bytes.fromhex(s['board_tiles']) == bytes(edited))
            command(['xdotool', 'key', 's'], env)
            deadline = time.monotonic() + 20
            while board_file(runtime).read_bytes() != bank_expected:
                if time.monotonic() >= deadline:
                    raise AssertionError('Full editor-created single-brick bank differs')
                time.sleep(0.1)
            (output / 'edited-bank.bds').write_bytes(board_file(runtime).read_bytes())
            capture_ready(output, 'single-brick-editor', env)
            command(['xdotool', 'key', 'Escape'], env)
            observer.mode(0, 'editor-return-menu')
            click(env, 320, 390)
            initial = attached(observer, 'single-brick-game-attached')
            assert initial['board_index'] == 0 and initial['remaining_bricks'] == 1
            assert bytes.fromhex(initial['board_tiles']) == bytes(edited)
            assert initial['lives'] == 3 and initial['score'] == 0
            release(observer, env, 185, 'single-brick-release')
            observer.wait('single-brick-hit', lambda s: s['score'] > 0 and s['remaining_bricks'] == 0)
            advanced = observer.wait('next-original-board-ready', lambda s: s['display_mode'] == 1
                                     and s['board_index'] == 1 and s['restart_requested'] == 0
                                     and s['level_changed'] == 0 and s['end_requested'] == 0
                                     and s['balls'] is not None and s['balls']['attached'] == 1)
            next_board = bank_input[400:800]
            assert bytes.fromhex(advanced['board_tiles']) == next_board
            assert advanced['remaining_bricks'] == sum(tile not in (0, 2) for tile in next_board)
            assert advanced['lives'] == 3 and advanced['score'] > 0
            (output / 'loaded-board.bin').write_bytes(bytes.fromhex(advanced['board_tiles']))
            capture_ready(output, 'next-original-board', env)
            prefix = {'status': 'pass', 'kind': 'editor-created-brick-clear-original-board1-loaded',
                      'scope': 'transition prefix only; shutdown/focus not yet checked',
                      'profile': profile, 'score': advanced['score'], 'lives': advanced['lives'],
                      'board_index': advanced['board_index'], 'remaining_bricks': advanced['remaining_bricks'],
                      'edited_bank_sha256': digest(output / 'edited-bank.bds'),
                      'loaded_board_sha256': digest(output / 'loaded-board.bin'),
                      'inputs': {**input_identities(), 'tests/test_windows_round.py': digest(Path(__file__))},
                      'reader': reader_identity()}
            (output / 'round-prefix.json').write_text(json.dumps(prefix, indent=2) + '\n')
            if focus_recovery:
                release(observer, env, 200, 'next-board-release-before-focus')
                focus, peer, peer_window = focus_cycle(observer, env, output)
            command(['xdotool', 'key', 'Escape'], env)
            observer.mode(0, 'round-return-menu')
            command(['xdotool', 'key', 'Escape'], env)
            code = process.wait(timeout=20)
            assert code == 0 and game_window(env) is None
            assert board_file(runtime).read_bytes() == bank_expected
            if peer is not None:
                command(['xdotool', 'windowfocus', peer_window, 'key', 'Escape'], env)
                focus['peer_exit_code'] = peer.wait(timeout=20)
                assert focus['peer_exit_code'] == 0
        except Exception:
            command(['import', '-window', 'root', str(output / 'failure.png')], env)
            (output / 'failure-windows.txt').write_bytes(command(['xwininfo', '-root', '-tree'], env))
            raise
        finally:
            stop(process)
            if peer is not None:
                stop(peer)
            assert verified_originals() == originals
    return {'profile': profile, 'focus': focus, 'exit_code': code,
            'score_after_clear': advanced['score'], 'lives_after_clear': advanced['lives'],
            'next_board_index': advanced['board_index'], 'next_remaining_bricks': advanced['remaining_bricks'],
            'edited_bank_sha256': digest(output / 'edited-bank.bds'),
            'loaded_board_sha256': digest(output / 'loaded-board.bin'),
            'executable_sha256': digest(runtime / 'dxball.exe'),
            'state_reads': len(observer.records), 'originals_unchanged': len(originals)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--profile', choices=('original', 'vc40', 'windows-i686'))
    parser.add_argument('--focus-recovery', action='store_true',
                        help='also diagnose focus recovery; original Wine control currently stalls')
    args = parser.parse_args()
    limit_cpu()
    if os.environ.get('DXBALL_ROUND_DISPLAY') != '1':
        lock = session_lock()
        READER.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_state_reader.c'),
                        '-o', str(READER)], check=True, timeout=60)
        lock.close()
        env = os.environ.copy(); env['DXBALL_ROUND_DISPLAY'] = '1'
        subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                        str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve()), *sys.argv[1:]],
                       env=env, check=True, timeout=360)
        return
    lock = session_lock()
    report_name = 'windows-focus' if args.focus_recovery else 'windows-round'
    reports = ROOT / 'build/reports' / report_name
    reports.mkdir(parents=True, exist_ok=True)
    (ROOT / 'build/reports' / (report_name + '.json')).unlink(missing_ok=True)
    (reports / 'failure.json').unlink(missing_ok=True)
    observations = []
    for profile in ((args.profile,) if args.profile else ('original', 'vc40', 'windows-i686')):
        try:
            row = observe(profile, environment(), reports, args.focus_recovery)
        except Exception as error:
            failure = {'status': 'failed', 'profile': profile,
                       'focus_recovery_requested': args.focus_recovery,
                       'error': repr(error), 'completed_observations': observations,
                       'inputs': {**input_identities(), 'tests/test_windows_round.py': digest(Path(__file__))},
                       'reader': reader_identity(), 'originals': verified_originals(),
                       'limitations': ['A failed diagnostic is not accepted focus-recovery evidence.']}
            (reports / 'failure.json').write_text(json.dumps(failure, indent=2) + '\n')
            raise
        observations.append(row)
        print(profile + ': editor-created board clear/advance and zero-code exit passed', flush=True)
    inputs = input_identities()
    for name in ('tests/test_windows_round.py', 'tests/test_gameplay_differential.py',
                 'tests/test_powerups_differential.py'):
        inputs[name] = digest(ROOT / name)
    report = {'status': 'pass', 'kind': 'real-Wine-single-brick-clear-next-board-runs',
              'focus_recovery_requested': args.focus_recovery,
              'observations': observations, 'inputs': inputs, 'original_addresses': FIELDS,
              'reader_shapes': {'board_tiles': ':board'}, **reader_identity(),
              'vc40_map_sha256': digest(ROOT / 'build/vc40/dxball.map'),
              'mingw_dll_sha256': digest(ROOT / 'build/windows-i686/libdxball_core.dll'),
              'originals': verified_originals(),
              'limitations': ['No target writes/hooks/injected calls; board edits use the real editor.',
                              'Editor-created single-brick board tests a real transition to original board1, not completion of all original levels.',
                              'Focus flags/request clearance and resumed movement do not by themselves prove an actual SURFACELOST/Restore call.',
                              'Sequential reads and Wine/Xvfb captures do not establish atomic-frame/pixel fidelity.',
                              'Physical audio, asynchronous MIDI and terminal board50 remain unverified.']}
    (ROOT / 'build/reports' / (report_name + '.json')).write_text(json.dumps(report, indent=2) + '\n')
    print('Round-transition controls passed; full banks/loaded board and live states retained.')


if __name__ == '__main__':
    main()
