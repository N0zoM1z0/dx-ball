# Native Linux port

The `dxball_linux` target runs the reconstructed game core as a Linux executable.
The platform adapter in `linux/` supplies an SDL2 window, indexed-color surfaces,
mouse and keyboard input, WAV playback, and a simple synthesizer for the original
MDS music files. The recovered sources in `src/` and the existing Proton launch
path are unchanged.

## Build and play

Install a C/C++ compiler, CMake, Ninja, pkg-config and the SDL2 development
package. From the repository root:

```bash
cmake -S . -B build/native -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DDXBALL_BUILD_LINUX_GAME=ON
cmake --build build/native --target dxball_linux --parallel 1
./linux/run.sh
```

The launcher copies the separately supplied files in `original/` to
`build/native/game-data/` with lowercase names, as expected by the original
game. It does not overwrite existing copies, so board and score changes in the
native data directory persist. The launcher runs the native executable
directly; it does not require Wine, Proton or systemd.

The window starts at 1280x960, twice the game's 640x480 logical resolution, and
can be resized. Move the mouse to move the paddle; click to release the ball.
Esc opens the game menu and exits from there. F12 toggles mouse capture:
press it once to move the pointer outside the window and see it again; press
it again to confine and hide the pointer. Ctrl+Shift also toggles capture.

During play, use Ctrl+1 through Ctrl+4 for the game's built-in cheats. Ctrl+5
enables the brick-piercing power and shows "Pierce ON" in the window title
until the effect ends. Cheat 1 resets the paddle, 2 makes the paddle catch the ball, 3 enables
paddle projectiles, and 4 doubles its width. The game's Ctrl+F1 through
Ctrl+F4 shortcuts still work where the desktop passes them through, but XFCE
reserves Ctrl+F1 through Ctrl+F9 for workspace switching. The board editor
remains available through the game's own controls.

## Implementation

`linux/sdl_port.c` maps the core's window and DirectDraw interfaces to SDL2.
It maintains the game's 8-bit front and back surfaces and presents the palette
through an RGBA texture. DirectDraw's `DDBLTFAST_WAIT` flag (0x10) must still
copy zero-valued pixels; only `DDBLTFAST_SRCCOLORKEY` (0x01) enables the sprite
color key. The distinction prevents stale paddle images after a wide mouse move.

`linux/sdl_audio.c` mixes the original PCM WAV effects. `linux/sdl_music.c`
decodes all six MDS files and synthesizes their note events. The synthesizer
uses approximate instrument sounds; its timbre is not a General MIDI soundfont.

## Verification on 2026-11-08

- The complete native CMake build passed with warnings treated as errors for
  the adapter.
- `build/native/dxball_linux --verify-music build/native/game-data` decoded
  all six supplied MDS tracks.
- The game started in an isolated 1280x960 Xvfb display, entered board 1,
  released the ball, broke bricks and updated the score.
- Mouse moves from the center to both horizontal edges left exactly one paddle
  on screen after the DirectDraw flag correction.
- SDL's disk audio driver captured nonzero stereo PCM from the running game.
- Esc from gameplay, then Esc from the menu, exited with status 0.
- Ctrl+F4 visibly doubled the paddle width in isolated play. Ctrl+F5 set
  the title to "Pierce ON". At 800x600, F12 let the pointer leave the window;
  pressing it again confined the pointer.
- Ctrl+4 doubled the paddle and showed a confirmation title; Ctrl+5 showed
  "Pierce ON". XFixes reported a transparent 1x1 cursor while captured, a
  visible 16x16 cursor after F12, and a transparent cursor after F12 again.

The full 50-board campaign, every power-up, editor persistence and ranking
persistence have not yet been exercised on this Linux adapter. Those are
separate validation tasks; the Windows and Proton results do not establish
their behavior here.
