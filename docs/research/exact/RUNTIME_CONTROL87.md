# Abstract x87 control entry

`src/runtime_control87.c` restores the complete ordinary control layer at
`0x0041CF30`, `_control87`. Its 68-byte VC4 body compares against all 63 original
bytes with four actual bindings and 44 differing positions. It is a complete
nonexact candidate. The genuine 52-byte `_ctrlfp` hardware backend remains a
library dependency; no replacement hardware implementation is claimed.

The original reads the x87 control word, calls the recovered hardware-to-abstract
converter, merges `(old & ~mask) | (value & mask)`, calls the inverse converter
and unconditionally loads the resulting hardware word. It returns the full
32-bit merged abstract value, including bits without a hardware representation.
In particular, mask zero still canonicalizes and writes the hardware word.
The pseudocode omits that physical write and the inverse converter's argument;
the complete assembly establishes both.

The C implementation uses the existing typed `_ctrlfp` boundary to read and
write hardware. Its read performs an additional same-value control-word write.
Final control state and return behavior agree in the checked states, but access
sequence and pending-exception delivery timing are not claimed identical. The
read's sign-extended return is explicitly narrowed to the actual unsigned
16-bit word before abstract conversion. No guessed register state, assembly,
copied instructions or artificial argument is introduced.

## Original and source evidence

REA 6.5.0 / Ghidra 12.1.4 queried only assembly and pseudocode for this entry:

- Assembly: `ev_5802dd9ae322e87820f82a7b79f48a4d2195266b98ccca4e016ca3bb103f6c4c`.
- Pseudocode: `ev_222956f1a92e6b84c71a94a393f56eb6c69ce21e4bcc41daedb88717ddb0fe93`.

The session closed and saved normally. Complete responses are in
`.analysis/rea/runs/2026-10-16T12-46-07.263Z-requests-865796/`.
Retained whole-CRT bytes from
`ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`
cover the full function. The pinned `ieee87.obj` section agrees after its two
actual converter relocations. Both converters, 161 and 141 bytes, and the
relocation-free 52-byte `fpctrl.obj` hardware entry independently agree with
their previously grounded complete original sections. The existing accepted C
converter objects have identical bytes and unchanged complete inputs.

The hardware backend's prior assembly is retained as
`ev_07b9d75df739075b7b823b8a69d32f9b8289cf3c9c9c2619cd86515b2d1fca64`
under `.analysis/rea/runs/2026-10-13T20-53-53.317Z-interactive-2116938/13-procedure_assembly.json`.

## Focused checks

One compilation per VC4, native and i686 profile checks the new source owner.
Strict C90 native/i686 builds pass. All prior source and header inputs remain
unchanged; the old 380 exact and 91 candidate products/results are reused.

There are 1,792 logical control cases: all four precision and four rounding
encodings, varying exception masks, every abstract bit set and cleared, zero
and full masks, defined groups and mixed unsupported bits. Original, VC4 and
i686 emulation execute the actual original hardware entry and byte-exact
maintained converters. Complete return values and final control words agree;
status/tags, cdecl stack balance, saved registers and stack-only writes pass.
The native C comparison uses a typed hardware-state fixture and reuses the
previous native converter object.

A custom-entry VC4 executable runs the same 1,792 cases with actual x87
instructions under Wine, without host CRT startup. It compares original
controller/converter bodies with the maintained C bodies through the genuine
pinned physical backend. Return values, final control words and status words
agree. Only two original COFF symbol names are changed to allow both versions
in one image; every code, data and relocation byte remains unchanged. Six whole
controller/converter bodies also agree with their actual linked image bytes.
The original member's unused fpreset dependency uses its genuine precision
member and a typed null information-pointer fixture; fpreset is not exercised.

An initial fixture link exposed those two unused dependencies. The repaired link
succeeded; a subsequent receipt-path error was fixed by inspecting and running
that already linked image. No production object was recompiled or relinked for
the receipt repair. These are bounded control-word checks, without pending
unmasked exception delivery, full reconstructed FP startup or final game claims.

Private evidence is `.analysis/runtime-control87-source-20261016/`, including
`original-proof.json`, `source/{product,comparison,portable}.json`,
`differential.json`, `windows-link.json`, `windows-probe.json` and `adoption.json`.
Heavy commands run serially with CPU 35%, memory high 640 MiB/maximum 768 MiB
and Ghidra heap 256 MiB. No full replay ran. The 249 historical semantic rows
are byte-identical. Current totals: 472 source entries, 380 exacts, 92 complete
candidates and 73 inventory entries without source.
Sharing six byte-identical immutable snapshots/member carriers reclaimed about
2.1 MiB; all unique evidence, source products and mutable build objects remain.

## Bounded inventory follow-up

Before selecting this entry, a complementary library scan checked 141 code
sections excluded by the earlier single-function predicate. Its 39 complete
fixed-byte/repeated-binding matches expose no absent type-32 entries. Another
49 single-function sections of 5 through 15 bytes, with at least two fixed
anchor bytes, produce no wholly unowned match. Both retain the same three
ASCII-name parser skips. These are discovery bounds, not exhaustive inventory
or independent relocation-binding proofs. Receipts remain under
`.analysis/crt-multi-entry-scan-20261016/`; neither scan ran a provider or compiler.
