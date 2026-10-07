"""Attest installed Ghidra launch metadata and the JDK used by headless queries."""
import hashlib
from pathlib import Path
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def verify(ghidra_home, java_home):
    lock = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())
    for section, root, entries in (
        ("ghidra", ghidra_home, {
            "application_properties_sha256": "Ghidra/application.properties",
            "analyze_headless_sha256": "support/analyzeHeadless"}),
        ("temurin_jdk", java_home, {
            "java_sha256": "bin/java", "modules_sha256": "lib/modules",
            "release_sha256": "release"}),
    ):
        if root is None:
            continue
        root = Path(root)
        for key, filename in entries.items():
            if hashlib.sha256((root / filename).read_bytes()).hexdigest() != lock[section][key]:
                raise ValueError(f"analysis tool hash mismatch: {section}/{filename}")
