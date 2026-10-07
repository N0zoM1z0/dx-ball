#!/usr/bin/env python3
"""Build the i686 Windows inspectors and game with one compiler session/CPU."""
import argparse
import subprocess
from legacy_toolchain import ROOT, session_lock
from resource_limits import BUILD_JOBS, limit_cpu
from windows_resources import prepare_game_resources


def main():
    limit_cpu()
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--without-game-resources', action='store_true',
                        help='source-only public compile check; original resources are omitted')
    args = parser.parse_args()
    lock = session_lock()
    resource = ''
    if not args.without_game_resources:
        resource, _ = prepare_game_resources('windows-i686')
    subprocess.run(['cmake', '-S', '.', '-B', 'build/windows-i686', '-G', 'Ninja',
                    '-DCMAKE_TOOLCHAIN_FILE=config/mingw-i686.cmake',
                    '-DCMAKE_BUILD_TYPE=Release',
                    '-DDXBALL_RESOURCE_OBJECT=' + str(resource)], cwd=ROOT, check=True)
    subprocess.run(['cmake', '--build', 'build/windows-i686', '--parallel', str(BUILD_JOBS)],
                   cwd=ROOT, check=True)


if __name__ == '__main__':
    main()
