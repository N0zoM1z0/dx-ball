"""Pinned VC4.0 compiler execution, isolated from other repositories' Wine state."""
import fcntl
import hashlib
import os
from pathlib import Path
import subprocess
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def sha256(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def tree_hash(directory):
    digest = hashlib.sha256()
    for path in sorted(Path(directory).rglob("*")):
        if path.is_file():
            digest.update(path.relative_to(directory).as_posix().encode() + b"\0")
            digest.update(bytes.fromhex(sha256(path)))
    return digest.hexdigest()


def windows_path(path):
    return "Z:" + str(Path(path).resolve()).replace("/", "\\")


class Toolchain:
    def __init__(self):
        self.lock = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["msvc40"]
        self.path = ROOT / self.lock["selection"]
        prefix = ROOT / ".tools/wineprefix-msvc400"
        self.env = os.environ.copy()
        for variable in ("CL", "_CL_", "LINK", "INCLUDE", "LIB"):
            self.env.pop(variable, None)
        self.env.update(WINEARCH="win32", WINEPREFIX=str(prefix), WINEDEBUG="-all",
                        INCLUDE=windows_path(self.path / "include"),
                        LIB=windows_path(self.path / "lib"))

    def verify(self, execute=False):
        head = subprocess.check_output(["git", "-C", str(self.path), "rev-parse", "HEAD"],
                                       text=True).strip()
        if head != self.lock["commit"]:
            raise ValueError("compiler checkout commit mismatch")
        for name, key in (("cl.exe", "compiler"), ("c1.exe", "c_frontend"),
                          ("c1xx.exe", "cpp_frontend"), ("c2.exe", "optimizer"),
                          ("link.exe", "linker"), ("mspdb40.dll", "pdb_backend")):
            if sha256(self.path / "bin" / name) != self.lock[key + "_sha256"]:
                raise ValueError(f"toolchain hash mismatch: {name}")
        if tree_hash(self.path / "include") != self.lock["include_tree_sha256"]:
            raise ValueError("toolchain include tree mismatch")
        if tree_hash(self.path / "lib") != self.lock["lib_tree_sha256"]:
            raise ValueError("toolchain library tree mismatch")
        if execute:
            for name, key in (("cl.exe", "compiler"), ("link.exe", "linker")):
                result = self.run(name, [], check=False)
                if self.lock[key + "_banner"] not in result.stdout:
                    raise ValueError(f"toolchain version banner mismatch: {name}")
        return self.lock

    def run(self, name, arguments, check=True):
        result = subprocess.run(
            ["xvfb-run", "-a", "wine", str(self.path / "bin" / name), *arguments],
            cwd=ROOT, env=self.env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, errors="replace", timeout=120,
        )
        if check and result.returncode != 0:
            raise RuntimeError(result.stdout)
        if "ignoring unknown option" in result.stdout:
            raise ValueError(f"legacy compiler rejected a configured option:\n{result.stdout}")
        return result

    def compile(self, source, output, flags):
        output = Path(output)
        output.parent.mkdir(parents=True, exist_ok=True)
        output.unlink(missing_ok=True)
        result = self.run("cl.exe", [*flags, "/Fo" + windows_path(output),
                                      windows_path(source)])
        if not output.is_file():
            raise RuntimeError("compiler produced no object")
        return result


def session_lock():
    path = ROOT / ".tools/compiler-session.lock"
    path.parent.mkdir(exist_ok=True)
    stream = path.open("w")
    fcntl.flock(stream, fcntl.LOCK_EX)
    return stream
