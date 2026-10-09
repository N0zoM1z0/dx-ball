#!/usr/bin/env python3
"""Build and compare the standalone CRT termination owner with original x86.

The returning ExitProcess boundary records arguments and callback state; it
does not execute Windows process termination or replace the host's own CRT.
"""
if not __debug__:
    raise RuntimeError('Termination comparisons require nonoptimized Python')

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
from legacy_toolchain import session_lock
from resource_limits import limit_cpu


def sha(path):
    with Path(path).open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def compiler_inputs(compiler, linked=False):
    paths = {compiler}
    for name in ('cc1', 'as', 'collect2', 'ld'):
        value = subprocess.check_output([str(compiler), '-print-prog-name=' + name], text=True).strip()
        path = Path(value) if Path(value).is_file() else Path(shutil.which(value))
        paths.add(path.resolve())
    if linked:
        for name in ('crtbeginS.o', 'crtendS.o', 'crti.o', 'crtn.o', 'libgcc.a', 'libgcc_s.so', 'libc.so'):
            path = Path(subprocess.check_output([str(compiler), '-print-file-name=' + name], text=True).strip())
            assert path.is_file(), path
            paths.add(path.resolve())
    return {str(path): sha(path) for path in sorted(paths)}


def compare(original, maintained):
    from termination_oracle import fixtures
    counts = Counter()
    projection = hashlib.sha256()
    for index, recipe in enumerate(fixtures()):
        original.reset(recipe)
        maintained.reset(recipe)
        expected, actual = original.run(), maintained.run()
        assert actual == expected, (index, recipe, expected, actual)
        counts[recipe['name']] += recipe.get('repeat', 1)
        projection.update(json.dumps(dict(recipe=recipe, result=expected), sort_keys=True,
                                     separators=(',', ':')).encode() + b'\n')
    return dict(cases=dict(counts), total=sum(counts.values()), fixtures=index + 1,
                observations_sha256=projection.hexdigest())


def inputs():
    # Freeze the actual imported Python source/cache and native engine images,
    # in addition to this owner's declared source and target manifest.
    paths = {ROOT / name for name in ('src/termination.c', 'src/termination.h',
             'tests/termination_oracle.py', 'tests/test_termination_differential.py',
             'tests/target_oracle.py', 'scripts/repo-python', 'config/target.toml')}
    paths.add(Path(sys.executable).resolve())
    for module in tuple(sys.modules.values()):
        for attr in ('__file__', '__cached__'):
            value = getattr(module, attr, None)
            if value and Path(value).is_file():
                paths.add(Path(value).resolve())
    for line in Path('/proc/self/maps').read_text().splitlines():
        path = line.split()[-1]
        if path.startswith('/') and Path(path).is_file():
            paths.add(Path(path).resolve())
    return {str(path): sha(path) for path in sorted(paths)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/reports/termination-differential.json')
    parser.add_argument('--source-check', action='store_true')
    parser.add_argument('--compile-only', action='store_true')
    args = parser.parse_args()
    if args.source_check:
        import ast
        ast.parse((ROOT / 'tests/termination_oracle.py').read_text())
        print('Termination oracle source parses; no runtime acceptance claimed')
        return
    output = args.output.resolve()
    assert output.is_relative_to(ROOT / 'build/reports') or output.is_relative_to(ROOT / '.analysis')
    assert not output.is_relative_to(ROOT / '.analysis/checkpoints')
    limit_cpu()
    with session_lock():
        library = args.library.resolve() if args.library else ROOT / 'build/probes/termination/libtermination.so'
        compiled = {}
        build_inputs = {str(ROOT / n): sha(ROOT / n) for n in ('src/termination.c', 'src/termination.h')}
        if not args.library:
            library.parent.mkdir(parents=True, exist_ok=True)
            compiler = Path(shutil.which('cc')).resolve()
            build_inputs.update(compiler_inputs(compiler, linked=True))
            command = [str(compiler), '-std=c90', '-Wall', '-Wextra', '-Wpedantic', '-Werror',
                       '-O2', '-fPIC', '-shared', str(ROOT / 'src/termination.c'), '-o', str(library)]
            compiled = dict(command=command, compiler_sha256=sha(compiler))
            result = subprocess.run(command, capture_output=True, text=True)
            (library.parent / 'native-compiler.log').write_text(result.stdout + result.stderr)
            result.check_returncode()
        for name, digest in build_inputs.items():
            assert sha(name) == digest, name
        if args.compile_only:
            print('Standalone termination C90 build:', sha(library))
            return
        # Load all fixture definitions before freezing import identities.
        import unicorn.unicorn_py3.arch.intel
        from termination_oracle import Native, Target
        original = Target()
        maintained = Native(library)
        frozen = inputs()
        frozen.update(build_inputs)
        frozen[str(library)] = sha(library)
        report = dict(status='running', inputs=frozen, target_sha256=original.target_sha256,
                      library_sha256=sha(library), compiler=compiled,
                      limitations=['Controlled returning callbacks and ExitProcess; no physical exit or full CRT initialization.',
                                   'Same-array valid bounds and finite mutations; no dangling tables, arithmetic wrap or nonterminating callbacks.',
                                   'Standalone owner is not connected to the experimental game or host CRT.'])
        output.parent.mkdir(parents=True, exist_ok=True)
        try:
            report.update(compare(original, maintained))
            for name, digest in frozen.items():
                assert sha(name) == digest, name
            report['status'] = 'pass'
        except BaseException as exc:
            report.update(status='fail', error=str(exc))
            raise
        finally:
            output.write_text(json.dumps(report, indent=2) + '\n')
        print('CRT termination original/native:', report['cases'], report['total'])


if __name__ == '__main__':
    main()
