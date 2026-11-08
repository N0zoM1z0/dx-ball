#!/usr/bin/env bash
set -euo pipefail

repo_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
data_dir="$repo_dir/build/native/game-data"
game="$repo_dir/build/native/dxball_linux"

if [[ ! -x "$game" ]]; then
    echo "Build the native game first: cmake -S . -B build/native -G Ninja -DDXBALL_BUILD_LINUX_GAME=ON && cmake --build build/native --target dxball_linux --parallel 1" >&2
    exit 1
fi

mkdir -p "$data_dir"
for source in "$repo_dir"/original/*; do
    [[ -f "$source" ]] || continue
    name="${source##*/}"
    target="$data_dir/${name,,}"
    [[ -e "$target" ]] || cp -- "$source" "$target"
done

exec "$game" "$data_dir"
