# Original-board integration

## Restored-CRT entry and gameplay episode clock, October 17

The campaign CLI now accepts `--profiles vc40-restored-crt` and records that
profile's own map digest. It uses the existing Observer checks for the current
image, all 116 source objects and actual shared-storage offsets. The default
three historical profiles and the full 50-board predicate are unchanged.

`--episode-seconds` now starts at the first initialized, ready gameplay sample.
Previously startup consumed this interval: an entry check ended after 25.715
seconds total, immediately after board 0 became ready. That record validates the
new profile/map route, without establishing 20 seconds of gameplay. Earlier
records retain their elapsed observer times; no gameplay duration is backfilled.

A final check of image `345a6887…` runs **20.000 seconds after ready gameplay**
within 44.005 seconds total. It consumes 1,314 valid SDK samples with no malformed
lines, retains two complete initial-board-0 witnesses and sends 101 mouse clicks.
The score reaches 40, lives stay 3 and remaining bricks fall 168→164. The complete
20,000-byte bank and all 49 immutable originals remain unchanged. The result is
`bounded-episode`; it supplies no full-campaign, normal application-exit,
physical audio or synchronized pixel claim. The observer stops the game process
group after the episode. Only eleven bounded events and the consumed stream
digest are retained, not the full raw sample stream.

One strict SDK compile supplies the entry check. The final check reuses that
verified reader with unchanged C inputs through the existing child entry; no
game compilation, relink or full replay runs. It explicitly routes audio to
`dxball_reconstruction_silent` and leaves the host default unchanged. The initial
entry check used inherited audio routing and carries no silent-audio claim.

With the existing project silent sink available, the public short command is:

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=640M -p MemoryMax=768M \
  env PULSE_SINK=dxball_reconstruction_silent \
  scripts/repo-python tests/test_windows_campaign.py \
  --profiles vc40-restored-crt --episode-seconds 20 --seconds 90
