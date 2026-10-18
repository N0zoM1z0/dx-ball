# VC4 expression ordering observations

The October 17 investigation connects a numeric symbol-record lookup key to a
real child-ordering decision in the pinned VC4 backend. It does **not** yet
connect that decision to a specific original-game instruction difference.
No game source, exact claim, compiler recipe or delivery product changes here.
This research-only checkpoint retained 393 exact functions and 22 authored
candidates; the later linked owner note below supplies the current totals.

The target is the attested `.tools/msvc400/bin/c2.exe`, SHA-256
`820ed4e4930db97bcba646afb88fdb7d1f329631ca8e5b84096c0d6daa82e9a9`.
This follows the [symbol-record reader observations](VC4_BACKEND_SYMBOL_RECORDS.md).
REA 6.5.0/Ghidra 12.1.4 retains four new records in
`.analysis/rea/vc4-backend/runs/2026-10-17T13-24-57.149Z-interactive-3651932/`
and 46 in
`.analysis/rea/vc4-backend/runs/2026-10-17T13-45-34.524Z-interactive-3690015/`.
The closed cumulative snapshot contains 64 records, including the previous 14.
Complete responses, profiles and provider limitations remain private.

## Actual ordering decision

The 58-byte function at `0x413ded` receives a node and two unsigned ranks. It
swaps the node's `+0x0c` and `+0x10` children only when left rank is less than
right rank; ties preserve the children. It returns their unsigned minimum.
After swapping, operator attribute bit `0x10` gates replacement of the root
opcode through `0x430323(opcode, 0)`. The assembly confirms both the unsigned
branch and the stores. Mode zero reads the table at `0x481c0c`.

The six table entries for opcodes `0x1f..0x24` are
`1f→1f`, `20→20`, `21↔23` and `22↔24`. All six have attributes `0x6118`.
These are numeric opcode mappings; their source operator names have not been
established by this investigation.

The 206-byte caller at `0x408d62` conditionally visits the right child, then
the left child, obtaining their ranks recursively. It computes the current
node's rank through `0x40846e` before the ordering decision. Attribute bit
`0x8` and a separate special path gate the call to `0x413ded`. This traversal
is not by itself the final machine-instruction evaluation order, and not every
node reaches the swap helper.

## Consumed record field

For opcode `0x26`, `0x40846e` reads a record pointer at node `+0x14` and its
32-bit field at record `+0x24`. A null record or record kind `0x18` at `+0x0c`
returns rank `0x10`. Otherwise, assembly establishes this arithmetic:

```text
k = u32(record + 0x24)
a = k >> 8
b = ((a - k) mod 2^32) >> 4
rank = 0x10 | ((b - a + k) & 0x0f)
```

Both shifts are logical. There are only 16 possible results; this is not
monotonic key ordering. For example, keys 16 and 18 produce ranks 31 and 16.

The existing reader at `0x41bb61` stores integer-reader results at `+0x24`;
its newly retained full assembly confirms those writes. Pseudocode for
`0x41a4c1` compares that field to a numeric lookup key in chained tables, and
pseudocode for the opcode-`0x26` builder at `0x407575` stores its supplied record
at node `+0x14`. This establishes a consumed numeric lookup key, not its original
frontend assignment rule, source declaration order or identifier spelling.
The reader's retained control-flow limitations still apply.

| Observation | Evidence ID |
| --- | --- |
| Swap helper pseudocode / assembly | `ev_f3697f64010353fa335cead0c3f0ffb10493bc76140926d0bbb920c4730c4bdb` / `ev_b46805a114b06c821f75a563a8c424152eb16d76d416cda8932324aab3227125` |
| Recursive caller pseudocode / assembly | `ev_df37b8dc3ce522d96cf46509d239bb4dcf9b839623e9cf2d17f8a672a89cd0c5` / `ev_2b6f9254159151bf2fc84c7a41ad22880c65240519dda60e0ff4585c0b3a0fa3` |
| Opcode mapping assembly / six actual table entries | `ev_590dd5d1b1e54073d524c88cbebe21fa747c5c775ac9fb89140f7adfdc5fd003` / `ev_dda3d22f55bf5101f1942ff8b6afd6211da8fa0142f65fb7bc37f14fc90feb76` |
| Rank function pseudocode / assembly | `ev_cb5eba78e7e479074c1480e2f9f262737eecb4896f899fccb83cb2305d0bcaa1` / `ev_b0fd95723f8982595e11981815cf9d9cba0fb3e1a53d4227a7a54ee20999891c` |
| Record reader assembly | `ev_b72644fd2d85d07e930898c7f59b826775d5ceeb65897545fdb7196799331f5a` |
| Key lookup / opcode-`0x26` builder pseudocode | `ev_a6c839e4776192f89a175ffe6797917cbda64da676bff56e68570348badb2610` / `ev_7b0d659b205c3a2ec492e9bd2ebe1b27e39a0cc3d1a425ab2f2453e92bbeab5e` |

## Bounds, validation and next question

