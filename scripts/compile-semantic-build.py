#!/usr/bin/env python3
"""Cold-build a configured VC4 product for generated-code semantic execution."""
import argparse
import json
from pathlib import Path
import tomllib

from legacy_toolchain import ROOT, Toolchain, session_lock, sha256


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build', required=True, help='configured builds table entry')
    args = parser.parse_args()
    with session_lock():
        driver_sha = sha256(Path(__file__))
        toolchain = Toolchain()
        toolchain.verify(execute=True)
        manifest = ROOT / 'config/match-units.toml'
        manifest_sha = sha256(manifest)
        config = tomllib.loads(manifest.read_text())['builds'][args.build]
        inputs = {name: sha256(ROOT / name) for name in config['inputs']}
        output = ROOT / config['object']
        result = toolchain.compile(ROOT / config['source'], output, config['flags'])
        assert inputs == {name: sha256(ROOT / name) for name in config['inputs']}
        assert sha256(manifest) == manifest_sha
        assert sha256(Path(__file__)) == driver_sha
        report = dict(status='pass', object=config['object'], object_sha256=sha256(output),
                      inputs=inputs, compiler_sha256=toolchain.lock['compiler_sha256'],
                      flags=config['flags'], manifest_sha256=manifest_sha,
                      driver_sha256=driver_sha,
                      scope='Configured shared-source compiler product; no exactness claim')
        directory = ROOT / 'build/reports'
        directory.mkdir(parents=True, exist_ok=True)
        (directory / (args.build + '-compile.json')).write_text(json.dumps(report, indent=2) + '\n')
        output.with_suffix('.log').write_text(result.stdout)
        print('Semantic compiler build:', args.build, report['object_sha256'])


if __name__ == '__main__':
    main()
