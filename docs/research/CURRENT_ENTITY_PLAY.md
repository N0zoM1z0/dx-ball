# Current rebuilt entity use

The VC4 executable built from source checkpoint `d544ecf` runs a bounded
45-second original-board episode after the
[direct entity allocation restoration](exact/EXACT_ENTITY_ALLOCATION.md).
Read-only SDK samples observe nonzero particle, animation and explosion current
pointers and nonempty bonus lists during actual game play. The score increases
from zero to 824. This adds current executable integration evidence to the
controlled native/original-x86 and actual relocated VC4 owner checks.

## Product and observation

- Source commit: `d544ecf53ad64b615823a4ddd5efdcad2de1320a`.
- VC4 executable SHA-256:
  `650968e5641d4662b53093656b59b50888bc6b0a0b904a1981503a64ef69a428`.
- Link map SHA-256:
  `ab7ad8032307e666568f42629940aa0f46bccf2278df472b8d8675a0c2dfc80e`.
- Unmodified original `DEFAULT.BDS` SHA-256:
  `f2d055c7a6a43815dc8d4e9387770ee6e966587b4c802b32dbb693ce35a73f30`.

The unchanged [campaign observer](../../tests/test_windows_campaign.py) and
[mouse controller](../../scripts/campaign_controller.py) supply ordinary XTest
input. A private wrapper adds three scalar fields to the existing reader and
retains its latest processed states. The SDK observer uses ReadProcessMemory;
it does not write target memory, hook execution, suspend the game or alter
boards. The run uses one CPU, Xvfb/Wine and the dedicated silent audio sink.

The result is `bounded-episode` after 45.019 seconds. The pipe yields 3,941 valid
SDK records and zero discarded malformed records; the existing latest-record
consumer processes 3,940. Of these, 3,480 have game mode 1. There are 382 mouse
clicks. The initialized board indices are `[0]`; the last state has score 824,
one ball and seven remaining bricks. No board completion is claimed.

The observer/controller wrapper returns successfully. The existing `finally`
stops the reader and game, sending SIGTERM to a still-running process group.
This is not evidence of a graceful game exit with status zero.

## Reads and observed presence

REA's retained [entity](ENTITIES_OWNER.md) and [effect](EFFECTS_OWNER.md) contracts
identify each owner as three x86 pointers: current, first and last. Current
rebuilt addresses come from the verified link map. Explosions use the maintained
`dxball_board_storage_offsets` metadata and the existing `STORAGE_FIELDS` index;
the observer does not assume that the rebuilt layout has original addresses.

| Owner | Original owner VA | Current owner VA | Read | Nonzero/nonempty game samples | Boolean presence changes |
| --- | --- | --- | --- | ---: | ---: |
| Particles | `0x43A868` | `0x4274A8` | Four-byte current pointer | 252 | 10 |
| Brick animations | `0x43FA98` | `0x422488` | Four-byte current pointer | 256 | 18 |
| Explosion requests | `0x43F8E0` | `0x427300` | Four-byte current pointer | 151 | 34 |
| Bonuses | `0x43FAC8` | `0x4274B8` | Linked list from first at owner +4 | 1,088 | 10 |

All four counts use the same 3,480 game-mode samples. A zero **current** pointer
alone does not establish that first/last are empty. The bonus reader traverses
next links with the unchanged 128-node bound, cycle detection and actual sprite
dimension checks. Fields and nodes are read sequentially, so even a successfully
parsed record is not an atomic frame. Boolean changes therefore do not prove
individual constructor, deletion or ownership events. The earlier controlled
owner checks retain responsibility for those assertions.

## Retained proof and limits

Private records live in `.analysis/windows-entity-use-current/`: the original
`observe.py`, compiled `campaign-reader.exe`, `reader-identity.json`,
`vc40/observation.json`, `report.json`, logs and `sampled-entity-states.json`.
The latter retains all 3,940 processed rows in 623,801 bytes, SHA-256
`ff4533a761b3ff6e5f2cc2c89ff325b53702fb369e2a6897db90ff35436c26ea`.
The pipe consumer reports 6,052,620 bytes and a digest; the complete raw stream
was not retained. Its digest identifies consumed bytes, not a replayable stream.

The offline `verify-and-derive.py` preserves the original report and produces
`verified-state-summary.json`. The original `occupied_samples`/`empty_samples`
labels mean only `bool(value)`; the derived summary explicitly labels nonzero
current pointers versus nonempty lists. It checks recorded source/observer
inputs, all 35 current game objects and their recorded project closures,
resources, SDK import libraries, executable/map, reader/compiler, the six
recorded SDK headers, X input libraries, all 49 original assets, the copied
campaign bank, retained sample hashes and rebuilt address mappings. The six
SDK header hashes are a selected subset, not a complete recursive SDK closure.
Verification requires no additional game run or production compilation.

The checkpoint seal is
`.analysis/checkpoints/entity-play-283-171/sha256.json`. It retains this proof
and the current source/product inputs before disposable runtime copies are
cleaned. Previous full-campaign and screenshot observations keep their own
historical executable identities; they are not attributed to this product.

This selection does not compare synchronized original/MinGW trajectories,
pixels, physical drivers or asynchronous audio. It does not prove a full
50-board campaign, every entity lifecycle or whole-game source fidelity.
No source, exact or semantic ledger count changes: 283 source-present entries,
171 exact functions /30,744 code bytes /136 metadata bytes and 247 historically
scoped semantic rows. The reconstruction remains unfinished.
