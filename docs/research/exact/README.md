# Exact reconstruction notes

All 270 classified authored functions are exact: 84,968 code bytes across
53 compiler closures. The [PCX closing audit](PCX_FILE_PREFIX_RECOVERY.md)
checks all 270 complete spans, 4,759 code bindings and 252 full literal references.
[Progress](../../PROGRESS.md) also covers the CRT inventory and live verification.

## Final source recoveries

| Family | Record |
| --- | --- |
| PCX decoder and final audit | [File prefix and decoder](PCX_FILE_PREFIX_RECOVERY.md) |
| Last-brick lightning | [Source owner](LAST_BRICK_EXACT_SOURCE_OWNER.md) |
| Rotated sprites | [Typed cursor recovery](ROTATION_TYPED_CURSOR_RECOVERY.md) |
| Triangle controller | [Conditional temporaries](TRIANGLE_CONDITIONAL_TEMPORARIES.md) |
| Paddle rendering | [Renderer source owner](PADDLE_RENDERER_SOURCE_OWNER.md) |
| High-score drawing | [Scalar recovery](HIGH_SCORE_SCALAR_RECOVERY.md) |
| Dirty-region presentation | [Include/source context](PRESENTER_INCLUDE_SOURCE_RECOVERY.md) |
| Polygon filling | [Local source recovery](POLYGON_LOCAL_SOURCE_RECOVERY.md) |
| Glyphs and text | [Glyph source owner](GLYPH_SOURCE_OWNER.md) |
| Sprite operations | [Separate source owners](SPRITE_SOURCE_OWNERS.md) |
| Line and rectangle drawing | [Drawing primitives](DRAWING_PRIMITIVES_OWNER.md) |
| Frame pacing | [Waiting cursor](FRAME_WAIT_CURSOR.md) |

## Function families

These records follow the original instructions, recovered source and complete
compiler comparisons. Counts inside them describe their dated checkpoints.

- Windows: [instance lock](EXACT_WINDOW_INSTANCE.md), [initialization](EXACT_WINDOW_INITIALIZATION.md),
  [WinMain](EXACT_WIN_MAIN.md), [messages](EXACT_WINDOW_PROC.md),
  [switch exits](EXACT_WINDOW_SWITCH_EXITS.md), [key routing](EXACT_WINDOW_KEYS.md),
  [game-key exits](EXACT_GAME_KEY_SHARED_EXIT.md).
- Modes: [main frame](MAIN_FRAME.md), [mode lifecycle](MAIN_MODE_LIFECYCLE.md),
  [menu/gameplay frames](EXACT_MODE_FRAMES.md), [editor](EXACT_EDITOR_FRAME.md),
  [intro](EXACT_INTRO.md), [splash](EXACT_SPLASH.md), [round lifecycle](EXACT_LIFECYCLE.md),
  [runtime setup](EXACT_RUNTIME_SETUP.md).
- Gameplay: [core](EXACT_CORE.md), [ball/projectile controllers](EXACT_CORE_CONTROLLERS.md),
  [bonuses](EXACT_BONUSES.md), [brick powers](EXACT_BRICK_POWERS.md),
  [connected effects](EXACT_CONNECTED_EFFECTS.md), [brick animation](EXACT_EFFECTS.md),
  [typed lists](EXACT_LISTS.md), [list initialization](EXACT_LIST_INITIALIZERS.md),
  [projectile lists](EXACT_PROJECTILE_LISTS.md).
- Rendering: [frame boundary](EXACT_FRAME_BOUNDARY.md), [presentation](EXACT_PRESENTATION.md),
  [restoration](EXACT_RENDER_RESTORATION.md), [display](EXACT_DISPLAY.md),
  [control flow](EXACT_CONTROL_FLOW.md), [fixed-point triangles](EXACT_FIXED_POINT.md),
  [integer trig](EXACT_INTEGER_TRIG.md), [projection/text](EXACT_PROJECTIONS_TEXT.md),
  [early helpers](EXACT_EARLY_HELPERS.md), [exits](EXACT_EXITS.md).
- Resources/device: [bitmap loader](EXACT_BITMAP_LOADER.md), [bank loops](EXACT_BANK_LOOPS.md),
  [palettes](EXACT_PALETTES.md), [device frame](DEVICE_FRAME.md),
  [device dependencies](DEVICE_DEPENDENCIES.md), [shared files](EXACT_FILE_SERVICES.md).
- Audio: [MDS parser](EXACT_MDS_PARSER.md), [MIDI imports](EXACT_MIDI_IMPORTS.md),
  [MIDI lifecycle](EXACT_MIDI_LIFECYCLE.md), [sound loading](EXACT_SOUND_DEPENDENCIES.md),
  [sound buffers](EXACT_SOUND_BUFFERS.md), [sound voices](EXACT_SOUND_VOICES.md).

## Compiler and runtime investigations

- [Source context](AUTHOR_SOURCE_CONTEXT.md), [October 22 controls](SOURCE_CONTEXT_CONTROLS_20261022.md)
- [Expression ordering](VC4_EXPRESSION_ORDERING.md), [frontend symbol order](VC4_FRONTEND_SYMBOL_ORDER.md)
- [Storage diagnostics](CLOSED_STORAGE_DIAGNOSTICS.md), [fragment ownership](COMPILER_FRAGMENT_OWNERSHIP.md)
- [CRT dependency inventory](CRT_DEPENDENCY_INVENTORY.md), [runtime interface ownership](VC4_RUNTIME_INTERFACE_OWNERSHIP.md)
- [Remaining runtime source/comparison work](REMAINING_EXACT_FUNCTIONS.md)
