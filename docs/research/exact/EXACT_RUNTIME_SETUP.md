# Complete game setup, redraw and score controllers

This batch restores initialize-game (736 bytes), redraw-game (269) and draw-score
(433) from complete contiguous REA instruction dossiers: 1,438 original bytes.
Original names, declaration order and score-buffer capacity remain unproven.
One maintained controller body serves native, MinGW and VC4 builds.

| Entry | Complete body | Primary Evidence |
| --- | ---: | --- |
| 0x40F4C0 | initialize-game / 736 | ev_8dcd43fc9cee3e9d52bc3af33b744a2136c00f6ae467d12e84ba774fb3037077 |
| 0x40F7A0 | redraw-game / 269 | ev_aeece82729d07e73584d5066745d79f92597ed573a1580ab42f3a47dbbf9a3cd |
| 0x4158D0 | draw-score / 433 | ev_5bd8ce0bb9a8d5a889e6d06e213d148ea1bd2ad54e5d755b82c7705c50cfff4c |

Initialize preserves all 42 direct original call sites, including 25 separately
ordered sound slot/path calls and both display-surface bind branches. It keeps
actual resource-owner calls, bank-two fields, score/life/paddle state and board /
round setup. Removing the callback loop also removes its iterator/table storage;
there is no original automatic frame. All path operands require their complete
null-terminated contents, including the separate reset-round background literal.

Redraw keeps one real 16-byte rectangle and three original COM Blt calls. It
reads the current shared handles after clear, draw and text callbacks. Its direct
clear/text owners, paused==1 branch, signed positive buffer-count gate and
primary-selection gate follow the observed instructions. Callback-installed
handles are not cached across earlier operations.

Score calls the actual unsigned decimal CRT boundary at 0x41F570 with radix 10,
then the separately identified strlen dependency. It preserves the unsigned32
score bit pattern before widening to host unsigned long. The existing 11-byte
buffer holds the full unsigned32 decimal representation and NUL; its capacity
is not inferred as the original array spelling. Two COM BltFast operations read
current shared handles; text, keyed sprite and by-value invalidation are direct
owners. The real lives DWORD is consumed first as capped count, then reused as
22*(count+1) restore span. Shared life cap, icon rows and ordinary return remain.

Focused pinned REA establishes the complete 30-byte _ultoa wrapper and its
96-byte static xtoa helper, with an observed fourth sign flag zero and unsigned
DIV. Evidence ev_16217354766a89a301447e87d1396fc7f6bd91da34cd7b14476c9618f48377f6
and ev_ae3a244793f13621a162cda74914dec8c6030edc2382ca7fa8cf1c7e5fc2decb
supply ownership and ABI, corroborated by whole pinned VC4 library sections.
Both entries gain runtime-origin identification (50 runtime / 166 unknown);
authored270 / generated42 remain fixed. These identities are separate from
source presence or compiler exact units. A checked platform-only Linux CRT bridge supports this caller's decimal
unsigned32 domain; Windows uses its genuine CRT. It is not restored vendor code.

One diagnostic compile retains 69 source inputs. Initialize and redraw match
all 1,005 bytes. Score has equal 433-byte extents with 76 full differences in
frame/local/expression emission. The 127 actual new relocations are all explicit;
no masking, padding, alternative layouts, fake locals, copied machine bytes or
name/declaration-order trials force a zero. Existing reset's generated literal
label is rebound only after full content/target attestation.

Existing selected cases are 18 initialization, 24 redraw and 63 score cases;
continuous connected scenarios remain included in existing owner totals. Native
fixtures forward genuine direct owners through current copied-image tables,
with ownership/default checks and null/self/reentry guards. Existing cases and
oracle bodies remain fixed. Hardware and dependency implementations remain
independently scoped. All 22 owner scripts pass against 286 frozen inputs in 560.878 seconds.
The sole configured cold epoch reproduces 104 exact units / 12,964 code bytes
plus 136 separate metadata bytes and preserves all 102 prior complete identities.
Fourteen rejection controls, fresh 7,164 raster / 1,024 rotation COFF vectors,
strict MinGW and full VC4 builds pass. Native fixtures check 23 actual default
slots / 22 distinct symbols and retain 45 actual compiler dependency identities.
After verification, the runtime owner declared closure adds only the already
frozen and actually compiled host bridge; its original recipe/outcome is retained.
This metadata correction adds no execution or behavioral coverage. The >=95% complete-source goal remains open.
