# Current VC4 build and play record

October 22, 2026. All **270/270 classified authored functions** and
**84,968/84,968 authored code bytes** are exact. The original-VC4 game now builds
from that source and passes basic play, editor save/reload and a real round
transition under Wine. The directly tested executable is in the local delivery
ZIP. The [handoff](../agent/HANDOFF.md) records the completed source audit.

## Current products

Source checkpoint: `ecfc475715238c43241a5979b1745a163749b9dc`.

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| `build/vc40-restored-crt/dxball.exe` | 166,400 | `bdd425241ba51d6fe671bb0184b4ad86062326fc9e1eb407d2536235b93df79c` |
| `build/delivery/dxball-v1.07-vc40-reconstructed.zip` | 474,899 | `00a6d9799327a71c11a2b9afa71ae38c1db34249c98259303c00e2f3b5e6ba4d` |

The ZIP has 50 verified members: this exact tested EXE, 48 unchanged supplied
assets and unchanged extraction instructions. Every member is read back and
checked by size, SHA-256 and ZIP CRC. It includes the original score table;
automated editor saves and test rankings are excluded. The adjacent manifest
records source, build, flow evidence and every member. Extract the complete
folder and run `dxball.exe` there. Products and supplied assets remain private
and are excluded from a source-only clone.

## Build and exact-source continuity

The pinned VC4 compiler 10.00.5270/linker 3.00.5270 link **141 objects**:
138 source owners and three integration objects. Four require compilation;
137 are reused after verifying compiler, current recursive source/header inputs,
flags and object hashes. The 19 explicitly approved original CRT members remain
under `/NODEFAULTLIB`. Resource and DirectX import inputs are also verified.

All **53 authored compiler recipes** have the same flags and object hashes as
the completed 270-function audit. The game therefore includes the accepted exact
owners, including the final rotation, last-brick and PCX recoveries. No recovered
source, compiler recipe or exact/semantic ledger changes in this build/play stage.

Build report SHA-256:
`1551821330f892615e78cb0fa0d3a16d525a4074b5503fd93627c14695bf2891`.
Linked map SHA-256:
`524f10a78f63422fc8ca79bf665180efb79ff098bfb79be6c86a4d4c686390f2`.

The exact claim covers complete authored functions after explicit address
mapping for actual code/data references, full literals and attached metadata.
It does not establish byte identity of the whole PE or uniquely recover the
original source spelling. The source audit checks 4,759 actual code bindings,
252 full literal references and all 53 current recursive compiler closures.

## Checks on this executable

Both existing flows use real Wine input and read-only process-state observation.
The observer test bodies and readiness deadlines remain unchanged. Existing
verified readers are reused; neither flow recompiles or relinks the game or reader.

| Flow | Observed result | State reads | Exit |
| --- | --- | ---: | ---: |
| Basic/editor | Opening/menu, mouse paddle movement, released moving ball, pause/resume, editor paint, complete save/reload, return to menu | 534 | 0 |
| Round transition | Create and clear one brick, score 10/lives 3, load original board index 1 with 222 remaining bricks, return to menu | 116 | 0 |

The basic flow verifies the complete 20,000-byte saved bank. Its persistent
reader produces 2,346 valid samples and zero malformed samples. The round flow
compares all 400 loaded board bytes with `original/DEFAULT.BDS[400:800]`.
Saved PNG review confirms the paused board, two painted editor cells and the
coherent next original board. All 49 original files and protected source/build
inputs remain unchanged in both flows. Both owned game processes exit normally.

| Flow | Report SHA-256 | REA process evidence |
| --- | --- | --- |
| Basic/editor | `f005c982449bdea99111457ca65268717c38c0a7b87ee5e614efb4dc25299774` | `ev_7177de8ca01a9230f41ad0c347acb50306bc9362b4b3728c0adcc80af32f5279` |
| Round | `2e17ffbb134e6257c5eb58335ad416b58dfd42484d3532e6e0e3b2de3166af03` | `ev_1ab24f160aab5333bd4b8e14871b622321de24605629cd348bfc32bceb042ac5` |

REA 6.5.0 captures the declared process scenarios without a new Ghidra import.
The full responses are retained under
`.analysis/rea/current-vc4-exact270-20261022/`. REA's generic process-settlement
status remains `unverifiable`; the separate per-flow receipts verify each owned
process identity has exited. No system-wide process-quiescence claim follows.

## Resource bounds and scope

Build and Wine commands run serially on CPU 0, with 35% CPU, 384 MiB memory high
and 512 MiB max. Xvfb is 640×480×24; game audio uses the silent sink, with the
default host sink unchanged.

| Operation | Seconds | Peak bytes | Soft high events | Max/OOM events |
| --- | ---: | ---: | ---: | ---: |
| Game build | 22.362 | 176,939,008 | 0 | 0 |
| Basic/editor | 76.490 | 403,005,440 | 586 | 0 |
| Round | 84.202 | 403,271,680 | 222 | 0 |

The two game runs briefly cross the soft high threshold; neither reaches the
hard limit or records an OOM. Each owned 49-file probe runtime is archived,
member-size/SHA/mode verified and retired after checking against the current
EXE, original assets and retained complete saved bank. Current game/delivery
products, accepted objects, useful caches and manual runtimes remain.

The current checks establish bounded playability of this image. Full 50-board
play, current-image game-over/ranking persistence, focus/surface recovery,
physical graphics/audio fidelity and exceptional paths remain outside this
checkpoint. They are separate from the completed authored exact denominator.

## Evidence and history

Current private authority:
`.analysis/current-vc4-exact270-20261022/current-checkpoint.json`.
It links the build, 53-recipe continuity check, two flow verifications, delivery
member manifest and cleanup. The authored audit remains at
`.analysis/pcx-file-prefix-source-search-20261022/completion-audit.json`.

The [October20 record](https://github.com/N0zoM1z0/dx-ball/blob/ecfc475715238c43241a5979b1745a163749b9dc/docs/research/CURRENT_VC4_BUILD.md)
retains its 246-exact/24-candidate source checkpoint, 118-object cold build and
separate tested/cold image identities. Those claims remain attached to their
historical products. The older linked-section proof is also not promoted to
this image. Prior tested products and the replaced delivery remain recoverable
in private member-verified history.

The earlier `12ccdb1` image failed its return-menu deadline after pause/resume.
Its cause remains unresolved, and passing on this image does not identify a
historical fix. Complete failure evidence stays under
`.analysis/current-vc4-refresh-20261019/`. Earlier bff527e build and loader evidence
remain under `.analysis/current-vc4-build-20261020/`.
