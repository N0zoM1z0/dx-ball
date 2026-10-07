#!/usr/bin/env python3
"""Run a reconstructed game with copied data, preserving private originals."""
import argparse
import subprocess
import sys
from legacy_toolchain import session_lock
from resource_limits import limit_cpu
from windows_runtime import PROFILES, environment, prepare, verified_originals


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--profile', choices=PROFILES, default='vc40')
    parser.add_argument('--prepare-only', action='store_true',
                        help='copy a Windows working directory without launching Wine')
    args = parser.parse_args()
    limit_cpu()
    lock = session_lock()
    directory, originals = prepare(args.profile)
    print('Windows game directory:', directory, flush=True)
    if args.prepare_only:
        return
    try:
        result = subprocess.run(['wine', str(directory / 'dxball.exe')], cwd=directory,
                                env=environment())
    finally:
        if verified_originals() != originals:
            raise ValueError('Original files changed during the Windows run')
    sys.exit(result.returncode)


if __name__ == '__main__':
    main()
