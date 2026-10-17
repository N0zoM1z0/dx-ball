# Exact bonus generation scopes

Bonus generation at `0x4138D0` now matches the entire 1,197-byte original extent
and all 89 relocations. Three accepted companions retain their exact 2,287 bytes.
The total advances to 190 exact functions / 36,559 code bytes / 136 metadata
bytes, with source presence and origin counts unchanged.

[`src/bonuses.cpp`](../../../src/bonuses.cpp) restores creation-success, particle-loop
and rare-reward case scopes. Screen x/chance remain outer; screen y/kind belong
to the creation branch; each loop and rare case owns its temporary. These typed
scopes reproduce the original 36-byte frame, including the compiler selector.
Names, types, operations and RNG order remain intact. No padding, fake locals,
machine-code patch or name permutation. Original identifiers remain unknown;
exactness establishes the complete emission under the pinned compiler.

Two bounded compiles are retained. Particle/case scopes leave six chance/y-home
differences; the creation-success scope removes them. All three companion exact
functions pass in both stages. Only the final matching object enters production.

The original dossier contains 260 instructions and 1,116 owned bytes. Complete
comparison additionally includes the five-byte `e960000000` jump at `0x413D08`
to `0x413D6D`, and all 76 bytes of the nineteen-entry table at `0x413D21`.
The old candidate mistakenly bound the table label to case 13 at `0x413C28`.
The corrected address follows the original indirect jump at `0x413D1A` and all
nineteen independently read original pointers. The defining COFF label is at
offset 1105. A final-object control restores the wrong binding and rejects both
differing address bytes. No table, relocation, gap or epilogue is masked.

Two unchanged generation loops from the maintained entities oracle pass all
1,750 original/Native cases: nineteen kinds, five rare outcomes, three particle
flags, three positions, count/chance gates, complete queues/allocation ownership,
ordered RNG consumption and audio/particle events. A private AST selector retains
the existing case and comparison subtrees; unrelated particle grids are omitted.
No tests change, new provider session or full gameplay replay.

Two canonical VC4 `/MT` compiles bind 22 project inputs. The final object is
linked with 35 verified unchanged objects, without another legacy source compile.
Native/MinGW rebuild the affected owner and products. All 190 exact input/object
closures and 36 game-object closures verify; 247 historical semantic scopes and
case counts remain unchanged, with 235 input closures refreshed. Complete game
fidelity, other owners and original declaration spelling remain open.

Original REA Evidence:
`ev_ef8ebb1d4341bf24e0f31fba3bfb64c963503539c43bd3f13e61c367b4d84aed`.
Its target identity and closed session reverify. Private
`.analysis/bonus-generation-scope/` retains both stages, complete comparisons,
table/gap proof, negative control, unchanged selected-case identities, production
receipts and final review. Its immutable checkpoint preserves new products
independently of current paths and references prior carriers without copies.
