#!/usr/bin/env python3
"""Install the project-pinned REA package and its official Ghidra build."""
import json
from pathlib import Path
import shutil
import subprocess
import urllib.request
import zipfile

from legacy_toolchain import ROOT, sha256


def main():
    lock = json.loads((ROOT / "config/rea.lock.json").read_text())
    runtime = ROOT / ".tools/rea-runtime"
    runtime.mkdir(parents=True, exist_ok=True)
    for name in ("package.json", "package-lock.json"):
        shutil.copyfile(ROOT / "config/rea" / name, runtime / name)
    subprocess.run(["npm", "ci", "--prefix", str(runtime), "--registry=https://registry.npmjs.org",
                    "--no-audit", "--no-fund"], check=True)
    ghidra = lock["ghidra"]
    archive = ROOT / ".tools" / ghidra["asset"]
    if not archive.exists() or sha256(archive) != ghidra["archive_sha256"]:
        temporary = archive.with_suffix(".download")
        print(f"Downloading {ghidra['url']}", flush=True)
        urllib.request.urlretrieve(ghidra["url"], temporary)
        if sha256(temporary) != ghidra["archive_sha256"]:
            raise ValueError("official Ghidra archive hash mismatch")
        temporary.replace(archive)
    installation = ROOT / ".tools" / ghidra["directory"]
    if not installation.exists():
        with zipfile.ZipFile(archive) as bundle:
            for member in bundle.infolist():
                relative = Path(member.filename)
                if relative.is_absolute() or ".." in relative.parts:
                    raise ValueError("unsafe Ghidra archive member")
                extracted = Path(bundle.extract(member, ROOT / ".tools"))
                mode = member.external_attr >> 16
                if mode:
                    extracted.chmod(mode & 0o777)
    link = ROOT / ".tools/ghidra-rea"
    if not link.exists():
        link.symlink_to(installation.name, target_is_directory=True)
    from rea import environment
    environment()
    print("REA package, dependencies, Node, Ghidra and JDK identities verified")


if __name__ == "__main__":
    main()
