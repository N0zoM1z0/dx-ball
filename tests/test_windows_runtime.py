#!/usr/bin/env python3
"""Observe real game startup/input/shutdown under Wine, with original controls."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import digest, environment, launch, prepare, stop, verified_originals


def command(args, env):
    return subprocess.check_output(args, env=env, stderr=subprocess.STDOUT, timeout=20)


def game_window(env):
    result = subprocess.run(['xdotool', 'search', '--onlyvisible', '--name', '^DX-Ball$'],
                            env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                            text=True, timeout=10)
    if result.returncode not in (0, 1):
        raise RuntimeError(result.stderr)
    windows = result.stdout.split()
    for window in windows:
        geometry = command(['xdotool', 'getwindowgeometry', '--shell', window], env).decode()
        if 'WIDTH=640\n' in geometry and 'HEIGHT=480\n' in geometry:
            return window
    return None


def screenshot(directory, scene, env, minimum_colors=4):
    path = directory / (scene + '.png')
    command(['import', '-window', 'root', str(path)], env)
    raw = command(['convert', str(path), '-depth', '8', 'rgb:-'], env)
    if len(raw) != 640 * 480 * 3:
        raise AssertionError('Unexpected display dimensions')
    # This detects blank captures; scene identification is reviewed separately.
    if len({raw[offset:offset + 3] for offset in range(0, len(raw), 3)}) < minimum_colors:
        raise AssertionError('Blank or degenerate game screenshot: ' + scene)
    return {'path': str(path.relative_to(ROOT)), 'sha256': digest(path)}, raw


def observe(profile, env, reports):
    directory, originals = prepare(profile, probe=True)
    output = reports / profile
    output.mkdir(parents=True, exist_ok=True)
    steps, captures, pixels = [], {}, {}
    with (output / 'wine.log').open('w') as log:
        process = launch(directory, env, log)
        try:
            deadline = time.monotonic() + 30
            window = None
            while window is None and time.monotonic() < deadline:
                if process.poll() is not None:
                    raise AssertionError(f'{profile}: exited before creating a game window')
                window = game_window(env)
                time.sleep(0.1)
            if window is None:
                raise AssertionError(profile + ': no 640x480 game window')
            deadline = time.monotonic() + 30
            while True:
                time.sleep(0.5)
                try:
                    captures['splash'], pixels['splash'] = screenshot(output, 'splash', env)
                    break
                except AssertionError:
                    if time.monotonic() >= deadline:
                        raise
            window = game_window(env)
            command(['xdotool', 'windowfocus', window], env)
            steps.append('visible 640x480 window and nonblank opening screen')
            command(['xdotool', 'key', 'space'], env)
            time.sleep(2)
            captures['menu'], pixels['menu'] = screenshot(output, 'menu', env)
            if pixels['menu'] == pixels['splash']:
                raise AssertionError(profile + ': opening key did not change the screen')
            steps.append('opening key changes screen')
            command(['xdotool', 'mousemove', '320', '390', 'mousedown', '1'], env)
            time.sleep(0.4)
            command(['xdotool', 'mouseup', '1'], env)
            time.sleep(2)
            captures['board'], pixels['board'] = screenshot(output, 'board', env)
            if pixels['board'] == pixels['menu']:
                raise AssertionError(profile + ': held click did not change the screen')
            steps.append('held click changes screen to reviewed first-board fixture')
            command(['xdotool', 'key', 'Escape'], env)
            time.sleep(2)
            captures['return-menu'], pixels['return-menu'] = screenshot(output, 'return-menu', env)
            steps.append('first Escape returns to reviewed menu fixture')
            command(['xdotool', 'key', 'Escape'], env)
            code = process.wait(timeout=15)
            if code != 0:
                raise AssertionError(f'{profile}: game exit {code}')
            if game_window(env) is not None:
                raise AssertionError(profile + ': visible game window survives exit')
            steps.append('second Escape exits with code zero; game window gone')
        finally:
            stop(process)
            if verified_originals() != originals:
                raise AssertionError('Original files changed')
    return {'profile': profile, 'exit_code': code, 'steps': steps,
            'originals_unchanged': len(originals), 'captures': captures,
            'executable_sha256': digest(directory / 'dxball.exe'),
            'dll_sha256': digest(directory / 'libdxball_core.dll')
            if profile == 'windows-i686' else None}, pixels


def difference(left, right, rectangle):
    x0, y0, x1, y1 = rectangle
    count = 0
    for y in range(y0, y1):
        for x in range(x0, x1):
            offset = (y * 640 + x) * 3
            count += left[offset:offset + 3] != right[offset:offset + 3]
    return {'rectangle': rectangle, 'pixels': (x1 - x0) * (y1 - y0),
            'different_pixels': count}


def main():
    limit_cpu()
    if os.environ.get('DXBALL_RUNTIME_DISPLAY') != '1':
        for tool in ('xvfb-run', 'wine', 'xdotool', 'import', 'convert'):
            if shutil.which(tool) is None:
                raise RuntimeError('Required runtime probe tool missing: ' + tool)
        env = os.environ.copy()
        env['DXBALL_RUNTIME_DISPLAY'] = '1'
        # xvfb-run handles an occupied display and auth; automatic -displayfd fails here.
        subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                        str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve())],
                       env=env, check=True, timeout=180)
        return
    lock = session_lock()
    env = environment()
    reports = ROOT / 'build/reports/windows-runtime'
    reports.mkdir(parents=True, exist_ok=True)
    observations, pixels = [], {}
    for profile in ('original', 'vc40', 'windows-i686'):
        observation, pixels[profile] = observe(profile, env, reports)
        observations.append(observation)
        print(profile + ': real window/input/zero-exit checks passed', flush=True)
    comparisons = {}
    for profile in ('vc40', 'windows-i686'):
        comparisons[profile] = {
            scene: difference(pixels['original'][scene], pixels[profile][scene], [0, 0, 640, 480])
            for scene in ('splash', 'menu', 'board', 'return-menu')}
        comparisons[profile]['first-board-tiles'] = difference(
            pixels['original']['board'], pixels[profile]['board'], [20, 110, 620, 275])
    sources = [str(path.relative_to(ROOT)) for path in sorted((ROOT / 'src').glob('*.[ch]'))]
    sources += ['CMakeLists.txt', 'config/assets.csv', 'config/tools.lock.toml',
                'config/mingw-i686.cmake', 'scripts/build-legacy.py',
                'scripts/build-windows.py',
                'scripts/windows_resources.py', 'config/windows-resources.json',
                'scripts/windows_runtime.py', 'scripts/legacy_toolchain.py',
                'scripts/resource_limits.py', 'tests/test_windows_runtime.py']
    report = {'status': 'pass', 'kind': 'real-Wine-window-input-shutdown-probe',
              'display': 'Xvfb 640x480x8', 'observations': observations,
              'pixel_comparisons': comparisons,
              'inputs': {name: digest(ROOT / name) for name in sources},
              'originals': verified_originals(),
              'limitations': ['Unsynchronized frames; pixel differences are reported, not masked or exact claims.',
                              '8-bit Wine/Xvfb palette artifacts also affect the original control.',
                              'No physical audio or asynchronous MIDI delivery claim.',
                              'No complete-game, editor, focus-recovery or all-board acceptance.']}
    (ROOT / 'build/reports/windows-runtime.json').write_text(json.dumps(report, indent=2) + '\n')
    print('Windows runtime probe passed; screenshot differences retained without an exact claim.')


if __name__ == '__main__':
    main()
