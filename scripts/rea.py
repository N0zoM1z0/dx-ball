#!/usr/bin/env python3
"""Attest project REA/Node/Ghidra/JDK inputs before dispatching through REA."""
import importlib.util
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tomllib

from legacy_toolchain import ROOT, sha256, tree_hash, session_lock
from resource_limits import ghidra_environment, limit_cpu


def environment():
    lock = json.loads((ROOT / "config/rea.lock.json").read_text())
    runtime = ROOT / ".tools/rea-runtime"
    ghidra = ROOT / ".tools/ghidra-rea"
    java = ROOT / ".tools/jdk"
    node = Path(shutil.which("node") or "missing-node")
    if sha256(node) != lock["node"]["sha256"]:
        raise ValueError("REA Node executable identity changed")
    if sha256(ROOT / "config/rea/package-lock.json") != lock["package_lock_sha256"]:
        raise ValueError("REA package lock changed")
    if tree_hash(runtime / "node_modules") != lock["node_modules_sha256"]:
        raise ValueError("REA package/dependency bytes changed; bootstrap the pinned installation")
    for name, expected in lock["ghidra"]["files"].items():
        if sha256(ghidra / name) != expected:
            raise ValueError(f"REA Ghidra input changed: {name}")
    java_lock = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["temurin_jdk"]
    for name, key in [("bin/java", "java_sha256"), ("lib/modules", "modules_sha256"),
                      ("release", "release_sha256")]:
        if sha256(java / name) != java_lock[key]:
            raise ValueError(f"REA JDK input changed: {name}")
    env = os.environ.copy()
    env.update(GHIDRA_INSTALL_DIR=str(ghidra.resolve()), JAVA_HOME=str(java.resolve()),
               REA_ANALYSIS_PROVIDER="ghidra")
    return node, runtime, ghidra_environment(env)


def main(arguments):
    limit_cpu()
    node, runtime, env = environment()
    if not arguments:
        arguments = ["--help"]
    if "--provider" in arguments and arguments[arguments.index("--provider") + 1] != "ghidra":
        raise ValueError("this showcase pins the Ghidra provider")
    if any(arg.startswith("--provider=") and arg != "--provider=ghidra" for arg in arguments):
        raise ValueError("this showcase pins the Ghidra provider")
    # Verify the original separately from REA's immutable target copy. Inspection
    # commands must name our pinned target; setup/doctor/providers are target-free.
    target_commands = {"analyze", "inspect", "function", "decompile", "instructions", "search",
                       "xrefs", "read-bytes", "address-to-file-offset", "inspect-native-load-image",
                       "inspect-native-api", "resolve-native-call-targets", "inspect-native-instruction",
                       "inspect-native-data-type", "annotate-native-function", "trace-native-values"}
    if arguments[0] in target_commands and "--help" not in arguments and "--schema" not in arguments:
        spec = importlib.util.spec_from_file_location("verify_target", ROOT / "scripts/verify-target.py")
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        target, _, _ = module.verify()
        if len(arguments) < 2 or Path(arguments[1]).resolve() != target.resolve():
            raise ValueError("REA query must use the configured original/DXBALL.EXE")
    if arguments[0] == "session":
        if len(arguments) != 2:
            raise ValueError("usage: scripts/rea session REQUESTS.json|--interactive")
        spec = importlib.util.spec_from_file_location("verify_target", ROOT / "scripts/verify-target.py")
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        module.verify()
        lock = session_lock()
        request = arguments[1] if arguments[1] == "--interactive" else str(Path(arguments[1]).resolve())
        return subprocess.run([str(node), str(ROOT / "scripts/rea-session.mjs"),
                               request], env=env, cwd=ROOT).returncode
    # Runtime capture may launch a repository probe which acquires this same
    # lock for its actual compiler/Wine work. Holding it in the parent would
    # deadlock the child; process capture does not own a Ghidra analysis session.
    lock = None if arguments[0] == "capture-process" else session_lock()
    return subprocess.run([str(node), str(runtime / "node_modules/rea-agents/scripts/rea.mjs"),
                           *arguments], env=env, cwd=ROOT).returncode


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv[1:]))
    except (OSError, ValueError, IndexError) as exc:
        print(f"REA dispatch failed: {exc}", file=sys.stderr)
        raise SystemExit(1)
