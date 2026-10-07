#!/usr/bin/env python3
"""Real Wine gameplay/editor checks, observing state without modifying the target."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time
import struct
import pefile
from source_state import STORAGE_FIELDS

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock, windows_path
from resource_limits import limit_cpu
from windows_runtime import digest, environment, launch, prepare, stop, verified_originals
from test_windows_runtime import command, game_window, screenshot

# Retained original state contracts, already used by the named differential suites.
# MODE/INDEX: target_oracle.py; input: platform/core; ball layout: powerups/balls.h.
ORIGINAL = {'display_mode': 0x421074, 'board_index': 0x43A8F8,
    'application_active': 0x438B08, 'control_pressed': 0x438B04,
    'end_requested': 0x425974, 'return_to_menu': 0x425978,
    'device_reset_requested': 0x4228A8, 'mouse_action': 0x438B10,
    'mouse_x': 0x438B0C, 'mouse_y': 0x438B14, 'paddle_x': 0x43A878,
    'paused': 0x43FAE4, 'ball_count': 0x43F8F0, 'balls': 0x43A8B8,
    'score': 0x422D18, 'lives': 0x43A888, 'editor_selected_tile': 0x438AF0,
    'board_tiles': 0x43F8F8}
FLAGS = ['-std=c90', '-O3', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
READER = ROOT / 'build/probes/windows-runtime/state-reader.exe'


def shape(name):
    return ':ball' if name == 'balls' else ':scores' if name == 'scores' else ''


class Observer:
    def __init__(self, profile, env, output, fields=None, shapes=None):
        self.env, self.records, self.output = env, [], output
        fields = ORIGINAL if fields is None else fields
        shapes = {} if shapes is None else shapes
        prefix = ['wine', str(READER)]
        if profile == 'windows-i686':
            self.arguments = prefix + ['dll', windows_path(ROOT / 'build/windows-i686/libdxball_core.dll')]
            self.arguments += ['dxball_' + name + shapes.get(name, shape(name)) for name in fields]
        else:
            addresses = fields
            if profile == 'vc40':
                metadata = json.loads((ROOT / 'build/vc40/build.json').read_text())
                link_map = ROOT / 'build/vc40/dxball.map'
                assert metadata['game_map_sha256'] == digest(link_map)
                text = link_map.read_text()
                addresses = {}
                executable = ROOT / 'build/vc40/dxball.exe'
                assert metadata['executables']['dxball'] == digest(executable)
                image = pefile.PE(str(executable))
                def mapped(name):
                    values = re.findall(r'\s_' + name + r'\s+([0-9a-fA-F]{8})\s', text)
                    if len(values) != 1:
                        raise AssertionError('Missing/ambiguous VC4 map symbol: ' + name)
                    return int(values[0], 16)
                storage = mapped('dxball_board_storage')
                layout = struct.unpack('<6I', image.get_data(
                    mapped('dxball_board_storage_offsets') - image.OPTIONAL_HEADER.ImageBase, 24))
                assert layout[0] == 0
                for name in fields:
                    symbol = 'dxball_' + name
                    if symbol in STORAGE_FIELDS:
                        offset = layout[STORAGE_FIELDS[symbol]]
                        assert offset < layout[5]
                        addresses[name] = storage + offset
                    else:
                        addresses[name] = mapped(symbol)
            self.arguments = prefix + ['addresses']
            self.arguments += [name + shapes.get(name, shape(name)) + '=' + hex(address)
                               for name, address in addresses.items()]

    def read(self, phase):
        data = json.loads(command(self.arguments, self.env))
        values = {name.removeprefix('dxball_'): value for name, value in data['values'].items()}
        self.records.append({'phase': phase, 'monotonic': time.monotonic(),
                             'windows_pid': data['pid'], 'values': values})
        self.output.write_text(json.dumps(self.records, indent=2) + '\n')
        return values

    def wait(self, phase, predicate, seconds=20):
        deadline = time.monotonic() + seconds
        while True:
            values = self.read(phase)
            if predicate(values):
                return values
            if time.monotonic() >= deadline:
                raise AssertionError('Live state timeout: ' + phase + ' ' + str(values))
            time.sleep(0.1)

    def mode(self, number, phase):
        return self.wait(phase, lambda state: state['display_mode'] == number
                         and state['end_requested'] == 0 and state['device_reset_requested'] == 0)


def click(env, x, y):
    command(['xdotool', 'mousemove', str(x), str(y), 'mousedown', '1'], env)
    time.sleep(0.25)
    command(['xdotool', 'mouseup', '1'], env)


def capture_ready(output, scene, env, minimum_colors=4):
    deadline = time.monotonic() + 20
    while True:
        try:
            return screenshot(output, scene, env, minimum_colors)
        except AssertionError:
            if time.monotonic() >= deadline:
                raise
            time.sleep(0.1)


def board_file(runtime):
    matches = [path for path in runtime.iterdir() if path.name.casefold() == 'default.bds']
    if len(matches) > 1:
        raise AssertionError('Ambiguous board filename aliases')
    return matches[0] if matches else None


def observe(profile, env, reports):
    runtime, originals = prepare(profile, probe=True)
    output = reports / profile
    output.mkdir(parents=True, exist_ok=True)
    observer = Observer(profile, env, output / 'states.json')
    steps, captures = [], {}
    board_input = (runtime / 'DEFAULT.BDS').read_bytes()
    expected = bytes([2, 2]) + bytes(398) + board_input[400:]
    with (output / 'wine.log').open('w') as log:
        process = launch(runtime, env, log)
        try:
            deadline = time.monotonic() + 30
            window = None
            while window is None and time.monotonic() < deadline:
                if process.poll() is not None:
                    raise AssertionError(profile + ': exited before its game window')
                window = game_window(env)
                time.sleep(0.1)
            if window is None:
                raise AssertionError(profile + ': no game window')
            observer.mode(4, 'opening-ready')
            captures['opening'], _ = capture_ready(output, 'opening', env)
            command(['xdotool', 'windowfocus', window, 'key', 'space'], env)
            observer.mode(0, 'menu-ready')
            click(env, 320, 390)
            state = observer.mode(1, 'game-ready')
            assert state['ball_count'] > 0 and state['balls']['attached'] == 1
            steps.append('real mode1 initializes an attached ball')
            command(['xdotool', 'mousemove', '480', '390'], env)
            observer.wait('paddle-right', lambda state: state['paddle_x'] == 480)
            command(['xdotool', 'mousemove', '200', '390'], env)
            observer.wait('paddle-left', lambda state: state['paddle_x'] == 200)
            steps.append('actual mouse input moves paddle to x480 then x200')
            command(['xdotool', 'mousedown', '1'], env)
            released = observer.wait('ball-release', lambda state: state['balls'] is not None
                                     and state['balls']['attached'] == 0)
            command(['xdotool', 'mouseup', '1'], env)
            observer.wait('ball-motion', lambda state: state['balls'] is not None
                          and (state['balls']['x'], state['balls']['y']) !=
                          (released['balls']['x'], released['balls']['y']))
            steps.append('real click releases attached ball and its coordinates change')
            command(['xdotool', 'key', 'p'], env)
            observer.wait('pause', lambda state: state['paused'] == 1)
            # Observe a later queued mouse event before measuring frozen frames;
            # merely seeing paused=1 can still mean the key handler is fading.
            command(['xdotool', 'mousemove', '300', '390'], env)
            paused = observer.wait('pause-input-processed', lambda state: state['paused'] == 1
                                   and state['mouse_x'] == 300)
            time.sleep(0.5)
            frozen = observer.read('pause-stability')
            assert frozen['paused'] == 1 and frozen['balls'] == paused['balls']
            captures['pause'], _ = capture_ready(output, 'pause', env)
            command(['xdotool', 'key', 'space'], env)
            observer.wait('resume-motion', lambda state: state['paused'] == 0 and state['balls'] is not None
                          and state['balls'] != frozen['balls'])
            steps.append('P pauses ball fields for 0.5s; another key resumes motion')
            command(['xdotool', 'key', 'Escape'], env)
            observer.mode(0, 'game-return-menu-ready')
            command(['xdotool', 'key', 'ctrl+F1'], env)
            observer.mode(2, 'editor-ready')
            observer.wait('editor-modifiers-released', lambda state: state['control_pressed'] == 0)
            captures['editor'], _ = capture_ready(output, 'editor', env)
            command(['xdotool', 'key', 'BackSpace'], env)
            observer.wait('editor-cleared', lambda state: state['board_tiles'] == 0)
            click(env, 67, 392)
            observer.wait('editor-tile2-selected', lambda state: state['editor_selected_tile'] == 2)
            command(['xdotool', 'keydown', 'ctrl', 'mousemove', '35', '57', 'mousedown', '1'], env)
            observer.wait('editor-control-held', lambda state: state['control_pressed'] == 1)
            time.sleep(0.25)
            command(['xdotool', 'mousemove', '65', '57'], env)
            observer.wait('editor-second-cell', lambda state: state['mouse_x'] == 65)
            time.sleep(0.25)
            command(['xdotool', 'mouseup', '1', 'keyup', 'ctrl'], env)
            observer.wait('editor-release', lambda state: state['control_pressed'] == 0 and state['mouse_action'] == 0)
            command(['xdotool', 'key', 's'], env)
            deadline = time.monotonic() + 20
            while board_file(runtime).read_bytes() != expected:
                if time.monotonic() >= deadline:
                    raise AssertionError(profile + ': full editor bank file differs')
                time.sleep(0.1)
            steps.append('real editor CTRL paint and S persist exactly two tile2 cells; 49 other boards unchanged')
            command(['xdotool', 'key', 'equal'], env)
            observer.wait('editor-next-board', lambda state: state['board_index'] == 1)
            command(['xdotool', 'key', 'minus'], env)
            observer.wait('editor-previous-board', lambda state: state['board_index'] == 0)
            command(['xdotool', 'key', 'BackSpace'], env)
            observer.wait('editor-clear-before-reload', lambda state: state['board_tiles'] == 0)
            command(['xdotool', 'key', 'l'], env)
            observer.wait('editor-reload', lambda state: state['board_index'] == 0 and state['board_tiles'] == 0x202)
            captures['editor-reload'], _ = capture_ready(output, 'editor-reload', env)
            # A second S proves L restored the saved working board after Backspace.
            board_file(runtime).unlink()
            command(['xdotool', 'key', 's'], env)
            deadline = time.monotonic() + 20
            while board_file(runtime) is None or board_file(runtime).read_bytes() != expected:
                if time.monotonic() >= deadline:
                    raise AssertionError(profile + ': L/S did not recreate the complete expected bank')
                time.sleep(0.1)
            steps.append('next/previous board, Backspace/L/S preserve the complete expected bank')
            command(['xdotool', 'key', 'Escape'], env)
            observer.mode(0, 'editor-return-menu-ready')
            captures['return-menu'], _ = capture_ready(output, 'return-menu', env)
            command(['xdotool', 'key', 'Escape'], env)
            code = process.wait(timeout=20)
            assert code == 0 and game_window(env) is None
            steps.append('editor Escape reaches completed mode0; next Escape exits zero and removes window')
        finally:
            stop(process)
            assert verified_originals() == originals
    (output / 'saved-bank.bds').write_bytes(board_file(runtime).read_bytes())
    return {'profile': profile, 'steps': steps, 'captures': captures,
            'state_reads': len(observer.records), 'exit_code': code,
            'executable_sha256': digest(runtime / 'dxball.exe'),
            'bank_input_sha256': digest(ROOT / 'original/DEFAULT.BDS'),
            'bank_saved_sha256': digest(board_file(runtime)), 'originals_unchanged': len(originals)}


def input_identities():
    inputs = [str(path.relative_to(ROOT)) for path in sorted((ROOT / 'src').glob('*.[ch]'))]
    inputs += ['tests/source_state.py', 'tests/windows_state_reader.c', 'tests/test_windows_play.py',
               'CMakeLists.txt', 'config/mingw-i686.cmake', 'scripts/build-windows.py',
               'tests/test_windows_runtime.py', 'tests/target_oracle.py',
               'tests/test_powerups_differential.py', 'tests/test_core_differential.py',
               'tests/test_runtime_differential.py', 'tests/test_platform_differential.py',
               'tests/test_editor_differential.py', 'scripts/windows_runtime.py',
               'scripts/legacy_toolchain.py', 'scripts/resource_limits.py',
              'scripts/build-legacy.py', 'config/assets.csv', 'config/tools.lock.toml']
    return {name: digest(ROOT / name) for name in inputs}


def reader_identity():
    compiler = Path(shutil.which('i686-w64-mingw32-gcc')).resolve()
    sdk = Path('/usr/i686-w64-mingw32/include')
    return {'reader_sha256': digest(READER), 'reader_flags': FLAGS,
            'compiler': str(compiler), 'compiler_sha256': digest(compiler),
            'compiler_version': command([str(compiler), '--version'], os.environ).decode().splitlines()[0],
            'sdk_headers': {name: digest(sdk / name) for name in
                            ('windows.h', 'tlhelp32.h', 'winbase.h', 'winuser.h', 'windef.h', 'basetsd.h')}}


def main():
    limit_cpu()
    if os.environ.get('DXBALL_PLAY_DISPLAY') != '1':
        lock = session_lock()
        READER.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_state_reader.c'),
                        '-o', str(READER)], check=True, timeout=60)
        lock.close()
        env = os.environ.copy(); env['DXBALL_PLAY_DISPLAY'] = '1'
        subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                        str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve())],
                       env=env, check=True, timeout=300)
        return
    lock = session_lock()
    reports = ROOT / 'build/reports/windows-play'
    reports.mkdir(parents=True, exist_ok=True)
    observations = []
    for profile in ('original', 'vc40', 'windows-i686'):
        observations.append(observe(profile, environment(), reports))
        print(profile + ': real ball/pause/editor/zero-exit checks passed', flush=True)
    report = {'status': 'pass', 'kind': 'real-Wine-ball-pause-editor-control-runs',
              'observations': observations, 'inputs': input_identities(), **reader_identity(),
              'vc40_map_sha256': digest(ROOT / 'build/vc40/dxball.map'),
              'mingw_dll_sha256': digest(ROOT / 'build/windows-i686/libdxball_core.dll'),
              'original_addresses': ORIGINAL, 'originals': verified_originals(),
              'limitations': ['ReadProcessMemory only; no target writes/hooks/thread suspension.',
                              'Scalar/ball reads are sequential, not an atomic frame snapshot.',
                              'Input/state predicates verify paths; random trajectories are not synchronized.',
                              'No physical audio, asynchronous MIDI, all-board/full-game fidelity claim.',
                              'Original and source controls share Wine/Xvfb palette limitations.']}
    (ROOT / 'build/reports/windows-play.json').write_text(json.dumps(report, indent=2) + '\n')
    print('Real gameplay/editor controls passed; full bank bytes and live state retained.')


if __name__ == '__main__':
    main()