```

The public entry compiles the SDK reader. Total `--seconds` still bounds startup
and gameplay together. Private `.analysis/restored-crt-campaign-entry-20261017/`
retains both executed source versions, reports, reader products, final frozen
inputs, resource sample and verification. Forty-nine disposable runtime copies
are removed after equality checks, releasing 1,703,936 allocated copy bytes.
Game source, products, 380 exacts and all other acceptance remain unchanged.

## SIGINT reporting during observation, October 17

Ctrl-C during active observation now writes `interrupted` to both the profile
observation and top-level summary. The profile retains its latest complete SDK
state, partial gameplay duration, consumed-stream counters and unchanged-file
checks. KeyboardInterrupt is re-raised, preserving exit 130; ordinary exceptions
remain `fail`. Completed episode/campaign predicates and normal control paths
are unchanged.

One real SIGINT check waits for original board 0 initialization, then signals only
the verified controller PID/start-tick identity. The child exits 130; both reports
contain `KeyboardInterrupt()` and `interrupted`. All three owned controller,
reader and game kernel identities are subsequently absent. The profile retains
767 valid SDK samples with no malformed lines. This is an intentional-cancellation
check, not a game or campaign pass. It reuses the current image and existing SDK
reader with the explicit silent sink; no compilation, relink or replay runs.

Private `.analysis/campaign-interruption-20261017/` retains the actual signal,
process identities, executed-source/input hashes, reports and normal-path AST
comparison. Forty-nine runtime copies are removed after equality checks,
releasing 1,703,936 allocated copy bytes. Historical interrupted reports below
retain their original `running` values and external terminal receipts; none are
rewritten. SIGTERM, hard kills, transport loss and interruption during cleanup
are outside this check.

## Display and retained campaigns

The campaign harness now defaults to640x480x24 Xvfb, consistent with the
[original display-depth correction](WINDOWS_DISPLAY_DEPTH.md). Its new
`--display-depth {8,24}` option is forwarded to the child and recorded in the
report; use8 to reproduce the historical full controls below. This changes the
host screen, not the game's original eight-bit DirectDraw request.

The independent current VC4 attempt was deliberately stopped when the user
reaffirmed exact function restoration as the first priority. SIGINT to the
verified controller produces child exit130; all five saved process identities
are inactive. Complete initial slots0–14, partial observer/SDK logs,108 frozen
inputs, unchanged four products and originals are verified in
`.analysis/current-vc40-campaign-independent/stopped-for-exact/verification.json`.
The harness's KeyboardInterrupt cleanup retains status running in its partial
observation; the terminal child receipt establishes that execution has ended.
The full50-board predicate remains unproved for this product.49 disposable
runtime copies are removed after backup equality checks. Further long campaigns
are deferred while exact function recovery proceeds.

A fresh current-product VC4 full-bank run was interrupted. Its unchanged game
SHA-256 is `7c44dc20c84a7b3c96670200c6a772b1a9263b85c44e58cd057dd0864292a551`.
The retained SDK events verify complete initial slots0–12 in the
unaltered20,000-byte original bank. The goal remains all50 initial slots followed
by terminal index50, mode0 and cleared end/reset/menu flags. The outer executor
returned143; all recorded process identities are inactive. The last periodic
event at3,626.414seconds records index12,157remaining bricks, score29,708 and
three lives. The cause is unknown. No full pass, game-source failure or normal
game exit is established. The existing persistent reader
and ordinary XTest controller are reused; no game compilation or target write.
Private `.analysis/current-vc40-campaign/` retains108 frozen inputs, the actual
SDK compile receipt, products, scenario and recorded kernel process identities.
`interruption-verification.json` verifies the prefix, unchanged inputs/products
and originals; `interruption-sha256.json` seals182 private files. Final child,
recorder and capture-summary receipts are absent, the final REA carrier is empty,
and the harness did not write its final summary. These missing terminal outputs
remain missing; no receipt is synthesized and the producer is not rerun.
Complete partial observations/logs are preserved as byte-exact verified gzip
carriers. After identity checks,49 disposable probe files are removed, releasing
1,590,725bytes; the completed5,069,846-byte raw REA progress log is compressed.

A completed passive visual supplement retains three unaltered640x480 frames
from this existing game's display, with147/148/147 colors. The frames show the
brick field, ball, paddle, falling bonuses, projectiles and score. The existing
controller's display authorization is reused; no input, target memory or
display access policy changes, and no extra game run. A subsequent X window
ownership check identifies the same recorded game PID/start ticks. Periodic
observer rows are not synchronized to frames: no exact frame-to-board assignment,
original/source pixel equality or all-state rendering claim follows.

Private `play-spotcheck/verification.json` within the campaign folder verifies
all108 frozen inputs and four unchanged products, the capture driver and three
image digests/dimensions, and retains complete initial-board event witnesses for
slots0–11. Its small supplementary manifest refers to the preceding completed
digital-audio seal. This is a verified campaign prefix and visual observation;
the interrupted attempt supplies neither the full50-board predicate nor final
REA process Evidence.

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

The [current entity-use episode](CURRENT_ENTITY_PLAY.md) observes the VC4
product from source commit `d544ecf` for 45.019 seconds on original board 0.
It supplies bounded game-use evidence after the latest allocation changes;
full campaigns below retain their earlier executable identities.

## Completed original control

The original-only control now passes the full predicate with the unchanged
campaign bank. REA `capture-process` Evidence
`ev_e7f2df5e40a1a0ba723c0156934c2684a7f136e0ebee954177b00cac5e746c8f`
records normal child exit zero and binds the complete final report digest.
The harness verifies initial board bytes for all indices 0–49, then observes
index 50 in the menu with end, reset and return-to-menu flags cleared.
It finishes in **5,465.402 seconds**, retaining eight lives and score 149,624.
Bonus advancement is permitted; this is campaign completion, not a claim
that every brick was destroyed.

The read-only SDK observer consumes 428,040 valid samples with no malformed
samples. Its pipe-byte digest and bounded transition observations are retained;
the full streamed data is not stored. Game audio is routed to the dedicated
null sink while the host default stays unchanged. All original files and the
bank remain identical. Both game/reader identities are inactive before the
98-file `original-campaign-contact-control-01` archive is sealed and verified.
The final report SHA-256 is
`8815d628797edf34ce45d70ed0300d35bec47090d0beee9461c73583f61dfc6f`.

This establishes the original control under the recorded Wine/Xvfb environment.
Both maintained VC4 and MinGW board/menu controls also pass below.
Physical audio/Windows behavior and synchronized trajectory or pixel equivalence
remain unverified. Maintained source and exact
acceptance are unchanged. The earlier timeout below remains negative evidence.

## Maintained allocation integration control

After [shared allocation integration](ALLOCATOR_OWNER.md), both rebuilt products
pass a fresh bounded transition with the unchanged campaign bank. REA process
Evidence `ev_7bb287fac944b6b78929cba21f4bc7b24f904f6a08104f8fcc30cd304b834e44`
records child exit zero and the complete final-report digest. VC4 verifies
initial slots 0 and 1 in 27.655 seconds; MinGW does so in 34.124 seconds. Both
retain three lives. Independent clock/RNG/input trajectories produce scores
844 and 1202; equal scores or synchronized frames were not a predicate.

These runs use current maintained source defaults, including the recovered
allocation chain and real Windows adapter. They add integration evidence,
not direct owner cases or full-campaign acceptance. No target bytes, campaign
boards or game memory are changed. The SDK stream is consumed into a digest;
only bounded transitions are retained. Playback stays on the dedicated silent
sink, and the processes use one allowed CPU.

A full VC4 run with the same verified products now passes: **all 50 unchanged
initial board slots**, terminal index **50**, display mode **0**, and cleared
end/reset/menu requests. It completes in **5,081.596 seconds (84.69 minutes)**,
retaining **10 lives** and score **148,628**. REA process Evidence
`ev_e10e14cb27e397943eabc8cc454c4ae7bd1f213ac1de79d3680f443032880c7b`
records exit zero and final-report SHA-256
`4fd1d507444783711eacc6522b391938e34444908dde53264db975a289fda367`.
The observer consumes 408,990 valid SDK samples with no malformed lines;
620,223,362 stream bytes are retained as a digest rather than a large trace.

The private `allocator-vc40-full-243-35` checkpoint seals 220 supporting files,
the input closure and recovery receipt. All 468 frozen inputs and 49 original
files verify. The process capture completed while the executor's permissions
changed; recovery finalized the stale outer phase without rerunning the game.
Only the VC4 report subtree belongs to this run; older profile aliases were
excluded from its archive. The actual SDK reader is retained in a separate
SHA-verified supplement before subsequent capture compilation can replace it.

REA's global `truncated` flag is true: accumulated rendered terminal snapshots
exceeded their output budget. The raw messages retain all 50 initial-board
observations and completion, and the filesystem observation binds the complete
final report. Sampled process trees and before/after file observations retain
their normal limits. Bonus level advances are legal, so completion does not
mean every brick was destroyed. Synchronized trajectories, pixel equivalence
and complete CRT cleanup remain open. Source/direct/exact counts are unchanged,
and the original-only full control remains separate.

The maintained **MinGW full campaign also passes**: all 50 original initial
boards and the same terminal index/menu/cleared-request predicate, in
**5,631.519 seconds (93.86 minutes)**, with **4 lives** and score **131,576**.
REA process Evidence
`ev_1ee2cbd8a145ce95dd95b57f7c8f4f56ac96e02382c703dfe95f95b57fc124b5`
records exit zero and binds final-report SHA-256
`f7a6b3deb7725a7ceca4af0a5d008954ec6ecc3c6079f41ef6e57c6e15532ce4`.
The recorder reports no truncation. Its process group cleanup is verified;
settlement is quiescent and needs no additional cleanup. These are recorder
lifecycle observations, not proof of original CRT teardown.

The SDK observer consumes 422,167 valid samples and discards one malformed
line; 731,131,818 stream bytes are retained as a digest. Nonatomic sampling and
that discarded line remain explicit limits. The 220-file private
`allocator-mingw-full-243-35` checkpoint retains the actual reader EXE, the
MinGW-only report subtree and historical copies of mutable inputs. All 471
frozen inputs and 49 originals verify. The game runs silently on one allowed
CPU; the host default output remains unchanged. Independent clock/RNG/input
trajectories explain why this predicate does not compare scores between builds.

```bash
scripts/repo-python scripts/capture-windows-probe.py --probe campaign \
  --profile vc40 --campaign-seconds 7200
