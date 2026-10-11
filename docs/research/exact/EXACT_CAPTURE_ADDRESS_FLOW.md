# Complete sprite capture address and interface flow

The complete original852-byte/current876-byte capture bodies contain248
instructions each. All instructions decode; none of the enclosing span is
excluded. The remaining803 strict differences do not reveal a missing source
producer:18 actual bank-address groups explain144 instructions, while all104
other instructions agree after an explicit frame map and CFG-target pairing.
No game source or compiler input changes in this batch.

Each group rereads the live bank selector at `0x421088` and the caller's sprite
argument. Original code uses a scaled final address after shifting sprite;
current code shifts the bank product before the final scaled sprite address.
Symbolic execution of each actual eight-instruction group proves the same
32-bit address for every input: `0x425980 + 1048 * bank + 4 * sprite`.
The stride is the255-pointer bank plus two integers and20 filename bytes.
One group publishes the allocated pointer;17 load the then-current slot.
These are18 static read sites, refreshed whenever reached, including retries.
No intervening call or external write occurs inside a group. They are not a
cached selector/record across COM calls. Ordered source producers include width,
height, code, baseline, source RECT, surface output address, color key, descriptor
retry, saved pitch and final Blt arguments.

Both frames allocate140 bytes. The complete140-byte bijection pairs five typed
objects; no byte, padding or invented local is added:

| Object | Current base below EBP | Original base below EBP | Bytes |
| --- | ---: | ---: | ---: |
| Allocated record pointer | 140 | 28 | 4 |
| API result | 136 | 32 | 4 |
| Surface descriptor | 132 | 140 | 108 |
| Color key | 24 | 24 | 8 |
| Capture RECT | 16 | 16 | 16 |

The five direct branch successors pair by actual instruction identity,
including allocation and CreateSurface decisions, failed creation exit,
GetSurfaceDesc retry and final exit. Seven call sites retain actual targets:
release, malloc, exit, CreateSurface slot6, SetColorKey slot29,
GetSurfaceDesc slot22 and Blt slot5. The caller supplies five32-bit arguments;
plain `RET` retains caller cleanup. Complete relocation-aware comparison checks
all42 actual code bindings. The already-linked `/MT` production resource
object has identical capture code bytes and actual relocations to the `/ML`
matching object, so this proof binds the current VC4 product's owner without a
new compilation or link.

This is defined typed producer/CFG correspondence at the controlled API
boundary. Passed frame pointees translate by object identity and known extent;
raw pointer-address equality, arbitrary driver/COM callback aliasing or retaining
stack addresses, uninitialized descriptor fields and scratch/EFLAGS/void-exit
residue are outside the claim. Original declaration spelling and physical
DirectDraw behavior remain unproved. The existing31-case resource scope and six
COM mutation cases retain their original products/assertions; none is rerun.
There is no new runtime acceptance or exact-function claim.

The closed REA6.3 dossier is
`2026-10-10T17-22-54.305Z-requests-825249/00-analyze_function.json`, Evidence
`ev_d7dd48a6f210a1a2cffea6be8318655763959610c9d94f8f8ff5621dad169b76`.
Its contiguous body addresses match every original instruction in this proof.
The historical carrier has944994 bytes; its compact assembly projection has
8558 bytes. These are retained serialization sizes, not fresh provider latency,
transport, model tokens or RSS. No provider, compiler, build or runtime replay
runs. Private complete disassemblies, symbolic groups, frame map and product
identities: `.analysis/capture-producer-flow/`. Immutable seal:
`.analysis/checkpoints/capture-address-flow-283-186/sha256.json`.

Retire capture-sprite's abstract change groups as a source-gap hypothesis.
Do not trial bank expressions, local declarations/names or layout merely to
alter code generation. The source frontier must distinguish real missing
control/data producers from addressing and temporary-storage residuals. Next
inspect the game-key handler's complete831-byte enclosing span against its645
Ghidra-owned bytes, including dispatch tables and every successor, before any
source/compiler change. [Earlier key recovery](EXACT_WINDOW_KEYS.md) already
retains full reads, six music targets, fifteen key targets and92 selectors;
reuse those bytes. The open question is current complete code/table CFG
correspondence, not missing original byte acquisition. Full original-source and synchronized game/audio
fidelity remain open.

Cleanup verifies25 owned files/24 immutable dependencies and four unchanged
products after five scoped hardlinks replace1,191,936 single-link allocated
bytes. No unique payload or mutable product is deleted; no device-free-space
measurement. Supplemental post-cleanup identities bind the cleanup record,
current documentation and final reviewer without altering the immutable seal.
