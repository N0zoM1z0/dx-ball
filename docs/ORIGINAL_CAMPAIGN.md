# Original-board integration

The earlier terminal control completes 50 editor-created single-brick boards.
It establishes the terminal storage and routing behavior described in
[terminal evidence](TERMINAL_RUNTIME.md), but does not exercise the original
campaign. These integration probes retain the hash-verified, unmodified
`DEFAULT.BDS` and actual sprite dimensions.

Static contracts reuse the saved REA evidence in the
[core](CORE_OWNER.md), [resource](RESOURCE_OWNER.md),
[entity](ENTITIES_OWNER.md), and [power-up](POWERUPS_OWNER.md) investigations.
The new runtime observations test those recovered contracts together; they
do not introduce a second transcription of the game.

## Windows observation

`tests/windows_campaign_reader.c` is a persistent i686 SDK observer. It requests
read/query/synchronize process access, traverses ball and bonus lists, and reads
complete 400-byte boards. Original addresses reuse the reviewed resource,
entity, power-up and runtime contracts. VC4 addresses come from its verified
map; MinGW uses actual DLL exports and compiler-emitted storage offsets.

`tests/test_windows_campaign.py` supplies ordinary XTest mouse input. Its
controller follows falling balls and avoids observed harmful bonuses where
possible. It never writes game memory, patches code, suspends threads or edits
the campaign bank. Before playing a new board it requires two complete reads
matching that original bank slot. Reads are sequential, not atomic snapshots;
broken traversals are discarded and counted. A bounded episode or progression
is explicitly separate from full-campaign acceptance.

REA process Evidence
`ev_dc82f3c5ca2b1c30f9a3af4d208d6fef0bf21a032c0e937d638a73eb86435042`
records three 25-second episodes with child exit 0. Each product loads the
original first board and accepts ordinary launch/paddle input; independent
clock/RNG trajectories need not produce equal scores. MinGW also reaches the
next original board during its episode. These are limited integration runs.

A later pilot exposed an observer gap: VC4 had already launched on board 1,
while the harness was waiting for a briefly attached ball. REA Evidence
`ev_5140d880de7dd5ce975f74988b1eaf33a9dce560c8102e179d583dcec816283f`
retains child exit 1; ordinary Escape ended the stalled observation. The original
had completed the requested transition. The revised predicate identifies a new
board through complete bank bytes, without requiring that attachment transient.
No game-source correction follows from this observer failure.

The revised three-product progression run passes: REA Evidence
`ev_79991d871a117a9ce71859f372b6f9272a0b8e9fb1547c64b6151fe043e6dc98`
records child exit 0. Original, VC4 and MinGW each verify the complete initial
bytes of slots 0 and 1. Their independent runs take about 17, 59 and 99 seconds;
each retains three lives. This establishes the first original-board transition,
not full-campaign or synchronized-trajectory acceptance. The source version and
reports are retained in `campaign-reader-first-transition-01`.

The follow-up three-product episode capture
`ev_ae21658400c496f6a801b88fa6134d63fb42e96c225530277620dfb5eda67f44`
also exits zero. The final harness waits for cleared end/reset/menu flags at
index 50, consistent with the saved custom-board terminal observations. Its
original-only episode replay
`ev_fae013a8191a1f90e0f07475096da93b2ec3a3c2176a44b6e5ed76ee2af0241f`
exits zero. The terminal predicate remains unaccepted for the full original
campaign until that complete run succeeds.

```bash
# Public compilation needs neither original assets nor a Wine run.
scripts/repo-python tests/test_windows_campaign.py --compile-only

# Short observation; its result is explicitly bounded-episode.
scripts/repo-python scripts/capture-windows-probe.py --probe campaign \
  --episode-seconds 25 --campaign-seconds 90

# Verify progression and the next original board, independently per product.
scripts/repo-python scripts/capture-windows-probe.py --probe campaign \
  --campaign-boards 1 --campaign-seconds 300

# Full campaign goal, one product at a time. Timeouts/game-over are failures.
scripts/repo-python scripts/capture-windows-probe.py --probe campaign \
  --profile original --campaign-seconds 3600
```

Full acceptance requires all indices 0..49 to be observed with their original
initial board bytes, followed by index 50 and a completed menu transition.
A bonus can advance a level without destroying every brick; a progression
report must not be described as 50 brick clears. Physical Windows behavior,
audio, synchronized pixels and full original-campaign acceptance remain open.

## Original-x86 connected episodes

`tests/test_campaign_differential.py` extends the existing display oracle with
a reusable, bounded node arena. Reuse occurs only after the frame's full
comparison and freed-memory poison checks. Actual SBK geometry is obtained by
executing the reviewed original resource loader. Every gameplay frame executes
all twelve original phases and compares maintained C state, typed ownership,
ordered effects, dirty/presentation state and controlled pixel buffers.

The first maintained run compares **20,654 continuous frames**, progresses from
index 0 through index 5, and retains three lives at each transition. The run
uses original `MBALL2.SBK` and `THEFONT.SBK` geometry; other resource dispatch
remains within the display oracle's declared controlled boundary. All 97 report
inputs and the native library are hashed. These frames add integration depth
without changing the owner-function or direct-case counts.

```bash
scripts/repo-python tests/test_campaign_differential.py --frames 40000 --boards 5
```

COM, audio, glyph, resource dispatch and non-game boundaries remain controlled.
Fixture mouse requests bypass the Windows message loop. Native host pointer
width changes the raw terminal shared-storage layout; this test stops before
that boundary and does not substitute for the actual x86 Windows campaign.
Its connected frames are separate from the 95,873 direct owner cases.

## Storage and evidence

The persistent reader buffers each sample into one pipe flush. The harness
drains the pipe, hashes consumed bytes, retains state transitions and one
periodic sample per ten seconds, and caps the event log. It does not retain an
unbounded frame stream. A stream hash is an identity of consumed bytes; it
cannot reconstruct discarded samples. Reports bind the reader, SDK/compiler,
input libraries, original files, source inputs and actual game products.

Archive the current attempt and its REA record before journaled cleanup:

```bash
scripts/repo-python scripts/clean-local.py --apply
```

Keep unique Evidence, originals, pinned tools and manual saves. Unchanged
owner/exact evidence is reused only after a complete input and product audit;
this integration work adds no function or exact promotion.
