# Mantissa iteration and 96-bit arithmetic

The complete zero predicate now matches all 29 bytes. Indexed three-limb
iteration preserves its original EAX counter and ECX pointer. The 102-byte
little-endian addition also matches, including all four actual carry calls.
Totals are 249 exact functions / 63,697 code bytes / 136 metadata bytes and
302 source-present functions. Ten affected exacts retain 502 bytes and both
full format records; 239 other exact producers and 34 authored candidates
are reused unchanged.

Three little-endian arithmetic bodies are recovered in the existing
`runtime_mantissa_arithmetic.c` owner. Addition preserves the original nested
carry propagation and ordered loads/stores, including aliasing. Both one-bit
shifts capture the outgoing bits before changing any limb. They remain
candidates: VC4 removes their explicit masks. The big-endian shift separately
accumulates the shifted word into its carry before its second store.

| Runtime candidate | Current/original bytes | Differences |
| --- | ---: | ---: |
| Rounding | 163/172 | 153 |
| Copying | 29/29 | 5 |
| Big-endian shifting | 172/173 | 134 |
| Scalar addition | 35/35 | 5 |
| Binary conversion | 459/459 | 94 |
| Left shift96 | 50/62 | 47 |
| Right shift96 | 48/54 | 35 |

An original-style countdown copy worsens five differences to eighteen and is
rejected. Capturing carry masks separately produces the same shift bodies.
Disabling global optimization enlarges all four arithmetic functions and is
rejected. The unchanged normal recipe remains authoritative. Shared-header
context changes the converter and shift allocation; their full differences
are retained, not summarized as semantic acceptance.

Closed REA run `2026-10-13T10-31-33.913Z-requests-1407849` provides information,
pseudocode and assembly for all three new bodies. Assembly Evidence IDs are
`ev_623c6589217ebc640b8f63d53fc8c92a5af21577400fa094d004d4fe8d4ee0a9`,
`ev_f1493a27dd977038ff4d9d55a829c251d66cedbbee73380a0cce548448f58259`
and `ev_6e767a83a03a591ebb03a1450da8a14030f6f37d10e3abd5d8a772ad9adeaa52`.
Their contiguous bodies cover 102, 62 and 54 bytes. The zero predicate reuses
the complete original evidence in [the preceding note](RUNTIME_MANTISSA_HELPERS.md).
Actual source stages, producers and all seventeen comparisons are retained in
`.analysis/runtime-mantissa-lifetimes-20261013/`. Both owners compile on VC4,
native and i686. No runtime test or game build runs. Parser recovery,
remaining exact gaps and game integration stay open.
