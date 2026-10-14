# CRT case conversion

The complete `toupper` and `tolower` bodies at `0x418040` and `0x418130`
are exact:229 bytes each, with all14 actual relocations. `_isctype` at
`0x41AC70` now matches all145 bytes and three actual relocations.
The three complete pinned VC4 CRT sections independently match the original.

The shipped `ctype.h` macro casts the lead-byte table index to unsigned char.
Restoring that exact selection with the signed three-byte payload and consumed
payload/length order from `isctype.c` closes17 differences. Both229-byte converters
remain exact; all342 prior exacts and106 other candidates retain their verified
inputs/products. One compiler set, no runtime tests or provider work;
totals343/71,081 code bytes, candidates106. Receipt:
`.analysis/character-classification-macro-selection-20261014/verification.json`.

Source retains the C-locale fast path, shared `_pctype`/`__mb_cur_max` state,
lead-byte selection, observed NUL stores, locale backend calls and unsigned
two-byte result packing. Both3-byte mapping buffers are grounded by the call
capacity and stores. Classification returns one character's16-bit flags.
The table must back the original EOF slot and valid encoded input; locale/table
storage and the mapping backends remain dependencies, not invented host defaults.

Retained REA conversion dossiers: `ev_741079328a09289a6523e5a9365d6ca97b607694cbe5dd64cf98e1e917cddc67`
and `ev_b85e4d23ab3b7cd4d420c6629eca0ead2ace6d4c26aa6ec924e209ad525785d5`.
New classification assembly: `ev_47a036db560d67307ffa7aad537b42b78fdfebb00d193f40a063e500f094cc8e`,
closed run `2026-10-13T16-14-44.533Z-interactive-1819824`.
Two bounded VC4 compilations preserve both exacts; explicitly materializing the
classification high byte leaves the same17 register/scheduling differences.
Native/i686 standalone compilation and complete new-owner comparisons run;
all265 preceding exacts and69 candidates reuse unchanged inputs/products/results.
No game builds or runtime tests. Source346/exact267/65,205 code bytes;
candidates70, metadata136 unchanged. Private seal:
`.analysis/runtime-case-conversion-20261014/verification.json`.
