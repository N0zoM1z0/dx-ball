# Command-line and environment startup

Four full bodies now have standalone shared source. Environment setup219 is
exact; argument setup151/155/116, parsing475/466/280 and environment acquisition
389/411/404 remain candidates. Five native-width state definitions live outside
the consuming argument translation unit, following actual CRT external symbols.
Four definitions are proved in `crt0dat.obj`; the original aenvptr defining member
remains unknown. All20 initial target field bytes agree. Program-name storage is
260 bytes, as proved by the actual local symbol and API count, not a frame gap.

The parser preserves two passes, terminal argument slot, first-program-name
rules, quoted DBCS counting asymmetry, slash parity, doubled quotes and consumed
lead/trail bytes. Its input and output backing, lead pairs and signed counters
must be coherent; total allocations must fit the32-bit allocator request domain
while pointer slots grow natively. Module-name output must be NUL-terminated.
Allocation failures enter the original fatal path and must not return. Environment
setup filters initial equals signs, separately owns copied entries and releases
the temporary block without clearing the shared stale pointer, as in the original.

Environment acquisition retains the first OS block, supports UTF-16/ANSI paths,
converts the whole terminated block and releases OS ownership on all paths.
The original cached path reads an uninitialized stack slot. Source initializes
the actual acquisition pointers; cached-path fidelity remains unproved and the
backend is not exact or runtime-accepted. C++ mode follows genuine local-static
mangling; allocator/fatal APIs keep their existing C linkage.

Private `.analysis/runtime-arguments-20261014/verification.json` retains four
whole CRT proofs and one closed12-record REA run. Affected VC4 whole comparisons
and native/i686 standalone compilation run; no runtime tests/game builds.
Program-pointer lifetime improves setup159/136→151/116. State ownership changes
do not alter code; published-global selection worsens to159/136 and is reverted.
All four code-page exacts227 and its candidate are recompiled unchanged after
aligning the locale-word declaration with the existing unsigned shared API.
Other277 exacts/79 candidates and249 semantic rows retain their prior producers.
