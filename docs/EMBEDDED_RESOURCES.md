# Embedded Windows resources

Private VC4 and MinGW game builds now include the original executable's two
reviewed resource payloads. Maintained game C is unchanged; the public repository
contains the inventory, hashes, extraction/build code and independent SDK probe.
Readers supply the verified original through the documented import workflow.

## Original evidence

REA/Ghidra read the complete mapped resource interval `0x442000..0x442400`
and the PE headers. The two completed observations are:

- Resource bytes: `ev_976caff6e8b92ae322f3964b85a0e918c39ef19b7a30da45208cccbc8b819f8e`.
- PE headers: `ev_89f8d211bb42186931d85b134afccaa07f27c8f681efd5bb4e8cb81b34a71827`.

Parsing those observed bytes gives a 924-byte resource directory with exactly
two ordinal leaves. This inventory is a format interpretation of retained
bytes, not an observation that the game displayed an icon.

| Type | Name | Language | Original RVA | Payload bytes |
| --- | --- | --- | --- | --- |
| `RT_ICON` (3) | 1 | 1033 / `0x409` | `0x420A0` | 744 |
| `RT_GROUP_ICON` (14) | 101 | 1033 / `0x409` | `0x42388` | 20 |

Both data entries have codepage 0. The group references image 1: one 32×32,
four-bit icon with sixteen palette entries and separate color/mask planes.
There are no menu, dialog or version-resource leaves in this complete tree.
Payload SHA-256 values, target identity, REA IDs and the pinned legacy converter
are recorded in [windows-resources.json](../config/windows-resources.json).
[rea-embedded-resources.json](../config/rea-embedded-resources.json) preserves
the two queries for reproduction; matching retained Evidence can be reused.

Saved startup dossiers establish an important original quirk. Both fullscreen
initialization (`0x40CF70`,
`ev_2cc92baf4edd1bfc64e4ea142dd7d186ca9124af4dda1bda4b72cb0945cc88d8`)
and compatible initialization (`0x40D4B0`,
`ev_11e3dc434ea2130b97aafcbdeb5927e235c6ea83b327a1346881a3898124fa3b`)
pass their nonnull instance and `0x7f00` to `LoadIconA`. The existing maintained
window code already agrees. The resource group is 101; its identifier is not
changed and no 32512 alias is synthesized. With a nonnull instance, the SDK
interprets the second argument as a module resource identifier; predefined
system icons require a null instance. [Microsoft LoadIconA documentation](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadicona).

## Build integration

`scripts/windows_resources.py` verifies the complete original executable hash,
then checks every resource leaf, RVA, size, language, codepage and payload hash
against the reviewed manifest before extracting anything. It serializes the
two payloads into a private Win32 `.res` under `build/<profile>/`. Ordinal
headers and four-byte alignment follow the documented resource file format;
this is asset serialization, independent of function exact matching.
[Microsoft RESOURCEHEADER documentation](https://learn.microsoft.com/en-us/windows/win32/menurc/resourceheader).

The VC4 build uses hash-pinned `cvtres.exe` with `/MACHINE:IX86`. MinGW uses
`i686-w64-mingw32-windres -J res -O coff --target=pe-i386`. Both link the
resulting object into the game EXE only. Each `game-resources.json` binds the
original, extraction inputs, converter identity, flags and generated hashes.
No original pixels, resource object or resource file are published.

```bash
scripts/repo-python scripts/build-legacy.py
scripts/repo-python scripts/build-windows.py
scripts/repo-python tests/test_windows_resources.py
scripts/repo-python scripts/capture-windows-probe.py --probe resources
```

The default builds require the verified original. Public CI explicitly uses
`scripts/build-windows.py --without-game-resources` for strict source/SDK
compilation without private assets. That option clears any cached private
resource-object path. Its EXE has no embedded resource fidelity claim.

## Independent SDK control

`tests/windows_resource_reader.c` loads each EXE with
`LOAD_LIBRARY_AS_DATAFILE`, enumerates all types/names/languages and reads every
payload using Win32 resource APIs. It also calls `LoadIconA` for both identifiers
and reads the selected icon's 32×32 color and mask bitmaps through GDI. This
probe uses SDK declarations and executes no target entry point.

Original, VC4 and MinGW agree on the complete inventory and both payloads.
Their SDK-decoded color and mask bytes agree on the same 24-bit Xvfb display.
Group 101 loads; the original startup request 32512 returns null with Wine
error 1813 in all three. A controlled VC4 link of the same maintained objects
without the resource object has an empty inventory, cannot load 101 and returns
error 1812 for 32512. This checks that the probe detects a real missing-resource
build, including the failure-detail difference previously left by omission.

REA process Evidence
`ev_2f8be9e3450e9a90aa426454e49f746651d08c2948b2974d69942956fd0726aa`
records the successful four-product SDK control. Detailed payload/bitmap output,
build provenance and executable hashes remain in ignored `build/reports/`.
The recorder does not attest artifact identity or inherited environment;
product identities come from the linked SDK report. Its process samples and
before/after file observations are not syscall traces.
Resource directory placement and whole-section bytes are not claimed exact.
Live window-class icons, shell/taskbar behavior and physical Windows rendering
remain outside this data-file probe.

This batch adds no function or exact promotion: acceptance remains 214 scoped
functions / 95,873 direct cases and 35 exact functions / 3,478 bytes. A sealed
checkpoint audit verifies all 71 semantic/ledger inputs, eight exact build
groups and the native library before reusing the prior owner/cold reports.
Changed Windows products and their runtime harness inputs are checked anew.
