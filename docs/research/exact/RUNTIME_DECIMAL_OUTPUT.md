# Extended decimal output and multibyte classification

Three complete CRT bodies now have shared standalone C source. The lead-byte
entry at `0x0041BEF0` is exact across18 bytes and its actual call relocation.
Its private classifier at `0x0041BF10` retains58 bytes/seven register differences.
The full923-byte `$I10_OUTPUT` at `0x0041EF20` currently emits922 bytes with535
differences. Neither candidate is counted exact. Previous276 exacts and77
candidates preserve their source inputs, compiler products and results.

`runtime_decimal_output.c` restores the serialized80-bit by-value argument,
26-byte output record, all four complete special-value strings, decimal exponent
estimation,12-byte one-tenth constant, scaling, digit extraction and rounding.
Precision is capped at21; the22-byte digit array includes the generated guard
digit. Finite callers supply nonnegative precision unless flag bit0 requests
fixed-point adjustment, and avoid signed overflow of precision plus exponent.
Character cursors cover the entire output record; backward rounding scans may
reach its length byte without forming a pointer before an array/object.

`runtime_multibyte.c` preserves the unsigned-byte argument truncation,257-entry
shared table contracts and conditional ctype value. Table storage and runtime
integration remain open. No native long-double ABI or locale/game acceptance is
claimed; native pointers and existing shared conversion dependencies are unchanged.

Complete pinned `x10fout.obj` and `ismbbyte.obj` sections, all actual relocations,
the retained full original REA byte observation and the retained decimal
pseudocode/assembly ground these boundaries. No new REA session runs.
Private evidence: `.analysis/runtime-decimal-output-20261014/verification.json`.
Only affected native/i686 standalone compilation and whole VC4 comparisons run;
there are no runtime tests or game builds. The first nonintrinsic compiler product
is retained, but its comparison stopped at an unmapped memcpy binding. Original
inlined copies justify the final `/Oi` recipe. Guard/value lifetime recovery reduces
decimal differences854→758→557→535. Conditional classification reduces34→7;
separating its phases worsens7→39 and is reverted. No blind register/name search.
