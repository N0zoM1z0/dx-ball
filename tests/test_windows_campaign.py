#!/usr/bin/env python3
"""Observe untouched original-board play through a persistent read-only SDK reader.

An explicitly bounded episode is integration evidence, not a campaign pass.
The default goal requires progression through all 50 original boards.
"""
import argparse
import ctypes
import hashlib
import json
import os
from pathlib import Path
import selectors
import shutil
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from campaign_controller import CONTACT_BIASES, DECISIONS_PER_CONTACT_BIAS, choose_mouse
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import digest, environment, launch, prepare, stop, verified_originals
from test_windows_play import FLAGS, Observer, input_identities
from test_windows_round import FIELDS, wait_window
from test_windows_runtime import command

# Contracts retained by the resource, entity and power-up REA owner suites.
FIELDS = dict(FIELDS, sprite_banks=0x425980, sprite_bank=0x421088,
              bonuses=0x43FAC8, paddle_width=0x43FA94,
              paddle_previous_x=0x43A904, paddle_previous_y=0x43A908,
              bonus_3_ticks=0x43A88C)
SHAPES = {'balls': ':ball_list', 'bonuses': ':bonus_list', 'board_tiles': ':board'}
READER = ROOT / 'build/probes/windows-runtime/campaign-reader.exe'


class Mouse:
    """Ordinary X server input; no process-memory writes or target hooks."""
    def __init__(self):
        self.x11 = ctypes.CDLL('libX11.so.6')
        self.xtst = ctypes.CDLL('libXtst.so.6')
        self.x11.XOpenDisplay.argtypes = [ctypes.c_char_p]
        self.x11.XOpenDisplay.restype = ctypes.c_void_p
        self.x11.XFlush.argtypes = [ctypes.c_void_p]
        self.x11.XCloseDisplay.argtypes = [ctypes.c_void_p]
        self.xtst.XTestFakeMotionEvent.argtypes = [ctypes.c_void_p, ctypes.c_int,
                                                  ctypes.c_int, ctypes.c_int, ctypes.c_ulong]
        self.xtst.XTestFakeButtonEvent.argtypes = [ctypes.c_void_p, ctypes.c_uint,
                                                  ctypes.c_int, ctypes.c_ulong]
        self.display = self.x11.XOpenDisplay(None)
        if not self.display:
            raise RuntimeError('XOpenDisplay failed')
        self.down = False
        self.identities = {}
        for line in Path('/proc/self/maps').read_text().splitlines():
            name = line.split()[-1]
            if '/libX11.so.' in name or '/libXtst.so.' in name:
                path = Path(name).resolve()
                self.identities[str(path)] = digest(path)

    def move(self, origin, x):
        if not self.xtst.XTestFakeMotionEvent(self.display, -1, origin[0] + x,
                                             origin[1] + 390, 0):
            raise RuntimeError('XTest mouse motion failed')
        self.x11.XFlush(self.display)

    def button(self, down):
        if not self.xtst.XTestFakeButtonEvent(self.display, 1, int(down), 0):
            raise RuntimeError('XTest mouse button failed')
        self.down = down
        self.x11.XFlush(self.display)

    def close(self):
        if self.down:
            self.button(False)
        self.x11.XCloseDisplay(self.display)


