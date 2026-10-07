#!/usr/bin/env python3
"""Observe 50 real clears and diagnose the unresolved terminal storage contract."""
import argparse
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
from windows_runtime import digest, environment, launch, prepare, stop, verified_originals
from test_windows_runtime import command, game_window
from test_windows_play import (FLAGS, READER, Observer, board_file, capture_ready,
                               click, input_identities, reader_identity)
from test_windows_round import CELL, FIELDS, attached, release, wait_window


class StreamObserver(Observer):
    """Append complete samples; avoid rewriting an ever-growing JSON array."""
    def read(self, phase):
        data = json.loads(command(self.arguments, self.env))
        values = {name.removeprefix('dxball_'): value for name, value in data['values'].items()}
        row = {'phase': phase, 'monotonic': time.monotonic(),
               'windows_pid': data['pid'], 'values': values}
        self.records.append(row)
        with self.output.open('a') as stream:
            stream.write(json.dumps(row, separators=(',', ':')) + '\n')
        return values


def identities():
    return {**input_identities(),
            'tests/test_windows_round.py': digest(ROOT / 'tests/test_windows_round.py'),
            'tests/test_windows_terminal.py': digest(Path(__file__))}


def observe(profile, env, reports):
    runtime, originals = prepare(profile, probe=True)
    output = reports / profile
    output.mkdir(parents=True, exist_ok=True)
    (output / 'states.jsonl').unlink(missing_ok=True)
    fields = dict(FIELDS, board_bank=0x43AAB8)
    observer = StreamObserver(profile, env, output / 'states.jsonl', fields,
                              {'board_tiles': ':board', 'board_bank': ':bank_tail'})
    brick = bytearray(400)
    brick[CELL] = 1
    expected = bytes(brick) * 50
    rows = []
    with (output / 'wine.log').open('w') as log:
        process = launch(runtime, env, log)
        try:
            window = wait_window(process, env)
            observer.mode(4, 'opening-ready')
            capture_ready(output, 'opening', env)
            command(['xdotool', 'windowfocus', window, 'key', 'space'], env)
            observer.mode(0, 'menu-ready')
            command(['xdotool', 'key', 'ctrl+F1'], env)
            observer.mode(2, 'editor-ready')
            observer.wait('editor-control-released', lambda s: s['control_pressed'] == 0)
            click(env, 37, 392)
            observer.wait('editor-tile1-selected', lambda s: s['editor_selected_tile'] == 1)
            for index in range(50):
                observer.wait('editor-board-' + str(index), lambda s: s['board_index'] == index)
                command(['xdotool', 'key', 'BackSpace'], env)
                observer.wait('editor-empty-' + str(index),
                              lambda s: bytes.fromhex(s['board_tiles']) == bytes(400))
                click(env, 215, 327)
                observer.wait('editor-brick-' + str(index),
                              lambda s: bytes.fromhex(s['board_tiles']) == bytes(brick))
                if index < 49:
                    command(['xdotool', 'key', 'equal'], env)
            command(['xdotool', 'key', 's'], env)
            deadline = time.monotonic() + 20
            while board_file(runtime).read_bytes() != expected:
                if time.monotonic() >= deadline:
                    raise AssertionError('Full editor-created 50-board bank differs')
                time.sleep(0.1)
            (output / 'edited-bank.bds').write_bytes(board_file(runtime).read_bytes())
            command(['xdotool', 'key', 'Escape'], env)
            observer.mode(0, 'editor-return-menu')
            click(env, 320, 390)
            for index in range(50):
                initial = attached(observer, 'round-attached-' + str(index))
                assert initial['board_index'] == index and initial['remaining_bricks'] == 1
                assert initial['lives'] == 3 and initial['score'] == index * 10
                assert bytes.fromhex(initial['board_tiles']) == bytes(brick)
                if index == 49:
                    (output / 'tail-before-last-release.bin').write_bytes(
                        bytes.fromhex(initial['board_bank']))
                release(observer, env, 185, 'round-release-' + str(index))
                observer.wait('round-hit-' + str(index), lambda s: s['score'] > initial['score']
                              and (s['remaining_bricks'] == 0
                                   or (index == 49 and s['board_index'] == 50)))
                if index < 49:
                    state = observer.wait('round-next-' + str(index),
                        lambda s: s['display_mode'] == 1 and s['board_index'] == index + 1
                        and s['restart_requested'] == 0 and s['level_changed'] == 0
                        and s['end_requested'] == 0 and s['balls'] is not None
                        and s['balls']['attached'] == 1)
                else:
                    state = observer.wait('terminal-ready', lambda s: s['display_mode'] in (0, 3)
                        and s['end_requested'] == 0 and s['device_reset_requested'] == 0)
                    (output / 'terminal-tiles.bin').write_bytes(bytes.fromhex(state['board_tiles']))
                    (output / 'terminal-tail.bin').write_bytes(bytes.fromhex(state['board_bank']))
                    capture_ready(output, 'terminal', env, minimum_colors=2)
                rows.append({name: state[name] for name in ('board_index', 'display_mode',
                             'lives', 'score', 'remaining_bricks')})
                rows[-1]['cleared_board'] = index
                (output / 'rounds.json').write_text(json.dumps(rows, indent=2) + '\n')
                print(profile + ': cleared board ' + str(index), flush=True)
            terminal = state
            if state['display_mode'] == 3:
                command(['xdotool', 'key', 'r', 'e', 'a', 'Return'], env)
                observer.mode(0, 'ranking-return-menu')
            command(['xdotool', 'key', 'Escape'], env)
            code = process.wait(timeout=20)
            assert code == 0 and game_window(env) is None
            assert board_file(runtime).read_bytes() == expected
        except Exception as error:
            (output / 'failure.txt').write_text(repr(error) + '\n')
            command(['import', '-window', 'root', str(output / 'failure.png')], env)
            raise
        finally:
            stop(process)
            assert verified_originals() == originals
    tiles = bytes.fromhex(terminal['board_tiles'])
    # For this empty-request/single-ball fixture, the original copies its four
    # clock bytes, empty list region, ball-count DWORD and zeroed board suffix.
    # Clock values vary with execution time; retain them rather than compare
    # independent runs byte-for-byte. This is a scoped storage contract only.
    storage = (tiles[4:24] == bytes(20) and tiles[24:28] == b'\x01\0\0\0'
               and tiles[28:] == bytes(372))
    routing = (terminal['display_mode'] == 0 and terminal['board_index'] == 50
               and terminal['lives'] == 3 and terminal['score'] == 500)
    row = {'profile': profile, 'status': 'pass' if storage and routing else 'mismatch',
           'routing_matches_original': routing, 'storage_matches_original_fixture': storage,
           'rounds_cleared': len(rows), 'exit_code': code, 'terminal': terminal,
           'state_reads': len(observer.records), 'executable_sha256': digest(runtime / 'dxball.exe'),
           'edited_bank_sha256': digest(output / 'edited-bank.bds'),
           'inputs': identities(), 'reader': reader_identity(), 'originals': originals}
    (output / 'summary.json').write_text(json.dumps(row, indent=2) + '\n')
    return row


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--profile', choices=('original', 'vc40', 'windows-i686'))
    args = parser.parse_args()
    limit_cpu()
    if os.environ.get('DXBALL_TERMINAL_DISPLAY') != '1':
        lock = session_lock()
        READER.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['i686-w64-mingw32-gcc', *FLAGS, str(ROOT / 'tests/windows_state_reader.c'),
                        '-o', str(READER)], check=True, timeout=60)
        lock.close()
        env = dict(os.environ, DXBALL_TERMINAL_DISPLAY='1')
        return subprocess.run(['xvfb-run', '-a', '-s', '-screen 0 640x480x8',
                               str(ROOT / 'scripts/repo-python'), str(Path(__file__).resolve()),
                               *sys.argv[1:]], env=env, timeout=1140).returncode
    lock = session_lock()
    reports = ROOT / 'build/reports/windows-terminal'
    reports.mkdir(parents=True, exist_ok=True)
    aggregate = ROOT / 'build/reports/windows-terminal.json'
    aggregate.unlink(missing_ok=True)
    (reports / 'failure.json').unlink(missing_ok=True)
    observations = []
    for profile in ((args.profile,) if args.profile else ('original', 'vc40', 'windows-i686')):
        try:
            observations.append(observe(profile, environment(), reports))
        except Exception as error:
            (reports / 'failure.json').write_text(json.dumps({'status': 'failed',
                'profile': profile, 'error': repr(error), 'completed_observations': observations,
                'inputs': identities(), 'reader': reader_identity()}, indent=2) + '\n')
            raise
    passed = all(row['status'] == 'pass' for row in observations)
    aggregate.write_text(json.dumps({'status': 'pass' if passed else 'mismatch',
        'observations': observations, 'inputs': identities(), 'reader': reader_identity(),
        'limitations': ['50 editor-created single-brick boards, not the original campaign.',
                        'Original clock bytes vary; a scoped storage pattern is compared.',
                        'A routing pass alone does not establish terminal storage fidelity.',
                        'No target writes, hooks or complete-frame pixel comparison.']},
        indent=2) + '\n')
    print('Terminal storage diagnostic: ' + ('pass' if passed else 'mismatch'), flush=True)
    return 0 if passed else 1


if __name__ == '__main__':
    raise SystemExit(main())
