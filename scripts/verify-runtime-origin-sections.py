#!/usr/bin/env python3
"""Verify bounded CRT origins by complete code sections and grounded relocations."""
import argparse
import hashlib
import json
from importlib.util import spec_from_file_location, module_from_spec
from pathlib import Path

from coff import parse, region, _relocations
from crt_library import members, relocate
from legacy_toolchain import Toolchain, session_lock
from resource_limits import limit_cpu

ROOT = Path(__file__).resolve().parents[1]


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/reports/runtime-origin-sections.json')
    args = parser.parse_args()
    with session_lock():
        Toolchain().verify()
        manifest_path = ROOT / 'config/runtime-origin-sections.json'
        manifest = json.loads(manifest_path.read_text())
        original = ROOT / 'original/DXBALL.EXE'
        library = ROOT / manifest['library']
        if digest(original) != manifest['target_sha256'] or digest(library) != manifest['library_sha256']:
            raise ValueError('origin target/library identity mismatch')
        spec = spec_from_file_location('crt_provenance', ROOT / 'scripts/verify-crt-provenance.py')
        crt = module_from_spec(spec)
        spec.loader.exec_module(crt)
        _, observations, _ = crt.observations(ROOT / '.analysis/rea/runs', manifest['target_sha256'], manifest['provider'])
        requested = manifest['byte_observation']
        base = int(requested['address'], 0)
        evidence_path, observed, evidence_hash = observations[base, requested['size']]
        if observed['evidence_id'] != requested['evidence_id']:
            raise ValueError('unexpected original-byte Evidence ID')
        loaded = bytes.fromhex(observed['result']['bytes_hex'])
        prior_path = ROOT / manifest['prior_binding_manifest']
        prior = json.loads(prior_path.read_text())
        if prior['target_sha256'] != manifest['target_sha256'] or prior['provider'] != manifest['provider']:
            raise ValueError('prior relocation map belongs to another target/provider')
        fixed = {name: int(value, 0) for name, value in prior['relocations'].items()}
        selected = {s['member_header_offset'] for s in manifest['sections']}
        raw_members = {offset: (name, raw) for offset, name, raw in members(library) if offset in selected}
        inputs = {str(p.relative_to(ROOT)): digest(p) for p in (
            manifest_path, prior_path, original, library, ROOT / 'scripts/verify-runtime-origin-sections.py',
            ROOT / 'scripts/verify-crt-provenance.py', ROOT / 'scripts/crt_library.py', ROOT / 'scripts/coff.py',
            ROOT / 'scripts/legacy_toolchain.py', ROOT / 'scripts/resource_limits.py',
            ROOT / 'scripts/repo-python', ROOT / 'scripts/verify-python.py',
            ROOT / 'config/tools.lock.toml', ROOT / 'requirements-analysis.txt',
            evidence_path.parent / 'close.json')}
        inputs[str(evidence_path.relative_to(ROOT))] = evidence_hash
        results = []
        for entry in manifest['sections']:
            address = int(entry['address'], 0)
            name, raw = raw_members[entry['member_header_offset']]
            if name != entry['member'] or hashlib.sha256(raw).hexdigest() != entry['member_sha256']:
                raise ValueError('selected member identity changed')
            obj = ROOT / 'build/probes/runtime-origin-sections' / f"{entry['member_header_offset']:08x}.obj"
            obj.parent.mkdir(parents=True, exist_ok=True)
            obj.write_bytes(raw)
            data, sections, symbols = parse(obj)
            index = entry['section_index']
            if not 1 <= index <= len(sections):
                raise ValueError('missing code section')
            section = sections[index - 1]
            if not section['flags'] & 0x20 or not section['data'] or section['size'] != entry['size']:
                raise ValueError('whole code section identity/size mismatch')
            code = region(data, section['data'], section['size'])
            rels = _relocations(data, section, symbols, code)
            local = {s['name']: address + s['value'] for s in symbols.values() if s['section'] == index}
            if any(s['value'] > len(code) for s in symbols.values() if s['section'] == index):
                raise ValueError('defined symbol exceeds the selected code section')
            if any(n in fixed and fixed[n] != a for n, a in local.items()):
                raise ValueError('local definition contradicts the prior relocation map')
            mapping = {**fixed, **local}
            linked = relocate(code, rels, address, mapping)
            if not base <= address <= base + len(loaded) - len(linked):
                raise ValueError('whole section exceeds the complete REA read')
            target = loaded[address-base:address-base+len(linked)]
            if linked != target:
                raise ValueError('whole relocated code section differs: ' + entry['address'])
            for candidate in entry['entries']:
                if not address <= int(candidate, 0) < address + len(linked):
                    raise ValueError('claimed origin entry lies outside the matched section')
            inputs[str(obj.relative_to(ROOT))] = digest(obj)
            results.append(dict(**entry, status='same', difference_count=0,
                code_sha256=hashlib.sha256(linked).hexdigest(), relocations=rels,
                applied_bindings={r['symbol']: dict(address=hex(mapping[r['symbol']]),
                    basis='section-defined symbol' if r['symbol'] in local else 'reviewed prior CRT map') for r in rels}))
        for path, hashed in inputs.items():
            if digest(ROOT / path) != hashed:
                raise ValueError('origin input changed during verification: ' + path)
        report = dict(status='pass', target_sha256=manifest['target_sha256'],
            original_byte_evidence_id=observed['evidence_id'], inputs=inputs,
            complete_sections=len(results), complete_section_bytes=sum(r['size'] for r in results),
            origin_entries=len({a for r in results for a in r['entries']}),
            results=results, limitations=manifest['limitations'])
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + '\n')
        print('runtime origin sections:', report['complete_sections'], 'complete sections;',
              report['complete_section_bytes'], 'bytes;', report['origin_entries'], 'entries')


if __name__ == '__main__':
    main()
