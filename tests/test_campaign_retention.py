#!/usr/bin/env python3
"""Check campaign archival identity gates with synthetic files, without Wine."""
import contextlib
import copy
import fcntl
import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import sys
import tempfile
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
spec = importlib.util.spec_from_file_location('seal_campaign', ROOT / 'scripts/seal-original-campaign.py')
sealer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sealer)


def write(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + '\n')


def fixture(root):
    attempt = root / '.analysis/checkpoints/control'
    capture = root / 'build/reports/rea-process/capture'
    attempt.mkdir(parents=True)
    capture.mkdir(parents=True)
    reader = b'owned synthetic SDK product'
    source = b'owned synthetic harness'
    name = 'tests/test_windows_campaign.py'
    (attempt / name).parent.mkdir(parents=True)
    (attempt / name).write_bytes(source)
    (attempt / 'campaign-reader.exe').write_bytes(reader)
    actual_reader = root / 'build/probes/windows-runtime/campaign-reader.exe'
    actual_reader.parent.mkdir(parents=True)
    actual_reader.write_bytes(reader)
    inputs = {name: hashlib.sha256(source).hexdigest()}
    frozen = dict(profiles=['original'], seconds=7200, boards=50, inputs=inputs,
                  reader_sha256=hashlib.sha256(reader).hexdigest(), boot_id='owned-test-boot',
                  process_identities={'wine_game_pid': dict(pid=100, start_ticks=1),
                                      'reader_pid': dict(pid=101, start_ticks=2)})
    write(attempt / 'attempt.json', frozen)
    originals = {}
    for name, data in (('DXBALL.EXE', b'owned synthetic game'), ('DEFAULT.BDS', b'owned synthetic bank')):
        path = root / 'original' / name
        path.parent.mkdir(exist_ok=True)
        path.write_bytes(data)
        originals[name] = hashlib.sha256(data).hexdigest()
        working = root / 'build/runtime/probe-original' / ('dxball.exe' if name == 'DXBALL.EXE' else name)
        working.parent.mkdir(parents=True, exist_ok=True)
        working.write_bytes(data)
    observation = dict(profile='original', status='campaign-pass', bank_unchanged=True,
                       originals_unchanged=True, initialized_board_indices=list(range(50)),
                       executable_sha256=originals['DXBALL.EXE'], bank_input_sha256=originals['DEFAULT.BDS'],
                       last_state=dict(board_index=50, display_mode=0, end_requested=0,
                                       device_reset_requested=0, return_to_menu=0))
    report = dict(status='campaign-pass', inputs=inputs, reader_sha256=frozen['reader_sha256'],
                  goal_board_count=50, episode_seconds=0, originals=originals, observations=[observation])
    scenario = dict(executable=str(root / 'scripts/repo-python'), working_directory=str(root),
                    arguments=[str(root / 'tests/test_windows_campaign.py'), '--profiles', 'original',
                               '--seconds', '7200', '--boards', '50', '--episode-seconds', '0'],
                    filesystem_observation_paths=[str(root / 'build/reports/windows-campaign/summary.json')])
    evidence = dict(operation='capture_process_scenario', evidence_id='ev_owned_test', normalized_result=dict(
        manifest=dict(scenario=scenario), exit=dict(reason='exited', code=0), files_after=[]))
    sync(root, capture, report, observation, scenario, evidence)
    return attempt, capture, report, observation, scenario, evidence


def sync(root, capture, report, observation, scenario, evidence, missing_digest=False):
    output = root / 'build/reports/windows-campaign/summary.json'
    write(output, report)
    write(output.parent / 'original/observation.json', observation)
    write(capture / 'scenario.json', scenario)
    evidence['normalized_result']['files_after'] = [dict(path='root_0:.', type='file',
        size=output.stat().st_size, sha256=None if missing_digest else sealer.digest(output))]
    write(capture / 'evidence.json', evidence)
    write(capture / 'summary.json', dict(evidence_id=evidence['evidence_id'],
          exit=evidence['normalized_result']['exit'], evidence_sha256=sealer.digest(capture / 'evidence.json'),
          scenario_sha256=sealer.digest(capture / 'scenario.json')))


def reject(root, attempt, capture, label, is_live=lambda *_: False):
    before = sorted(str(p.relative_to(attempt)) for p in attempt.rglob('*') if p.is_file())
    try:
        sealer.validate(root, attempt, capture, is_live)
    except ValueError:
        pass
    else:
        raise AssertionError('Accepted invalid retention: ' + label)
    after = sorted(str(p.relative_to(attempt)) for p in attempt.rglob('*') if p.is_file())
    assert before == after, 'Rejected validation mutated the frozen attempt'


