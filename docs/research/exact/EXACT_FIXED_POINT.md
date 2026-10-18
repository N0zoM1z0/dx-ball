# Fixed-point class and triangle lifetime recovery

October 16 [ownership follow-up](COMPILER_FRAGMENT_OWNERSHIP.md): the 24 old
auto-analysis splits are now recorded as parent-owned compiler fragments,
without independent source/exact claims. Complete parent extents and current
comparison results are unchanged. Earlier counts below are historical.

The later [genuine API integration](#genuine-api-integration-october18) adopts
the direct imported MulDiv call and a separate host fixture. The earlier
callback-table source and its IAT-root interpretation below are historical.

The [independent Fixed-class model](#independent-fixed-class-contract-october18)
below tests a newly found complete eight-operation contract. Its mixed polygon
producer changes remain private; current source and exact claims are unchanged.

This batch restores eight previously unmaintained fixed-point entries in the
shared [C++ raster owner](../../../src/raster.cpp), adding 571 complete code bytes.
The accepted ledger becomes 63 exact units / 8,802 code bytes and 265
source-present entries (253 application utilities and game entries, 12 runtime
entries). The 247 directly validated entries and 112,273 distinct direct cases
remain unchanged. This is a bounded reconstruction checkpoint; the complete
authored denominator and the >=95% objective remain open.

| Original entry | Shared source meaning | Complete code bytes |
| --- | --- | ---: |
| `0x0040B240` | Default constructor, leaves value uninitialized | 25 |
| `0x0040B260` | Empty destructor | 22 |
| `0x0040B280` | Integer constructor, shifts to 16.16 representation | 38 |
| `0x0040B2B0` | Signed integer conversion | 30 |
| `0x0040B2D0` | Division with by-value operand and hidden return storage | 182 |
| `0x0040B390` | Scalar ratio through the stdcall MulDiv boundary | 35 |
| `0x0040B3C0` | By-value comparison, returns an integer | 129 |
| `0x0040B450` | By-value addition, returns the owning object | 110 |

The class is four bytes, uses genuine ECX thiscall, and defines constructors,
destructor and operators out of line. The source preserves real temporary
objects and their lifetime. The division result is a real default-constructed
object; the compiler supplies conditional cleanup of return storage, destruction
of the local result and destruction of the by-value denominator. The comparison
and addition also destroy their by-value operands. Historical class/member names,
const qualification and reference-versus-pointer return spelling are not uniquely
recoverable from this emission. No fake EDX argument, copied instruction body,
forced assembly, profile-selected source, extra padding or artificial locals are
used. Integer conversion relies on the signed shift behavior checked on the
selected native, MinGW and VC4 targets; existing vectors bound arithmetic.

The shared raster callback table now marks only its math callback stdcall,
matching the original import at `0x004412A8`. For exact relocation the table root
is bound to `0x004412A0` with the emitted field addend of eight. This attests that
specific callback slot; it does not assert that the complete host callback table
was an original allocation/free/IAT structure. The native and Windows adapter
implementations use the same declaration.

The strict COFF oracle compares the entire dedicated code COMDAT and every
relocation. For three methods it also compares the full initialized data COMDAT:
32-byte FuncInfo header plus the complete unwind map, at `0x00420350` (56 bytes),
`0x00420388` (40 bytes), and `0x004203B0` (40 bytes). These 136 metadata bytes are
separate from the code-byte total. The metadata root must agree with its code
DIR32 binding; interior labels are permitted, but a shorter matching prefix,
missing relocation or missing metadata attestation cannot pass. Four additional
oracle controls exercise these rules. The linked runtime exception handler at
`0x00418570` remains a dependency, without a new maintained implementation.

The triangle at `0x0040AB90` is restored as an ordinary C++ controller using this
class, independent upper/lower scan loops, original expressions and real
scope-based cleanup. The original computed `0xF0000 / (y3-y1)` local is retained;
its value is not subsequently read in the recovered body, and its intended role
is unresolved. The full controller extent is 1,710 bytes through `0x0040B23D`,
including sixteen cleanup funclets, the handler and the plain-RET continuation.
Its 160-byte FuncInfo/unwind metadata matches completely. The code remains a
configured candidate: the current complete 1,710-byte emission differs in 235
bytes, including local slot allocation and expression scheduling. It is not
included in the exact total. Adjacent auto-analysis fragment rows remain
provisional for denominator review; they are not new authored functions or
separate accepted units. The three class operator extents similarly now include
their owned cleanup/handler/continuations rather than stopping at old split rows.

Closed REA 4.1.0 / Ghidra 12.1.4 records provide the destructor, epilogues,
cleanup calls, handler bindings and complete metadata. The request set is
[rea-fixed-lifetime.json](../../../config/rea-fixed-lifetime.json). Reused class and
triangle dossiers retain their original target identity. An undefined Listing
instruction at `0x0040B346` remains explicitly undecoded; the complete original
byte read and compiler-owned cleanup metadata support the extent instead.
Private diagnostics retain the class-only match, triangle expression/order
trials and canonical source/object. The first class-only raw source was changed
before it was copied; its compiler listing survives, while the accepted cold
build has complete frozen source inputs. No frozen-source claim is made for that
initial probe.

Validation uses one frozen batch of all 22 existing game-owner scripts, complete
cold replay of all 63 exact units, and actual relocated VC4 C++ raster bodies
against the existing 7,164 original/native cases. Those cases include complete
pixel buffers, guards, padding, callbacks and scalar scratch; they are counted
once. Complete attached metadata is loaded for generated-code execution, while
exceptional unwinding itself is not exercised by these normal bounded vectors.
The COFF reader edit also affects four existing termination input closures;
their 1,031 original/native cases and actual VC4/MinGW object checks were rerun
as a separate existing-owner supplement, without increasing direct-case totals.
A first promotion attempt refused those missing input attestations before
writing semantic rows; its partial CSV writes were restored from frozen inputs
before the successful promotion refreshed 239 existing semantic rows.
Controlled allocation/free/MulDiv boundaries and unresolved active game use
retain the existing scope. Strict native Debug, MinGW and full legacy VC4 builds
cover C/C++ linkage and the Windows callback ABI. A Release attempt encountered
an existing unrelated ignored-fread warning under `-Werror`; it is retained as
a failed diagnostic, without a Release validation claim.

The private checkpoint `.analysis/checkpoints/exact-fixed-265-63` retains source,
frozen inputs, closed provider records, full code/metadata comparison, compiler
products, reports and a losslessly compressed 387-evidence snapshot before
cleanup. Historical display, palette, list, core and allocator native products
retain their identities. Originals and compiler binaries remain private.

## Read-only receiver control, October 17

The original conversion, division and comparison read their receiver without
writing it; addition mutates it. This supports one coherent inferred API model
with `const` on the first three methods, while retaining their by-value operands,
result lifetime and complete executable bodies. Read-only behavior does not
uniquely establish the original qualification. No equivalent control was found
in the bounded retained fixed-lifetime and triangle-scope records.

One current raster compile compares all12 complete functions. All resolved code
digests and attached metadata equal their retained canonical results: nine
accepted bodies retain715 code bytes/136 metadata bytes; triangle remains
1710/88 bytes/differences with its full160-byte metadata exact. The polygon
candidates remain1543/214 and1592/214. The model is closed as an exactness
improvement, without adoption or further qualifier combinations.

Three explicit actual method definitions change from non-const to const
decorated identities. The21 changed triangle bindings are16 conversions, three
divisions and two comparisons. Every original target, relocation type and
addend is preserved; other decorated rebinding stays prohibited. Complete-span
and local-target checks remain active. No byte projection or mask is accepted.

Private `.analysis/fixedpoint-const-receivers-20261017/` retains the transformation,
full comparisons, actual definition/binding checks and independent review.
Raw inputs/products are archived and every member hash verified before deletion.
Canonical source, cached objects, ledgers, image and totals remain unchanged:
391 exacts and24 authored candidates. No provider query, runtime check, game run
or full replay accompanies this rejected source model.

## Direct MulDiv boundary control, October18

The original ratio's complete 35 bytes call `KERNEL32.dll!MulDiv` through IAT
slot `0x4412A8`, with three signed 32-bit arguments and stdcall cleanup. The
current table binding at `0x4412A0+8` attests that slot, not an original table.
One fixed source model declares the genuine imported API and calls it directly.
It moves the existing three-field fixture table and defaults to a host owner;
native `MulDiv` forwards the live math callback. A Windows default wrapper avoids
an imported function address requiring dynamic initialization. Arithmetic,
local names, types, scopes, class methods and compiler flags remain unchanged.

One canonical-path VC4 compile compares all 12 complete raster functions,
141 actual code/metadata bindings and 296 attached metadata bytes. The genuine
ratio binding remains 35-byte exact. All nine prior exacts retain 715 code bytes
and 136 metadata bytes; triangle remains byte-identical at 1710/88. Ordinary
polygon changes 1543/214→216 and clipped polygon 1592/214→213. The four inspected
bodies preserve all 17/482/458/468 instruction boundaries and widths. Ordinary
polygon changes 14 instructions, losing five previously raw-matching instructions
and restoring three; clipped changes five and restores one raw-matching branch.
These raw counts do not identify variable roles when stack homes differ.

The initial control rejects the model as an exactness improvement, without
selective adoption or variants. At that checkpoint the host, adapter and CMake
proposals are uncompiled; both legacy integrations and runtime remain unvalidated.
All 851 protected canonical hashes and four source modes/nsmtimes restore;
the new import header is removed. Source, delivery and 250 authored exact/20
candidates remain unchanged. This does not reject the genuine API identity or
establish original header placement, source names or optimality.

Private `.analysis/raster-muldiv-api-20261018/` retains the prepared model,
complete comparisons, instruction delta and independent reviews. The compile
takes 2.589 seconds; its complete pilot scope peaks at 192,634,880 bytes under
CPU 0/35% and 384/512 MiB limits, with no memory-limit events. There is no
provider query, native build, relink, runtime case, game or full replay.

## Genuine API integration, October18

The complete integration adopts that same frozen source model. The earlier
decision gave too much weight to mixed instruction scheduling in two nonexact
polygons: it did not establish a defect in the genuine API contract. The original
35-byte ratio independently identifies `KERNEL32!MulDiv`, three signed 32-bit
arguments and stdcall cleanup. Calling that import directly restores this
contract without claiming recovery of its original header or translation unit.
The earlier rejection and all comparison changes remain retained.

[raster.cpp](../../../src/raster.cpp) now consumes the genuine
[import declaration](../../../src/raster_imports.h). The existing callback type,
table and portable default move to [raster_host.cpp](../../../src/raster_host.cpp)
and its header. Native MulDiv forwards the live math callback; its saved portable
default is a separate function. Windows uses a static 36-byte stdcall wrapper
calling the real IAT, with no dynamic initializer. Both legacy source lists and
CMake include the host owner. No algorithm, local spelling, type, scope or
compiler flag changes from the frozen model.

The prior single-compile raster object is reused after verifying all five inputs,
flags and the pinned toolchain. Rechecking all 12 complete functions, 141 actual
bindings and 296 metadata bytes reproduces the frozen results exactly. All nine
prior exacts retain 715 code/136 metadata bytes. Triangle remains 1710/88;
ordinary polygon is 1543/216 and clipped is 1592/213. Both polygons are adopted
together as candidates; neither is claimed closer or exact. Twenty generated
unwind-label pairs refresh through the actual parent metadata, preserving all
24 fragment extents, ownership and original evidence.

Native and Windows builds pass. The existing 7,164 original/native raster cases
pass, including live callbacks and the saved portable default within their
existing domain. All 249 semantic scopes, case counts and oracle identities
remain unchanged; only their affected input inventories refresh. The ordinary
VC4 game links, and the restored-CRT game reuses all 118 objects: 115 source and
three integration objects, with the same 19 explicit original CRT members.

Linked verification checks 673 complete located sections and 5,904 actual
bindings across 137 source/CRT objects. Five additional complete data containers
account for 39 fields. All 4,488 loader fields have actual COFF or SDK-thunk
ownership. All 59 adapter function bodies retain their complete raw bytes;
four bindings rename two compiler-generated static symbols, with actual BSS
definitions and unchanged linked targets verified. Imports and resource
payloads remain unchanged. This establishes those containers and bindings,
not whole-PE byte identity or a new physical Windows observation.

Current linked image: 166,400 bytes, SHA-256
`40f92f0ff8b175c3ff4e38cba6760cce30081c25bc5b8300d1aaa2f2932d551f`.
Private `.analysis/raster-muldiv-integration-20261018/` retains the reuse proof,
independent reviews, build/case results and initial verifier failures. The
highest recorded step peak is 170,659,840 bytes, with CPU 0/35%, 384/512 MiB
and zero memory-limit events. No VC4 raster recompile, provider query, game launch
or full replay runs. Current authored coverage remains 250 exact/20 candidates.

## Independent Fixed-class contract, October18

A code-index hit leads to the complete 1,742-byte
[Fixed.h at Steem commit67925be](https://github.com/steem-engine/steem-engine/blob/67925be656c4b27151fd64de39be218f0ecfb262/include/fixed.h),
SHA256 `9e1cc435e25ba7468998273ef54685d897ad867eaa4629a18f02acf0ffffc1fe`.
Its private signed32 `long fx`, empty constructor/destructor, integer constructor,
signed conversion, by-value division with local `c`, integer comparison,
reference-return addition and `MulDiv(a,65536,b)` agree with all eight observed
contracts. This supports a declaration inference beyond a shared constant;
historical lineage to1.07 and original source spelling remain unproved.

One fixed model moves only those eight operations into an inline header, using
`Fixed/fx/i/a/c/fixed_div`. Windows long and native signed32 preserve four-byte
storage; the existing unsigned intermediate shift remains. No unused donor
constructors/operators or invented triangle names enter the model. The actual
emitted eight-function order agrees with the original address order, even though
the scalar helper definition precedes the class. This permits inline ownership;
it does not uniquely establish the original declaration context.

One unchanged-recipe VC4 compile compares all12 full functions,141 actual
code/data bindings and296 metadata bytes. All nine prior exacts retain715 code/
136 metadata bytes; triangle keeps its complete1710/88 result and160 metadata
bytes. Ordinary polygon privately improves1543/216→212 by restoring two next/used
comparison producers, with no formerly matching instruction lost. Clipped stays
1592/213, but reverses an already correct first/second-Y producer while restoring
a later sort comparison. The unchanged difference count conceals this tradeoff.

Keep the whole model private, without subsets or further variants. The eligible
independent class model does not establish a historical fidelity gain sufficient
to adopt those mixed polygon changes. Current source, products and250 authored
exacts/20 candidates remain. Full input hashes, actual eight-definition bindings,
metadata ownership and local-target guards pass independent review. All746
protected hashes and five source modes/nsmtimes restore before documentation;
the temporary header is removed. A stale-variable bug in the summary's candidate
display is corrected in a separate journal from unchanged raw comparisons,
without repeating the compiler or producer.

Private `.analysis/fixed-muldiv-code-index-20261018/` retains the complete donor,
index responses, frozen model, comparisons and independent reviews. Archive
members are size/SHA verified before deleting proposal objects, source copies
and closed helpers. Compilation takes2.613 seconds; its comparison scope peaks
at178,302,976 bytes under CPU0/35% and384/512MiB, with zero memory-limit events.
No native build, relink, provider query, runtime case, game or full replay runs.
Two additional ratio-index queries establish no connected triangle: the first
matches comment openers; the corrected parenthesized-denominator query returns
no match. These are bounded index findings, not proof of source absence.
