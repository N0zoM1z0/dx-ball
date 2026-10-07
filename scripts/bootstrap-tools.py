#!/usr/bin/env python3
"""Install pinned tools, or reuse matching Ghidra/JDK from a local tool root."""
import argparse
import hashlib
from pathlib import Path
import subprocess
import sys
import tomllib
import urllib.request

from analysis_tools import verify as verify_analysis_tools
from legacy_toolchain import ROOT, Toolchain


def download(entry, path):
    if not path.exists():
        temporary = path.with_suffix(path.suffix + ".part")
        urllib.request.urlretrieve(entry["url"], temporary)
        if hashlib.sha256(temporary.read_bytes()).hexdigest() != entry["sha256"]:
            temporary.unlink()
            raise ValueError(f"download hash mismatch: {path.name}")
        temporary.rename(path)
    if hashlib.sha256(path.read_bytes()).hexdigest() != entry["sha256"]:
        raise ValueError(f"cached archive hash mismatch: {path.name}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-tools", type=Path,
                        help="reuse matching ghidra and jdk directories by local symlinks")
    args = parser.parse_args()
    tools = ROOT / ".tools"
    tools.mkdir(exist_ok=True)
    lock = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())
    for name, table in (("ghidra", "ghidra"), ("jdk", "temurin_jdk")):
        destination = tools / name
        if destination.exists():
            continue
        if args.reference_tools:
            source = args.reference_tools.resolve() / name
            if not source.is_dir():
                raise ValueError(f"missing reference tool: {source}")
            destination.symlink_to(source, target_is_directory=True)
        else:
            entry = lock[table]
            archive = tools / entry["asset"]
            download(entry, archive)
            if name == "ghidra":
                extracted = tools / ("ghidra_" + entry["version"] + "_PUBLIC")
                if extracted.exists():
                    raise ValueError("partial Ghidra install exists; move it aside before retrying")
                subprocess.run(["unzip", "-q", str(archive), "-d", str(tools)], check=True)
            else:
                extracted = tools / ("jdk-" + entry["version"])
                if extracted.exists():
                    raise ValueError("partial JDK install exists; move it aside before retrying")
                subprocess.run(["tar", "-xzf", str(archive), "-C", str(tools)], check=True)
            if not extracted.is_dir():
                raise ValueError(f"archive lacks expected installation directory: {extracted}")
            destination.symlink_to(extracted.name, target_is_directory=True)
    verify_analysis_tools(tools / "ghidra", tools / "jdk")
    compiler = lock["msvc40"]
    checkout = ROOT / compiler["selection"]
    if not checkout.exists():
        subprocess.run(["git", "init", str(checkout)], check=True, stdout=subprocess.DEVNULL)
        subprocess.run(["git", "-C", str(checkout), "remote", "add", "origin", compiler["repository"]], check=True)
        subprocess.run(["git", "-C", str(checkout), "fetch", "--depth", "1", "origin", compiler["commit"]], check=True)
        subprocess.run(["git", "-C", str(checkout), "checkout", "--detach", "FETCH_HEAD"], check=True)
    Toolchain().verify()
    print("pinned Ghidra, JDK and VC4.0 tools ready")


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(f"tool bootstrap failed: {exc}", file=sys.stderr)
        sys.exit(1)