class Stream:
    """Drain the SDK pipe without saving an unbounded sample log."""
    def __init__(self, arguments, env, log):
        self.process = subprocess.Popen(arguments, env=env, stdout=subprocess.PIPE,
                                        stderr=log, start_new_session=True)
        os.set_blocking(self.process.stdout.fileno(), False)
        self.selector = selectors.DefaultSelector()
        self.selector.register(self.process.stdout, selectors.EVENT_READ)
        self.buffer = b''
        self.hasher = hashlib.sha256()
        self.valid = self.broken = self.bytes = 0
        self.latest = None
        self.last_sample = time.monotonic()

    def read(self, timeout=0.1):
        latest = None
        if self.selector.select(timeout):
            while True:
                try:
                    chunk = os.read(self.process.stdout.fileno(), 65536)
                except BlockingIOError:
                    break
                if not chunk:
                    raise RuntimeError('Campaign reader exited: ' + str(self.process.poll()))
                self.hasher.update(chunk)
                self.bytes += len(chunk)
                self.buffer += chunk
                if len(self.buffer) > 1024 * 1024:
                    raise RuntimeError('Campaign reader line exceeded buffer limit')
                lines = self.buffer.split(b'\n')
                self.buffer = lines.pop()
                for line in lines:
                    try:
                        record = json.loads(line)
                    except (ValueError, UnicodeError):
                        self.broken += 1
                        continue
                    record['values'] = {key.removeprefix('dxball_'): value
                                        for key, value in record['values'].items()}
                    self.valid += 1
                    latest = record
                if len(chunk) < 65536:
                    break
        if latest is not None:
            self.latest = latest
            self.last_sample = time.monotonic()
        elif time.monotonic() - self.last_sample > 10:
            raise RuntimeError('No valid SDK sample for ten seconds')
        return latest

    def close(self):
        stop(self.process)
        self.process.stdout.close()
        self.selector.close()


