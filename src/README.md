# Source map

Read [platform.c](platform.c) → [runtime.cpp](runtime.cpp) → [core.c](core.c)
to follow input, mode dispatch, and a gameplay frame. The
[architecture guide](../docs/ARCHITECTURE.md) explains how those calls fit together.

| Start here | Responsibility |
| --- | --- |
| [windows_entry.c](windows_entry.c), [windows_adapter.c](windows_adapter.c) | Windows entry and bindings to OS, graphics, and audio services |
| [platform.c](platform.c), [platform_host.c](platform_host.c) | Instance lock, window creation, message loop, input, display setup, DirectDraw factory and process-exit transports |
| [startup.c](startup.c) | Working resources, score files, RNG, and sprite-bank cleanup |
| [runtime.cpp](runtime.cpp) | Five-mode dispatch, game lifecycle, clock, paddle drawing, and score |
| [core.c](core.c) | Gameplay frame, ball/projectile movement, firing, and entity queues |
| [intro.cpp](intro.cpp) | Menu and splash lifecycles, point animation, scroller, and credits |
| [editor.c](editor.c) | Board editor, toolbar hit regions, painting, and persistence |
| [gameover.c](gameover.c) | Name entry, rankings, and high-score persistence |
| [boards.c](boards.c), [board_storage.h](board_storage.h) | Board bank, working tiles, shared storage, and tile drawing |
| [gameplay.c](gameplay.c) | Brick-hit rules, board power-ups, explosion requests, and sound pan |
| [balls.c](balls.c), [paddle.c](paddle.c), [round.c](round.c) | Ball lifecycle/rebounds, paddle movement, and lives/level progression |
| [effects.c](effects.c) | Brick and explosion animation lifecycle |
| [bonuses.c](bonuses.c), [particles.c](particles.c) | Bonus selection/collection and particle movement/drawing |
| [resources.cpp](resources.cpp), [resources.h](resources.h) | Sprite banks, PCX loading, glyphs, palettes, and DirectDraw interfaces |
| [display.cpp](display.cpp), [device.c](device.c) | Dirty regions, presentation, fades, synchronization, and surface recovery |
| [ui.c](ui.c) | Text layout, lines, fill requests, and palette operations |
| [rotation.c](rotation.c), [raster.cpp](raster.cpp), [bitmap.c](bitmap.c) | Software rotation, fixed-point rasterization, and bitmap reading |
| [geometry.c](geometry.c), [trig.c](trig.c) | Overlap/distance helpers and quantized trigonometry |
| [sound.c](sound.c), [midi.c](midi.c), [music.cpp](music.cpp) | DirectSound buffers, WinMM streams, and music object lifetime |
| [file.c](file.c), [memory.c](memory.c) | Shared file and local-memory services for sound, MDS, and bitmap loading |
| [allocator.c](allocator.c), [allocator_host.c](allocator_host.c) | Recovered allocation policy and portable heap callbacks |
| [list_initializers.cpp](list_initializers.cpp) | Global list owners and their C++ constructors |
| [runtime_text_host.c](runtime_text_host.c) | Unix implementation of the score caller's decimal conversion boundary |
| [board_inspector.c](board_inspector.c), [resource_inspector.c](resource_inspector.c) | Command-line board and image/sprite-bank inspection |
| [runtime_cpp_unwind.cpp](runtime_cpp_unwind.cpp) | Exact state-map unwinding with real Win32 SEH and the original frame-setting transport; standalone CRT owner outside the CMake game library |
| [runtime_cpp_object.cpp](runtime_cpp_object.cpp) | Catch-object construction and exception-object destruction with real member ABI and Win32 SEH; standalone CRT owner outside the CMake game library |
| [runtime_cpp_terminal.cpp](runtime_cpp_terminal.cpp) | Original C++ terminal callbacks and Win32 SEH scopes; standalone CRT owner outside the CMake game library |
| [termination.c](termination.c) | Separate CRT initializer/exit reconstruction; outside the CMake game library |

Each module's `.h` file describes its public state and call contracts.
[state_types.h](state_types.h) defines the shared scalar widths and board sizes;
the entity headers define payloads and links. Surface and OS handles grow with
the host, while game integers stay 32-bit. C++ is used for the fixed-point
class and global list construction; the game-facing interfaces retain C linkage.

To trace a feature, follow its frame call into the owning module, then inspect
that module's header and dependencies. Independent import cells and `*Ops`/`*Api` tables provide service
bindings for the Windows adapter and host tools. Definitions such as
`/* FUNCTION: DXBALL 0x... */` connect reconstructed routines to original addresses.
