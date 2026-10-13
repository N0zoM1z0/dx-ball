# Exact filter initialization and lifetime

The complete unhandld.obj sections establish the30-byte installer at0x0041E140
and5-byte forwarding entry at0x0041E130. Both source bodies match in full after
all actual relocations. Each complete relocated section has one original code
location. The4-byte CRT$XCC initializer record at0x00421004 points to the forwarding
entry and matches completely. Native pointer storage grows naturally.

The installer first registers the existing restoration function with the genuine
recovered atexit API, ignores its result as the original does, then installs the
existing C++ filter and saves the old OS callback. The forwarding entry invokes
that installer. No extra cleanup callback, dummy object or synthetic class layout
is added. The reconstructed initializer record is explicit typed state; original
CRT linker-section placement and process startup execution remain unclaimed.

Current inventory543/source425/exact314/code68,725/metadata136, candidates102
(34 authored/68 runtime). The two newly proved entries retain compiler-generated
origin; origins270/200/45/28. All312 old exact and102 candidate producers reuse
unchanged inputs/objects;249 semantic rows are unchanged. One focused VC4/native/
i686 compile and full code/record comparisons ran. One closed three-record REA
byte-reading session supplements complete local CRT decoding. No runtime tests
or game builds. Proofs/products remain private in
`.analysis/runtime-filter-lifetime-20261014/`. Linker integration and the broader
unfinished restoration remain open.
