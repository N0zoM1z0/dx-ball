# WinMain entry and message loop

The complete entry at `0x40D930` is 320 contiguous bytes, ending in `RET 16`.
REA supplies 86 instructions and 14 calls in
`ev_44569046e29fafd9e3d92f911c45121c537e6f2fd3112ffd497195c11e26321e`.

[platform.c](../../../src/platform.c) now follows that flow directly. A failed
instance claim displays the two original string objects and calls the process
exit boundary. Cursor-warp-disabled selects compatible initialization first;
the other arm selects fullscreen. A failed initializer returns zero. Successful
startup initializes the clock and trigonometry, clears Control before Shift,
then reads and copies the cursor position.

Each loop iteration calls PeekMessage once. A pending message passes through
GetMessage; zero returns its live `wParam`, while any nonzero result reaches
TranslateMessage and DispatchMessage. An empty queue dispatches a frame when
active and waits otherwise. The original locals are one 28-byte MSG and one
four-byte initializer result.

[platform_host.c](../../../src/platform_host.c) supplies the shared ordinary
cdecl exit transport. It calls the optional typed backend, then the host CRT's
`exit` if that backend returns or is absent. The existing native constructor
binds its existing isolated exit callback; case logic remains unchanged.
The caller maps to the original direct call at `0x417910`.

The first stable VC4 compile matches all 320 bytes, with 26 actual relocations
and both full NUL-terminated strings at `0x422B98` and `0x422BA0`. Across 25
affected recipes, all 121 previous accepted functions remain exact: 122 full
comparisons and 1,261 relocations. Current totals are 136 exact functions and
21,293 code bytes, with 283 source-present functions.

Only the existing 56 WinMain cases were replayed: message/idle paths,
initialization failures and two fork-isolated exits. Native, VC4 and MinGW
builds pass. Full input, object, comparison and review evidence is retained
under `.analysis/checkpoints/exact-win-main-283-136/`.
