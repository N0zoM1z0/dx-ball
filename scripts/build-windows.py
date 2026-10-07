#!/usr/bin/env python3
"""Build the i686 Windows inspectors and game with one compiler session/CPU."""
import subprocess
from legacy_toolchain import ROOT, session_lock
from resource_limits import BUILD_JOBS, limit_cpu


def main():
    limit_cpu()
    lock = session_lock()
    subprocess.run(['cmake', '-S', '.', '-B', 'build/windows-i686', '-G', 'Ninja',
                    '-DCMAKE_TOOLCHAIN_FILE=config/mingw-i686.cmake',
                    '-DCMAKE_BUILD_TYPE=Release'], cwd=ROOT, check=True)
    subprocess.run(['cmake', '--build', 'build/windows-i686', '--parallel', str(BUILD_JOBS)],
                   cwd=ROOT, check=True)


if __name__ == '__main__':
    main()
