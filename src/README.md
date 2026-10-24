# Source map

Start with [platform.c](platform.c) → [runtime.cpp](runtime.cpp) → [core.c](core.c).
The [architecture guide](../docs/ARCHITECTURE.md) follows that path through one
frame. `config/functions.csv` maps original addresses to current source files;
`/* FUNCTION: DXBALL 0x... */` comments mark recovered routines.

## Game control and entities

| Files | Responsibility |
| --- | --- |
| [platform.c](platform.c), [platform_host.c](platform_host.c) | Window setup, instance lock, message loop, input and OS transports |
| [startup.c](startup.c) | Working resources, score files, RNG and initial bank cleanup |
| [runtime.cpp](runtime.cpp) | Five-mode lifecycle/dispatch, shared clock state and score updates |
| [core.c](core.c) | Gameplay frame, ball/projectile movement, firing and entity queues |
| [intro.cpp](intro.cpp) | Menu, splash, point animation, credits and scroller |
| [editor.c](editor.c) | Toolbar, painting, navigation and board-bank persistence |
| [gameover.c](gameover.c) | Name entry, ranking insertion and score persistence |
| [boards.c](boards.c), [board_storage.h](board_storage.h) | Board bank, working tiles, shared storage and tile drawing |
| [round.c](round.c), [round_reset.cpp](round_reset.cpp) | Level/life progression and per-board reset |
| [gameplay.c](gameplay.c) | Brick-hit rules, board power-ups, explosion requests and sound pan |
| [balls.cpp](balls.cpp), [paddle.c](paddle.c) | Ball lifecycle/rebounds and paddle movement |
| [paddle_render.cpp](paddle_render.cpp), [last_brick.cpp](last_brick.cpp) | Paddle drawing and last-brick lightning control |
| [effects.c](effects.c), [bonuses.cpp](bonuses.cpp), [particles.c](particles.c) | Animation, bonus and particle lifecycles |
| [list_initializers.cpp](list_initializers.cpp) | Global typed list owners and constructors |
| [clock.cpp](clock.cpp), [frame_wait.cpp](frame_wait.cpp) | Current time, elapsed intervals and frame waiting |

## Resources and rendering

Some routines use small compiler-owner files to retain their VC4 source context.
They share the same headers and implementations across native and legacy builds.

| Files | Responsibility |
| --- | --- |
| [resources.cpp](resources.cpp), [resources.h](resources.h) | Shared bank state, PCX decoding, sprite/font types and DirectDraw interfaces |
| [load_sprite_bank.cpp](load_sprite_bank.cpp), [release_sprite_bank.cpp](release_sprite_bank.cpp), [resources_bank.h](resources_bank.h) | Whole-bank loading and retirement |
| [select_sprite_bank.cpp](select_sprite_bank.cpp), [select_font_bank.cpp](select_font_bank.cpp) | Active sprite/font bank selection |
| [capture_sprite.cpp](capture_sprite.cpp), [release_sprite.cpp](release_sprite.cpp) | Sprite storage and lifetime |
| [draw_sprite.cpp](draw_sprite.cpp), [blt_sprite.cpp](blt_sprite.cpp), [draw_keyed_sprite.cpp](draw_keyed_sprite.cpp), [blt_keyed_sprite.cpp](blt_keyed_sprite.cpp) | Ordinary and keyed sprite drawing |
| [stretch_keyed_sprite.cpp](stretch_keyed_sprite.cpp), [draw_rotated_sprite.cpp](draw_rotated_sprite.cpp) | Stretch/rotation draw entry points |
| [load_live_palette.cpp](load_live_palette.cpp), [load_saved_palette.cpp](load_saved_palette.cpp), [load_surface_palette.cpp](load_surface_palette.cpp) | Palette loading paths |
| [glyphs.cpp](glyphs.cpp), [ui.c](ui.c) | Glyph lookup/drawing, text layout and UI palette operations |
| [display.cpp](display.cpp), [device.cpp](device.cpp) | Dirty regions, presentation, fades and surface recovery |
| [drawing_primitives.cpp](drawing_primitives.cpp) | Line and rectangle drawing |
| [rotation.cpp](rotation.cpp), [raster.cpp](raster.cpp), [fill_polygon.cpp](fill_polygon.cpp), [fill_polygon_clipped.cpp](fill_polygon_clipped.cpp) | Software rotation and fixed-point/polygon rasterization |
| [bitmap.c](bitmap.c), [geometry.c](geometry.c), [trig.c](trig.c) | Bitmap loading, geometry and integer trigonometry |

## Services, entry points and CRT

| Files | Responsibility |
| --- | --- |
| [windows_crt_entry.c](windows_crt_entry.c), [runtime_entry.c](runtime_entry.c) | Current restored-CRT entry: Windows bindings, recovered heap/I/O/environment initialization, then game entry |
| [windows_entry.c](windows_entry.c) | WinMain wrapper for compiler-CRT profiles |
| [windows_adapter.c](windows_adapter.c), [directx_factory_host.c](directx_factory_host.c) | Win32, DirectDraw, DirectSound and WinMM bindings |
| [sound.c](sound.c), [midi.cpp](midi.cpp), [music.cpp](music.cpp) | WAV buffers, MDS streaming and music lifetime |
| [file.c](file.c), [memory.c](memory.c) | File/local-memory imports shared by sound, MDS and Bitmap |
| [allocator.c](allocator.c), [allocator_host.c](allocator_host.c), [cpp_allocator.cpp](cpp_allocator.cpp) | Recovered heap policy, host callbacks and C++ allocation |
| [runtime_text_host.c](runtime_text_host.c) | Unix score-text conversion boundary |
| [runtime_initialization.c](runtime_initialization.c), [termination.c](termination.c) | Recovered CRT initialization and process exit |
| [runtime_cpp_catch.cpp](runtime_cpp_catch.cpp), [runtime_cpp_unwind.cpp](runtime_cpp_unwind.cpp), [runtime_cpp_object.cpp](runtime_cpp_object.cpp) | Win32 C++ exception machinery |
| [board_inspector.c](board_inspector.c), [resource_inspector.c](resource_inspector.c) | Command-line asset inspection |

The remaining `runtime_*` files cover CRT strings, numeric conversion, streams,
low-level I/O, locale, floating point and exception transports. The full legacy
link is recorded in [restored-crt-link.json](../config/restored-crt-link.json).
[The build guide](../docs/BUILD.md) distinguishes native, MinGW and VC4 profiles.

Headers define public state and call contracts. [state_types.h](state_types.h)
fixes game scalar widths; entity headers define payloads and links. OS handles
and pointers follow the host ABI. Service pointers and `*Ops`/`*Api` tables bind
Windows services or controlled native dependencies.