```

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
exits zero. At that checkpoint the terminal predicate was still unaccepted
for the full original campaign; the completed original control above supplies
the subsequent full-run evidence.

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
  --profile original --campaign-seconds 7200
```

Full acceptance requires all indices 0..49 to be observed with their original
initial board bytes, followed by index 50 and a completed menu transition.
A bonus can advance a level without destroying every brick; a progression
report must not be described as 50 brick clears. Physical Windows behavior,
audio, synchronized pixels and full campaigns of the latest products remain
open. The older reconstructed full controls above retain their own product
identities and are not attributed to the latest products.

## Full-control timeout

The 7,200-second original-only control did not finish the requested campaign.
REA Evidence
`ev_567ab025c40f68e7056eb5f905564b5b0c86581f13cc630efdaa914d68615c2f`
records a timeout and signal 9, with no child exit code or final diagnostic
summary. Its output records initialization of slots 0..36. The last periodically
saved observation remains `running`, at board index 36 with six remaining
bricks, six lives and score 86,734. Its last retained event is at 6,527.416
harness seconds; it is not an observation of the termination instant.

This is an incomplete original control, not a reconstructed-game failure or
full-campaign acceptance. All recorded game/reader process identities are
confirmed inactive before archival. The private
`original-campaign-control-01` archive seals 91 files: the unchanged frozen
inputs and actual SDK reader, the complete REA capture, the unchanged partial
observation and stderr logs. Its separate checkpoint records `interrupted`,
missing final summary and `full_campaign_accepted: false`; initial `attempt.json`
and the partial observation keep their historical statuses.

