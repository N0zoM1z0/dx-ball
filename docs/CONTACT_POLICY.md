# Original-backed campaign input policy

The campaign controller now prioritizes the earliest reachable falling-ball
contact. Greatest-Y priority can follow a slow or already-passed ball while a
faster ball reaches the paddle first. This changes the external mouse policy;
it does not change game code, boards or target memory.

## Contracts and decisions

The policy reuses REA instruction evidence in the [core investigation](CORE_OWNER.md)
and [power-up investigation](POWERUPS_OWNER.md). Ball collision uses the previous
paddle cache, integer centers and inclusive overlap radii. Nonzero kind-3 tick
storage adds one to vertical displacement, while the original collision still
requires positive `dy`. A live nonzero producer remains unestablished.

Reachable contact is calculated from that discrete vertical band, including
odd/even sprite heights. Horizontal projection below the brick field preserves
the original clamp-before-reflection wall rule. Above the field, future brick
collisions remain unknown and short lookahead is used. Passed balls are removed
from the choice, without removing them from the game.

Ball projection and bonus lookahead are independent. The old test-only policy
passed zero lookahead to both, unintentionally changing reward/hazard estimates.
The revised policy retains the existing reward choices and best-effort hazard
avoidance. Bonus gravity, width changes and same-frame life loss are exercised
through actual original code; the heuristic does not guarantee safe collection.
Six contact offsets still vary every 100 caller decisions, not fixed frames or
seconds. Simultaneous incompatible contacts remain unguaranteed.

## Controlled execution

`tests/test_campaign_policy_differential.py` executes **1,464 fixtures / 21,168
complete original/native frames**. It covers nonzero kind-3 storage, odd/even
geometry, wall reflection, moving rewards/hazards, all six offset phases,
bonus gravity boundaries, and continued two-ball traces with declared sample
and delivery delays. The complete Core Harness checks globals, tiles, pixels,
typed roots, ordered effects, allocation lifetime and released-memory poisoning.
Original code bytes remain unchanged.

In the 72 continued two-ball fixtures, the contact policy catches and retains
both initially falling balls in all 72; greatest-Y priority does so in 16.
The greatest-Y baseline preserves at least one ball in those bounded traces. These
results do not establish every-ball survival across an entire round.
The moving-bonus matrices retain life-loss outcomes, including harmful bonuses;
they do not turn best-effort avoidance into a guarantee.

Catch metrics require an observed positive-to-negative velocity transition.
An initially rising ball is not counted as a new catch. The pre-correction
metric report and its exact producer are retained as a private diagnostic.
Reports are generated directly as deterministic gzip JSON to keep storage and
serialization memory bounded.

The earlier contact suite remains **320 fixtures / 2,560 compared calls**;
its historical greatest-Y baseline stays explicit. The 216 rebound fixtures
continue to check the six original quantized contact offsets. None of these
integration fixtures adds maintained functions, direct owner cases or exact
units.

```bash
scripts/repo-python tests/test_campaign_policy_differential.py
scripts/repo-python tests/test_campaign_differential.py --frames 40000 --boards 5
```

## Live observation boundary

The read-only SDK observer now emits previous paddle X/Y, kind-3 tick storage
and the bonus gravity counter already present in the reviewed node record.
These fields use retained REA owner contracts; no new addresses or offsets are
guessed. Valid JSON remains a sequential sample that can cross game frames.
Declared test delays are not measurements of Windows/Wine delivery.

The live controller uses the same contact policy. Actual original/VC4/MinGW
campaign observations remain separate from synthetic frame fixtures. Full
50-board completion, terminal menu routing, physical audio and Windows driver
fidelity still require their own complete evidence.

REA game captures now route playback to a dedicated PulseAudio null sink by
default, using `pactl`. The game still creates and uses its audio interfaces;
this host setting keeps tests quiet without changing video playback elsewhere.
Capture summaries record the selected sink. Independent display/resource SDK
captures do not need that audio route.

REA process capture
`ev_fe68d60b541b3d4c36af3de49724b3b6d15a51d2f8b969d8d3b72ddccb2e0ee7`
records successful first transitions in the original, VC4 and MinGW products;
each verifies complete initial bytes for indices 0 and 1. Their independent
runs take about 39, 37 and 27 seconds. Playback was muted partway at the user's
request, so this is not physical audio evidence.

The silent original-only follow-up,
`ev_a5eaf855aaac8738e31c74803c466a27df0ab8b5259d48a4e54c44d6278e5552`,
exits zero and verifies initial indices 0–3 with three lives. A separate host
observation confirms the game's actual PulseAudio stream on the dedicated
null sink. The earlier 25-second silent episode is retained independently as
`ev_97fbf35d5564225294240560b099e91089f21d8be6f7fe02f31c1bb814a776e3`.
These controls still do not establish a complete 50-board campaign.
