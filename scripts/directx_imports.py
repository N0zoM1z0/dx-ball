"""Generate missing DirectX SDK import libraries with the pinned librarian."""
import json
import struct

from crt_library import defines, members
from legacy_toolchain import ROOT, sha256, windows_path


def _prepare_import(toolchain, dll, export):
    """Caller holds the compiler session lock; no original game bytes are copied."""
    directory = ROOT / "build/directx-imports"
    directory.mkdir(parents=True, exist_ok=True)
    definition = directory / (dll + ".def")
    definition.write_text(f"LIBRARY {dll}.dll\nEXPORTS\n{export}@12\n")
    library = directory / (dll + ".lib")
    result = toolchain.run("lib.exe", ["/NOLOGO", "/MACHINE:IX86",
        "/DEF:" + windows_path(definition), "/OUT:" + windows_path(library)])
    (directory / (dll + "-librarian.log")).write_text(result.stdout)
    generated_sha256 = sha256(library)
    data = bytearray(library.read_bytes())
    replacements = 0
    for offset, _, raw in members(library):
        # The descriptor member has a PE optional header, unlike the thunk.
        if struct.unpack_from("<H", raw, 16)[0] != 0:
            continue
        if not defines(raw, "_" + export + "@12"):
            continue
        _, count, _, _, _, optional, _ = struct.unpack_from("<HHIIIHH", raw)
        for index in range(count):
            section = 20 + optional + index * 40
            if raw[section:section + 8] != b".idata$6":
                continue
            size, start = struct.unpack_from("<II", raw, section + 16)
            hint = raw[start:start + size]
            if hint[:2] != b"\0\0" or hint[2:].split(b"\0", 1)[0] != (export + "@12").encode():
                raise ValueError("unexpected generated DirectX import hint")
            # VC4's librarian decorates both the link symbol and DLL name.
            # Keep the stdcall symbol; the SDK exports the undecorated name.
            replacement = b"\0\0" + export.encode() + b"\0"
            replacement += bytes(size - len(replacement))
            position = offset + 60 + start
            data[position:position + size] = replacement
            replacements += 1
    if replacements != 1:
        raise ValueError("expected one DirectX import-name record")
    library.write_bytes(data)
    metadata = {"library": str(library.relative_to(ROOT)),
        "library_sha256": sha256(library), "generated_library_sha256": generated_sha256,
        "definition_sha256": sha256(definition),
        "librarian_sha256": sha256(toolchain.path / "bin/lib.exe"),
        "link_symbol": "_" + export + "@12", "dll": dll + ".dll",
        "export": export, "import_hint_records_updated": replacements}
    (directory / (dll + "-receipt.json")).write_text(json.dumps(metadata, indent=2) + "\n")
    return library, metadata


def prepare_directx_imports(toolchain):
    products = [_prepare_import(toolchain, dll, export) for dll, export in
        (("dsound", "DirectSoundCreate"), ("ddraw", "DirectDrawCreate"))]
    return [path for path, _ in products], [receipt for _, receipt in products]