A local audit verifies all 80 current/frozen inputs, the actual SDK product,
49 original files and their runtime copies. These file identities do not turn
the partial record into a terminal runtime observation. After verifying the
archive, journaled cleanup removes the 49 disposable runtime copies and
recovers 1,599,429 bytes (1.53 MiB). A subsequent preview has no pending actions.

## Diverse contact offsets

A review of the sealed original control finds a sampled plateau on board 36:
168 final gameplay snapshots retain the same grid, score 86,734, six remaining
bricks and six lives over 1,671.159 seconds. The application remains active and
unpaused at those samples, with velocities `(±5, ±7)`. This establishes stalled
progress under that controller; it does not establish a frozen process, closed
orbit or reconstruction defect. The final `running` save remains historical
partial evidence, rather than the termination instant.

The earlier sealed counterfactual executed original rebound `0x00411410` for
12 centered, width-219 fixtures: the alternating 20% offsets produced two
velocity pairs, while six different contact offsets produced six. The current
[campaign controller](../../scripts/campaign_controller.py) adopts those six
offsets while retaining the existing bounds and best-effort catch/bonus rules.
Its fallback does not guarantee avoidance when no safe candidate is available.
[test_campaign_aim.py](../../tests/test_campaign_aim.py) executes 216 original
rebound fixtures across two paddle widths, three positions, three incoming
horizontal velocities, two lookaheads and six phases. Complete original code
bytes remain unchanged. These contact counterfactuals have no bonuses and do
not establish live prediction or add direct owner cases.

The revised original/native episode compares **17,688 frames**, advances from
index 0 to 5 and retains three lives. All 103 report inputs and the unchanged
native product are bound. This is another controlled connected episode, not
whole-campaign or physical input acceptance.

REA process Evidence
`ev_a6bd19829343823e686056aebc4ddb1d94a99b43f2ad71518fa4b0c6b74ddc84`
records the revised original-only runtime control exiting zero. It verifies
complete initial bank bytes for indices **0–3** and finishes in about 188 seconds
with two lives. All six phases have ordinary XTest mouse requests. The sealed
`original-campaign-diverse-pilot-01` retains 98 files and the actual SDK reader;
REA binds the complete final report digest. Reconstructed Windows products and
full 50-board completion remain separate and unaccepted by this pilot.

A phase spans 100 processed latest SDK records, rather than 100 game frames or
fixed wall time. Reports retain phase request counts and the last ordinary
mouse request beside bounded state events. Sequential live reads can mix
frames; discarded malformed lines do not make valid JSON atomic. The counter
is now named `discarded_malformed_samples` to describe its actual scope.

Campaign captures allow a 4 MiB whole-file hash budget, replacing the earlier
128,000-byte limit that omitted the long interrupted report digest. A report
larger than that budget can still have a null REA digest; the sealer separately
retains its complete bytes without inventing a REA observation. Initial input
snapshots use a distinct `input-snapshot.sha256.json`; only the final sealer
creates `sha256.json`, preserving its existing overwrite rejection.

