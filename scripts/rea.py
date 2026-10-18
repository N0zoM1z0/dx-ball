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

from legacy_toolchain import ROOT, Toolchain, sha256, tree_hash, session_lock
from resource_limits import ghidra_environment, limit_cpu


COMPILER_TARGETS = {
    "vc4-backend": ("c2.exe", "optimizer_sha256"),
    "vc4-c-frontend": ("c1.exe", "c_frontend_sha256"),
    "vc4-cpp-frontend": ("c1xx.exe", "cpp_frontend_sha256"),
}


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
    provider_environment = ghidra_environment(env)
    # The REA entry point uses the lower budget requested for this workspace.
    # Keep the provider's supported launcher variable and pinned files intact.
    provider_environment["GHIDRA_HEADLESS_MAXMEM"] = "256M"
    return node, runtime, provider_environment


def main(arguments):
    limit_cpu()
    compiler_session = bool(arguments and arguments[0] == "compiler-session")
    if compiler_session:
        if len(arguments) != 3 or arguments[1] not in COMPILER_TARGETS:
            raise ValueError("usage: scripts/rea compiler-session "
                             "vc4-backend|vc4-c-frontend|vc4-cpp-frontend REQUESTS.json|--interactive")
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
    if compiler_session:
        # Compiler investigation has its own pinned input and REA snapshot.
        # Keep the ordinary game-query guard and game session unchanged.
        lock = session_lock()
        toolchain = Toolchain()
        toolchain.verify()
        mode = arguments[1]
        executable, hash_key = COMPILER_TARGETS[mode]
        target = ROOT / ".tools/msvc400/bin" / executable
        if target.resolve() != (toolchain.path / "bin" / executable).resolve():
            raise ValueError("REA compiler target is not the selected pinned VC4 tool")
        request = arguments[2] if arguments[2] == "--interactive" else str(Path(arguments[2]).resolve())
        return subprocess.run([str(node), str(ROOT / "scripts/rea-session.mjs"),
                               request, mode, toolchain.lock[hash_key]],
                              env=env, cwd=ROOT).returncode
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
