# Complete exits, text centering and palette guard

Eleven complete functions pass grouped cold replay with zero differences,
adding 641 code bytes. All 86 preceding units preserve their complete code
and metadata identities.

| Entry | Function | Complete bytes | Saved REA Evidence |
| --- | --- | ---: | --- |
| `0x4050F0` | `prepare_sound` | 33 | `ev_5345b28e6714252665c89598e94047ef4b2947c4ad089e47fa294ed785c5c948` |
| `0x4058B0` | `release_sounds` | 61 | `ev_94a38a0c816a05c2eae87be84cd560341ef73e597cb6637f535aec41f628d6f9` |
| `0x405EB0` | `stop_all_sounds` | 61 | `ev_2b3dd1168377f765b3a2aa76502a2a941735ed95a792fab6139481e60c68e8c4` |
| `0x406270` | `release_audio` | 26 | `ev_a555f330cfa6fce76d239915d26e68401117a5a9fdc4df26ebda7a734f239585` |
| `0x409000` | `bind_board_surface` | 24 | `ev_793213d9624462f067cc47da086586081b3930aeda1fdcb6bd960c76c67f27ab` |
| `0x409020` | `bind_display_surface` | 24 | `ev_00b16a611bc5e4f266b1e88706440b0a105d15aae971652ef533c26512984fd7` |
| `0x407AB0` | `splash_key` | 36 | `ev_d1c87d90c887ddeb6eefe0dcd882a3c99b7c1bbfa0c5ffdad565e81e696538ac` |
| `0x411820` | `retire_ball` | 45 | `ev_a36e9fab3ac21396c7a04fb5c8ea1b26eb31446fb29f612397d068d2eed7d17c` |
| `0x404EE0` | `draw_text` | 150 | `ev_163d2c095b63214d821d53492ba6108c07a18e965f5135a2e90af53cb53aadd3` |
| `0x404F80` | `draw_centered_text` | 73 | `ev_3aaaa3e23bdd7e6a30fce980204aff52420ded4f7e5cbb9015195196594b429a` |
| `0x40AB20` | `set_palette_rgb` | 108 | `ev_677c089ab1d99c09f648bf51f8d486dc81df271573b32af3ba3f53fdb5c50e68` |

Each saved dossier owns its full contiguous span through RET. Explicit ordinary
returns restore the observed branches into the frame epilogue. These are
source control-flow operations; no padding, assembly or machine bytes are added.
The original source spelling remains unproven.

Centered text stores the measured width in a real, consumed local and passes
`x - width / 2` to the drawing function. Original instructions store/reload
that width and leave the x parameter unchanged. Palette setting returns early
when cursor warping is disabled with value 1, then has a final ordinary return
after the COM SetEntries call. The earlier enclosing conditional omitted both
observed exit branches. Public signatures, field ownership and layouts remain
unchanged.

Every emitted relocation has an explicit saved-reference binding. Ball count
remains the previously attested field at offset 20,024 of whole board storage
root `0x43AAB8`; the independent ball list is at `0x43A8B8`. No owner is split.
The sound wrappers call maintained game routines directly; their complete
matching does not establish complete sound-driver or asynchronous audio
fidelity. Table, palette, COM and surface pointers retain their observed roles.

Existing owner tests and compiler recipes are used. No new test matrix, fixture,
original-analysis session or semantic case is added. Saved REA evidence and the
465-record snapshot are reused. Valid backing, bounded text/record inputs and
previous arithmetic exclusions retain their existing scopes.

The frozen native Debug batch passes all 22 existing owner scripts. Complete
grouped cold replay passes **97 units / 11,765 code bytes + 136 separate
metadata bytes** across nineteen actual compiler objects. Existing fourteen
rejection controls, strict MinGW and full VC4 builds pass. Raster and rotation
reuse their preceding 7,164 and 1,024 COFF vectors after complete compiler-input,
recipe and actual test-log identities are verified. No tracked test changes.

Acceptance stays at **283 source-present / 247 scoped semantic entries /
112,273 distinct cases**. Origins remain 270 authored, 48 runtime,
42 compiler-generated and 168 unknown. Private checkpoint:
`.analysis/checkpoints/exact-exits-283-97`, parent
`.analysis/checkpoints/exact-integer-trig-283-86`. It retains frozen inputs,
actual products, saved evidence and independent reviews before verified cleanup.
The 465-record REA snapshot is unchanged.

Source presence and origin counts stay unchanged. The complete authored
denominator, original types, whole-game fidelity and **>=95% complete-source
objective remain open**.
