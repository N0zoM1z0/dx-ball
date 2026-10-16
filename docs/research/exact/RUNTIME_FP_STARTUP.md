# FP initialization through the actual CRT controller

The later [actual CRT entry check](RUNTIME_ENTRY_EXECUTION.md) also runs the
version, command/environment and multibyte stages before this FP/XI/XC chain,
then observes normal and native SEH quick exits. Its WinMain is a typed fixture;
the real game remains open. The following text retains this FP-stage scope.

The isolated VC4 startup now runs the maintained FP callback and initialization
controller before XI/XC, followed by the existing XP/XT cleanup. It links 41
source owners and imports only KERNEL32. Its custom entry uses `/NODEFAULTLIB`;
a host CRT does not initialize floating point, streams or constructors first.
This closes the preceding higher-level FP initialization check, while the full
CRT entry, remaining low-level source and final game remain unfinished.

Forty source objects are reused after complete input, flags and product checks.
Only the callback-state data owner needed recompilation: its previous producer
receipt named an older `runtime_float_format.h`. The current source still emits
all 24 initialized bytes and six genuine trap bindings correctly. Strict native
and i686 C90 compilation also passes. The refreshed canonical object remains
independent of its archived compiler product.

## Source state and linked code

[The FP state recipe](../../../config/runtime-fp-state.json) records both complete
initialized owners, totaling 52 Win32 bytes and nine actual function bindings:

| Owner | Bytes | Bindings | Original address |
| --- | ---: | ---: | --- |
| Four marker/flag words and three FP callbacks | 28 | 3 | `0x00423090` |
| Six initially unavailable conversion slots | 24 | 6 | `0x004231F8` |

Both source sections agree with the original after all independently grounded
bindings. Both also agree with the actual linked image under its real symbol
addresses. Native pointers retain their natural width; these byte sizes are
the original Win32 layout.

The complete 84-byte XC/XI/XP/XT table and all 13 callback bindings also remain
correct in the new image. The registration order is preserved, including stdio
before onexit within `.CRT$XIC`. Source recipes and original table Evidence
remain in [initializer sections](RUNTIME_INITIALIZER_SECTIONS.md) and
[exit sections](RUNTIME_EXIT_SECTIONS.md).

Eight complete emitted source bodies, totaling 597 bytes, agree with the linked
image after actual relocations: the runtime controller, math initializer,
default precision, `_controlfp`, `_control87`, processor FDIV test, physical FDIV
test and conversion-table publisher. This is a source-object-to-image check;
the math initializer and `_control87` retain their existing nonexact original
comparisons. No new original-code exact is claimed.

## Actual execution

The process creates the maintained heap and low-I/O state, then verifies the
initial FP marker words, three default callbacks and six unavailable slots.
It deliberately selects 64-bit x87 precision and seeds a masked inexact flag.
The actual `dxball_crt_initialize_runtime` invokes its real `_FPinit`, XI and XC.
The recovered publisher, processor test and default-precision controller run;
the genuine physical clear operation completes FP initialization.

Afterward the hardware reports 53-bit precision and cleared sticky exception
flags. The FDIV flag is zero on this host, and all six slots name their actual
maintained functions. Eight calls through those slots check zero cropping,
double/float assignment, decimal insertion, positive/negative classification,
fixed formatting and the compatible exponent-formatting slot. Their ordinary
C-locale results agree with the expected values and strings.

The same process checks 20 real standard-stream identities and the null table
tail, onexit allocation, actual OS filter installation and nine prefilled list
roots cleared by their genuine constructors. Returning normal, quick and
low-byte cleanup preserve the established callback traces, including real
filter restoration. The process exits zero. Only this affected startup process
ran; previous physical exit modes and unrelated function checks are reused.

The first fixture still expected an empty onexit table at an observation that
had moved from after XI to after the complete controller. XC has already
registered filter restoration there, so the correct count is one. That fixture
postcondition was repaired; production functions, the refreshed data object and
all other fixtures were reused. The initial result remains archived.

## Boundaries and reproducibility

Five pinned original library members provide physical x87 control, SEH transport
and the narrow-string dependencies of unexercised formatting/error paths. Their
identities and hashes are explicit in the link receipt. The C++ terminal and
pointer-validation owners are maintained source, replacing the earlier unused
failure traps. Flush/close effects remain typed fixture boundaries; physical
stdio cleanup, exception delivery and full reconstructed CRT entry are not
claimed. The board aggregate's nonexact generated initializer is unchanged.

All 380 exact and 95 candidate recipes, function inputs, products and comparison
reports remain unchanged. Function/origin/source/exact ledgers and all 249
historical semantic rows are byte-identical. Totals remain 545 inventory,
475 source entries, 380 exacts/77,485 code bytes/244 metadata bytes and 95
complete candidates. No full replay, provider query or game campaign ran.

Private receipts are `.analysis/crt-fp-startup-20261016/`: `closure.json`,
`source/runtime_float_format_state/{product,portable}.json`, `callback-data.json`,
`link.json`, `runtime-before-stage-assertion-fix.json`, `runtime.json`,
`verification.json` and `adoption.json`. The complete initialization-table read
is reused from REA Evidence
`ev_73a146a038dc9800cd869abb7261b6989c3713c813683a1453cd464602ea0586`.
Earlier full member/state proofs remain in the initialization and float-format
owner notes. Heavy work is serial, one allowed CPU, CPU 35%, memory high
640 MiB/maximum 768 MiB. REA remains pinned to 6.5.0.
Sharing 20 identical immutable member/header snapshots reclaimed 80 KiB;
unique evidence and mutable build products are retained.
