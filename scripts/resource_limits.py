"""Small resource budgets for project builds and REA's native provider."""
import os

BUILD_JOBS = 1
GHIDRA_HEAP_MIB = 512


def limit_cpu():
    """Keep this process and future children on one already-allowed Linux CPU."""
    if hasattr(os, "sched_getaffinity"):
        allowed = os.sched_getaffinity(0)
        os.sched_setaffinity(0, {min(allowed)})


def ghidra_environment(env):
    """Use supported launcher variables; do not modify pinned provider files."""
    env = env.copy()
    env["GHIDRA_HEADLESS_MAXMEM"] = f"{GHIDRA_HEAP_MIB}M"
    # REA sanitizes external JVM option strings. Its supported heap variable
    # survives, and inherited affinity limits all provider/decompiler threads.
    return env
