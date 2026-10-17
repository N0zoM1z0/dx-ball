# VC4 C++ frontend symbol traversal

October 17, 2026. The pinned C1XX name interner, bucket insertion and traversal
explain all16 current bank-loader objects in the previously observed C2 reader
order. This recovers a compiler mechanism; it does not recover original variable
names or make the1475/66 candidate exact. Counts remain394 exact/21 authored
candidates. No game source, compiler recipe or delivery changes.

## Target and evidence

`c1xx.exe` is775,680 bytes, SHA-256
`3376b1dfaff0bdb1018b13fbb22cf407858044f327d4bbc3e4d9335640aea7f0`.
REA6.5.0/Ghidra12.1.4 retains115 successful observations and five indexed
invalid-input results in
`.analysis/rea/vc4-cpp-frontend/runs/2026-10-17T15-22-12.705Z-interactive-3876461/`.
It closes and saves a separate frontend snapshot; the backend's86 records and
game snapshot remain separate.

| Primary observation | Evidence ID |
| --- | --- |
| Actual name-interner instructions,405BD8 | `ev_7e8c6aa653f05af7d7d80f21a5d4ef35c40d308622700855be0b46adb8d31f7b` |
| Stored hash word at405CD4 | `ev_34841013ad86fc72244ce1bd578d2ceca48a18ae926e8f672f1b6ee8fa01766b` |
| Hash-bucket insertion bytes,407CF3 | `ev_b4d08a3218a4a293dbab85f7507efe057171792c90522c218d31e2b31ead1630` |
| Hash-table output traversal bytes,40F16F | `ev_da6d775167e7413b670acb0acdae54f41a6d576bd82f9520d918ed0362f85efa` |
| Scope constructor,417DEA, including mask15 | `ev_28565faa79ba3a48018e2ace457584068c9d2dbc9da2e760644de0c8d40d26ae` |
| Function-end output-object traversal,417ED7 | `ev_0468dc1bd232ce921c2020884b0698ea90bdb2c8a678fcf7c2768c64aa3b46b7` |
| Output vtable4AB7D0 | `ev_4e49fa753bc68cc4103d737e6323519f44c1697f4abaaec9c1cf24df5731b7bd` |
| Sink selection,402D54 | `ev_58df9163007543b754a0bdb1c399ec7abbcbc95ffeca36e870f756cff31a4bbd` |

Several vtable methods lack imported function ownership. Retained byte ranges,
vtable references and decoded instructions supply the boundaries used here.
The67KB pseudocode for41DCDC follows shared regions outside its imported411-byte
body. The `symtable.inl` assertion branch and44A022 cold dispatcher block did
not establish an ordering algorithm; their bounded negative results remain saved.

## Actual mechanism

The name interner starts with unsigned32-bit `h=0`. For each nonzero name byte,
it computes `h = byte + (h >> 7) + 4*h`, with32-bit wraparound. Its own intern
table uses `h & 0x7ff`; the name allocation stores `h & 0x3ff` in the word four
bytes before the returned name pointer. These are distinct masks.

Insertion407CF3 reads the symbol's name pointer at`+8`, takes that stored word,
ANDs it with the scope table's word at`+0x14`, and prepends the symbol to that
bucket. Bucket heads are addressed through table`+0x10`; symbol`+4` links the
chain. Constructor417DEA initializes one scope-table kind with mask15. Other
tables exist: the49722C path also constructs a derived instance with mask255.

Output40F16F walks bucket0 through the inclusive mask value, then follows each
chain. Ordinary symbols reach40E8AF. Distinct type/scope handling and a deferred
pass are not exercised below. The output vtable points to40F16F at`+0x20` and
407CF3 at`+0x24`. Function-end417ED7 walks output objects from owner`+0x30`,
calling virtual`+0x20` before following object`+4`.

For the current bank source, the hash/bucket rule gives:

| Current declaration group | Predicted output order, with bucket number |
| --- | --- |
| Function locals | count0, cursor2, pitch5, row7, sprite7, saved_bank13, column14 |
| Sprite iteration | pixels0, code1, baseline1, pixel_count6, height9, width12 |
| Record allocation | record8 |
| Surface API workspace | key1, api12 |