Literal xrefs to `canon.c` and `cgcanon.c` first located tree rewrite code.
An instruction search for stores across the two observed child fields then
supplied candidates, not procedure or reachability claims. REA confirmed the
selected procedures, their actual extents and the algorithm above. Several
other procedures have noncontiguous bodies; their enclosing address spans
must not be treated as complete function bytes.

A bounded Unicorn execution of the unmodified pinned C2 instructions and PE
tables passes 44 synthetic cases: 20 record-key/kind rank cases and 24 swap,
tie, unsigned-boundary and opcode-map cases. No original-game keys are claimed.
The private source and complete observations are under
`.analysis/compiler-operand-canonicalization-20261017/`. Independent review
confirms the arithmetic and flags the missing game producer link.

The first session ended after an unowned procedure query returned invalid
input. The session helper now retains each interactive inspection error,
including its full response, and continues using the same live import. Batch,
transport, provider, open, identity and close failures remain fatal. Seven
actual-module mocked cases pass, including two consecutive invalid queries
followed by a successful query; they start no provider. Open/close failures and
event-only transport notifications were reviewed by inspection, not injected.
The second real session reused one import and closed normally; no invalid
query was needed there. Its cold query took 407,402 ms under the existing
CPU/memory caps. Both sessions' observations and the first failure are retained.

Two identical closed catalogs now share hash-verified immutable storage,
releasing 17,526,784 allocated bytes net (16.7 MiB). Their paths and bytes remain
intact. Current tested build products and useful CMake caches remain retained.
No game compilation, relink, game episode or full replay follows this research.

The later [resource drawing-wrapper investigation](RESOURCE_ROTATION_WRAPPER_OWNER.md)
captures concrete current-game node opcodes, record keys and both child ranks,
then compares all affected complete emitted functions. Original-game intermediate keys and original
compiler/settings identity remain unknown. Do not turn the ranking mechanism
into a name, declaration-count, order or compiler-flag sweep.

## C-source comparison observation, October18

The earlier line and resource observations compile C++ sources through C1XX.
Their frontend addresses and source-field formulas do not establish the C1
implementation used by `editor.c`. One unchanged editor compilation now observes
the actual CL/C1/C2 process chain, with no C1XX process. The selected C frontend
is pinned `c1.exe`, SHA-256
`7a7c14aff9631b9460a5666a8c344a5a177fce125ba3c4e9c2a4d57c7f402bb2`.
The existing sealed C2 debugger executable is reused byte-for-byte; no observer
build, source adaptation, compiler option or game-source variant is introduced.

All 181 helper entries have paired returns, including 23 in
`find-hit-region`; 32 calls actually swap children. Every owned process exits0,
all stack/register guards pass and there are no mandatory read failures or
extra C2 threads. Ten omitted children lie below the explicit depth-five bound
in unrelated trees. The selected loop guard has a complete five-node tree:
two symbol leaves and their load wrappers below the comparison.

| Current role | C2 record key | Record kind | Derived leaf rank | Observed load rank |
| --- | ---: | ---: | ---: | ---: |
| Live hit-region count | 219 | 1 | 29 | 32 |
| Local `i` | 1178 | 1 | 28 | 47 |

Call35 receives the actual rank pair32/47, exchanges the children and changes
opcode `0x24` to `0x22`. Its 27 single-step events reach the saved return address
with return rank32 and the expected stack/saved registers. The retained REA
rank/load instructions independently reproduce the observed ranks. This agrees
with the emitted current guard loading the count into EAX before comparing
local `i` against it. Original instructions instead load `i`, compare the live
count against EAX and exit through JLE rather than the current JGE.

The complete original173/current172-byte bodies each contain46 instructions.
Forty-two instruction encodings agree. Only the three guard instructions and
the necessary backedge displacement differ; all eight branch successors agree
by instruction ordinal. The strict132-position difference remains unmasked.
All14 complete editor units,223 bindings and12 full literal references compare
against the original and current authority, retaining every raw/resolved code
identity and all13 prior exacts/3,267 bytes. Forty applicable exact local-target
guards also pass. No exact, source or delivery claim changes.

This observes C2 records from an actual C-source compilation. It does not locate
C1's serializer/key-assignment instructions, observe a direct final-emitter node
chain or recover original IDs/names/declarations. Do not transfer the C1XX
NameMap/source-field formulas or derive source permutations from these ranks.
The next concrete gap is the actual C1 output/key producer and its transport
to these consumed records.

Private `.analysis/editor-c-comparison-20261018/` retains the sealed trace,
full comparisons, source/process identities and independent reviews. All851
protected hashes and22 source-input modes/nanosecond mtimes remain unchanged.
The single observation takes4.186 seconds, with a160,743,424-byte whole-scope
peak under one CPU/35%, memory high384 MiB/max512 MiB and zero memory-limit
events. There is no provider import, native build, oracle, game, relink or full
replay. One explicit metadata receipt corrects a field label:42 counts equal
instructions, not42 individual bytes; no successful producer is repeated.
Archive/member verification precedes removing21 temporary carriers, including
one object and one executable, releasing958,464 allocated bytes net. The reused
observer remains in its earlier verified carrier, without a duplicate binary
in the new archive. Current tested products and useful caches remain.
