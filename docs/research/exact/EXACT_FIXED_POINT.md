# Fixed-point class and triangle lifetime recovery

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
