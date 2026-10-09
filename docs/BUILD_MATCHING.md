# Compiler evidence and exact units

The current shared-source checkpoint retains **86 exact functions / 11,124 code
bytes**, plus 136 separate exception metadata bytes. The
[integer trig/hit-region batch](EXACT_INTEGER_TRIG.md) adds five complete
functions / 365 bytes and preserves all 81 preceding units. Source presence
and distinct cases remain unchanged. Triangle remains a complete 1,710-byte
candidate with 99 frame-displacement differences.

The historical display checkpoint retained 55 exact functions / 8,231 bytes.
Its [display batch](EXACT_DISPLAY.md) adds four missing Blt/rectangle-queue
entries, restores both full BltFast bodies and recovers the ordinary resource
blit. Seven complete emissions add 2,219 bytes. All preceding 48 units and
these seven pass grouped cold replay with every relocation applied.

The preceding [palette batch](EXACT_PALETTES.md) adds three complete RGB-tail
loaders, including the missing surface palette creation/attachment entry, and
1,020 exact bytes. Its 48 units passed grouped cold replay. The resource build
uses `/ML` to reproduce the original inline getc expression from pinned stdio.h;
other exact builds retain `/MT`. The same source and layouts serve all profiles.

The preceding [cloning and cleanup batch](EXACT_LISTS.md) adds the complete
637-byte ball clone and five 48-byte cleanup entries, with five new source
mappings. Its total-cleanup caller remains a 107/106-byte candidate. Its 45
units passed grouped cold replay after content-attested literal rebinding.

The [core source batch](EXACT_CORE.md) adds the complete 232-byte trig initializer,
both 130-byte lookups and the 244-byte ball constructor. Its 39 configured units
pass one grouped cold replay with every relocation applied. At that checkpoint,
the rotation offset had a reconciled 259-byte span and a nonmatching 261-byte
emission; the subsequent [projection batch](EXACT_PROJECTIONS_TEXT.md) restores
its complete exact emission. Existing semantic cases are replayed and
counted once; this batch adds no fixtures or campaign observations.

The [allocator integration](ALLOCATOR_OWNER.md) cold replay found two changed
operand bytes in the 139-byte `stretch-keyed-sprite` body. The current complete
comparison has four differences. Its behavior still
passes, but its exact claim is now a candidate. The pan literal names changed
to `$T1142` / `$T1143`; contents and complete relocations were checked.

