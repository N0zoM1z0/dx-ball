# Runtime and floating-point initialization

Later [FP startup integration](RUNTIME_FP_STARTUP.md) runs the actual FP callback
and this controller through XI/XC, followed by returning XP/XT cleanup. It checks
the complete52-byte FP state/nine bindings,84-byte CRT table/thirteen bindings,
hardware state and actual conversion slots without host CRT startup. Full CRT
entry, physical low-level source and the final game remain open. The text below
retains the earlier code/section checkpoints.

The subsequent [initializer-section recovery](RUNTIME_INITIALIZER_SECTIONS.md)
supplies XI/XC producers and checks the complete64-byte linked prefix with12
bindings. An isolated VC4 entry without a host CRT runs actual heap/low-I/O,
XI/XC, filter lifetime and list constructors. FP/full entry, XP/XT sections
and the final game remain open. Text below retains the earlier code checkpoint.

Three complete bodies are exact: initialization controller48, default precision19
and the original empty thread callback1. The callback entry4175A0 is absent from
Ghidra's procedure inventory: the complete pinned fpinit definition, actual
initialized callback slots, fresh one-byte REA read and RET decode prove it.
This is not a unique-RET-pattern placement. Inventory becomes532.

Math startup25/23/5 remains a candidate. Its original final FNCLEX is absent from
the pseudocode but present in both the full pinned code and returned assembly.
Source calls the genuine `_clrfp` boundary rather than omitting the operation or
embedding assembly. VC4 rejects its requested intrinsic pragma; the final source
removes that unsupported directive and retains the real tail call. Both bounded
source trials preserve the three exacts. The unused `_setfflag` library body has
no complete linked match and is not added to the original inventory.

The source-owned FP state matches all28 bytes and three actual relocations:
four32-bit marker/flag words and three typed callback slots. Native pointers grow
naturally. The complete initialized section has an independently unique16-byte
prefix; no partial record or guessed padding is accepted. The controller gates
the FP callback and invokes the existing initializer walker on the actual two
linker-marked ranges. Those bounds must describe coherent same-array callback
ranges; actual constructor storage, conversion initialization, processor FDIV
testing, physical x87 boundaries and game integration remain open.

Private `.analysis/runtime-initialization-20261014/verification.json` retains four
whole CRT proofs and one closed11-record REA run. Affected whole comparisons and
native/i686 standalone compilation run; no runtime tests or hardware execution.
All282 preceding exacts,83 candidates and249 semantic rows retain their inputs,
products and results. Source378/exact285/66,349, candidates84 are current.
