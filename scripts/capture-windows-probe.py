#!/usr/bin/env python3
"""Retain REA process Evidence for a Wine game or independent SDK diagnostic."""
import argparse
from datetime import datetime, timezone
import json
import os
from pathlib import Path
import subprocess

from resource_limits import limit_cpu
from windows_runtime import digest

ROOT = Path(__file__).resolve().parents[1]


def silent_audio_environment():
    """Keep Wine audio APIs active while routing probe playback to a null sink."""
    name = 'dxball_reconstruction_silent'
    sinks = json.loads(subprocess.check_output(
        ['pactl', '--format=json', 'list', 'sinks'], text=True))
    if not any(sink['name'] == name for sink in sinks):
        subprocess.run(['pactl', 'load-module', 'module-null-sink',
                        'sink_name=' + name,
                        'sink_properties=device.description=DX-Ball-Reconstruction-Silent'],
                       check=True, stdout=subprocess.DEVNULL)
    environment = os.environ.copy()
    environment['PULSE_SINK'] = name
    return environment


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', choices=('round', 'focus', 'ddraw-loss', 'terminal', 'resources', 'campaign'), default='round')
    parser.add_argument('--profile', choices=('original', 'vc40', 'windows-i686'))
    parser.add_argument('--campaign-seconds', type=int, default=3600)
    parser.add_argument('--campaign-boards', type=int, choices=range(1, 51), default=50)
    parser.add_argument('--episode-seconds', type=int, default=0)
    args = parser.parse_args()
    if args.probe in ('ddraw-loss', 'resources') and args.profile:
        parser.error('--profile selects a game build; this independent SDK probe takes no profile')
    script = ROOT / 'tests' / ('test_windows_ddraw_loss.py' if args.probe == 'ddraw-loss'
                              else 'test_windows_resources.py' if args.probe == 'resources'
                              else 'test_windows_terminal.py' if args.probe == 'terminal'
                              else 'test_windows_campaign.py' if args.probe == 'campaign'
                              else 'test_windows_round.py')
    arguments = [str(script)]
    if args.probe == 'focus':
        arguments.append('--focus-recovery')
    if args.profile:
        arguments.extend(['--profiles' if args.probe == 'campaign' else '--profile', args.profile])
    if args.probe == 'campaign':
        if args.campaign_seconds < 1 or not 0 <= args.episode_seconds <= args.campaign_seconds:
            parser.error('Invalid campaign observation deadline')
        arguments.extend(['--seconds', str(args.campaign_seconds),
                          '--boards', str(args.campaign_boards),
                          '--episode-seconds', str(args.episode_seconds)])
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    directory = ROOT / 'build/reports/rea-process' / (stamp + '-' + args.probe)
    directory.mkdir(parents=True)
    name = {'focus': 'windows-focus', 'ddraw-loss': 'windows-ddraw-loss',
            'terminal': 'windows-terminal', 'round': 'windows-round',
            'resources': 'windows-resources', 'campaign': 'windows-campaign'}[args.probe]
    timeout = 1200000 if args.probe == 'terminal' else 300000
    if args.probe == 'campaign':
        timeout = (args.campaign_seconds + 60) * (1 if args.profile else 3) * 1000
    scenario = {
        'executable': str(ROOT / 'scripts/repo-python'),
        'arguments': arguments, 'working_directory': str(ROOT),
        'timeout_ms': timeout, 'idle_timeout_ms': timeout,
        # Compact SDK JSON numbers are data. REA's generic port/PID rules can
        # replace unrelated numeric values, so declare all text rules explicitly.
        'normalization': {'paths': False, 'pids': False, 'ports': False},
        'limits': {'output_bytes': 16000, 'files': 4,
                   'file_bytes': (4 * 1024 * 1024 if args.probe == 'campaign'
                                  else 128000 if args.probe == 'terminal' else 32000),
                   'filesystem_depth': 1, 'processes': 64},
        'filesystem_observation_paths': ([str(ROOT / 'build/reports/windows-campaign/summary.json')]
            if args.probe == 'campaign' else [
                str(ROOT / 'build/reports' / (name + '.json')),
                str(ROOT / 'build/reports' / name / 'failure.json')]),
    }
    request = directory / 'scenario.json'
    request.write_text(json.dumps(scenario, indent=2) + '\n')
    evidence_path = directory / 'evidence.json'
    audio_environment = (os.environ.copy() if args.probe in ('ddraw-loss', 'resources')
                         else silent_audio_environment())
    # The child harness takes the compiler/Wine session lock. REA's process
    # recorder owns no Ghidra session; a parent lock would deadlock that child.
    with evidence_path.open('w') as output, (directory / 'rea.log').open('w') as log:
        captured = subprocess.run([str(ROOT / 'scripts/rea'), 'capture-process',
                                  str(request), '--format', 'json'],
                                  cwd=ROOT, env=audio_environment, stdout=output, stderr=log)
    if captured.returncode:
        print('REA capture failed; see', directory.relative_to(ROOT))
        return captured.returncode
    evidence = json.loads(evidence_path.read_text())
    exit_state = evidence['normalized_result']['exit']
    code = exit_state['code']
    summary = {'evidence_id': evidence['evidence_id'], 'probe': args.probe,
               'profile': ('independent-sdk' if args.probe in ('ddraw-loss', 'resources') else args.profile or 'all'),
               'exit': exit_state,
               'scenario_sha256': digest(request), 'evidence_sha256': digest(evidence_path),
               'inputs': {str(path.relative_to(ROOT)): digest(path) for path in
                          (Path(__file__), script, ROOT / 'scripts/rea.py')},
               'audio': {'playback': ('not-applicable' if args.probe in ('ddraw-loss', 'resources') else 'silent'),
                         'pulse_sink': audio_environment.get('PULSE_SINK'),
                         'scope': 'Host playback routing; game audio APIs remain active.'},
               'limitations': evidence['limitations']}
    (directory / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print('REA', evidence['evidence_id'], 'observed', exit_state)
    print('Retained:', directory.relative_to(ROOT))
    # A valid Evidence record can describe a failed diagnostic. Propagate its
    # child result instead of treating the recorder's success as a game pass.
    return code if code is not None and code >= 0 else 1


if __name__ == '__main__':
    raise SystemExit(main())
