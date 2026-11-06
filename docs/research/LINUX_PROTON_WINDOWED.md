# Windowed Linux play with Steam Proton

This note records a local interactive run of the separately supplied original
DX-Ball v1.07 executable. It does not verify a locally rebuilt executable.

## Observed run

On 2026-11-06, the original executable opened in a 640×480 Linux window and
rendered its title screen. The user could interact with it and reported slow
play and delayed audio at first. The tested environment was Ubuntu 24.04.5 LTS
on X11, Steam Proton 10.0-4b, Xephyr at 640×480×24, and cnc-ddraw v7.1.0.0.
The source checkout was at `36856cb`. The imported original executable had
SHA-256 `756da1ba09edce716d5bf8770320ca0d5ed4e525672b6bb605b9bdb4b88972ba`;
the wrapper DLL had SHA-256
`85e0f7d530dfda134793a57cb3e76b0287dcc96892ee57162dd68f47283b03a9`.

This was an interactive observation, not a complete campaign or audio
synchronization check. The title image was captured locally, but no original
game files or runtime screenshots are committed.

## Reproduce the windowed launch

Start from the repository root after importing the original archive as
described in [Build and play](../BUILD.md). Install Xephyr, unzip and curl on
the Linux host. Steam must have Proton 10.0 installed. Keep the game copy,
wrapper and Proton prefix private under `.tools/`:

~~~bash
mkdir -p .tools/proton-windowed/game .tools/proton-windowed/compatdata
cp -a original/. .tools/proton-windowed/game/
curl -fL https://github.com/FunkyFr3sh/cnc-ddraw/releases/download/v7.1.0.0/cnc-ddraw.zip \
  -o .tools/proton-windowed/cnc-ddraw.zip
unzip -oj .tools/proton-windowed/cnc-ddraw.zip ddraw.dll ddraw.ini \
  -d .tools/proton-windowed/game
~~~

In the first `[ddraw]` section of
`.tools/proton-windowed/game/ddraw.ini`, set these values. Leave the
game-specific sections below it alone:

~~~ini
width=0
height=0
fullscreen=false
windowed=true
maintas=true
renderer=gdi
maxfps=60
maxgameticks=-1
nonexclusive=true
savesettings=0
~~~

Run one game instance at a time. Adjust the Proton path if Steam installed a
different version or library location:

~~~bash
game_dir="$(pwd)/.tools/proton-windowed/game"
compat_dir="$(pwd)/.tools/proton-windowed/compatdata"
proton="$HOME/.local/share/Steam/steamapps/common/Proton 10.0/proton"

Xephyr :199 -screen 640x480x24 -nolisten tcp -title DX-Ball-windowed &
xephyr_pid=$!
trap 'kill "$xephyr_pid" 2>/dev/null || true' EXIT
sleep 1

(
  cd "$game_dir"
  env DISPLAY=:199 \
    STEAM_COMPAT_CLIENT_INSTALL_PATH="$HOME/.local/share/Steam" \
    STEAM_COMPAT_DATA_PATH="$compat_dir" \
    STEAM_COMPAT_APP_ID=0 SteamAppId=0 \
    WINEDLLOVERRIDES=ddraw=n,b \
    systemd-run --user --scope \
      -p CPUQuota=200% -p MemoryHigh=640M -p MemoryMax=768M \
      "$proton" run "$game_dir/DXBALL.EXE"
)
kill "$xephyr_pid" 2>/dev/null || true
trap - EXIT
~~~

The first launch creates the private Proton prefix and can take longer. The
Xephyr window closes when the game process exits. Click inside the window to
give it focus. Move the paddle with the mouse; the original readme says the
left button releases a grabbed ball. cnc-ddraw's `Ctrl+Tab` releases the
captured cursor.

The 200% CPU quota above records the interactive setting that removed the
observed throttling on this host. It is an exception for this manual play
recipe; the 35% limit for project-controlled Wine jobs in
[AGENTS.md](../../AGENTS.md) remains the standard. Other hosts
should measure before choosing an interactive quota.

## Performance and display observations

At `CPUQuota=35%`, the Proton game scope was throttled in 2222 of 2240
measured CPU periods. The user reported slow play and delayed audio. Raising
the active scope to `CPUQuota=200%` produced zero newly throttled periods
during an 86-period sample. The private local launcher now uses that quota on subsequent starts. The user's perception of audio timing after the change has
not been verified, so the CPU limit is a measured bottleneck and a plausible
contributor to the audio delay, not a confirmed complete audio fix.

Two other windowing routes were tried on the same host. Wine's virtual
desktop opened a blank game surface. Running cnc-ddraw directly against the
multi-monitor host display caused Proton's `winex11.drv` to abort in
`xf86vm_free_modes`. The combination of Xephyr and cnc-ddraw rendered the
title screen. Xephyr alone opened a black game surface. These observations
are specific to the tested host and Proton version.
