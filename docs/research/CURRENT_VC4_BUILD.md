# VC4 build and play records

October22 status: this is the retained **October20 build/play checkpoint**.
Maintained reconstruction has since reached266/270 authored exact functions
and79,767/84,968 complete exact code bytes; see the
[current handoff](../agent/HANDOFF.md). The later exact source changes have not
yet been relinked or played as a new game image. Counts and build inputs below
describe the historical tested products, not the current source checkpoint.
The standing priority is to finish authored exact recovery, then refresh the
VC4 game build and play verification.

October 20, 2026. The bounded authored-source inventory is complete: all270
identified authored functions have maintained source and complete comparison
receipts across30 compiler closures. The current split is **246 authored exact
functions and24 complete nonexact candidates**; exact whole-EXE reproduction is
not a completion requirement. The78 entries without project source are77
runtime-library functions and compiler-generated `__chkstk`, not unidentified
game bodies. Their x87, SEH and stack transports remain explicit dependencies
rather than invented project C/C++.

This record covers the first game build after the text-width, text-advance, signed
rotation-row, rotation-destination and last-brick crop-magnitude recoveries. It
therefore supersedes the older bff527e product record. Validation is deliberately
bounded to the two affected existing flows; no full campaign or historical
three-profile replay was run.

## Current local products

The current restored-CRT executable is built from source checkpoint
`e6d5b55e6c3673448b022d95f3b8057532345f66`. It is166,400 bytes, SHA-256
`6c2c0d1c7224bd6d99dec53d80e83da27f9980235ab0f6f538750ac3cce3c1d1`, at
`build/vc40-restored-crt/dxball.exe`.

The private bundle `build/delivery/dxball-v1.07-vc40-reconstructed.zip` is475,010
bytes, SHA-256
`dfd91617b6c121924e5dd7323fd80150a1463cabd100f06fb81627a1ba116e94`.
Its50 members are read back and checked by size, SHA and ZIP CRC: the directly
tested executable,48 unchanged supplied assets and unchanged extraction
instructions. The original score table is included; the automated test ranking
is excluded. The adjacent manifest records every member. Extract the complete
folder and run `dxball.exe` there. Products and supplied assets remain private.
The ZIP retains executable SHA-256
`c77d6d31bc4447d9ac13e1fa68cf8326f8620139c968bae6af30bb2c94cada86`.
The cold build differs only in six typed PE/resource timestamp fields; all
other file bytes, including the complete code, data, imports and resources,
are identical. Both product identities are retained explicitly.

## Build and linked contents

The pinned VC4 compiler10.00.5270/linker3.00.5270 first relinks118 verified
objects, then a separate cold build disables both source-object reuse paths.
The cold build compiles all118 objects from current source:115 source owners
and three integration objects, with zero reused objects. It retains19 explicitly
approved original CRT members under `/NODEFAULTLIB`. All current project inputs,
flags, source objects, original members, resource object and DirectX import
libraries are hash-verified against the cold-build receipt.

Current `build.json` is SHA-256
`1ad2ee8875c9e44144175814b4712f93bc2579fb1110fef0f0ef79364f540b99` and
the linked map is SHA-256
`d6165d8bfbe180a4ef5d5209057270e3075260866ac594f0dd5c2439320d55bf`.
This establishes the inputs of the rebuilt game, not original whole-image
identity. The prior complete linked-section proof remains evidence for its
older bff527e image and is not silently promoted to this executable.

## Completion audit

The audit inspects current source/compiler receipts and actual products rather
than using source counts alone. Its private authority is
`.analysis/completion-audit-20261020/audit.json`, SHA-256
`685c180b1dd84d3ef1cab1a7b0475cb26d9168ce4bde647044890f83ababde35`.

