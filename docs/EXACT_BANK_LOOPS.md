# Bank loops and palette state restoration

Three complete functions pass grouped cold replay with zero differences: bank
initialization (131), bank release (125), and palette initialization (206),
462 code bytes in total. All 97 preceding units preserve their complete code
and accepted metadata identities.
The same batch restores five complete palette/COM candidates totaling 2,080
bytes; these remain nonexact and are not added to the exact count.

| Entry | Function | Whole bytes | Saved REA Evidence |
| --- | --- | ---: | --- |
| `0x403c20` | `initialize-sprite-banks` | 131 | `ev_ac7fa0e07bc68efa267f3caf8637f4a6912b4f5ba66ae42249ffbff5e5b53672` |
| `0x403cb0` | `release-sprite-banks` | 125 | `ev_446beb8f1f3a4a6caef3507317a6cc511c2d3afc8ebaf75fecd4cfa3ff164d8e` |
| `0x403230` | `fill-rect` | 85 | `ev_b99b4211419ba41390b72f70b56be67edc16632cfcad034c0a02edccf4b57629` |
| `0x40aa60` | `rotate-rgb-colors` | 188 | `ev_d69a03478a3300403b907eadb1d092d72ea91325ee9a2d51042a1105207b5bb3` |
| `0x40a880` | `rotate-palette-right` | 234 | `ev_35f62db7fc86382109be50f01f5d0ead909598ff5cb4328d8d76157b157b21d0` |
| `0x40a970` | `animate-palette` | 234 | `ev_a5263d59f79fee20c3d1c580888f256c258a6bb80332e83da49071d7e3048e9a` |
| `0x4096c0` | `initialize-palette` | 206 | `ev_1f7ee3646ca9d02b5f9f7b91f0c1cbfe3f3af3a8f021debadd09191a0c844cbd` |
| `0x40a340` | `palette-transition` | 1339 | `ev_eaf357e839ddf4487c962040bded218134cadfcccd5854a83a07cee7f285a71a` |

Both bank controllers retain their outer for loop and restore the inner while
loop: initialize before the condition, test slot <= 254, and increment inside
the body. Release initializes its slot before bank selection. Palette
initialization writes the six live/saved RGB fields independently and consumes
the same HRESULT local after CreatePalette and SetPalette, returning on each
failure. Ordinary returns preserve the observed epilogue branches. Flags and
whole bank/palette ownership remain unchanged.

The 1,339-byte fade restores two direction-specific do loops, explicit RGB
branches, six direct absolute-difference calls, two frame waits and the final
unchanged submission/wait. Saved direction checks are independent. Palette
colors use full signed component comparisons and byte stores; step must be
positive for the existing bounded termination claim. The complete emission
retains 18 comparison differences: twelve bytes in genuine palette-root
relocation operands and six inverse branch opcodes. Every relocation remains
fully applied and compared. Commuted operands and explicit
signed component casts emitted the same differences; neither is adopted.

Right/left rotation restores the single wrap branch with three consumed color
values and an alternate zero path. Complete entry shifts preserve flags;
terminal RGB writes leave their entry's flags intact. Both 234-byte bodies
retain eight frame-displacement differences. The 188-byte RGB rotation
restores its complete exit and retains seven frame differences.

Rectangle fill restores the actual 100-byte color-fill FX contract and its
size/fill-color fields, the original top/bottom/left/right store order, direct
handle access and ordinary return. The existing shared typed FX record replaces
the raw DWORD array. No additional clearing is performed: the original and
existing twelve-vector oracle define only size, color and four rectangle fields,
plus null source/rectangle and flag 0x400. Other FX bytes remain outside scope.
Its complete 85 bytes retain eight stack displacements.

All eight spans are contiguous through RET and retain every emitted relocation.
The saved references pin whole state roots and direct abs/frame-wait callees;
no callback table is mapped onto an unrelated import cell. No name/declaration
search, fake locals, padding, assembly, copied machine bytes or source profiles
are used. Original source spelling and the complete compiler configuration
remain unproven. Saved matching REA evidence and its 465-record snapshot are
reused; no new original-analysis session or test matrix is introduced.

All 22 existing owner scripts pass against the frozen native Debug product.
Complete grouped cold replay passes **100 units / 12,227 code bytes + 136
separate metadata bytes** across twenty-two actual compiler objects. Existing
fourteen rejection controls, strict MinGW and full VC4 builds pass. Unchanged
raster/rotation compiler inputs, recipes and actual logs verify reuse of their
preceding 7,164/1,024 COFF vectors. No tracked tests or fixtures change.

Acceptance remains **283 source-present / 247 scoped semantic entries /
112,273 distinct cases**. Origins remain 270 authored, 48 runtime,
42 compiler-generated and 168 unknown. Private checkpoint:
`.analysis/checkpoints/exact-bank-loops-283-100`, parent
`.analysis/checkpoints/exact-exits-283-97`. Frozen inputs, actual compiler
products, full saved REA dossiers and independent reviews are retained before
verified cleanup. The 465-record snapshot is unchanged.

Source presence, semantic scopes and distinct cases remain separate from exact
matching. Complete authored denominator, original types, driver/whole-game
fidelity and the **>=95% complete-source objective remain open**.
