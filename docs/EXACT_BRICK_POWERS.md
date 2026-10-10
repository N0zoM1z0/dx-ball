# Complete brick hit and board power restoration

This family restores the complete maintained source for brick hits at
`0x411F40`, explosive-neighbor conversion at `0x4150A0`, special-brick
softening at `0x415410`, and destructible-brick counting at `0x415A90`.
Source restoration, existing differential validation, and exact compiler
acceptance are recorded separately.

The full REA/Ghidra primary observations are
`ev_d09866ff22dc07f3ac28ef1d992c5876c1e58e1796dbe0f0c5c2814544aa27eb`,
`ev_3d377be2b21a0bacfa9d8a165f08def8fa9f77830b0d0fe671d3aaedbf5ac7cf`,
`ev_2658970814be31782b2c65645873f87b091af5efdba4f7936cd30159a223cf4b`,
and `ev_a3ef22630731d5acabc8242cde15f9f53faed00efd493b43428731c7a2caa2dc`.
Static evidence establishes instructions and recovered data accesses; it
does not recover original variable names or prove runtime behavior.

The hit body owns 1,244 bytes in two instruction ranges within its 1,315-byte
enclosing span. Its embedded switch tables require separate raw-byte evidence
and complete relocation reconciliation. The other three bodies are contiguous:
824, 397, and 149 bytes respectively. No ownership claim treats the gap as
additional executable instructions.

Hit restoration preserves signed selection, live tile reads, separate strength
transitions, direct effect/audio/RNG/particle calls, two particle loops, and the
full EAX score flag. Explosive conversion first collects the original sources,
then applies four independent neighbor blocks. Softening uses three sequential
live tests; counting excludes empty and hard bricks. Source declarations retain
consumed coordinates and counters without declaring compiler selector scratch.

The stable grouped replay and configured cold epoch establish the separate
acceptance scopes below. Existing cases remain the validation boundary.

The new raw REA evidence is
`ev_10cd80841785844ec7987b1228fd13206abe8f30d844d3451dcba1b4d16b7fdc`.
It returns all 71 gap bytes: 12 DWORD case targets and 23 selector bytes. Each
selector resolves to the full saved primary case mapping. Ghidra's recovered
11-entry count is incomplete. Every gap byte remains compared; ownership is
unchanged. The actual one-read provider session closes and saves the complete
474-record / 0-primitive snapshot.

One maintained diagnostic gameplay object physically freezes all 69 inputs.
All six preceding gameplay exact units remain zero; its previous queue candidate
is reproduced. Softening 397/counting 149 are whole zero units; hit 1,316/1,315 retains
418 differences and spread 844/824 retains 753. No additional source/body or
name/order/layout/capacity trials follow. Consumed source coordinates and loop
counters are retained; automatic selector storage is not invented as a local.
Original declarations, spelling and nonexact storage homes remain unknown.

The first mapping attempt assumes original embedded table offsets. The actual
hit candidate shifts its table by one byte; the complete failure log and driver
are retained. The corrected mapping binds the actual 12-entry table and identical
23 selectors to the full original raw table and primary cases. It preserves all
actual relocation offsets, addends and types. No compiler or source mutation is
used for this mapping correction. All 138 new actual relocation operands and
14 internal table bindings are explicit. Two prior generated literal names
refresh only after full literal/target equality; all seven changed-owner prior
accepted/candidate units are compared. All mappings are fixed before
Native replay is frozen, and whole candidate differences remain visible.

One configured 22-object cold epoch accepts 115 complete zero units / 17,678 code
bytes and 136 separate metadata bytes; all preceding 113 complete code/metadata
identities survive. The two new exact bodies add 546 bytes. Both new nonexact
comparisons reproduce the maintained diagnostic counts. Existing candidates
remain separate, including the paddle build outside this cold epoch.

Strict serial Native succeeds on its first attempt. The final 22 existing owner
scripts pass in 741.136 seconds against 291 physically frozen inputs. The seven
checks pass: whole cold replay, 14 existing rejection controls, actual cold raster
product adoption, 7,164 fresh raster vectors, 1,024 fresh rotation vectors, strict
MinGW and full VC4 builds. Adoption records semantic_driver_executed=false and
runs no additional compiler. Existing cases, target oracles, campaigns and
fixture bodies outside GameNative's constructor remain unchanged.

The minimal shared harness adds one typed
`dxball_spawn_brick_effect(DxBallInt, DxBallInt, DxBallByte, DxBallInt)` wrapper and a
private verified-real-body setter. It reads the current live slot, preserves
uint8 tile width, and guards null/default/self/reentry with the actual copied
source body. The prior 43 C function bodies remain identical. Constructor changes
select the owned copy before inherited setup and bind after the six existing
callbacks. The shim verifies 37 real symbols / 38 production default slots and
48 actual compiler dependencies. Effects owner adds only its four consumed
loader/shim/resource-control inputs. This is host forwarding evidence.

Native family/canonical SHA256 `7edcc33d4c2a090731ba17a5654e1b22c6b26b9e13d7badd27acfe96faff380f`; shim `0b1a5d56662168602b5d154a06b1b5002fcf9d9ce5f8030e97d7a1fe3f5211dc`.
Source presence stays 283, scoped semantic rows 247, unit-distinct cases 112,273;
235 actual semantic closures refresh with fixed cases,
addresses and scopes. Origins stay 270 authored / 50 runtime / 42 generated / 166
unknown. Checkpoint `.analysis/checkpoints/exact-brick-powers-283-115` links to
bonus-phase 113. The >=95% complete-source goal remains active and unachieved.
