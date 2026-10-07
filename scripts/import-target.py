#!/usr/bin/env python3
"""Import the pinned user-supplied archive, without replacing different files."""
import argparse
import csv
import hashlib
from pathlib import Path
import sys
import tomllib
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("archive", nargs="?", type=Path,
                        default=ROOT.parent / "game_exe/DX_Ball_Win_Preinstalled_EN.zip")
    args = parser.parse_args()
    manifest = tomllib.loads((ROOT / "config/target.toml").read_text())
    archive_data = args.archive.read_bytes()
    if hashlib.sha256(archive_data).hexdigest() != manifest["provenance"]["archive_sha256"]:
        raise ValueError("archive SHA-256 mismatch")
    entries = list(csv.DictReader((ROOT / "config/assets.csv").open()))
    pending = []
    # Check the whole archive and existing directory before writing any file.
    with zipfile.ZipFile(args.archive) as archive:
        for entry in entries:
            name = entry["filename"]
            if Path(name).name != name:
                raise ValueError("asset manifest contains a non-basename path")
            data = archive.read("DX_Ball_Win_Preinstalled_EN/Game Files/" + name)
            if len(data) != int(entry["size"]) or hashlib.sha256(data).hexdigest() != entry["sha256"]:
                raise ValueError(f"asset mismatch: {name}")
            path = ROOT / "original" / name
            if path.exists() and path.read_bytes() != data:
                raise ValueError(f"refusing to replace modified original: {name}")
            if not path.exists():
                pending.append((path, data))
    (ROOT / "original").mkdir(exist_ok=True)
    for path, data in pending:
        with path.open("xb") as stream:
            stream.write(data)
    print(f"verified {len(entries)} original files; imported {len(pending)}")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, KeyError, zipfile.BadZipFile) as exc:
        print(f"import failed: {exc}", file=sys.stderr)
        sys.exit(1)
