#!/usr/bin/env python3
"""Retain REA process Evidence for a real Wine round or focus diagnostic."""
import argparse
from datetime import datetime, timezone
import json
from pathlib import Path
import subprocess

from resource_limits import limit_cpu
from windows_runtime import digest

ROOT = Path(__file__).resolve().parents[1]


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--probe', choices=('round', 'focus'), default='round')
    parser.add_argument('--profile', choices=('original', 'vc40', 'windows-i686'))
    args = parser.parse_args()
    script = ROOT / 'tests/test_windows_round.py'
    arguments = [str(script)]
    if args.probe == 'focus':
        arguments.append('--focus-recovery')
    if args.profile:
        arguments.extend(['--profile', args.profile])
    stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
    directory = ROOT / 'build/reports/rea-process' / (stamp + '-' + args.probe)
    directory.mkdir(parents=True)
    name = 'windows-focus' if args.probe == 'focus' else 'windows-round'
    scenario = {
        'executable': str(ROOT / 'scripts/repo-python'),
        'arguments': arguments, 'working_directory': str(ROOT),
        'timeout_ms': 300000, 'idle_timeout_ms': 300000,
        # Compact SDK JSON numbers are data. REA's generic port/PID rules can
        # replace unrelated numeric values, so declare all text rules explicitly.
        'normalization': {'paths': False, 'pids': False, 'ports': False},
        'limits': {'output_bytes': 16000, 'files': 4, 'file_bytes': 32000,
                   'filesystem_depth': 1, 'processes': 64},
        'filesystem_observation_paths': [
            str(ROOT / 'build/reports' / (name + '.json')),
            str(ROOT / 'build/reports' / name / 'failure.json')],
    }
    request = directory / 'scenario.json'
    request.write_text(json.dumps(scenario, indent=2) + '\n')
    evidence_path = directory / 'evidence.json'
    # The child harness takes the compiler/Wine session lock. REA's process
    # recorder owns no Ghidra session; a parent lock would deadlock that child.
    with evidence_path.open('w') as output, (directory / 'rea.log').open('w') as log:
        captured = subprocess.run([str(ROOT / 'scripts/rea'), 'capture-process',
                                   str(request), '--format', 'json'],
                                  cwd=ROOT, stdout=output, stderr=log)
    if captured.returncode:
        print('REA capture failed; see', directory.relative_to(ROOT))
        return captured.returncode
    evidence = json.loads(evidence_path.read_text())
    exit_state = evidence['normalized_result']['exit']
    code = exit_state['code']
    summary = {'evidence_id': evidence['evidence_id'], 'probe': args.probe,
               'profile': args.profile or 'all', 'exit': exit_state,
               'scenario_sha256': digest(request), 'evidence_sha256': digest(evidence_path),
               'inputs': {str(path.relative_to(ROOT)): digest(path) for path in
                          (Path(__file__), script, ROOT / 'scripts/rea.py')},
               'limitations': evidence['limitations']}
    (directory / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print('REA', evidence['evidence_id'], 'observed', exit_state)
    print('Retained:', directory.relative_to(ROOT))
    # A valid Evidence record can describe a failed diagnostic. Propagate its
    # child result instead of treating the recorder's success as a game pass.
    return code if code is not None and code >= 0 else 1


if __name__ == '__main__':
    raise SystemExit(main())
