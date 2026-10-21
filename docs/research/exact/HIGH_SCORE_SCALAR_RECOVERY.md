# Exact high-score scalar and scope recovery

October22,2026. The complete404-byte `dxball_draw_high_scores` at0x406B20 is
now byte-exact. All seven previously exact game-over functions preserve their
complete code identities. Acceptance reaches **265/270 authored functions
(98.15%) and79,090/84,968 complete exact code bytes (93.08%)**. Five authored
candidates /5,878 original bytes remain. Overall acceptance is410 exacts,
93,474 code bytes and244 metadata bytes, with51 authored compiler closures.
The full270-function goal remains active and incomplete.

## Accepted source model

The old text buffer/count record remains. Its20-byte character buffer and
consumed count retain their original storage. Replace the three-field position
record with three real scalar values. Declare `i,x` at function root before
the text record, and retain `y` inside the existing row block:

```c
DxBallInt i, x;
struct { char value[20]; DxBallInt count; } text;
{
    DxBallInt y;
    x = 10;
    y = 170;
    /* Existing loop and direct i == selected comparison follow. */
}
```

All original executable operations, assignments, equality, score reads,
formatting, drawing calls, row advancement and unsigned coordinate arithmetic
remain. Inverse member/alpha substitution plus declaration removal preserves
the executable token stream. Fundamental scalars introduce no initialization
or destructor effect; their addresses never escape. The seven companion bodies,
headers, public ABI, globals and21-input/nine-flag recipe stay unchanged.
Portable and legacy builds share this same source.

The selected model restores every byte and the original36-byte frame: count−4,
buffer−24, X−28, index−32 and Y−36. This reconstructs an admissible declaration
model, not uniquely recovered historical names/scopes or newly observed C1 IDs.
Emitted equality establishes acceptance independently of inferred allocation or
rank rules. The resolved/original SHA-256 is
`959791bee9e179eacff224e879a9b6806acf8df639def3e0be307bdcee37c136`.

## Finite source families and useful negatives

The [retained row correspondence](RANKING_ROW_RECORDS.md) accounts for all135
instructions and the original403/404-byte difference. The earlier standalone
C/C++/header contexts retain the position record and do not solve it.
This follow-up tests distinct real scalar/scope and predicate contexts:

| Family | Successful compiles | Complete renderer result |
| --- | ---: | --- |
| Six scalar declaration orders in the old row block |6|Three403/330 and three403/334; seven prior exacts survive.|
| Five consumed-include orders on the usable scalar model |5|All403/330; reject.|
| Two defined unsigned-difference zero predicates |2|404/1 and403/330; reject.|
| Two modular sums with a negated index |2|Both406/348; reject.|
| Unsigned/volatile direct-equality read views |4|All403/330; reject.|
| Real scalar scope cohorts |3|Two403/330, then root i/x before text gives404/0.|

The last family freezes six models but stops after its third compile; the three
remaining positions are never compiled. Exactly22 distinct frozen input/flag
digests compile once. Comparisons cover176 complete function instances and5148
actual code-binding occurrences. All tested owners preserve the seven prior
exacts. None of the rejected arithmetic, qualifier or include views is adopted.

The404/1 arithmetic candidate differs at offset51: original opcode39 is CMP,
while actual2B is SUB. The initial description as only a CMP-direction change
is corrected against the retained actual bytes. Although the unsigned predicate
is equivalent for all DWORD pairs, this opcode difference is kept strict; no
patch, mask or partial acceptance turns it into an exact.

## Whole-object and relocation proof

The first compiler exits0, but the initial mapping correctly rejects a renamed
local `$L1346`. A separate report pass reuses that existing object, mapping
generated `$SG/$L/$T` families by actual logical section, value, type, storage
and auxiliaries. Numeric names can be reused for different roles and are not
treated as identities or recursively remapped. No producer is repeated.

The accepted whole object covers all eight complete functions,234 actual code
bindings and13 complete literal references/carriers against the original PE.
All110 non-FILE symbols have a bijective correspondence; all raw auxiliary bytes
are checked. Only the target code section's length403→404 changes in its
auxiliary record. Section flags, relocation counts, COMDAT selection, all other
auxiliaries, complete noncode payloads/relocations and global definitions agree.
The unchanged full comparator and exact local-target guard apply, including
actual switch-label destinations in companion code. No literal or byte is masked.

Publication's first formatter leaves old nested relocation-array tables behind
its replacement and fails parsed-TOML equality before any write marker. The
repair replaces each full primary table and its children, retains complete
parsed-manifest equality and reuses the successful compiler/native results.
Tracking then passes; all eight canonical units reproduce the accepted complete
comparison from the installed object without recompilation.

## Maintained verification and retention

Native incremental build changes only gameover.c and the shared-library link,
preserving59 companion objects and all62 prior command configurations. The
existing selected-row loop passes17 original/native cases: every row0–14 and
outside selections−1/15, with complete state and ordered text/line effects.
The full existing setup, mode/key-table and default checks stay intact. The
verified fixture cache is unchanged with zero preparation invocations. No
insertion, editing, lifecycle or game campaign is repeated. All249 historical
semantic scopes/counts/order/oracle fields remain; current dependency hashes
refresh without representing the historical sets as newly rerun.

Heavy work is serial on CPU0/35%, memory384/512MiB. Maximum observed compiler
scope peak is156,073,984 bytes; focused native peak is67,969,024 bytes, with no
memory events. No new provider/debugger session, game relink/play or physical
driver claim follows. The tested game delivery remains its historical image.

Private authority is
`.analysis/ranking-scope-source-search-20261022/current-checkpoint.json`, with
the selected x-index-before-text producer/comparison, complete auxiliary proof,
installed comparison, native summary and adoption. Unique closed inputs,
outputs, helpers, mapping/formatter failures and plans are member-size/SHA/mode
verified in a recovery archive before obsolete copies are removed. Current
accepted objects, native library, fixture cache and useful build caches stay.
Cleanup verifies676 archive members and retires651 obsolete files, releasing
5,505,024 allocated bytes net of the archive before small index/receipts. The
overwritten checkpoint's rollback archive is recoverable inside that archive.