### Diverse-controller full-control timeout

The 3,600-second original-only control also ends before full acceptance. REA
process Evidence
`ev_d4faf61d0314b010e141adf163e70a01f7561131e676432d331a97a694efe43d`
records timeout/signal 9, no child exit code and no final diagnostic summary.
The unchanged periodic observation verifies initialization of slots **0..26**.
Its last retained event is at **3,284.230 harness seconds**, at index 26 with
seven lives, 45 remaining bricks and score 73,018. All six controller phases
have ordinary mouse requests. These are partial observations, not the state
at termination or evidence that all requested boards completed.

`original-campaign-diverse-control-01` seals 97 files after both observed
game/reader kernel identities become inactive. It retains all 86 frozen source
inputs, the actual SDK reader and complete REA capture. The checkpoint records
`interrupted`, missing final summary and `full_campaign_accepted: false`;
the original attempt and partial observation keep their historical statuses.
There is no full-report digest for REA to bind. This remains an incomplete
original control; reconstructed campaign acceptance is separate.

The sequential queue then stopped because its local driver expected the
normal sealer's `pass` status; interrupted sealing correctly returned `sealed`.
The archive had already succeeded. The failed producer and phase log are
preserved before correcting that assumption; this attempt is never resealed.
The independent contact fixtures below execute after verifying the archive,
inactive processes and unchanged accepted native product.

### Controlled contact timing

[test_campaign_contact.py](../../tests/test_campaign_contact.py) executes **320
fixtures / 2,560 compared calls** through the original ball updater or full
gameplay frame and maintained native C. Those original entries are not hooked.
The reused Core Harness compares complete globals, tiles, auxiliary state,
typed list roots/cursors, allocations, free poisoning, ordered effects and
controlled pixels after every call. Original code bytes remain unchanged.
These integration fixtures add no direct owner cases or exact units.

The tests cover cached paddle position, wall clamping, mixed-speed balls,
already-passed balls, and ordinary mouse requests with declared sampling and
delivery delays. The original comparison used greatest-Y priority as its
live baseline. The [contact policy](CONTACT_POLICY.md) chooses the
earliest falling-ball contact and projects horizontal movement by the original
discrete wall clamp/reflection rule. It retains the six contact offsets.

| Controlled family | Greatest-Y baseline | Contact policy |
| --- | ---: | ---: |
| Mixed-speed fast-ball catches | 16/72 | 72/72 |
| Viable-ball catches beside a passed ball | 0/8 | 8/8 |
| Wall-projection contacts with sampling/delivery delay | 16/16 | 16/16 |

The original full frame updates the current paddle from the mouse request
before processing balls. Ball collision uses the previous paddle cache,
which is refreshed after the entity updates. The mixed-speed
fixtures demonstrate why greatest-Y priority can react too late: a faster
ball can contact first. The declared delays are frame controls, not measured
Wine/Windows latency. Fixtures use synthetic empty boards, controlled
non-game dependencies and known valid sprites/list metadata. They do not
cover active kind-3 movement, bonuses, atomic SDK sampling or a full campaign.
The initial candidate was confined to tests pending those wider observations.
Its shared `lookahead=0` changed bonus projection; the current policy keeps
bonus lookahead independent. These 320 fixtures still contain no bonuses.
Mixed-speed counts track the fast ball's catch; their fourteen-frame trace does
not establish survival of every ball or round. The subsequent
[expanded suite](CONTACT_POLICY.md) compares 1,464 fixtures / 21,168 complete
frames, including moving bonuses, all six phases, gravity/wall boundaries and
nonzero kind-3 storage. Its 40-frame two-ball traces track both initially
falling balls: the contact policy catches and retains both in 72/72 fixtures,
versus 16/72 for greatest-Y priority. No live kind-3 producer or full campaign
is established. The live controller now uses the same contact policy.

The contact suite now rejects optimized Python explicitly before constructing
the harness or writing a report. A fresh replay against the accepted core-queue native
product passes the same 320 fixtures / 2,560 compared calls; it adds no owner
acceptance cases. Greatest-Y remains an explicit historical comparison policy.
The aim, expanded policy, connected-episode and live-observation entry points
also reject optimized Python before executing their checks.