The preceding rotation checkpoint retained 36 units / 3,518 bytes.
The complete 40-byte wrapper at `0x00404280` matches with one explicit REL32
renderer binding; all 35 prior units pass the same cold replay. Renderer and
offset bodies retain scoped behavior acceptance without exact claims. See
[rotation compiler evidence](ROTATION_INVESTIGATION.md#maintained-and-compiled-behavior).

The raster drawing controller has a separate configured semantic compiler
product. The subsequent [fixed-point batch](EXACT_FIXED_POINT.md) accepts eight
class/helper units, 571 complete code bytes and 136 separate metadata bytes;
the full triangle remains nonexact. `compile-semantic-build.py --build raster`
cold-builds the shared source
and records its complete inputs, flags and product identity; `test_raster_coff.py`
executes that actual output against 7,164 complete original/native vectors.
The horizontal span emits 62 bytes versus the original 144, so behavior agreement
does not establish an instruction match. Static function COMDATs use the same
whole-section rules as external functions, including rejection of an additional
function alias. See [raster compiler evidence](RASTER_INVESTIGATION.md).

The bitmap owner also has a configured semantic compiler product:
`compile-semantic-build.py --build bitmap` builds the same C source, and
`test_bitmap_coff.py` executes its complete public/static COMDATs with every
relocation explicitly bound. The 949-byte public body differs in extent from
the original 976 bytes; its 64-byte static reader is a compiler product, not a
new original function. The same 975 full native/original vectors pass, counted
once. The native stack-seeding assembly belongs only to the test caller and is
excluded from production. No bitmap exact unit is configured. See
[bitmap compiler evidence](BITMAP_INVESTIGATION.md#shared-source-and-compiler-execution).

The preceding shared-storage replay of all forty previously accepted units
found five changed emissions:

| Retained candidate | Current / target bytes | Differing bytes |
| --- | ---: | ---: |
| load-editor-board | 58 / 52 | 23 |
| store-editor-board | 58 / 52 | 42 |
| blt-sprite (historical; now recovered) | 199 / 195 | 173 |
| queue-explosion-at | 100 / 99 | 51 |
| update-paddle-position | 203 / 203 | 4 |

These functions retain their scoped semantic validation. Their exact claims
are removed; reviewed relocation mappings remain under `[candidates]` in
`config/match-units.toml`. Run `scripts/repo-python scripts/replay-exact-units.py
--include-candidates` to reproduce the complete comparison, including its
nonzero exit status. At that historical checkpoint, normal replay selected 35 accepted units.
The current normal replay selects the complete configured 86-unit set.

REA's terminal-storage investigation establishes the recovered storage region
and overlapping original CRT copy. The shared C representation changes object
references and VC4 emission; it does not establish original declarations.
Relocations to its actual root use reviewed field addends and target base
`0x43AAB8`. Both copy calls map `memmove` to the observed overlap-aware entry
`0x417CA0`. The shared-storage checkpoint used pan labels `$T1075` / `$T1076`, and rb/wb labels
`$SG734` / `$SG738`; literal contents remain independently attested.

Adding the three [sound-control](SOUND_CONTROLS.md) declarations changes VC4's
internal pan names to `$T1084` / `$T1085`. Complete emitted data still agrees
with the previously accepted doubles at `0x420068` / `0x420070`. Only the
explicit relocation names change; targets, addends and expected literal bytes
remain fixed. The stopped cold replay and its objects are preserved before
updating the manifest. Original code, comparison rules and maintained pan
source are unchanged.

The following records describe the earlier owner checkpoints and their
original exact totals; the current accepted ledger takes precedence.

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

Default exact compile flags:

```text
/nologo /c /Od /Ob0 /Oi- /Oy- /Gd /MT /Gy
```

The resource exact build replaces `/MT` with `/ML`; see [palette evidence](EXACT_PALETTES.md).

These are reproducible per-unit evidence. Matching individual functions does not prove
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
global ownership. The overlap-aware copy entry is `0x00417CA0`, memset `0x00417C40`, fopen
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
machine byte must still pass. The oracle's ten tests cover baseline,
instruction corruption, extra emitted code, wrong/missing relocation, changed
addend, changed literal, wrong target identity, static whole-section extent and
an additional static function alias.

The tile mapping and two drawing functions have scoped semantic acceptance;
they have no exact claim. The unsupported mapping-helper return domain and
unimplemented rendering backend remain explicit debt.

The resource owner adds seven complete exact functions totaling **787 bytes**:
two bank selectors, plain/keyed BltFast, plain/keyed Blt, and keyed stretch.
Their complete extents and independently reviewed global destinations are in
[resource evidence](RESOURCE_OWNER.md). All thirteen units cold-replay with
zero differences, **1,157 bytes** for the board/resource owners. `match-units.toml` assigns each unit
to its canonical source build; reports bind each object's full input set.

REA's gameplay investigation adds the 146-byte fastcall explosion append and
63-byte cdecl sound-pan function and 139-byte explosive scan, bringing the total
to **16 exact functions, 1,505 bytes**. Complete body ranges, both double constants
and the allocation/conversion dependencies were reviewed through REA; nine relocations remain
explicit. The allocation bridge is not a reconstructed CRT implementation.
See [gameplay evidence](GAMEPLAY_OWNER.md). The hit function has scoped semantic
acceptance only.

The request/animation investigation adds eight exact units totaling **806 bytes**,
bringing the checkpoint to **24 exact functions, 2,311 bytes**. Both begin/advance
pairs, request enqueue, animation append, explosion construction and dispatch
cold-replay with zero differences. The dispatcher's complete 120-byte span
includes its unreachable five-byte gap. REA instruction/body dossiers and
explicit mappings are recorded in [animation evidence](EFFECTS_OWNER.md).
At that checkpoint, shared declarations renumbered the pan's private constants to `$T488` / `$T489`;
the manifest still verifies both constant contents in object and original target.

The particle/bonus investigation adds nine complete exact units totaling
**1,093 bytes**, bringing that checkpoint to **33 functions, 3,404 bytes**.
Both list append/begin/advance triples, particle creation/update and bonus
retirement pass zero-difference cold replay. REA's body dossiers and typed
state ownership establish their explicit relocation destinations; see
[entity evidence](ENTITIES_OWNER.md). The compact bonus selector, deletion and
controlled rendering retain semantic acceptance without an exact claim.
At that checkpoint, shared declarations renumbered the pan literals to `$T516` / `$T517`;
both object and target constant contents remain attested.

The power-up batch adds seven complete exact functions / **675 bytes**:
scratch-list clear, paddle position, ball append/begin/advance/clear and attached
ball release. That checkpoint totaled **40 functions, 4,079 bytes**. All prior units
and the expanded family passed one grouped cold replay after source stabilized.
The paddle entry includes the SetCursorPos import-slot mapping at `0x00441350`.
See [power-up evidence](POWERUPS_OWNER.md) for body extents and semantic-only
neighbors. Current pan literal labels are `$T617` / `$T618`; both contents are
attested. Natural source helpers shorten several recovered bodies, which remain
semantic-only rather than receiving artificial code or padding to force a match.

The core gameplay batch adds scoped ball/frame implementations and necessary
physics/shot/fire dependencies without new exact units. All existing 40 units
retain zero differences after one grouped cold replay. The corrected displayed-
score global name changes reviewed source/input identities, not target behavior.
See [core evidence](CORE_OWNER.md); independent leaf matching remains deferred
while the remaining runtime spine is reconstructed.
