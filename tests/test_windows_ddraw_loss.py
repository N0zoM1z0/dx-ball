#!/usr/bin/env python3
"""Observe lost-surface status on independent SDK surfaces, not on the game."""
import json
import os
from pathlib import Path
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import digest, environment, stop
from test_windows_runtime import command
from test_windows_play import FLAGS, READER, reader_identity
from test_windows_round import wait_window

PROBE = ROOT / 'build/probes/windows-directdraw-loss/ddraw-loss.exe'
LOST = '0x887601c2'
OK = '0x00000000'


def lines(path):
    return [json.loads(line) for line in path.read_text(errors='replace').splitlines()
            if line.startswith('{') and line.endswith('}')]


def wait_phase(path, phase, process):
    deadline = time.monotonic() + 20
    while True:
        rows = lines(path)
        matches = [row for row in rows if row['phase'] == phase]
        if matches:
            assert len(matches) == 1, 'Repeated phase: ' + phase
            return matches[0]
        if process.poll() is not None:
            raise AssertionError('SDK probe exited before ' + phase + ': ' + str(process.returncode))
        if time.monotonic() > deadline:
            raise AssertionError('SDK probe deadline: ' + phase)
        time.sleep(0.1)


def observe(renderer, reports):
    output = reports / renderer
    output.mkdir(parents=True, exist_ok=True)
    env = environment()
    env.pop('WINE_D3D_CONFIG', None)
    if renderer == 'gdi':
        env['WINE_D3D_CONFIG'] = 'renderer=gdi'
    transcript = output / 'sdk.log'
    with transcript.open('w') as log, (output / 'peer.log').open('w') as peer_log:
        probe = subprocess.Popen(['wine', str(PROBE)], cwd=PROBE.parent, env=env,
                                 stdout=log, stderr=log, start_new_session=True)
        peer = None
        try:
            window = wait_window(probe, env)
            initial = wait_phase(transcript, 'ready', probe)
            assert all(value == OK for key, value in initial.items() if key != 'phase')
            command(['xdotool', 'windowfocus', window], env)
            peer = subprocess.Popen(['wine', str(READER), 'peer'], env=env,
                                    stdout=peer_log, stderr=peer_log, start_new_session=True)
            peer_window = wait_window(peer, env, '^DX-Ball Focus Probe$')
            command(['xdotool', 'windowraise', peer_window, 'windowfocus', peer_window], env)
            wait_phase(transcript, 'inactive', probe)
            command(['xdotool', 'key', 'Return'], env)
            resumed = wait_phase(transcript, 'focus-return', probe)
            restore_calls = wait_phase(transcript, 'explicit-own-restore', probe)
            restored = wait_phase(transcript, 'after-own-restore', probe)
            assert resumed['primary_is_lost'] == LOST
            assert resumed['back_is_lost'] == resumed['back_lock'] == LOST
            assert resumed['board_is_lost'] == resumed['board_lock']
            assert resumed['board_is_lost'] in (OK, LOST)
            # A provider fix may report SURFACELOST here. Record the difference
            # rather than requiring this Wine version's missing status check.
            assert resumed['primary_blt_before'] in (OK, LOST)
            assert resumed['primary_blt_after'] in (OK, LOST)
            if restore_calls['primary'] == restore_calls['board'] == OK:
                assert all(value == OK for key, value in restored.items() if key != 'phase')
            probe_code = probe.wait(timeout=20)
            assert probe_code == 0
            command(['xdotool', 'windowfocus', peer_window, 'key', 'Escape'], env)
            peer_code = peer.wait(timeout=20)
            assert peer_code == 0
        finally:
            stop(probe)
            if peer is not None:
                stop(peer)
    rows = lines(transcript)
    (output / 'sdk.json').write_text(json.dumps(rows, indent=2) + '\n')
    return {'renderer': renderer, 'wine_d3d_config': env.get('WINE_D3D_CONFIG'),
            'before': initial, 'focus_return': resumed, 'after_own_restore': restored,
            'own_restore_calls': restore_calls,
            'blt_status_misses_lost_surface': resumed['primary_blt_after'] == OK,
            'exits': {'sdk': probe_code, 'peer': peer_code},
            'sdk_transcript_sha256': digest(transcript)}


def main():
    limit_cpu()
    if os.environ.get('DXBALL_DDRAW_LOSS_DISPLAY') != '1':
        lock = session_lock()
        PROBE.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_ddraw_loss_probe.c'),
                        '-lddraw', '-luser32', '-o', str(PROBE)], check=True, timeout=60)
        READER.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_state_reader.c'),
                        '-o', str(READER)], check=True, timeout=60)
        lock.close()
        env = dict(os.environ, DXBALL_DDRAW_LOSS_DISPLAY='1')
        subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                        str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve())],
                       env=env, check=True, timeout=120)
        return
    lock = session_lock()
    reports = ROOT / 'build/reports/windows-ddraw-loss'
    reports.mkdir(parents=True, exist_ok=True)
    (ROOT / 'build/reports/windows-ddraw-loss.json').unlink(missing_ok=True)
    (reports / 'failure.json').unlink(missing_ok=True)
    observations = []
    for renderer in ('default', 'gdi'):
        try:
            observations.append(observe(renderer, reports))
        except Exception as error:
            (reports / 'failure.json').write_text(json.dumps(
                {'status': 'failed', 'renderer': renderer, 'error': repr(error),
                 'completed_observations': observations}, indent=2) + '\n')
            raise
    libraries = {}
    for name in ('ddraw.dll', 'wined3d.dll'):
        path = Path(environment()['WINEPREFIX']) / 'drive_c/windows/system32' / name
        libraries[name] = {'path': str(path), 'sha256': digest(path)}
    inputs = {name: digest(ROOT / name) for name in
              ('tests/test_windows_ddraw_loss.py', 'tests/windows_ddraw_loss_probe.c',
               'tests/windows_state_reader.c', 'tests/test_windows_round.py',
               'tests/test_windows_play.py', 'tests/test_windows_runtime.py',
               'scripts/windows_runtime.py', 'scripts/legacy_toolchain.py', 'scripts/resource_limits.py')}
    report = {'status': 'pass', 'kind': 'independent-SDK-DirectDraw1-lost-status-observation',
              'observations': observations, 'inputs': inputs, 'libraries': libraries,
              'wine_version': subprocess.check_output(['wine', '--version'], text=True).strip(),
              'probe_sha256': digest(PROBE), 'reader': reader_identity(),
              'ddraw_header_sha256': digest('/usr/i686-w64-mingw32/include/ddraw.h'),
              'environment': {name: environment().get(name) for name in
                              ('WINEPREFIX', 'WINEARCH', 'WINEDEBUG', 'WINEDLLOVERRIDES', 'DISPLAY')},
              'limits': ['Independent SDK surfaces; no game executes in this scenario.',
                         'Explicit Restore calls act only on the probe-owned surfaces.',
                         'Original recovery control flow comes from retained REA Evidence.',
                         'Wine/Xvfb platform observation is not physical Windows verification.']}
    (ROOT / 'build/reports/windows-ddraw-loss.json').write_text(json.dumps(report, indent=2) + '\n')
    print('SDK loss observations retained:',
          [(row['renderer'], row['blt_status_misses_lost_surface']) for row in observations])


if __name__ == '__main__':
    main()