```bash
scripts/repo-python tests/test_campaign_contact.py
```

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
Its connected frames are separate from direct owner cases (95,873 at that
first checkpoint). The current contact-policy replay compares 16,756 frames
and five advances; it retains three lives at every transition.

## Storage and evidence

The persistent reader buffers each sample into one pipe flush. The harness
drains the pipe, hashes consumed bytes, retains state transitions and one
periodic sample per ten seconds, and caps the event log. It does not retain an
unbounded frame stream. A stream hash is an identity of consumed bytes; it
cannot reconstruct discarded samples. Reports bind the reader, SDK/compiler,
input libraries, original files, source inputs and actual game products.

For an original-only attempt with frozen inputs and a retained SDK product,
`scripts/seal-original-campaign.py` validates the finished report against that
snapshot and the REA scenario/child result, then retains complete reports and
small stderr logs under the attempt directory. It checks actual Linux process
identities (PID, kernel start ticks and boot ID), so a still-live game/reader
blocks sealing. An active writer lock also causes an immediate refusal. An
existing sealed archive is preserved.

The input snapshot consists of `attempt.json`, repository-relative input
copies and `campaign-reader.exe`. The manifest binds input SHA-256 values,
the retained reader hash, profiles, board/time scope and the two observed
kernel process identities. Keep this snapshot while the actual processes are
live; later validation requires the report's complete input set to agree.
Normal sealing retains failures as failures and excludes stale directories for
other products. Explicit `--interrupted` sealing accepts only a REA timeout
with a signal, no final summary and an unchanged original-only `running`
observation saved during that capture. It audits current/frozen inputs and
original/runtime files before retaining the partial bytes without editing them.
This path has no campaign-pass outcome. It does not promote owner functions or exact units.

REA 4.1.0's `file_bytes` budget bounds whole-file SHA-256 work. A larger file
is recorded with size and a null digest, and the filesystem snapshot is marked
truncated. The existing campaign scenario uses 128,000 bytes, so a long run's
complete report can exceed that budget. The sealer independently hashes and
retains the complete report and records `rea_binds_full_report_digest: false`
when REA supplied no matching digest. That distinction remains explicit in the
archive; a local hash does not retroactively become a REA observation. Future
long captures need a larger configured hash budget. This requires no original
game or provider patch.

After the attempt terminates, seal it before journaled cleanup. Supply its
existing snapshot and corresponding timestamped capture directory:

```bash
scripts/repo-python scripts/seal-original-campaign.py \
  --attempt .analysis/checkpoints/ATTEMPT \
  --capture build/reports/rea-process/CAPTURE
# Only when REA timed out and no final diagnostic summary exists:
scripts/repo-python scripts/seal-original-campaign.py \
  --attempt .analysis/checkpoints/ATTEMPT \
  --capture build/reports/rea-process/CAPTURE --interrupted
scripts/repo-python scripts/clean-local.py --apply
```

`tests/test_campaign_retention.py` checks these identity and rejection gates
using synthetic files and actual Linux process identity. Its 41 checks include
changed products/input sets, incomplete terminal predicates, contradictory
child results, oversized reports, live/competing sessions, changes during
archiving and archive overwrite. The interrupted cases also reject stale
observations, changed runtime inputs, conflicting final summaries and incompatible
REA exits/filesystem results, and verify byte-preserving partial archival.
Public CI runs it without private game assets, Wine or a compiler session.

Keep unique Evidence, originals, pinned tools and manual saves. Unchanged
owner/exact evidence is reused only after a complete input and product audit;
this integration work adds no function or exact promotion.

The first archive seals 133 files and 114 external evidence references. After
archiving, cleanup recovers 17.70 MiB across 154 operations, including redundant
REA aliases/catalog storage and resettable runtime copies. The final preview
has no pending operations and `build` is about 20 MiB. Public CI passes the
native integration helper and the persistent observer commits, including its
strict standalone SDK compilation without original assets.

The cleanup tool subsequently extends identical-record sharing to all complete
JSON in closed REA runs. Another 80 hardlinks recover 43.53 MiB while retaining
every path and Evidence ID. All 451 closed JSON identities and 114 checkpoint
references remain unchanged. Total recovery is 61.23 MiB and `.analysis` is
about 343 MiB. Mutable root aliases/snapshots, unique observations, originals,
installed tools and manual saves are excluded from this sharing rule.
