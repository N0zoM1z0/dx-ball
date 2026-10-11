# Intro-point pixel storage and timer exit

The point controller at `0x40ED40` now retains the original consumed pixel
pointer. It loads the descriptor's pixel base into that pointer, adds the
combined row/pitch/point/offset displacement, then writes palette index 200.
The expired-timer guard uses the observed early return. The same natural C
serves the portable and legacy builds; no unused request variable is introduced.

One stable VC4 intro compilation produces 682 of the original 711 bytes, with
604 unmasked differences in the complete relocation-applied comparison. The
preceding body was 666 bytes with 637 differences. All forty actual relocation
targets, types and addends are preserved. All thirteen accepted intro units
remain exact; the seven complete candidates are compared together. Other
candidate differences remain unchanged. Source presence, semantic scopes and
the 186-function / 33,001-byte exact ledger do not increase.

The closed REA dossier
`ev_380287bfea6a4f582b8e8ee477b5c7d470de69c6555f3ab997e0f5f7d4650b2d`
contains all 180 original instructions over the contiguous 711-byte span.
Its original-target SHA-256 is
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
It is reused without another provider call. The full carrier remains private;
the new receipt records its path, digest and Evidence ID.

All 178 current instructions correspond to retained original instructions
through an explicit bijective mapping of eleven frame references. Every
retained operand and all fourteen direct branch targets correspond, including
the timer exit, HRESULT retry and both point loops. Descriptor and rectangle
field offsets remain consistent within their records. This structural proof
does not change the strict complete-byte result.

The remaining structural differences are stack allocation and two original
stores at `0x40ED77` and `0x40ED7E`: size 100 at frame offset -116 and zero at
offset -36. The 100-byte interval has no other frame references, its address
is never formed, and no direct branch targets either store. Its type and source
origin remain unproved. These writes are retained as an explicit restoration
gap; they are not masked, reproduced with fake locals, or assigned a speculative
resource role. Original identifiers and declaration order are also unproved.

All 36 existing timing/wrap/lock-retry point cases and 58 separate connected
splash/menu/editor-request checks pass against the final native library. The
first connected run exposed an outdated fixture assumption: its native
descriptor callback allowed only the intro caller's fixed size 108, while the
shared glyph renderer uses the actual host `sizeof`, 120 here. The typed native
bridge now admits those two concrete sizes with flags 14; the original Oracle
still requires size 108 and flags 14. Case bodies, matrices, ordered effects and
complete storage/list comparisons are unchanged. Failed checks are retained.

Native and MinGW builds compile the changed intro owner and relink. VC4 reuses
the matching intro object plus 35 verified unchanged game objects, with no
additional source compilation. The 235 affected historical semantic input
inventories are refreshed without claiming their earlier suites reran. Private
receipts, products and scoped preservation records are under
`.analysis/intro-storage-dataflow/` and
`.analysis/checkpoints/intro-point-storage-283-186/`. There is no new physical
gameplay, arbitrary driver/caller-stack observation or complete-fidelity claim.