def observe(profile, args, reports):
    runtime, originals = prepare(profile, probe=True)
    bank = (runtime / 'DEFAULT.BDS').read_bytes()
    assert len(bank) == 20000
    output = reports / profile
    output.mkdir(parents=True, exist_ok=True)
    env = environment()
    observer = Observer(profile, env, output / 'unused.json', FIELDS, SHAPES)
    observer.arguments[1] = str(READER)
    events, initialized = [], set()
    summary = {'profile': profile, 'status': 'running', 'events': events,
               'initialized_board_indices': [], 'executable_sha256': digest(runtime / 'dxball.exe'),
               'bank_input_sha256': digest(runtime / 'DEFAULT.BDS'),
               'reader_arguments': observer.arguments,
               'controller': dict(contact_biases=CONTACT_BIASES, decisions_per_bias=DECISIONS_PER_CONTACT_BIAS,
                                  basis='processed latest SDK samples; cadence depends on scheduling'),
               'controller_phase_requests': [0] * len(CONTACT_BIASES)}
    if profile == 'windows-i686':
        summary['dll_sha256'] = digest(runtime / 'libdxball_core.dll')
    if profile == 'vc40':
        summary['map_sha256'] = digest(ROOT / 'build/vc40/dxball.map')
    began = time.monotonic()
    stream = mouse = process = None
    previous = None
    seen_game = False
    opening_input = 0
    sample_steps = clicks = 0
    last_click = last_record = 0
    candidate = None
    stable = 0
    last_mouse_request = None
    with (output / 'wine.log').open('w') as wine_log, (output / 'reader.log').open('w') as reader_log:
        try:
            process = launch(runtime, env, wine_log)
            window = wait_window(process, env)
            stream = Stream(observer.arguments, env, reader_log)
            mouse = Mouse()
            summary['x_input_libraries'] = mouse.identities
            while True:
                record = stream.read()
                now = time.monotonic()
                if record is None:
                    if now - began > args.seconds:
                        raise AssertionError('Campaign observation deadline')
                    continue
                sample_steps += 1
                state = record['values']
                key = (state['display_mode'], state['board_index'], state['lives'],
                       state['end_requested'], state['restart_requested'], state['return_to_menu'])
                if key != previous or now - last_record > 10:
                    if len(events) >= 10000:
                        raise RuntimeError('Bounded event log limit reached')
                    events.append({'seconds': round(now - began, 3), 'values': state,
                                   'origin': record['origin'],
                                   'last_mouse_request': last_mouse_request})
                    previous, last_record = key, now
                    # Persist transitions periodically so a failed run remains reviewable.
                    summary['last_state'] = state
                    (output / 'observation.json').write_text(json.dumps(summary, indent=2) + '\n')
                hold = 0.25 if state['display_mode'] == 0 else 0.06
                if mouse.down and now - last_click >= hold:
                    mouse.button(False)
                    last_click = now
                if state['display_mode'] == 4 and not opening_input and not state['device_reset_requested']:
                    command(['xdotool', 'windowfocus', window, 'key', 'space'], env)
                    opening_input = 1
                elif (state['display_mode'] == 0 and opening_input and not seen_game
                      and not mouse.down and now - last_click >= 0.1
                      and not state['device_reset_requested'] and not state['end_requested']):
                    mouse.move(record['origin'], 320)
                    mouse.button(True)
                    last_click = now
                if state['display_mode'] == 1:
                    index = state['board_index']
                    if index < 0 or index > 50:
                        raise AssertionError('Invalid observed board index: ' + str(index))
                    if (initialized and index < 50 and state['end_requested']
                            and not state['restart_requested']):
                        raise AssertionError('Game over before campaign goal')
                    ready = (state['application_active'] and not state['restart_requested']
                             and not state['device_reset_requested'] and not state['end_requested']
                             and state['balls'])
                    if index < 50 and ready and index not in initialized:
                        expected = bank[index * 400:(index + 1) * 400].hex()
                        # A launch can precede the next SDK sample. The complete
                        # unchanged bank bytes establish this initial board;
                        # attachment is a transient input state, not that identity.
                        if state['board_tiles'] == expected:
                            token = (index, state['board_tiles'])
                            stable = stable + 1 if candidate == token else 1
                            candidate = token
                            if stable >= 2:
                                initialized.add(index)
                                summary['initialized_board_indices'] = sorted(initialized)
                                print(profile + ': original board ' + str(index) + ' initialized', flush=True)
                        else:
                            candidate, stable = None, 0
                        if index not in initialized:
                            if now - began > args.seconds:
                                raise AssertionError('Board initialization observation deadline')
                            continue
                    if ready and index < 50:
                        seen_game = True
                        requested_x = choose_mouse(state, sample_steps)
                        mouse.move(record['origin'], requested_x)
                        phase = (sample_steps // DECISIONS_PER_CONTACT_BIAS) % len(CONTACT_BIASES)
                        summary['controller_phase_requests'][phase] += 1
                        last_mouse_request = dict(seconds=round(now - began, 3),
                                                  processed_sample=sample_steps, phase=phase, x=requested_x)
                        summary['last_mouse_request'] = last_mouse_request
                        if not mouse.down and now - last_click >= 0.03:
                            mouse.button(True)
                            clicks += 1
                            last_click = now
                    if args.boards < 50 and index >= args.boards:
                        if not ready or index not in initialized:
                            if now - began > args.seconds:
                                raise AssertionError('Next-board readiness observation deadline')
                            continue
                        if initialized != set(range(args.boards + 1)):
                            raise AssertionError('Missing initial original boards')
                        summary['status'] = 'bounded-progression'
                        break
                if seen_game and state['display_mode'] == 0:
                    if state['board_index'] == 50 and initialized == set(range(50)):
                        if (not state['end_requested'] and not state['device_reset_requested']
                                and not state['return_to_menu']):
                            summary['status'] = 'campaign-pass'
                            break
                    else:
                        raise AssertionError('Returned to menu before full campaign')
                if args.episode_seconds and seen_game and now - began >= args.episode_seconds:
                    summary['status'] = 'bounded-episode'
                    break
                if now - began > args.seconds:
                    raise AssertionError('Campaign observation deadline')
            summary['last_state'] = state
        except Exception as error:
            summary.update(status='fail', error=repr(error))
            raise
        finally:
            if stream is not None:
                stream.close()
                summary.update(valid_sdk_samples=stream.valid, discarded_malformed_samples=stream.broken,
                               sample_stream_bytes=stream.bytes, sample_stream_sha256=stream.hasher.hexdigest(),
                               processed_samples=sample_steps, mouse_clicks=clicks)
            if mouse is not None:
                mouse.close()
            if process is not None:
                stop(process)
            summary['seconds'] = round(time.monotonic() - began, 3)
            summary['bank_unchanged'] = (runtime / 'DEFAULT.BDS').read_bytes() == bank
            summary['originals_unchanged'] = verified_originals() == originals
            (output / 'observation.json').write_text(json.dumps(summary, indent=2) + '\n')
            assert summary['bank_unchanged'] and summary['originals_unchanged']
    return summary


def main():
    if not __debug__:
        raise RuntimeError("Campaign observations require assertions; do not use -O.")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--profiles', nargs='+', choices=('original', 'vc40', 'windows-i686'),
                        default=['original', 'vc40', 'windows-i686'])
    parser.add_argument('--seconds', type=int, default=3600)
    parser.add_argument('--boards', type=int, choices=range(1, 51), default=50)
    parser.add_argument('--episode-seconds', type=int, default=0,
                        help='Explicit bounded episode; never reported as a campaign pass')
    parser.add_argument('--compile-only', action='store_true',
                        help='Public strict SDK compilation; no original files or Wine run')
    args = parser.parse_args()
    if args.seconds < 1 or args.episode_seconds < 0 or args.episode_seconds > args.seconds:
        parser.error('Invalid observation deadline')
    limit_cpu()
    if args.compile_only or os.environ.get('DXBALL_CAMPAIGN_DISPLAY') != '1':
        with session_lock():
            READER.parent.mkdir(parents=True, exist_ok=True)
            subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_campaign_reader.c'),
                            '-o', str(READER)], check=True, timeout=60)
        if args.compile_only:
            print('Persistent campaign SDK reader: strict i686 C90 compilation passed')
            return
        env = os.environ.copy()
        env['DXBALL_CAMPAIGN_DISPLAY'] = '1'
        child = subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                                str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve()),
                                *sys.argv[1:]], env=env, timeout=(args.seconds + 60) * len(args.profiles))
        raise SystemExit(child.returncode)
    with session_lock():
        reports = ROOT / 'build/reports/windows-campaign'
        reports.mkdir(parents=True, exist_ok=True)
        destination = reports / 'summary.json'
        destination.unlink(missing_ok=True)
        inputs = input_identities()
        inputs.update({name: digest(ROOT / name) for name in
                       ('tests/test_windows_campaign.py', 'tests/windows_campaign_reader.c',
                        'scripts/campaign_controller.py', 'tests/test_windows_round.py')})
        report = {'status': 'running', 'inputs': inputs, 'originals': verified_originals(),
                  'original_addresses': FIELDS, 'reader_sha256': digest(READER), 'reader_flags': FLAGS,
                  'goal_board_count': args.boards, 'episode_seconds': args.episode_seconds,
                  'observations': [], 'limitations': [
                      'ReadProcessMemory samples are sequential and may cross frame/list changes; valid JSON is not an atomic snapshot.',
                      'Malformed lines are discarded; controller phases count processed latest samples, not game frames.',
                      'Retained mouse requests describe XTest inputs, not guaranteed game consumption or safe catches.',
                      'Ordinary XTest input; no target writes, hooks, suspension or altered boards.',
                      'Stream hash covers consumed pipe bytes; only bounded transition samples are retained.',
                      'Runs have independent clock/RNG trajectories; no synchronized pixel/audio claim.',
                      'A bounded episode/progression is not full original-campaign acceptance.',
                      'Bonus level advancement need not destroy every brick.']}
        compiler = Path(shutil.which('i686-w64-mingw32-gcc')).resolve()
        sdk = Path('/usr/i686-w64-mingw32/include')
        report['compiler'] = {'path': str(compiler), 'sha256': digest(compiler),
                              'version': command([str(compiler), '--version'], os.environ).decode().splitlines()[0],
                              'sdk_headers': {name: digest(sdk / name) for name in
                                  ('windows.h', 'tlhelp32.h', 'winbase.h', 'winuser.h', 'windef.h', 'basetsd.h')}}
        try:
            for profile in args.profiles:
                report['observations'].append(observe(profile, args, reports))
            statuses = {row['status'] for row in report['observations']}
            if len(statuses) != 1:
                raise AssertionError('Products completed different requested scopes: ' + str(statuses))
            report['status'] = statuses.pop()
        except Exception as error:
            report.update(status='fail', error=repr(error))
            raise
        finally:
            destination.write_text(json.dumps(report, indent=2) + '\n')
        print('Windows original-board observation: ' + report['status'], flush=True)


if __name__ == '__main__':
    main()