The two same-bucket pairs demonstrate head insertion: `row` follows `sprite`
in declarations but precedes it in output; `code` similarly precedes `baseline`.
Concatenating the four current groups gives exactly the16 names in the earlier
actual [C2 reader trace](VC4_BACKEND_SYMBOL_RECORDS.md#current-bank-loader-reader-order).
C2's observed decoration adds a leading underscore; this frontend model hashes
the current source identifiers without it.

## Controlled check and limits

Private `.analysis/frontend-record-order-20261017/check-order-machine.py` maps
the complete hash-pinned C1XX image. It runs the actual complete name interner16
times, insertion16 times and traversal four times. All36 calls pass stack and
saved-register checks. Every stored hash, bucket and traversal position agrees
with the separately calculated recurrence and retained C2 trace.

Explicit synthetic inputs are an empty intern table/pool, four current source
declaration groups, table mode1/mask15 and kind9 symbols. The40E8AF emitter and
41DCDC header calls are intercepted as recording boundaries. This checks actual
helper execution and correspondence to a previous live C2 trace; it is not a
new live frontend trace or complete IL serialization/transport execution.
Actual live frontend table masks, all symbol kinds/flags and deferred paths are
not observed here. Original names/scopes/settings remain unknown.

The mechanism explains why declaration order alone does not determine current
stack homes. It supplies no original identifier spelling, aggregate ownership
or new lifetime model. Do not rename variables, permute declarations or vary
masks to manufacture a match. The root14/current API workspace control remains
closed at1475/72. New source changes still require independent game producer/
consumer evidence and complete affected comparisons.

The wrappers add only the closed, pinned `vc4-cpp-frontend` selection alongside
the existing backend. Nine Python dispatch/guard cases and six provider-free
JavaScript lifecycle cases pass; a mismatched compiler cannot save a snapshot.
One import is reused throughout. Its first query takes819,640ms; subsequent
requests reuse it. A Decompiler Parameter ID timeout and imperfect ownership
remain explicit limitations. No new compiler, replay, relink or game runs.

The session closes normally, removes its temporary Ghidra project and preserves
all115 records, five failures, final logs and a verified compressed snapshot.
The closed identical8.36MiB tool catalog shares an immutable verified carrier,
releasing8,658,944 allocated bytes after the frozen snapshot and cleanup journal.
The standard build-cleanup preview finds no additional disposable products.
Current tested objects, delivery and valid CMake caches remain. Six resource
observations retain one CPU, CPU35%, memory high640MiB/max768MiB, with no max/OOM
events; soft-high reclamation events are explicitly recorded.

## NameMap key generation, October18

A focused follow-up distinguishes numeric symbol keys from the scope-table hash
above. Full472-byte/137-instruction `48B887` writes a source symbol's DWORD`+14`;
that is a different object/field from the scope table's WORD mask at`+14`.
The earlier record40 already supplied pseudocode. New complete assembly and
byte ranges establish its actual branches and finite-width arithmetic.

For ordinary named symbols, it prepares a name and calls vtable slot`+8` on
the object reached through`[4B52B4]+4`, passing a name and output-index address.
The initializer at`498262` obtains that object through IAT`4BD1E0`:
the actual import is `MSPDB40.DLL::NameMap::open`. Both open sites pass the
root's`+4` as the output slot. Structured external parameter types remain
unavailable; the virtual query method is not named here. The fallback name
producer`40E15E` delegates to`40E028` or`44598F`, so a bare-identifier lookup is
not established.

On successful query, the exact machine formulas are:

```text
cached_word = (old_word & 7) | u32(output_index * 8 + 0x80)
returned_key = cached_word >> 3 = (output_index + 16) & 0x1fffffff
```

All eight combinations of the low three flags survive. The29-bit projection
matters at wrap boundaries; an unrestricted32-bit `output_index+16` is wrong.
Other paths use bounded descending/increasing counters for special flagged
symbols or a descending fallback for missing/sentinel names. The routine also
checks its high-water mark against the descending counter; diagnostic callees
retain their own boundaries.

The CASE5 caller, rather than`48B887` itself, reuses a nonzero cached key.
At`44A1F4..44A214`, it reads symbol`+14`, calls the generator only when the upper
29 bits are zero, otherwise shifts by three. The alternate mode reads symbol
`+18`'s low24 bits. The ordinary kind1 format includes CASE5. Complete retained
blocks cover both integer-byte stores and the shared output-cursor increment;
this is static encoding evidence, not a live transport observation.

The root selection writes`4B5E80` or`4B5BF8` to`4B52B4`. Decoding all30 reported
direct references finds one writer, at`426273`; this does not exclude alias
writes. Runtime NameMap outputs, serialized bytes and the actual current C2
`record+24` have not yet been observed together. That is the next bounded
producer question. Original names, settings, database state and reversibility
remain unknown; no name/order/header/type/flag or source-scope trial follows.

Primary assembly is `ev_7e18dcba42aaba6cc891b3a770d9234657d3568cd6b06559da2257b6229f9021`;
the exact NameMap import observation is
`ev_0845015b6bfd4027e49ca0b8a8397b39964b25355981e283198645b1f4f53675`.
The closed run`2026-10-17T19-35-55.498Z-interactive-132738` retains71 direct
records and74 Evidence records including composed-workflow substeps. Private
`.analysis/frontend-key-producer-20261018/` retains full byte checks, field
formulas, source/product identities and independent review.

This separately recorded profile disables `Apply Data Archives` and the earlier
timed-out `Decompiler Parameter ID`, keeping REA6.5.0/Ghidra12.1.4 and256MiB heap.
The old115-record snapshot remains in its already verified sealed gzip; the new
74-record snapshot does not mix profiles. First query takes327,899ms, followed
by fast same-import queries. Analysis succeeds and the owned temporary project
is removed after normal close. One CPU/35% and640–768MiB whole-tree limits hold;
peak671,612,928 bytes,2,868 soft-high reclamation events, zero hard-max/OOM events.
Canonical source, objects, delivery and394 exact claims remain unchanged.
No game compilation, replay, relink or runtime observation runs.
The closed identical8.36MiB tool catalog shares its verified immutable carrier.
Two prefix-only intermediate logs and the archive-covered old raw snapshot are
removed; the new snapshot's gzip carrier is decompression-hash verified. Cleanup releases
10,043,392 allocated bytes net of that archive and journal. Primary Evidence,
the current useful snapshot and tested game products/caches remain.

## Actual transport modes, October18

An unchanged current `resources` compilation tests the mode-zero cache branch
at `44A1F4`, rather than assuming the static NameMap path is active. CL, C1XX
and C2 all exit normally, but that C1 site has zero hits. The observer therefore
returns1 for zero selected samples. The C2 site has116 fully checked MOV
hit/step pairs and20 load-bank records. This is a bounded negative observation:
it establishes neither the actual C1 mode nor a cache/wire/reader linkage.
The raw local names are unprefixed (`count`, `width`, etc.); the function tag
has the separate spelling `_dxball_load_sprite_bank`. An unused positive
verifier's underscore-local-name assumption is explicitly excluded.

All18 complete affected functions,262 actual bindings and6 full literal
references remain identical to the canonical object. One CPU/35% limits hold,
peak292,057,088 bytes, with zero memory-limit events. No source variant, relink,
runtime case, provider query or full replay runs. Private
`.analysis/frontend-wire-reader-20261018/` retains the trace, negative verifier,
independent review and sealed archive. Twelve archive/member-hash-verified input
copies and products are removed, releasing225,280 allocated bytes net.

The retained assembly identifies a common entry at `401BD5`, the complete
four-byte `MOV EAX,[ESP+18]`. It preserves the previous mode comparison's flags.
The nonzero C1 mode bypasses the cache generator and consumes
`source+18 & 0xffffff`, with a two/four-byte WORD-based encoding. The C2 reader
has its own actual mode at `481844`; numeric mode values must not be assumed to
match between compiler stages. A common-entry observation can distinguish
these paths without changing any game source or flags.

The subsequent common-entry capture succeeds with one unchanged recipe. All28
selected C1 samples have mode1 and use `source+18 & 0xffffff`; source`+14` stays
unchanged. Six actual function tags disambiguate the samples. The16 bank locals
have source`+14` values6 or7, with no cached high key bits. Their actual
stream flags2/3/4 are nonzero, selecting sink`4B6090` before the mode-dependent
sink branch. Every selected sample writes two bytes; all28 independently decode
to the selected ID. This does not exercise the retained four-byte or compact
encoding branches.

| Current bank local | Selected/source`+18` ID | Actual wire bytes |
| --- | ---: | --- |
| `count` | 28268 | `6c 6e` |
| `width` | 28281 | `79 6e` |
| `key` | 28293 | `85 6e` |
| `api` | 28303 | `8f 6e` |

C2's actual decoder mode is0 for all20 bank records, consistent with this
WORD-based encoding despite the different front-end mode value. All16 selected
bank locals have one same-run correspondence by concrete key, raw local name,
function tag and encoding mode. The other four C2 records are the unnamed
record and parameters `path`, `allocation_mode`, `bank`, outside the selected
local whitelist. The function spelling differs only by its observed leading
underscore between stages; local spellings match directly. No event-order or
name-only join is used. The observer does not record C2 stream byte positions,
so these correspondences are not a byte-position consumption proof.

All413 trap hits execute the complete original MOV and pass register, ESP,
EIP, non-debug flags and actual C2-store checks. The28 entry/key/wire samples
and20 C2 samples each have their own checked single step. All three compiler
processes and the observer exit0, with no pending frame or read failures.
All18 complete functions/262 actual bindings/6 full literals remain identical.
Peak181,526,528 bytes, zero memory-limit events; one CPU/35% limits hold.
No source variant, provider query, full replay, relink or runtime case runs.
Private `.analysis/frontend-mode-wire-reader-20261018/` retains raw traces,
comparisons, independently checked summaries and reviews.

This actual recipe's key path is now `source+18 → selected ID → WORD bytes`,
with independently corresponding current C2 records. The static NameMap/cache
path remains a distinct mode and is not observed here. The next specific
producer question is the writer of `source+18` in this mode and its relation to
scope/declaration processing. It is not an invitation to vary names, scopes,
flags or context without independent game evidence. Original IDs, names and
settings remain unknown; exact coverage stays394 and the tested delivery is
unchanged.
