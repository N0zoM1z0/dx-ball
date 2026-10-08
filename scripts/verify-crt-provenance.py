#!/usr/bin/env python3
"""Compare complete pinned CRT sections with retained REA observations."""
import argparse
import hashlib
import json
from pathlib import Path
import tomllib

from crt_library import extract, function_section, relocate
from legacy_toolchain import ROOT, Toolchain, session_lock
from resource_limits import limit_cpu


def digest(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def observations(root, target, provider):
    bodies, byte_records, close_hashes = {}, {}, {}
    for run in sorted(root.iterdir()):
        if not run.is_dir() or not (run / 'close.json').is_file():
            continue
        close_hashes[run / 'close.json'] = digest(run / 'close.json')
        for path in sorted(run.glob('*.json')):
            if not any(word in path.name for word in ('analyze_function', 'read_bytes')):
                continue
            if path.stat().st_size > 2 * 1024 * 1024:
                continue
            raw = path.read_bytes()
            record = json.loads(raw)
            parsed_sha256 = hashlib.sha256(raw).hexdigest()
            evidence = record.get('evidence', {})
            if (evidence.get('subject', {}).get('digest', {}).get('sha256') != target
                    or evidence.get('provider') != provider
                    or evidence.get('analysis_profile', {}).get('provider') != provider):
                continue
            result = record.get('result', {})
            if 'analyze_function' in path.name:
                procedure = result.get('procedure', {})
                address = procedure.get('address')
                body = procedure.get('body', {})
                if address and body.get('available'):
                    bodies[int(address, 0)] = (path, record, parsed_sha256)
            elif result.get('complete'):
                address = int(result['address'], 0)
                size = result['requested_bytes']
                if result['returned_bytes'] != size or len(bytes.fromhex(result['bytes_hex'])) != size:
                    raise ValueError('inconsistent complete REA byte observation')
                byte_records[address, size] = (path, record, parsed_sha256)
    return bodies, byte_records, close_hashes


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-root', type=Path, default=ROOT / '.analysis/rea/runs',
                        help='repository-contained closed REA runs')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/reports/crt-provenance.json')
    args = parser.parse_args()
    args.evidence_root = args.evidence_root.resolve()
    args.evidence_root.relative_to(ROOT)
    with session_lock():
        Toolchain().verify()
        manifest_path = ROOT / 'config/crt-provenance.json'
        manifest_bytes = manifest_path.read_bytes()
        manifest = json.loads(manifest_bytes)
        target_path = ROOT / 'original/DXBALL.EXE'
        configured_target = tomllib.loads((ROOT / 'config/target.toml').read_text())['target']['sha256']
        if digest(target_path) != manifest['target_sha256'] or manifest['target_sha256'] != configured_target:
            raise ValueError('CRT investigation target mismatch')
        bodies, byte_records, close_hashes = observations(args.evidence_root, manifest['target_sha256'], manifest['provider'])
        inputs = {str(path.relative_to(ROOT)): digest(path) for path in (
            manifest_path, ROOT / 'scripts/verify-crt-provenance.py', ROOT / 'scripts/crt_library.py',
            ROOT / 'scripts/coff.py', ROOT / 'scripts/legacy_toolchain.py', ROOT / 'scripts/resource_limits.py',
            ROOT / 'scripts/repo-python', ROOT / 'scripts/verify-python.py', ROOT / 'config/target.toml',
            ROOT / 'requirements-analysis.txt', ROOT / 'config/tools.lock.toml', target_path)}
        inputs[str(manifest_path.relative_to(ROOT))] = hashlib.sha256(manifest_bytes).hexdigest()
        mapping = {name: int(value, 0) for name, value in manifest['relocations'].items()}
        results = []
        for entry in manifest['entries']:
            address, size = int(entry['address'], 0), entry['size']
            body_path, dossier, body_sha256 = bodies[address]
            body = dossier['result']['procedure']['body']
            if (body['total_bytes'] != size or body['span_bytes'] != size
                    or body['non_contiguous'] or not body['contains_entry']
                    or body['ranges'] != [dict(start=hex(address), end=hex(address + size - 1))]):
                raise ValueError('unreconciled target extent: ' + entry['address'])
            bytes_path, observed, bytes_sha256 = byte_records[address, size]
            target_code = bytes.fromhex(observed['result']['bytes_hex'])
            inputs[str(body_path.relative_to(ROOT))] = body_sha256
            inputs[str(bytes_path.relative_to(ROOT))] = bytes_sha256
            for path in (body_path.parent / 'close.json', bytes_path.parent / 'close.json'):
                inputs[str(path.relative_to(ROOT))] = close_hashes[path]
            comparisons = []
            for name in manifest['libraries']:
                library = ROOT / '.tools/msvc400/lib' / name
                inputs[str(library.relative_to(ROOT))] = digest(library)
                obj, identity = extract(library, entry['symbol'], ROOT / 'build/probes/crt-provenance' / library.stem)
                code, relocations = function_section(obj, entry['symbol'])
                inputs[str(obj.relative_to(ROOT))] = digest(obj)
                row = dict(library=name, library_sha256=digest(library), object_sha256=digest(obj),
                           symbol=entry['symbol'], object_bytes=len(code), **identity)
                if len(code) != size:
                    row.update(status='different', reason='whole-section-size', difference_count=None)
                else:
                    linked = relocate(code, relocations, address, mapping)
                    differences = [index for index, pair in enumerate(zip(linked, target_code)) if pair[0] != pair[1]]
                    row.update(status='same' if not differences else 'different', reason='whole-section-bytes',
                               difference_count=len(differences), difference_offsets=differences,
                               relocations=relocations, linked_sha256=hashlib.sha256(linked).hexdigest())
                comparisons.append(row)
            if comparisons[0]['library'] != 'libc.lib' or comparisons[0]['status'] != 'same':
                raise ValueError('expected whole libc section agreement: ' + entry['address'])
            results.append(dict(**entry, body_evidence_id=dossier['evidence_id'],
                                byte_evidence_id=observed['evidence_id'], target_bytes_sha256=hashlib.sha256(target_code).hexdigest(),
                                comparisons=comparisons))
        for name, hashed in inputs.items():
            if digest(ROOT / name) != hashed:
                raise ValueError('provenance input changed during comparison: ' + name)
        report = dict(status='pass', target_sha256=manifest['target_sha256'], inputs=inputs,
                      matched_libc_functions=len(results), matched_libc_bytes=sum(x['size'] for x in results),
                      library_comparisons=sum(len(x['comparisons']) for x in results), results=results,
                      limitations=['Library-origin comparisons do not add maintained C, semantic cases or exact units.',
                                   'All relocation operands are applied explicitly; no byte masking or prefix comparison.',
                                   'Matching a batch does not establish the whole executable build configuration.',
                                   'Host dependency bridges and physical Windows services remain separately scoped.'])
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2)+'\n')
        print('CRT provenance:',len(results),'whole functions;',report['matched_libc_bytes'],'bytes;',report['library_comparisons'],'library comparisons')


if __name__ == '__main__':
    main()
