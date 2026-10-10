# Complete menu and gameplay frames

The menu frame at `0x0040E330` has one contiguous 242-byte body ending at
`0x0040E421`, retained in REA Evidence
`ev_6209121031ff06b1a5ae1e284316241f2d319a9129ad4c33ccab80d4381195b1`.
The gameplay frame at `0x0040F8B0` owns 1,683 bytes in a 1,688-byte enclosing
span ending at `0x0040FF47`, Evidence
`ev_5d1d8d47e797530fa172e492b60eebe40dcf8a855a6d9125eb644dccb2e15d43`.
Both complete saved instruction dossiers precede this source restoration.

One focused pinned REA 4.1.0 / Ghidra 12.1.4 session checks the five unowned
bytes at `0x0040FB21..0x0040FB25`. Read Evidence
`ev_094a11dead7ae99ddcbcb79aba5bee332c7d58cf8329ece1c5c1099392400896`
retains all 26 bytes around the gap. The gap is `e90f000000`; interpreting its
x86 relative displacement yields a jump to the known switch exit `0x0040FB35`.
That interpretation is analyst inference. Instruction inspection
`ev_9374bb78607bd5bb0e9ebcb085b5a7be95b8960a9bd27c8542abbc0846809972`
returns undecodable and no containing procedure. Reference Evidence
`ev_c022b74166fe2a92ae4ef9e0204a6182f34ca46438232cfe00505e11db081c54`
returns no direct references to the gap. These observations do not expand
Ghidra's body ranges or prove execution of those bytes. A configured whole-span
comparison must include all five bytes, without masking or skipping them.

The shared menu source inlines the observed mouse-to-cursor stores and signed
X upper/lower and Y upper clamps. Negative Y survives. Independent mouse-action
gates and the ordinary return preserve the complete original exit structure.
The unused cursor helper is removed.

Gameplay restores actual direct phase calls, the original pause/active branches,
the inline explosion-request switch and pending sound block, two independent
ball-speed traversals and the inline enlargement traversal. Each speed path
retains distinct consumed direction signs, live list-owner reads, both velocity
stores before absolute-value/sign restoration and the original x87 expression
order. Slowing preserves fire sprite 61; speeding caps at nine. Genuine cloning
and ignition calls, completion short circuit, round restart and input order
remain intact. No inert compiler scratch locals, layout trials, padding or copied
machine code are introduced. Original source spelling remains unknown.

Compiler diagnostics, original-execution replay and configured cold acceptance
establish the separate scopes reported below.
The >=95% complete English-source restoration goal remains open.

The sole diagnostic batch freezes all 69 maintained source/header files and
compiles intro/core once each. No source bodies change afterward. Four mapping
script failures are retained: an overly strict old candidate offset assertion,
text formatting of a hexadecimal relocation row, a stack-space reference and a
shared-owner base/addend reference. Each fails before any manifest write and
executes no additional compiler. The final mapping covers all 185 new actual
relocations and both complete eight-byte 1.2 operands. Every old accepted and
candidate unit in the two changed owners is checked. Complete literals, actual
current offsets and original resolved operands are bound before native replay
is frozen; there is no post-replay mapping amendment.

One configured cold epoch accepts 111 whole zero units / 14,900 code bytes plus
136 separate exception metadata bytes, preserving all 110 preceding complete
identities. Menu adds 242 bytes. Gameplay compares all 1,688 enclosing bytes
against 1,692 emitted bytes with 1,155 differences. The shared explosion owner
view accounts for three LEA/MOV address differences; unsigned auxiliary-byte
promotion differs from the original signed load. Pause exit and equivalent
completion comparisons also remain different. Original source spelling and
storage declarations are unknown; source layouts and inert locals are not
changed merely to force agreement. Pulse's unchanged body now emits 368/370
with 127 differences; other old complete candidate counts are unchanged.

All 22 existing owner scripts pass in 424.391 seconds against 289
physically frozen inputs. Existing 708 gameplay-frame and 32 menu-frame cases,
all 1,510 runtime cases and connected display/mode checks retain their existing
counts. Seven checks pass: whole cold exact replay, 14 existing rejection
controls, cold raster-product adoption, 7,164 fresh raster vectors, 1,024 fresh
rotation vectors, strict MinGW and full VC4 builds. Raster adoption records
semantic_driver_executed=false and executes no extra compiler.

Only the existing native interposer/loader gain eleven typed boundaries: ten
FrameOps phases and the four-integer bonus generator. All 24 previous production
wrappers, constructors, complete fixtures, oracles and campaign matrices remain
unchanged. Current actual copied-image slots guard null/default/self/reentry,
preserving unsigned clock and signed elapsed returns. The shim checks 35 genuine
symbols and 36 production-default slots and retains 47 actual compiler
dependencies. Host forwarding does not establish physical graphics/audio.

Native family/canonical SHA256 `59923c0f3fa9159d4595dd744fe7c4f0c4d919e996879a769b6a0925df34b518`; shim `8f971067c1eb00a3632a011992e0203ea0b49d7668c0d269396aabe66b372769`.
Source present stays 283, scoped semantic rows 247, unit-distinct cases 112,273;
235 semantic input closures refresh with no new cases.
Origins stay 270 authored / 50 runtime / 42 generated / 166 unknown. The three
focused gap queries extend the complete REA snapshot from 468 to 471 records,
with zero primitive cache entries, after an explicit successful close/save.
Checkpoint `.analysis/checkpoints/exact-mode-frames-283-111` links to splash 110.
The >=95% complete English-source goal remains active and unachieved.
