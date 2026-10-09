# Core source emission restoration

This batch restores the computation and storage sequence of four maintained
game functions. The same C builds natively, with MinGW, and with the pinned
VC4 compiler. Configured whole-section cold replay accepts **39 exact units /
4,115 bytes**, adding **four functions / 736 bytes**. Source presence stays
247 (235 game and 12 runtime), and the direct-case total stays 112,273.

| Unit | Original complete extent | Bytes | Saved REA Evidence |
| --- | --- | ---: | --- |
| initialize-trig | `0x402250..0x402337` | 232 | `ev_be4c847d5647acb8d0ff686d8f938d149e4fd0968604c98669ff41f847fb20c5` |
| sine | `0x402400..0x402481` | 130 | `ev_844ec55c396bf6f53e88092f8514d492707cf2625133ae9ea2e38d42c948cf50` |
| cosine | `0x402490..0x402511` | 130 | `ev_34e8f2372ac37a7c69a602c5366b18f1cc8cd0873e9dbd3a51a4999d0e6f92bd` |
| spawn-ball | `0x4105D0..0x4106C3` | 244 | `ev_80aebbb169f0d2bc78a9f894e8a4f8a0dc72c3a0d0a4049fdc19518219a5f52b` |

All four saved dossiers have contiguous bodies ending in `ret`; subsequent
padding is outside the accepted extents. Existing matching closed REA records
were reused. No duplicate function query or original modification was needed.

The initializer previously cached one radians argument and wrote the cosine
table before calling sine. Original instructions independently compute both
arguments, store both returned doubles, and then convert and write both table
entries. Two meaningful double temporaries restore that sequence. Compiler
listings show that local names affect VC4 allocation: `cosine_value` and
`sine_value` obtain the observed real double slots, with `angle` in its observed
integer slot. The match establishes compatible emission; it does not recover
unique historical variable names or the original translation-unit layout.

Each lookup normalizes its signed angle, assigns the selected table integer
back to that parameter, and stores a real float result before returning.
The compiled `FST` leaves the x87 return value live, as in the original. Native
float ABI behavior and VC4 x87 emission are separately verified. Negative
multiples of 360 retain entry 360 rather than entry zero.

The ball constructor writes sprite 1, then reads the current ball's sprite
field again when looking up its height. Using literal index 1 skipped that
read and shortened emission by 12 bytes. Restoring the typed field read gives
the complete 244-byte original body, including count increment, append,
all thirteen payload fields, rebound and the explicit terminal return.

Every DIR32/REL32 relocation has an explicit position, type, addend and target
in `config/match-units.toml`. The three equal 1024.0 target literals at
`0x420010`, `0x420018` and `0x420020` are independently content-attested even
though this compiler pools their emitted source literal. Pi and divisor bytes,
the adjustment flag, division helper, integer conversion, math entries and
both table owners follow the retained instruction/data evidence. Ball storage
uses the reviewed root `0x43AAB8` with count-field addend 20024; sprite indexing
uses the established bank root and selected-bank scalar. Nothing is masked,
and the entire emitted COMDAT is compared.

The fixed VC4 flags are unchanged. One grouped cold replay rebuilds all 39
configured units after source stabilization. Existing game-oracle input
closures include all game source, so their 22 existing scripts are replayed
once against `build/native-exact-core/libdxball_core.so` before refreshing
semantic hashes. The existing rotation COFF comparison checks the changed
offset body. No new fixtures or campaign runs are added. Repeated cases are
not counted twice. Historical campaign products and reports retain their
sealed input identities; this source batch makes no fresh full-campaign claim.

## Rotation candidate and extent

The offset helper now preserves the original two separate negative returns.
Its current complete VC4 section is 261 bytes versus the original 259-byte
span, with 223 unmasked differing bytes; bank/slot address evaluation and
meaningful local allocation still differ. It remains a semantic candidate.
Typed pointer spelling and local-name
experiments are retained privately; no alternate layout, fixed address,
inert local, assembly or padding is introduced.

The saved offset dossier `ev_274065db33e0f5af45f91e84ec3c68bf86d6b31f20e54434e568a1cca50290f5`
owns 254 bytes across two ranges. The new bounded request set
`config/rea-exact-core.json` obtains the complete 259 bytes:

- `read_bytes`: `ev_1a1e5b15c7b174d385390945c96c2bf47fec10cf62ad260c7001598e5469e3e9`.
- Gap instruction inspection: `ev_e7e4c861bee9e143814af7018584c034e7a2db720e0bfe998af233c932e9928f`.
- Gap references: `ev_3df01667ee917695aa3ecda8a896bab408501f68af2f51503bea7992cd41b48b`.

REA returns `undecodable` at `0x402DBF`, where Ghidra has no Listing instruction,
and no direct references to that address. Complete bytes match the pinned PE.
The five gap bytes `e9 0a 00 00 00` derive an unconditional jump from
`0x402DBF` to the shared epilogue at `0x402DCE`. This is opcode/displacement
arithmetic inferred from REA's bytes, not provider decoding or observed
execution. The VC4 listing independently emits the unreachable jump after
the returning first branch of an `if/else`. The bytes lie inside the complete
function span and must be compared if it becomes exact; they are not padding
to discard. Explicit close saves 348 cumulative Evidence records.

The 95% complete-source objective remains open. These exact units establish
four specific source emissions; they do not prove complete CRT, driver,
rendering or synchronized whole-game fidelity.
