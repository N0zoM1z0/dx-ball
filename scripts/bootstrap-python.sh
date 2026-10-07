#!/usr/bin/env bash
set -euo pipefail
repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd -P)"
bootstrap_python="${DXBALL_PYTHON:-$(command -v python3)}"
if [[ -e "$repo_root/.tools/python" ]]; then
    if "$repo_root/scripts/repo-python" "$repo_root/scripts/verify-python.py"; then
        exit 0
    fi
    printf '%s\n' 'Existing .tools/python failed attestation; move it aside before reinstalling.' >&2
    exit 1
fi
"$bootstrap_python" -m pip install --no-deps --require-hashes \
    --target "$repo_root/.tools/python" -r "$repo_root/requirements-analysis.txt"
"$repo_root/scripts/repo-python" "$repo_root/scripts/verify-python.py"
