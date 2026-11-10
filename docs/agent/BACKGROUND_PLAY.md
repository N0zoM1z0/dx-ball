# Background play without host interference

Use Wine on a private Xvfb server when the Windows host's desktop, input and
audio must remain undisturbed. Do not start the game or an input controller on
the Windows input desktop or WSLg's inherited display. Windows manual play is
performed by the user.

## Display and input

Start Xvfb through `xvfb-run -a` with a 24-bit screen and `-nolisten tcp`.
The ordinary game fixture uses 640×480; the 960×720 windowed profile was checked
inside a 1280×960 Xvfb screen. Record the resulting `DISPLAY` and Xvfb process.
Unset `WAYLAND_DISPLAY` and disable `winewayland.drv`. Every XTest/xdotool call
must inherit that private display, including focus-peer diagnostics.

Keep the original `DISPLAY` and `WAYLAND_DISPLAY` values in the run receipt.
Never send synthetic input to them. An alternate Windows virtual desktop or a
minimized game is not the isolated setup tested here.

## Audio

Create `dxball_reconstruction_silent` with PulseAudio `module-null-sink` if it
does not already exist. Mute that sink and set
`PULSE_SINK=dxball_reconstruction_silent` for the game and its Wine children.
Keep the default sink, default device and other applications unchanged.

Record the default sink before/after and inspect the game's sink inputs during
execution. Wine reports `application.process.binary=wine` and
`application.name=dxball.exe`; join `application.process.id` to the owned game
process before attributing a stream. Matching the binary name alone misses it.
When finished, unload only a null-sink module created by this run, after checking
that it has no streams and is not the user's default sink.

## Products, limits and cleanup

Use a dedicated copy under `build/runtime/`; preserve original files, user saves,
the current tested executable and accepted objects. Run one compiler/provider/
Wine job at a time in the user systemd scope from [AGENTS.md](../../AGENTS.md):
one allowed CPU, CPU quota 35%, memory high 384 MiB and max 512 MiB.

Retain full REA process responses under `.analysis/rea/`, observer records and
input/product hashes under `.analysis/`. Distinguish a normal game exit from
controller cleanup. Remove duplicate runtimes and obsolete probes when their
results are recorded; no replacement archive or cleanup journal is needed.

The user stopped broad campaign tests and frame sampling after the October 31
checks. Reuse the recorded
results instead of restarting a full historical queue.