def main():
    assert __debug__, 'Retention assertions must stay enabled'
    from resource_limits import limit_cpu
    limit_cpu()
    cases = 0
    with tempfile.TemporaryDirectory() as temporary:
        root = Path(temporary)
        attempt, capture, report, observation, scenario, evidence = fixture(root)
        files, metadata = sealer.validate(root, attempt, capture, lambda *_: False)
        assert metadata['rea_binds_full_report_digest'] and len(files) == 5
        reject(root, attempt, capture, 'live process', lambda *_: True)
        cases += 2
        reader = root / 'build/probes/windows-runtime/campaign-reader.exe'
        saved = reader.read_bytes()
        reader.write_bytes(b'overwritten reader')
        reject(root, attempt, capture, 'overwritten SDK product')
        reader.write_bytes(saved)
        copied = attempt / 'tests/test_windows_campaign.py'
        saved = copied.read_bytes()
        copied.write_bytes(b'changed frozen input')
        reject(root, attempt, capture, 'changed frozen source')
        copied.write_bytes(saved)
        cases += 2
        bad = copy.deepcopy(report)
        bad['inputs']['extra.py'] = '0' * 64
        sync(root, capture, bad, observation, scenario, evidence)
        reject(root, attempt, capture, 'different complete input set')
        cases += 1
        for field, value in (('board_index', 49), ('display_mode', 1), ('end_requested', 1),
                             ('device_reset_requested', 1), ('return_to_menu', 1)):
            bad_observation = copy.deepcopy(observation)
            bad_observation['last_state'][field] = value
            bad_report = dict(report, observations=[bad_observation])
            sync(root, capture, bad_report, bad_observation, scenario, evidence)
            reject(root, attempt, capture, 'missing terminal predicate: ' + field)
            cases += 1
        bad_observation = dict(observation, initialized_board_indices=list(range(49)))
        sync(root, capture, dict(report, observations=[bad_observation]), bad_observation, scenario, evidence)
        reject(root, attempt, capture, 'missing original board')
        cases += 1
        for field in ('bank_unchanged', 'originals_unchanged'):
            bad_observation = dict(observation, **{field: False})
            sync(root, capture, dict(report, observations=[bad_observation]), bad_observation, scenario, evidence)
            reject(root, attempt, capture, 'modified game input: ' + field)
            cases += 1
        sync(root, capture, report, observation, scenario, evidence)
        bad_evidence = copy.deepcopy(evidence)
        bad_evidence['normalized_result']['exit']['code'] = 1
        sync(root, capture, report, observation, scenario, bad_evidence)
        reject(root, attempt, capture, 'child failure contradicts campaign pass')
        cases += 1
        bad_observation = dict(observation, status='fail', error='owned controller failure')
        bad_report = dict(report, status='fail', error=bad_observation['error'], observations=[])
        sync(root, capture, bad_report, bad_observation, scenario, bad_evidence)
        _, result = sealer.validate(root, attempt, capture, lambda *_: False)
        assert result['diagnostic_status'] == 'fail'
        cases += 1
        oversized = dict(report, retained_test_data='owned synthetic bytes ' * 10000)
        sync(root, capture, oversized, observation, scenario, evidence, missing_digest=True)
        files, metadata = sealer.validate(root, attempt, capture, lambda *_: False)
        assert not metadata['rea_binds_full_report_digest']
        assert metadata['report_sha256'] == sealer.digest(files[0][0])
        cases += 1
        write(root / 'build/reports/windows-campaign/windows-i686/observation.json', {'status': 'stale'})
        assert all('windows-i686' not in name for _, name in files)
        cases += 1
        (root / '.tools').mkdir()
        actual_validate = sealer.validate
        with patch.object(sealer, 'ROOT', root), \
                patch.object(sealer, 'validate', side_effect=lambda r, a, c: actual_validate(r, a, c, lambda *_: False)), \
                patch.object(sys, 'argv', ['seal', '--attempt', str(attempt), '--capture', str(capture)]), \
                contextlib.redirect_stdout(io.StringIO()):
            with (root / '.tools/compiler-session.lock').open('a') as writer:
                fcntl.flock(writer, fcntl.LOCK_EX)
                try:
                    sealer.main()
                except ValueError as error:
                    assert 'session is active' in str(error)
                else:
                    raise AssertionError('Sealing acquired an already-held writer lock')
                assert not (attempt / 'sealed').exists()
                cases += 1
            validation_calls = 0
            report_path = root / 'build/reports/windows-campaign/summary.json'
            report_bytes = report_path.read_bytes()

            def change_after_validation(r, a, c):
                nonlocal validation_calls
                result = actual_validate(r, a, c, lambda *_: False)
                validation_calls += 1
                if validation_calls == 2:
                    report_path.write_bytes(report_bytes + b'\n')
                return result

            with patch.object(sealer, 'validate', side_effect=change_after_validation):
                try:
                    sealer.main()
                except ValueError as error:
                    assert 'changed evidence' in str(error)
                else:
                    raise AssertionError('Sealing copied a report changed after validation')
                assert not (attempt / 'sealed').exists() and not (attempt / 'sha256.json').exists()
                assert not list(attempt.glob('.seal-*'))
                cases += 1
            report_path.write_bytes(report_bytes)
            sealer.main()
            try:
                sealer.main()
            except ValueError as error:
                assert 'already sealed' in str(error)
            else:
                raise AssertionError('Sealing overwrote an existing immutable archive')
            cases += 1
        hashes = sealer.load(attempt / 'sha256.json')
        for name, expected in hashes.items():
            assert sealer.digest(attempt / name) == expected
        archived = attempt / 'sealed/runtime/summary.json'
        assert archived.stat().st_size > 128000 and sealer.digest(archived) == metadata['report_sha256']
        assert not sealer.load(attempt / 'sealed/checkpoint.json')['rea_binds_full_report_digest']
        cases += 1
    proc = Path('/proc') / str(os.getpid())
    start = int(proc.joinpath('stat').read_text().rsplit(') ', 1)[1].split()[19])
    boot = Path('/proc/sys/kernel/random/boot_id').read_text().strip()
    assert sealer.live(dict(pid=os.getpid(), start_ticks=start), boot)
    assert not sealer.live(dict(pid=os.getpid(), start_ticks=start + 1), boot)
    assert not sealer.live(dict(pid=os.getpid(), start_ticks=start), 'another boot')
    cases += 3
    print('PASS campaign retention:', cases, 'checks; synthetic files and Linux process identity only')


if __name__ == '__main__':
    main()
