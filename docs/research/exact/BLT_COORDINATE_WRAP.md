# Blt destination-edge arithmetic

October19,2026. All three rectangle-based sprite adapters now preserve the six
original DWORD edge sums before storing signed RECT coordinates. Keyed/plain
Blt retain live signed sprite-width/height reads; stretch retains its signed
width/height arguments. Calls, flags, ownership and storage stay in the shared
source. Original cast spelling is not claimed.

```cpp
destination.right = (DxBallInt)((DxBallUInt)x + (DxBallUInt)width);
destination.bottom = (DxBallInt)((DxBallUInt)y + (DxBallUInt)height);
```

## Original consumed operations

Three retained REA carriers establish the complete adapters and their consumed
DWORD results. Each ADD/store reaches the actual Blt call without an overflow
guard; nine plain-Blt and fourteen keyed/stretch instruction encodings are
independently checked against the pinned original PE.

| Adapter | Right ADD | Bottom ADD | Blt call | Flags |
| --- | --- | --- | --- | --- |
| Keyed |403FA4|403FC9|404026|1008000|
| Plain |4040E4|404109|404166|1000000|
| Stretch keyed |404208|404211|40426E|1008000|

Evidence IDs:

- Keyed: `ev_d6a0ba45ee8be3066c16e73824427edf3c335d36babf08a5ba613971e6a8d6c0`.
- Plain: `ev_1b6c1b404e87fc6a492e8b2ed1d3eea8020a9f5446a6c5eaf8d76b4a0533df40`.
- Stretch: `ev_a1de6b1fd71e04e5cb19b2cd96c5b604b588748746650f4a7e2bb791e0220953`.

Six finite witnesses execute the actual bank loader and selected adapter. Each
17-byte SBK prefix publishes sprite1 after a failed CreateSurface call; the
low32 bitmap product is zero and its allocation is three bytes. Plain/keyed
cases use width `INT_MAX`,height0,x1 or width0,height `INT_MAX`,y1. Stretch uses
a zero-size loaded record and the corresponding explicit extent arguments.
Right/bottom become `INT_MIN`. A typed failing Blt accepts the NULL source,
records the full destination/source rectangles and returns-1 without rendering.
Bank state,pixels,padding and the descriptor set stay fixed during the adapter.
The original file-stream leak and partial publication remain unchanged.

All six old-source instrumented runs fail on the specific signed sum; all six
restored runs agree with the original consumed rectangles. The canonical native
library passes the same six witnesses. These are loader/adapter boundary checks,
not whole-game or physical-driver evidence.

## Complete comparison, including losses

One VC4 compile compares all18 resource functions,262 actual bindings and six
whole literal references. The complete results are adopted together:

| Unit | Before current bytes / differences | Adopted current / original bytes / differences |
| --- | ---: | ---: |
| Plain Blt |199 /173|195 /195 /0|
| Keyed Blt |195 /0|195 /195 /0|
| Stretch keyed |139 /0|141 /139 /94|
| Capture |852 /0|864 /852 /726|
| PCX |979 /851|979 /862 /851|

Plain Blt gains a complete195-byte exact with ten actual bindings. Stretch and
capture are explicitly demoted. Net change is minus one exact/minus796 code
bytes:392 overall exacts/83,837 code bytes/244 metadata bytes,247 exact and23
nonexact authored functions. Fourteen other raw/resolved code identities stay
fixed. Nine prior resource exacts survive; plain Blt gives ten current resource
exacts/1,781 bytes. No old object or selective declaration view hides the losses.

Independent capture review covers all852 before/864 proposal bytes and248
instructions each. Eighteen eight-instruction bank graphs explain all12 bytes
of growth; the other104 instructions,42 bindings,seven calls,five branches and
140-byte frame correspond. Algebraic address and subsequent register/flag walks
leave no missing consumed operation in the stated domain. Capture source text
is unchanged.

Stretch review covers all51 instructions/139 before/141 proposal bytes. Two
commutative ADD pairs and two equivalent bank-address graphs account for every
changed operation; twelve subsequent scratch/flag walks close. Its one branch
and Blt call retain their instruction-ordinal roles. PCX source is unchanged;
all227 instructions correspond, with a nine-byte ripple in one exchanged
comparison/converse branch and four subsequent EAX/flag checks. Its strict
851 result stays visible. These proofs require stable ordinary memory and the
normal ABI; they do not establish raw frame,trap,concurrency or driver fidelity.

The unchanged maintained drawing loop supplies108 calls across the three
adapters; twelve unchanged capture cases cover its changed compiler identity.
All120 pass. Two resource-only instrumented compilations reuse other objects;
the canonical native build recompiles only resources and links once. Current
library SHA-256:
`0a632e94edf77f0278257d1c0b7f13512ec842e8b4f6cc72e5f669016dd957cc`.

VC4 work takes9.808s,peak167,272,448 bytes; instrumented work11.223s,
peak55,197,696 bytes; canonical build1.216s; canonical checks11.681s,
peak51,134,464 bytes. All compiler/native work uses CPU0/35%,384MiB high/512MiB
max with zero high/max/OOM events. No full replay,game rebuild or game run follows.
Historical semantic counts/scopes stay fixed; current input identities refresh.

## Bounded readiness and retained evidence

An independent22-candidate review at608cca4 identifies this concrete Blt gap;
its other21 rows expose no additional missing consumed operation within their
existing correspondence domains. The separate inventory review accounts for
all3,719 direct edges,191 switch words,249 HIGHLOW code-address words and177
typed COM sites, with zero unexplained non-CC text-gap bytes. All78 no-source
entries have dependency receipts; only19 original CRT members are approved for
delivery. No missing authored body/callee is observed in that bounded inventory.
The final denominator and original declaration/compiler context remain unproven.

Current270 authored source/object/comparison receipts across30 closures verify
after adoption. All23 remaining nonexact results are disclosed. The next work
is a current-source VC4 build, then a focused diagnosis of the retained menu
initialization timeout with additional read-only stage observations. A prepared
relink was deferred before execution when this source gap was identified.

Private `.analysis/blt-coordinate-wrap-20261019/` retains the fixed proposal,
three primary seals,full comparisons,independent source/result reviews,all
counterexamples,current checks and receipts. The candidate/inventory reviews
are under `.analysis/authored-readiness-20261019/`. Root reviews cover stretch
and PCX; the independent reviewer rechecks them and owns the full capture proof.
Closed copies,temporary products and executed helpers are member-size/SHA
verified in an archive before exact-list cleanup; current products/caches stay.

Cleanup verifies all66 members of a1,356,538-byte archive before removal,
releasing8,372,224 allocated bytes net before small receipts. All926 protected
file identities survive; the separate failed-play evidence remains untouched.
