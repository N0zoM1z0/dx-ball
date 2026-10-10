# Exact mode initialization, redraw and cleanup

The three mode controllers in [runtime.c](../../../src/runtime.c) now call
the original owners directly. Their first stable VC4 compilation matches all
416 bytes: redraw at `0x4036B0` (127), initialization at `0x4038D0` (127), and
cleanup at `0x403950` (162).

Each controller reads the current display mode once and dispatches modes 0–4
to intro, game, editor, game-over or splash. Other values return without an
owner call. Cleanup forwards the full signed DWORD `fade` to the selected
owner. These are ordinary switches with final returns; the selector spills,
internal tables and trailing switch jumps come from the compiler.

The previous indexed ModeOps calls preserved most effects but hid the fifteen
original direct calls. The shared game API and the mode1 initialization,
redraw and disposal bodies stay unchanged. The native fixture adds twelve
typed forwards for the four non-game owners in each phase. They read the live
slots of the same copied-image ModeOps table; untouched defaults reach its
verified real owners. Cleanup uses its actual `void(DxBallInt)` signature.

Saved REA dossiers cover all 102 instructions and fifteen calls:

- Redraw: `ev_8771ae59b5d8c734a29634ce18f163f6247a0da754feadafe4cd8c76c008538d`.
- Initialize: `ev_ddf811bf45fa69ec6ed95204fd1225d97a5588d2ee943b2763d9afbbb4106742`.
- Cleanup: `ev_edf31fdc7ce974415c981438767f173e4b3666134e6650ef7e7b08a5e8c2cb91`.

One REA session read the three complete spans, filling fifteen missing jump
bytes and sixty table bytes. The resulting full reads are
`ev_559991ddd64e8b3235054ed44166837b75c9fd1bd9f00972195fc11adbce09d1`,
`ev_14b5b9eaba948c539a750307bf454a8e44ad09c4b35b87b240bf6ce66838b3bc`
and `ev_c4d6ac54ad2f975adcbcfe6266a6653708d89e878d9bd6791c45adbc51733657`.
All bytes equal the pinned PE. Each gap is a five-byte jump to the corresponding
post-table exit, following an unconditional transfer. Original source spelling
remains inferred. The provider closed with snapshot495; complete responses and
before/after snapshots are under `.analysis/main-mode-byte-review/`.

Nine whole comparisons apply 203 actual relocations. The three new units have
36; six previous exact runtime units have 167 and remain exact. This includes
the main dispatcher, whose six compiler label IDs changed. Its entire
unrelocated body and all six same-section label offsets remain identical;
bindings use the actual new IDs. No source or compiler alternatives were tried.

Only three unchanged existing Oracle loops ran, passing 149 cases once:
seven modes for each lifecycle controller and 128 dispatch-transition cases.
Other owner rows retain their historical case scope after input hashes are
refreshed. Native, VC4 and MinGW builds pass; the VC4 link reuses 35 valid
objects and compiles no additional sources. Totals are 143 exact functions,
23,090 code bytes and 136 metadata bytes.

Full inputs, objects, explicit bindings and receipts are retained under
`.analysis/exact-main-mode/`. This connects the exact main dispatcher to
original lifecycle calls across all five modes. Device reset and surface
synchronization remain the next related source boundary to inspect.
