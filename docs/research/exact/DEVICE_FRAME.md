# Device initialization and surface recovery

The exact main dispatcher calls device initialization before entering the
current mode, then synchronizes the surface before each frame. REA's saved
callers lead from those two edges into the recovery path and background-surface
cleanup. This batch restores all four complete bodies in their existing owners.

| Entry | Source | Original bytes | Result |
| --- | --- | ---: | --- |
| `0x403A00` initialize device state | `startup.c` | 359 | 359 compiled bytes, 10 differences |
| `0x4035B0` synchronize surface | `device.c` | 134 | Exact |
| `0x403640` recover surfaces | `device.c` | 97 | Exact |
| `0x403BD0` dispose working surface | `platform.c` | 80 | Exact |

## What REA established

CreateSurface writes directly to the global background COM pointer at
`0x421070`. Its descriptor has five specified fields: size 108, flags 7,
caps `0x840`, height 480 and width 640. The source now declares that owner as
`DxBallDDSurface *` and passes its address to CreateSurface. Existing APIs
that carry integer surface handles use explicit casts at their boundaries.

On failure, initialization calls the original process-exit boundary with 1.
On success, it sets mode 4, initializes and reads scores, calls the actual
board loader with the mutable filename global, seeds random state, clears
primary and initializes the palette. It then measures 32 vertical blanks,
updates the timing and reduced-particle flags, and saves the frame tick.

Synchronization preserves the original branch-local HRESULT write and calls
GetBltStatus through the live primary surface. SURFACELOST triggers recovery.
The alternate branch recovers only when the restore request equals 1; both
branches clear only a request equal to 1. Recovery restores primary first,
reads the board surface after that call, stops on either failed HRESULT, then
restores sprite banks and redraws the mode. Cleanup passes the full fade
argument to the mode owner, releases the live background surface and clears
its global pointer.

Four saved REA dossiers cover 170 instructions, 15 direct calls and six COM
sites across all 670 bytes. Their bodies are contiguous and end at their RET;
there are no embedded tables or unowned gaps. The complete records remain in
the closed October 7 sessions, reused with cumulative snapshot 495:

- Initialization: `ev_8681cf5b5b27dd9358b476476e4b5b63d76ccbb091fc483c58c3cea670a6e1db`
- Synchronization: `ev_7528b8fd339fe77e2bd500279969b4c0f36946e98a3556d3f30044c87289bb30`
- Recovery: `ev_38016d73060dc54237eaa650b38484472bf814f4c1eee8d11110beaecbc771de`
- Cleanup: `ev_165c97de81ef73fd69541c691fb8e54c52dab143890299a2cb392e597a303df5`

The full `default.bds` NUL-terminated bytes at `0x421078` are corroborated by
`ev_912015788fbe2640da31a1a231acd1da38864e8c84e5222e791a738e4cbbe066`,
the original image and the compiled global.

## Compilation and affected checks

The shared pointer declaration affects 27 configured recipes. Each was
compiled once. Complete comparisons preserve all 135 affected accepted
units and accept the three new exact bodies, adding 311 code bytes. The
comparison also retains the two current platform candidates and refreshes
actual compiler-local IDs with unchanged code and label/data contents.
In total, 141 whole comparisons account for 1,642 actual relocations.

Initialization's remaining ten differences are nine stack displacements for
the descriptor and loop counter, plus the failure branch's epilogue target.
Its complete extent and relocation mappings are retained as a candidate.
The first source proposal is preserved without compiler-layout trials.

Only the affected existing loops ran: 83 startup, 255 recovery/synchronization
and 54 working-surface cases, plus 21 existing connected checks. Startup's
native fixture binds its existing termination callback to the genuine host
exit transport. One typed board-loader forward uses the existing callback
slot, with its copied real body as the default. Case bodies are unchanged.
Other semantic rows retain their historical scope after input-hash refresh.

Native, VC4 and MinGW builds pass. VC4 reuses 26 verified objects and compiles
nine remaining game sources. Full inputs, objects, comparisons, selected case
bodies and receipts are retained under `.analysis/exact-device-frame/` and its
checkpoint. The ledger now has 146 exact functions / 23,401 code bytes and
136 metadata bytes. The next work follows the palette and sprite dependencies
that this recovery path actually calls.
