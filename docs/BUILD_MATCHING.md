# Compiler evidence and exact units

The target reports PE linker 3.00 and contains Microsoft CRT strings, with no
Rich header. The pinned candidate is
[archaic-msvc/msvc400](https://github.com/archaic-msvc/msvc400/tree/97b4a530238f38b9320a21ca0cb98e4044df7916),
commit `97b4a530238f38b9320a21ca0cb98e4044df7916`. Direct execution under the
repository's private win32 Wine prefix reports compiler 10.00.5270 and linker
3.00.5270. Compiler frontends, optimizer, linker, PDB backend, headers and
libraries are hash-pinned in `config/tools.lock.toml`.

The same `src/boards.c` / `src/boards.h` builds natively, with MinGW i386, and
with VC4.0. Fixed-width scalar aliases and pointer-sized opaque handles require
no compiler-selected layouts. Explicit terminal `return;` statements are normal
source control flow: a controlled VC4.0 `/Od` probe showed they emit the target's
five-byte jump to its epilogue. No copied instructions or padding are used.

Canonical compile flags:

```text
/nologo /c /Od /Ob0 /Oi- /Oy- /Gd /MT /Gy
```

These are reproducible per-unit evidence. Matching six functions does not prove
all original compilation flags, the complete compiler release, or original
translation-unit boundaries. `/Gy` gives complete independent function COMDAT
extents to the oracle; no comparison requests a truncated prefix.

| Exact unit | Target VA | Complete size |
| --- | --- | ---: |
| select-surface | `0x00403E50` | 24 |
| read-board-bank | `0x0040CC30` | 96 |
| write-board-bank | `0x0040CC90` | 96 |
| load-editor-board | `0x0040CEA0` | 52 |
| store-editor-board | `0x0040CEE0` | 52 |
| initialize-board | `0x00411930` | 50 |

All six are contiguous target functions ending in `ret`; instructions,
branches, shared epilogues, following `int3` padding, and target calls were
reconciled. Padding after the terminal return is outside each accepted extent.
They total **370 bytes**, with zero differences after all configured relocations.

Relocation evidence uses target instructions and independently reconstructed
global ownership. memcpy is `0x00417CA0`, memset `0x00417C40`, fopen
`0x00417C20`, fread `0x00417AA0`, fwrite `0x00417E70`, and fclose `0x00417A30`.
The board-bank owner documents the referenced globals. `rb\0` at `0x00422890`
and `wb\0` at `0x00422894` are attested in both the COFF data symbols and target.
Compiler-private string labels remain explicit; a name change requires review.

Replay:

```bash
scripts/repo-python scripts/verify-toolchain.py --execute
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python tests/test_exact_oracle.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Reports under ignored `build/reports/` bind the target, source/header, compiler,
object, manifest, and relocated span hashes. `config/matches.csv` records the
accepted checkpoint's object hash; a later cold build can have a different COFF
timestamp while reproducing identical complete code. Input hashes and every
machine byte must still pass. The oracle's eight rejection tests cover baseline,
instruction corruption, extra emitted code, wrong/missing relocation, changed
addend, changed literal, and wrong target identity.

The tile mapping and two drawing functions have scoped semantic acceptance;
they have no exact claim. The unsupported mapping-helper return domain and
unimplemented rendering backend remain explicit debt.
