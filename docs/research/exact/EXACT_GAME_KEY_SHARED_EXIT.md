# Exact game-key shared exits

The complete game-key controller at `0x410290` now matches all 831 bytes and
68 actual relocations. Original space and pause actions share one exit jump;
source now lets the pause case fall through to the space case's break.
The unpause path returns directly after its final palette call, before the
standalone key switch. No local names, storage layout or equivalent arithmetic
are trialed to force compiler agreement.

The original space selector targets `0x410350`, also the pause arm's exit.
Previously source emitted a separate five-byte space jump, shifting later code
and tables. Restoring that shared break gives 831/831 with one differing byte:
the unpause jump still reaches the switch exit rather than the epilogue.
Its original `0x4102EC` jump reaches `0x4105CA` directly. Adding an early return
while retaining the else wrapper creates an unreachable extra jump and gives
836/831 with 615 differences. That diagnostic is rejected. The natural early
return followed by the standalone switch reproduces the whole original body.
Three actual matching compilations are retained: partial shared break, rejected
return-plus-else, and final source. Dependent builds/cases run only on final
source, after the complete comparisons.

The full partition includes all bytes, rather than relying on Ghidra's 645
owned bytes:

| Content | Bytes |
| --- | ---: |
| 153 complete instructions | 655 |
| Six-entry music target table | 24 |
| Fifteen-entry key target table | 60 |
| All 92 key selectors | 92 |
| Complete enclosing span | 831 |

All 35 direct branch destinations and the two indirect dispatches hit decoded
boundaries. Each of the six music and fifteen key targets is attested, and all
92 selectors are bounded. The two previously unowned five-byte switch-end jumps
at `0x410498` and `0x410508` remain included. All actual internal COFF definitions
have the original relative positions; storage/type and offsets are checked.
The six complete NUL-terminated music filenames and eight-byte `-1.0` constant
retain their independently attested original contents. Parameter declaration
spelling remains unknown; the observed signed-byte load and stack ABI match.

Seven existing platform exact units retain all 936 bytes. Other complete
platform candidates remain: fullscreen 1406/1343 with 1278 differences,
compatible 1180/1147 with 1092, WindowProc 1166/1171 with 1006. Generated labels
renamed outside the changed controller are checked through actual old/current
section/value/type/storage identities; immutable original targets remain fixed.
A fixed-original-target relocation projection is used for strict comparison.
When a candidate's extent differs, resolve its actual internal definitions for
CFG work rather than treating that projection as its executable layout.

Native/MinGW each compile only platform and link the selected core/game targets.
VC4 links this same matching object plus 35 verified unchanged objects, with no
additional source compile. Only the five unchanged existing game-key loops run:
420 cases covering pause/control/keys, fade/cursor behavior, banks/paddle widths,
six music choices and pan doubles. Ordered API effects and defined state match
original execution. The initial private driver names a nonexistent dependency
path and stops before any case; its log remains, then the corrected driver
runs all 420 once. No clock, dispatch, historical full-owner or gameplay/audio
replay runs. Historical semantic input closures refresh in 235 rows; their
247 scopes remain unchanged. Current totals: 283 source, 187 exact functions,
33,832 complete exact span bytes and 136 accepted metadata bytes; origins remain
270 authored / 83 runtime / 42 compiler-generated / 133 unknown.

Closed full-read evidence is reused from
[earlier key recovery](EXACT_WINDOW_KEYS.md):
`ev_1df32140229eb7c88b6fe57d48814e8f138354ceeba1fd2a604233504998357a`,
plus its complete literal/double reads. All retained bytes independently match
the verified original. No provider/setup query. Private recipes, three stages,
complete comparisons, code/table partition, selected cases and product hashes:
`.analysis/game-key-shared-exit/`. Immutable seal:
`.analysis/checkpoints/game-key-shared-exit-283-187/sha256.json`.

Game-key's source/CFG hypothesis is closed. Further recovery must inspect actual
remaining whole-controller evidence; do not retry its empty cases or switch
spelling. WindowProc's smaller current span still needs a concrete source-flow
explanation if existing full evidence identifies one; its prior reachable-flow
proof does not authorize adding an invented operation or padding. Nearly
complete original source, authored denominator and synchronized game/audio
fidelity remain unproved.

Cleanup verifies 207 owned files / 145 immutable dependencies and four products.
97 scoped hardlinks replace 4,501,504 single-link allocated bytes; 62 completely
archived stage copies are removed, accounting 1,487,650 logical file bytes.
These are separate counts, not a measured device-free-space delta. Unique
before/current state, successful complete comparisons, both earlier stages and
selected cases remain in the seal. The final reviewer resolves every removed
stage payload through the immutable path. Supplemental post-cleanup identities
bind the cleanup receipt and current documentation.
