#!/usr/bin/env python3
"""Remove superseded probes and redundant REA aliases; preserve archived evidence."""
import argparse
import hashlib
import json
import os
from datetime import datetime, timezone
from pathlib import Path

from legacy_toolchain import ROOT, session_lock
from resource_limits import limit_cpu


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def regular(path):
    return path.is_file() and not path.is_symlink()


def plan():
    runs = ROOT / '.analysis/rea/runs'
    actions, closed_records = [], {}
    # The download is a cache, not an installed REA/Ghidra input. Require both
    # its original archive identity and a fully attested installation first.
    lock = json.loads((ROOT / 'config/rea.lock.json').read_text())
    archive = ROOT / '.tools' / lock['ghidra']['asset']
    if regular(archive) and digest(archive) == lock['ghidra']['archive_sha256']:
        from rea import environment
        environment()
        actions.append(('remove_download_cache', archive, None,
                        lock['ghidra']['archive_sha256']))
    # Closed runs retain immutable records. Share complete byte-identical JSON
    # without removing a path, Evidence ID, or unique observation. Mutable root
    # aliases and snapshots are deliberately outside this loop.
    for path in sorted(runs.glob('*/*.json')):
        if not regular(path) or not regular(path.parent / 'close.json'):
            continue
        key = (path.stat().st_size, digest(path))
        keeper = closed_records.setdefault(key, path)
        if path != keeper and not os.path.samefile(path, keeper):
            actions.append(('hardlink', path, keeper, key[1]))
    # Root aliases are mutable: never hardlink them to an immutable archive.
    for path in sorted((ROOT / '.analysis/rea').glob('[0-9][0-9]-*.json')):
        if not regular(path):
            continue
        hashed = digest(path)
        for archived in sorted(runs.glob('*/' + path.name)):
            if (regular(archived) and regular(archived.parent / 'close.json')
                    and archived.stat().st_size == path.stat().st_size
                    and digest(archived) == hashed):
                actions.append(('remove_alias', path, archived, hashed))
                break
    # Only disposable compiler outputs in established probe directories.
    for directory in (ROOT / 'build/probes', ROOT / '.analysis/probe-powerups'):
        for path in sorted(directory.rglob('*')):
            if regular(path) and path.suffix in ('.obj', '.log'):
                actions.append(('remove_probe', path, None, digest(path)))
    # These are resettable test fixtures, never the manual run directories/saves.
    for profile in ('original', 'vc40', 'windows-i686'):
        directory = ROOT / 'build/runtime' / ('probe-' + profile)
        if directory.is_symlink():
            continue
        for path in sorted(directory.glob('*')):
            if regular(path):
                actions.append(('remove_runtime_probe', path, None, digest(path)))
    return actions


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--apply', action='store_true', help='apply the reviewed cleanup')
    args = parser.parse_args()
    lock = session_lock()
    actions = plan()
    entries = []
    for operation, path, keeper, hashed in actions:
        entries.append(dict(operation=operation, path=str(path.relative_to(ROOT)),
                            keeper=str(keeper.relative_to(ROOT)) if keeper else None,
                            sha256=hashed, bytes=path.stat().st_size))
        if not args.apply:
            continue
        if digest(path) != hashed or (keeper and digest(keeper) != hashed):
            raise RuntimeError('Cleanup input changed: ' + str(path))
        if operation == 'hardlink':
            temporary = path.with_name(path.name + '.cleanup-' + str(os.getpid()))
            os.link(keeper, temporary)
            try:
                os.replace(temporary, path)
            finally:
                temporary.unlink(missing_ok=True)
        else:
            path.unlink()
    report = dict(applied=args.apply, operations=entries,
                  removed_duplicate_or_probe_bytes=sum(item['bytes'] for item in entries))
    print(json.dumps(dict(applied=args.apply, operations=len(entries),
                          recoverable_mib=round(report['removed_duplicate_or_probe_bytes'] / 2**20, 2))))
    if args.apply:
        directory = ROOT / '.analysis/cleanup'
        directory.mkdir(parents=True, exist_ok=True)
        stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S%fZ')
        destination = directory / (stamp + '.json')
        destination.write_text(json.dumps(report, indent=2) + '\n')
        print('Journal:', destination.relative_to(ROOT))
    else:
        for item in entries:
            print(item['operation'], item['path'])


if __name__ == '__main__':
    main()
