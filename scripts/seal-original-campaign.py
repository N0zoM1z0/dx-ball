#!/usr/bin/env python3
"""Seal a finished original-only campaign capture before cleaning its fixtures."""
import argparse
import fcntl
import hashlib
import json
from pathlib import Path
import shutil
import sys
import tempfile

from legacy_toolchain import ROOT
from resource_limits import limit_cpu


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def load(path):
    return json.loads(path.read_text())


def checked(path, expected):
    if not path.is_file() or path.is_symlink() or digest(path) != expected:
        raise ValueError('Missing or changed evidence: ' + str(path))
    return path


def live(identity, boot_id):
    if Path('/proc/sys/kernel/random/boot_id').read_text().strip() != boot_id:
        return False
    try:
        fields = (Path('/proc') / str(identity['pid']) / 'stat').read_text().rsplit(') ', 1)[1].split()
    except FileNotFoundError:
        return False
    return fields[0] != 'Z' and int(fields[19]) == identity['start_ticks']


def validate(root, attempt, capture, is_live=live):
    frozen = load(attempt / 'attempt.json')
    if frozen['profiles'] != ['original']:
        raise ValueError('This sealer requires an original-only attempt')
    identities = frozen['process_identities']
    if not all(key in identities for key in ('wine_game_pid', 'reader_pid')):
        raise ValueError('Missing recorded kernel process identities')
    if any(is_live(identity, frozen['boot_id']) for identity in identities.values()):
        raise ValueError('Recorded campaign process is still live; archive and cleanup must wait')
    for name, expected in frozen['inputs'].items():
        path = Path(name)
        if path.is_absolute() or '..' in path.parts:
            raise ValueError('Frozen input path must be repository-relative')
        checked(attempt / path, expected)
    checked(attempt / 'campaign-reader.exe', frozen['reader_sha256'])
    report_path = root / 'build/reports/windows-campaign/summary.json'
    report = load(report_path)
    if report['status'] not in ('campaign-pass', 'bounded-progression', 'bounded-episode', 'fail'):
        raise ValueError('Campaign report is not terminal')
    if report['reader_sha256'] != frozen['reader_sha256']:
        raise ValueError('Report names another SDK reader product')
    checked(root / 'build/probes/windows-runtime/campaign-reader.exe', frozen['reader_sha256'])
    expected_inputs = {name: sha for name, sha in frozen['inputs'].items()
                       if name != 'scripts/capture-windows-probe.py'}
    if report['inputs'] != expected_inputs:
        raise ValueError('Report input set differs from the frozen attempt')
    if report['goal_board_count'] != frozen['boards'] or report['episode_seconds'] != 0:
        raise ValueError('Report requested another campaign scope')
    scenario = load(capture / 'scenario.json')
    expected_arguments = [str(root / 'tests/test_windows_campaign.py'), '--profiles', 'original',
                          '--seconds', str(frozen['seconds']), '--boards', str(frozen['boards']),
                          '--episode-seconds', '0']
    if (scenario['executable'] != str(root / 'scripts/repo-python')
            or scenario['working_directory'] != str(root)
            or scenario['arguments'] != expected_arguments):
        raise ValueError('REA scenario differs from the frozen attempt')
    evidence = load(capture / 'evidence.json')
    if evidence['operation'] != 'capture_process_scenario':
        raise ValueError('Expected REA process evidence')
    result = evidence['normalized_result']
    observed_scenario = result['manifest']['scenario']
    for name in ('executable', 'arguments', 'working_directory'):
        if observed_scenario[name] != scenario[name]:
            raise ValueError('REA evidence describes another scenario')
    exit_state = result['exit']
    if exit_state['reason'] != 'exited' or exit_state['code'] is None:
        raise ValueError('REA did not observe a completed diagnostic process')
    if (exit_state['code'] == 0) != (report['status'] != 'fail'):
        raise ValueError('REA child result contradicts the diagnostic report')
    capture_summary = load(capture / 'summary.json')
    if (capture_summary['evidence_id'] != evidence['evidence_id']
            or capture_summary['exit'] != exit_state):
        raise ValueError('REA capture summary identity/result differs')
    checked(capture / 'evidence.json', capture_summary['evidence_sha256'])
    checked(capture / 'scenario.json', capture_summary['scenario_sha256'])
    observations = report['observations']
    if any(row['profile'] != 'original' for row in observations):
        raise ValueError('Report contains another product')
    observation_path = root / 'build/reports/windows-campaign/original/observation.json'
    observation = load(observation_path)
    if observation['profile'] != 'original' or observation['status'] == 'running':
        raise ValueError('Original observation is not terminal')
    if report['status'] == 'fail':
        if observations or observation['status'] != 'fail' or observation.get('error') != report.get('error'):
            raise ValueError('Failed observation does not belong to this report')
    elif observations != [observation] or observation['status'] != report['status']:
        raise ValueError('Original observation differs from this report')
    if not observation['bank_unchanged'] or not observation['originals_unchanged']:
        raise ValueError('Diagnostic reports modified game inputs')
    for name, expected in report['originals'].items():
        checked(root / 'original' / name, expected)
    if observation['executable_sha256'] != report['originals']['DXBALL.EXE']:
        raise ValueError('Observed game is not the original product')
    checked(root / 'build/runtime/probe-original/dxball.exe', observation['executable_sha256'])
    checked(root / 'build/runtime/probe-original/DEFAULT.BDS', observation['bank_input_sha256'])
    if observation['bank_input_sha256'] != report['originals']['DEFAULT.BDS']:
        raise ValueError('Observed bank is not the original input')
    if report['status'] == 'campaign-pass':
        state = observation['last_state']
        if (frozen['boards'] != 50 or observation['initialized_board_indices'] != list(range(50))
                or state['board_index'] != 50 or state['display_mode'] != 0
                or any(state[name] for name in ('end_requested', 'device_reset_requested', 'return_to_menu'))):
            raise ValueError('Report lacks the full original campaign terminal predicate')
    report_sha = digest(report_path)
    filesystem_paths = observed_scenario['filesystem_observation_paths']
    if filesystem_paths != [str(report_path)]:
        raise ValueError('REA filesystem scope differs from the campaign report')
    entries = [row for row in result['files_after'] if row['path'] == 'root_0:.' and row['type'] == 'file']
    if len(entries) != 1 or entries[0]['size'] != report_path.stat().st_size:
        raise ValueError('REA final file metadata differs from the full report')
    rea_digest = entries[0]['sha256']
    if rea_digest is not None and rea_digest != report_sha:
        raise ValueError('Full report differs from REA final file digest')
    files = [(report_path, 'runtime/summary.json'), (observation_path, 'runtime/original/observation.json')]
    for name in ('scenario.json', 'evidence.json', 'summary.json', 'rea.log'):
        source = capture / name
        if source.is_file():
            files.append((source, 'rea/' + name))
    for name in ('wine.log', 'reader.log'):
        source = observation_path.parent / name
        if source.is_file():
            files.append((source, 'runtime/original/' + name))
    metadata = dict(status='sealed', diagnostic_status=report['status'], evidence_id=evidence['evidence_id'],
                    rea_exit=exit_state, report_sha256=report_sha, reader_sha256=frozen['reader_sha256'],
                    rea_binds_full_report_digest=rea_digest is not None,
                    limitations=['Original-only control; reconstructed products and whole-game fidelity remain separate.',
                                 'REA filesystem hash budget may omit a large report digest; this archive hashes its complete bytes.'])
    metadata['archive_inputs'] = {name: digest(source) for source, name in files}
    if (metadata['archive_inputs']['runtime/summary.json'] != report_sha
            or metadata['archive_inputs']['rea/evidence.json'] != capture_summary['evidence_sha256']
            or metadata['archive_inputs']['rea/scenario.json'] != capture_summary['scenario_sha256']):
        raise ValueError('Validated capture/report changed while preparing the archive')
    return files, metadata


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--attempt', type=Path, required=True)
    parser.add_argument('--capture', type=Path, required=True)
    args = parser.parse_args()
    attempt, capture = args.attempt.resolve(), args.capture.resolve()
    attempt.relative_to(ROOT / '.analysis/checkpoints')
    capture.relative_to(ROOT / 'build/reports/rea-process')
    # Fail immediately for a live attempt, before acquiring the shared writer lock.
    validate(ROOT, attempt, capture)
    with (ROOT / '.tools/compiler-session.lock').open('a') as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise ValueError('Another compiler/analysis session is active; sealing must wait') from error
        files, metadata = validate(ROOT, attempt, capture)
        destination = attempt / 'sealed'
        if destination.exists() or (attempt / 'sha256.json').exists():
            raise ValueError('Attempt is already sealed; do not overwrite retained evidence')
        with tempfile.TemporaryDirectory(prefix='.seal-', dir=attempt) as temporary:
            staging = Path(temporary) / 'sealed'
            staging.mkdir()
            for source, name in files:
                expected = metadata['archive_inputs'][name]
                checked(source, expected)
                target = staging / name
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(source, target)
                checked(target, expected)
                checked(source, expected)
            (staging / 'checkpoint.json').write_text(json.dumps(metadata, indent=2) + '\n')
            staging.rename(destination)
        hashes = {str(path.relative_to(attempt)): digest(path)
                  for path in sorted(attempt.rglob('*')) if path.is_file()}
        manifest = attempt / 'sha256.json'
        manifest.write_text(json.dumps(hashes, indent=2) + '\n')
        print(json.dumps(dict(**metadata, archive_files=len(hashes)), indent=2))


if __name__ == '__main__':
    try:
        main()
    except (OSError, ValueError, KeyError) as error:
        print('Campaign sealing refused:', error, file=sys.stderr)
        raise SystemExit(1)
