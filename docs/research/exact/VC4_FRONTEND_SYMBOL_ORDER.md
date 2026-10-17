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