| Requested requirement | Current evidence |
| --- | --- |
| Recover the remaining authored code first | All270 authored address/source rows join the origin and implementation ledgers. All30 compiler closures and complete246 exact/24 candidate comparisons have current input/object/flag identities. |
| Complete the nonexact implementations | The retained22-candidate operation review and subsequent full capture/stretch/Y-offset correspondences cover the current24. The identified Blt, glyph, text, rotation and last-brick arithmetic gaps have adopted source corrections and focused original/native evidence. Remaining differences concern compiler emission and historical declarations. |
| Recompile the game | The maintained VC4 builder compiles118 source objects, reuses0 and links a complete Windows game with the19 approved CRT members. Every authored source owner is included. |
| Validate the actual game afterward | Current-source basic/editor and single-brick transition flows pass with152/133 state reads and exit0. Their exact tested EXE is in the delivery ZIP. The cold build is byte-identical after normalizing only one COFF and five parsed resource-directory timestamps. |
| Limit CPU and memory | The serial cold build takes238.593s at35% CPU; peak166,846,464 bytes,384MiB high/512MiB max, zero high/max/OOM events. |
| Clean disposable outputs | The49-file test runtime was verified and removed. Seven duplicate audit snapshots/helpers are member-verified in a135,966-byte archive, then removed, releasing688,128 allocated bytes net. Current tested delivery and useful build caches remain. |
| Keep focused checks and the required commit format | No historical replay queue, campaign or extra behavioral test is added. Published checkpoint subjects retain `gpt-6.1-sol: `. |

This closes the requested source/build/bounded-play workflow. The24 candidates
remain nonexact. Unique historical spelling, the final historical denominator,
arbitrary invalid-input behavior and physical-driver fidelity remain limits of
the evidence; they do not identify an unimplemented game function.

## Existing observations on the delivered image

Both selected flows use real Wine input and read-only process-state observation;
they do not patch, hook or suspend the game.

| Current flow | Observed result | State reads | Exit |
| --- | --- | ---: | ---: |
| Basic/editor | Opening/menu, live ball and paddle, pause/resume, editor paint, complete bank save/reload |152 |0 |
| Round transition | Real single-brick clear, score10, three lives, original board index1 with222 bricks |133 |0 |

The basic flow preserves the complete20,000-byte saved bank at SHA-256
`b88441eb5e06676a106501a60a450b8046fa7b880e8f53ffe5f556ae75a42cd2`.
The round flow reloads all400 bytes of original board index1 after creating and
clearing a one-brick editor board. Manual capture review confirms a coherent
opening screen, PAUSED overlay, editor palette/board and the next original board.
The report SHA-256 values are
`ced1f0b7d964c8617c2879ecf3ca7a523299b415562ec39e303f122371ff01ed`
and `be4f95b01197086ad55a8d2f7a455dba9b0ecab0043f4cc8ccf5e0df8bd18e73`.

All49 protected original files remain unchanged in each flow. Build and Wine
commands ran serially with35% CPU,384MiB memory high and512MiB max; audio used
the silent sink. The verified49-file isolated runtime copy was then removed,
releasing1,607,621 bytes. The delivery ZIP remains the runnable product.

These checks cover the affected startup/play/editor/render/transition paths.
Game-over was not repeated because no current change touches that path. Full
50-board play, focus/surface recovery, physical graphics/audio fidelity and
exceptional paths remain unverified. No exact or semantic ledger acceptance
changes.

## Retained history and evidence

The previous12ccdb1 image, SHA-256
`4d962eaaa2c6070047ffeb8e1edfb390f092a01b1f8e27eadda685242b217846`,
failed its20s return-menu deadline after pause/resume. Its cause remains
unresolved. Passing on the current image does not prove that historical cause
or identify a fix. Complete failed evidence remains under
`.analysis/current-vc4-refresh-20261019/`, together with retained image history.
The earlier717cc2f image and delivery have their own passing records in
[the preceding note](https://github.com/N0zoM1z0/dx-ball/blob/bff527e290098db516e3948905c92d1472ccb210/docs/research/CURRENT_VC4_BUILD.md).

The older bff527e private authority is `.analysis/current-vc4-build-20261020/`: complete
linked section/binding and loader proofs, frozen inputs, executed helpers,
observations/captures, complete banks/tables, per-flow verification/resource/
process receipts and all50 delivery member identities. Preserve unique evidence
before removing closed copied inputs/helpers or verified isolated runtime copies.
Nineteen closed copied-input/helper files are member-size/SHA verified in a
1,731,770-byte archive before exact-list removal, releasing1,654,784 allocated
bytes net before small receipts. All183 protected identities stay fixed.
Forty-nine isolated runtime copies are removed after matching retained current
image, original assets or the complete saved ranking, releasing1,724,416 bytes.
Current products, useful caches, manual runtimes and historical failure stay.

The current package helper, previous delivery backup and member verification are
retained under `.analysis/current-vc4-final-20261020/`. Future source work should
begin only from a newly evidenced authored gap; the24 nonexact authored bodies
are source-present and no longer block this reconstructed game.
