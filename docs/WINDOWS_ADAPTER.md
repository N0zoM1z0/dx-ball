# Windows adapter integration

The five mode controllers, gameplay/frame owners, DirectSound control and MDS
music control have maintained source. Real Win32/DirectDraw/DirectSound/WinMM
binding and the game executable remain pending. The current build products are
the analysis library and inspectors.

Before calling real DLLs, `tests/test_windows_abi.py` compiles the shared owner
headers against the actual i686 SDKs and executes three console probes under
Wine. The core probe builds with both the pinned VC4 compiler/SDK and MinGW;
the DirectX probe uses MinGW's SDK, because the pinned VC4 SDK lacks DirectX
headers and import libraries. No vendor header, source layout or compiler
binary is patched to satisfy a probe.

The checks corroborate existing REA observations in
[platform evidence](PLATFORM_OWNER.md), [resource evidence](RESOURCE_OWNER.md),
[music evidence](MIDI_OWNER.md) and [sound evidence](SOUND_OWNER.md). They add no
original-function acceptance, hardware behavior or playable-game claim. No new
binary query was needed; saved dossiers supplied the target-side contracts.

| Record | Verified i686 bytes | Relevant boundary |
| --- | ---: | --- |
| Pointer / handle / window result | 4 | Win32 and COM arguments |
| MSG | 28 | Message queue and dispatch |
| WNDCLASSA | 40 | Callback registration |
| SECURITY_ATTRIBUTES | 12 | Instance semaphore |
| OSVERSIONINFOA | 148 | Startup compatibility selection |
| LARGE_INTEGER | 8 | Clock frequency/counter |
| MIDIHDR | 64 | Stream buffers and callback user state |
| MIDIPROPTIMEDIV | 8 | Music time division |
| Sound record | 36 | Known fields; original allocation requests 37 |
| DSBUFFERDESC1 | 20 | Observed DirectSound descriptor |
| Modern DSBUFFERDESC | 36 | Extra GUID tail; different from the observed descriptor |
| DDSURFACEDESC | 108 | Surface creation and locks |
| DDBLTFX | 100 | Color fills |

Compile-time assertions compare individual message, window, MIDI and surface
field offsets with SDK definitions. They also check the called DirectDraw and
DirectSound COM slot positions, including the complete twenty-one-slot sound
buffer interface and Restore at slot 20. The resulting JSON records agree
between the VC4 and MinGW core probes. These checks require 32-bit pointers;
they do not imply that the original interfaces can receive a growing 64-bit
host record unchanged.

Run the probes after installing the existing project prerequisites:

```bash
scripts/repo-python tests/test_windows_abi.py
```

The report at `build/reports/windows-abi.json` records source/header identities,
the pinned compiler/SDK identities, installed MinGW compiler and relevant SDK
header hashes, executable hashes, flags and observed output. The complete
private CI includes this check. Public CI still checks portable compilation
and recorded reconstruction metadata without requiring private tools.

Wine/Xvfb can append its display-shutdown notice to console stdout after the
probe exits. The harness preserves the full log and permits that specific
trailing notice; unexpected text, a nonzero process result or differing JSON
fails the check.

The next integration work binds the actual window/clock/file APIs, the
DirectDraw and DirectSound factories, and WinMM stream calls. Factory lookup
can use LoadLibrary/GetProcAddress with the observed stdcall signatures, so a
missing legacy DirectX import library does not justify modifying the pinned
SDK. Real callbacks, buffer lifetime, device errors and whole-game behavior
need runtime checks after those bindings exist. Original target files remain
immutable; writable game runs will use a separate local working copy of data.
