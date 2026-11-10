# Public author context and the pinned target

The October 2026 search found related source and debug records, but no original
English DX-Ball 1.07 project. Related names and declarations are bounded source
hypotheses. Complete comparison with the supplied EXE establishes an accepted
reconstruction; it does not establish unique historical source spelling.

## Related source packages

Michael P. Welch's [development page](https://classic.blitwise.com/Scorched_Reality/index.html)
links [simple1.zip](https://classic.blitwise.com/Scorched_Reality/simple1.zip),
a 1997 Visual C++ 5.0 CreateDIBSection tutorial with a 600×400 window. Its
project format and flags do not identify the earlier game's build context.

The publisher's [programming index](https://web.archive.org/web/20000619112018/http://www.longbowdigitalarts.com/seumas/index.html)
led to BackBuffer.zip. Its DX-Ball 2 display framework merges touching dirty
rectangles during insertion and maps, clips and scales them while updating.
DX-Ball 1.07 instead sorts left+top keys, merges sequentially, marks consumed
records with top 9999 and uses separate clipping loops. These are materially
different implementations.

Selected source from [Particle Fire](https://github.com/LongbowGames/ParticleFire/tree/dbf61926072a34ff04879d1e35fa57c25014f014)
and [Tread Marks](https://github.com/LongbowGames/TreadMarks/tree/6af9528c67d867f7903eb2ea4834db0750629034)
provided related raster and display context. The inspected files did not
establish the game's PCX, fixed-point triangle, sprite-record or compiler
lineage. Shared authorship alone is insufficient to transplant a routine.

## Mac and DOS observations

The Mac port connects named glyph/text routines to the same broad operations:
`letterfind`, `fontwidth`, `fontletter`, `fontprint` and `fontprintcenter`.
Its glyph search preincrements from zero, treats a count-equal miss as zero,
and supplies the same broad advance/centering behavior. Port-specific types
and calling conventions are separate from the Windows implementation. See
[Mac candidate connections](MAC_CANDIDATE_FLOW_CONNECTIONS.md).

An author DOS demo contains actual debug records, source cues and relocation
information. It connects sprite, capture/release, random and trigonometry
families, and supplies real names and types to test. Fixed declaration models
did not identify the Windows 1.07 source uniquely. Trigonometry also has a
material scale difference; matching names or formulas do not remove it.

The accepted owners and their complete comparisons remain in the
[exact index](README.md). The standing
[source-candidate policy](../../agent/SOURCE_CANDIDATE_SEARCH.md) allows finite
name, scope, declaration-order and build-context hypotheses without another
public-source search or a uniquely known original identifier.

## Distribution boundaries and failed leads

The supplied 1.07 archive contains the pinned game and assets. Its examined
installer records did not expose an original source, PDB or MAP attachment.
The inspected classic 1.09 executable likewise supplied no selected debug
carrier. Those bounded observations do not prove that source was never
published elsewhere.

A DX-Ball 2 v1.2 Wise installer has 77 consecutive compressed streams and 61
main file records. Its 277,504-byte game executable reports linker 4.20 and
has neither COFF symbols nor a PE debug directory. None of the 34 selected
whole 1.07 bodies matched under the recorded relocation normalization. This
excludes unchanged reuse in that selection, not modified common source.

WinG samples and the 1995 WinDonut framework use different sprite/animation
records, clipping and retry behavior. They do not establish the game's local
declarations. Keep future searches tied to a specific unresolved operation or
compiler residual; repeating this broad search is unnecessary for the now
complete authored recovery.
