# Clock detection and key routing

The clock and input controllers in [platform.c](../../../src/platform.c) now
follow the original calls and branches. The clock detector sets the version
record size to 148, calls GetVersionExA, then writes zero for platform 1 and
one otherwise. VC4 reproduces its complete 83-byte body.

The key dispatcher calls the five actual owners: menu, game, editor, game-over
and splash. Its complete 162-byte span is exact, including the five-entry
switch table and the jump beyond the last arm. The splash call pushes an
argument that the callee ignores. Their shared API now takes `char`; the
original declaration's full parameter type is unknown. Splash's existing
36-byte body remains exact.

Game input preserves the two pause paths, Control-gated F1–F4 bonus and paddle
writes, F5 music selection, F6 music shutdown and F12 pan reversal. F5 chooses
before closing music, then calls the loader directly from six switch arms.
All six original filenames, including `acker-gs.mds`, and the eight-byte
`-1.0` constant are attested against the executable. VC4 emits 836 bytes for
the original 831-byte span; 522 positions differ, so this unit remains a
candidate. The maintained body is shared by portable and legacy builds.

## REA evidence

The three dossiers cover 216 instructions and 21 call sites:

- Clock: `ev_dc0dafecc27f037b35f96d78484d3582f5e70e4666096d803238dfccb02c6c96`.
- Dispatcher: `ev_ac5f83bb902255b7f7e010c66c9f6f8ddd53fe3dc3d95f96621ab1c202bf4f39`.
- Game input: `ev_a1126b60967546aced7cce45fa25634c65245ad3a415585374561d88ccbbaccb`.
- Splash callee: `ev_d1c87d90c887ddeb6eefe0dcd882a3c99b7c1bbfa0c5ffdad565e81e696538ac`.

Full reads complete the dispatcher and game-input spans:
`ev_8991b924a73b858da11e77034293d8da4f1c061b045313913a38750cf834b762`
and `ev_1df32140229eb7c88b6fe57d48814e8f138354ceeba1fd2a604233504998357a`.
They cover the jumps at `0x40388B`, `0x410498` and `0x410508`, the five-entry
dispatch table, six-entry music table, fifteen-entry key table and all 92 key
selectors. The music-string and floating-point reads are
`ev_0ed0ce7a7e43a9c4e3df7dc49d662d57ee68adac5787ea561ae59877706e2c19`
and `ev_0b47cf91071be94b7d351ae265192887b6ac073aaa52e35ee67d437c90b7f649`.
Original source spelling around switch-end jumps remains inferred.

## Result

The shared header affects 25 recipes, each compiled once. All 122 affected
accepted functions remain exact. Anonymous COFF symbols that changed names
retain their full literal contents and original targets. The complete batch
compares 126 units and 1,418 relocations, including the existing WindowProc
candidate. Totals rise to 138 exact functions and 21,538 code bytes, with
136 metadata bytes.

The existing clock, dispatch and game-key checks pass: 10 + 1,792 + 420 cases.
Four typed native forwarders connect the current callback slots to the direct
owners. Case bodies are unchanged. A private final counter assertion included
unused zero counters on the first invocation; after correcting that assertion,
the second invocation passed. Both runs and drivers are retained.

Native, VC4 and MinGW builds pass. The VC4 game reuses 26 valid objects and
compiles nine remaining sources. Full inputs, objects and receipts are retained
under `.analysis/checkpoints/exact-window-key-283-138/`.
