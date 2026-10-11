# Exact splash foreground phase

The complete splash redraw at `0x4075D0..0x407984` now matches all 949 bytes,
68 unchanged relocation bindings and 17 complete NUL-terminated string operands.
It adds one exact body: current totals are 204 exact functions / 43,605 code
bytes / 136 metadata bytes. Source presence remains 283, with 270 known authored
entries; the complete reconstruction goal remains active.

## Source and evidence

The full-screen rectangle is needed during background setup and again during
final primary-to-secondary copying. The foreground phase draws the logo, binds
credits surfaces, draws the colored band and writes the capability/author text.
Its logo rectangle and line counter do not survive into the final full-screen
copy. Maintained source now reflects this phase, leaving the full rectangle in
the outer function. Names, types and executable tokens stay unchanged; there
are no new variables, padding, capacity or name/declaration permutations.

REA Evidence
`ev_4a967bbbf38cd42ec661c8b5dc82686fc9c2ab4f8e75a5c9b7132067706f4739`
retains the complete contiguous body and return. Its private carrier is
`13-analyze_function.json` in closed run
`2026-10-07T11-58-17.972Z-interactive-3053414`, targeting SHA-256
`756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`.
No new provider session or capture is needed. Static source lifetime is a
reconstruction inference; full compiler agreement establishes a separate claim.
Original identifiers and exact declaration spelling remain unproved.

All 256 original instruction boundaries and widths, 13 branches and 30 calls
verify. The proof parses retained original REA assembly and decodes only our
emitted COFF; the strict whole-body comparison has zero differences. The original
36-byte frame has full rectangle base EBP-16, line counter EBP-20 and logo
rectangle base EBP-36. Full source operation order, COM handles, live flags,
text, narrow maintained line API and color expressions stay unchanged.

## Bounded source stages

| Source stage | Complete body bytes | Full differences |
| --- | ---: | ---: |
| Previous flat declarations | 949 | 23 |
| Logo-only rectangle block | 949 | 17 |
| Foreground logo/line/text phase | 949 | 0 |

The first actual compile scopes only the logo rectangle. Its home matches,
but moving it alone leaves outer full rectangle/counter homes unlike the
original. The second scopes the complete foreground phase between background
setup and final copying. It matches all three meaningful homes and the complete
body. Both stages, sources, objects and compiler receipts are retained. No
blind variable splitting or renamed-local trial follows either stage.

Both canonical MT compiles preserve 13 exact intro companions across 2545 bytes.
Every other candidate's complete comparison remains identical. All 68 relocation
offsets/symbols/types/addends/targets and complete string contents stay unchanged;
no manifest offset or generated-symbol reconciliation is needed. Only the final
body is promoted from candidate to unit.

## Checks and preserved products

Two unchanged Oracle loops pass all 16 redraw combinations of primary output,
software-only, low-video-memory and vertical-wait flags, plus 58 connected
splash/intro/editor mode and key checks. Full controlled pixels, state, point,
wave and palette arrays and ordered COM/resource/audio calls compare. A separate
unchanged prelude verifies production mode/key defaults, welcome text, splash
colors and initial span/phase, without replaying owner case loops. No tracked
test, case or assertion changes; physical driver/audio and campaign remain
outside these controlled checks.

Native and MinGW rebuild once. VC4 links the final matching MT intro object
with 35 independently verified unchanged objects, without another source compile.
All 204 exact input closures, 36 production objects and 247 unchanged historical
semantic scopes verify. The 235 changed historical input inventories refresh
without claiming new execution for those scopes.

Working evidence and both source stages are in `.analysis/splash-logo-scope/`.
Independent preservation is
`.analysis/checkpoints/splash-logo-scope-283-204/sha256.json`, with explicit
before/stage products and closed REA dependencies. Authored denominator, original
source spelling, physical rendering/audio and full campaign remain unproved.
