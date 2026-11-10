# Closed drawing and SDK storage diagnostics

These October 2026 trials explain rejected approaches. All 270 authored
functions now match; use [the exact index](README.md) for accepted owners.
A rejection applies to its tested source context. The
[source-candidate policy](../../agent/SOURCE_CANDIDATE_SEARCH.md) permits a
bounded new combination with changed preconditions.

## Conclusions worth reusing

| Trial family | Result and implication |
| --- | --- |
| Historical DirectDraw header | The pinned [VC4.2 header](https://github.com/archaic-msvc/msvc420/blob/b42c244f0a83ba15ba2ffb62b0dc240d7b2dea50/include/DDRAW.H) supports a 108-byte descriptor and v1 interface layout. Wholesale substitution lost existing matches. ABI compatibility does not establish the game's header text or local declarations. |
| Modern SDK descriptor | Historical mip-map and refresh/depth unions differ from modern headers. Preserve the observed offsets; do not infer them from a current SDK. |
| C and C++ COM calls | Genuine virtual calls improve some owners but can change many companions. Owner-local conversions and coherent shared-header closures need separate complete comparisons. |
| HRESULT and SDK scalar aliases | Several type-only changes left all code unchanged. Broader Windows C aliases gained one function while losing five; reject that whole context. |
| Clock interfaces | Moving a complete counter type into a shared header changed unrelated owners. Opaque-pointer and owner-local variants reduced the damage but did not yield an acceptable shared closure. |
| Explosion-list methods | Implemented methods could remain exact while converted callers lost matches. Neither an isolated winner nor a C adapter proves the complete API conversion. |
| PCX aggregate workspace | Adjacent stack homes do not prove one aggregate. Grouping descriptor, width and Lock result shortened a nonexact body without recovering an observed operation. |
| PCX packet-byte scope | A one-position difference improvement merely rotated four incorrect homes. It supplied no recovered storage and was not adopted. |
| PCX header lifetime | A plain 128-byte disk header did not recover the frame. The final [file-prefix type](PCX_FILE_PREFIX_RECOVERY.md) has an actual boundary consumer and signed maximum-coordinate reads. |
| Rotation receiver and inline accessor | Ordinary accessors introduced entry jumps; a direct bank pointer retained the previous mismatch. The accepted [typed cursor owner](ROTATION_TYPED_CURSOR_RECOVERY.md) resolves the complete renderer instead. |
| Polygon record copy | A plausible record-copy model did not establish the required whole-body output. Keep actual write order and lifetime constraints. |
| Iterator and scalar lifetimes | Moving declarations can preserve code, improve one displacement, or damage companions. A smaller difference count alone is not recovery. |
| `/G5`, debug information and optimization controls | These flags did not resolve the selected residuals and sometimes lost accepted companions. Keep the maintained recipe unless a concrete new residual justifies a bounded trial. |

## How to use a closed result

Check the current source context before reusing a negative result. Header
visibility, owner language and scope changes can alter emitted code even when
expressions are unchanged. Compile each distinct candidate once, compare all
complete affected units and relocations, and keep the result private until its
whole closure passes. Rejected probes need only a concise conclusion unless a
current unresolved question depends on their exact compiler context.
