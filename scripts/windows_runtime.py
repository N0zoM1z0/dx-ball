"""Isolated working data for real i686 Windows game execution."""
import csv
import hashlib
import os
from pathlib import Path
import shutil
import subprocess

from legacy_toolchain import ROOT, Toolchain

PROFILES = ('vc40', 'windows-i686')


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def verified_originals():
    with (ROOT / 'config/assets.csv').open() as stream:
        entries = list(csv.DictReader(stream))
    result = {}
    for entry in entries:
        name = entry['filename']
        if Path(name).name != name:
            raise ValueError('Asset name must be a basename: ' + name)
        path = ROOT / 'original' / name
        if path.stat().st_size != int(entry['size']) or digest(path) != entry['sha256']:
            raise ValueError('Original asset identity mismatch: ' + name)
        result[name] = entry['sha256']
    return result


def copy_file(source, destination):
    if destination.is_symlink():
        raise ValueError('Refusing a runtime symlink: ' + str(destination))
    shutil.copyfile(source, destination)


def prepare(profile, probe=False):
    if profile not in PROFILES and not (probe and profile == 'original'):
        raise ValueError('Unknown Windows game profile: ' + profile)
    originals = verified_originals()
    directory = ROOT / 'build/runtime' / (('probe-' if probe else '') + profile)
    directory.mkdir(parents=True, exist_ok=True)
    if directory.is_symlink() or directory.resolve().parent != (ROOT / 'build/runtime').resolve():
        raise ValueError('Runtime directory must be an isolated child of build/runtime')
    for name in originals:
        if Path(name).suffix.lower() == '.exe':
            continue
        destination = directory / name
        # Manual runs preserve score/editor saves; probes reset only their own fixtures.
        aliases = [path for path in directory.iterdir() if path.name.casefold() == name.casefold()]
        if any(path.is_symlink() for path in aliases):
            raise ValueError('Refusing a runtime asset symlink: ' + name)
        if probe:
            for path in aliases:
                if path != destination:
                    path.unlink()
        elif len(aliases) > 1:
            raise ValueError('Ambiguous Windows filename aliases: ' + name)
        if probe or not aliases:
            copy_file(ROOT / 'original' / name, destination)
    source = ROOT / ('original/DXBALL.EXE' if profile == 'original'
                     else 'build/' + profile + '/dxball.exe')
    copy_file(source, directory / 'dxball.exe')
    if profile == 'windows-i686':
        copy_file(ROOT / 'build/windows-i686/libdxball_core.dll', directory / 'libdxball_core.dll')
    return directory, originals


def environment():
    return Toolchain().env


def launch(directory, env, log):
    return subprocess.Popen(['wine', str(directory / 'dxball.exe')], cwd=directory,
                            env=env, stdout=log, stderr=log, start_new_session=True)


def stop(process):
    if process.poll() is None:
        import signal
        os.killpg(process.pid, signal.SIGTERM)
        try:
            process.wait(timeout=10)
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait(timeout=10)
