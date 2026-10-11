# Point animation's observed unpassed request writes

`dxball_update_intro_points` at `0x40ED40` now restores two actual original
writes after selecting the board surface and before constructing the redraw
rectangle: size 100 at EBP-116 and zero at EBP-36. The earlier reconstruction
omitted them because the request is not passed to any call. The current change
retains both writes using the existing `DxBallColorFillFx` ABI rather than
introducing padding or an arbitrary buffer. It does not initialize other fields,
pass a new pointer or change the drawing calls.

The type association is inferred, not recovered source spelling. The existing
clear-surface owner at `0x409F10` independently writes size 100 and a color at
offset 80 of the same request-shaped region, then passes that request to Blt.
Its complete 89-byte accepted body supports the shared ABI. The animation's
observed region lies immediately below its 16-byte rectangle; the later index,
result, 108-byte surface descriptor and pixel pointer account for the rest of
the original 236-byte frame. This evidence supports retaining a real written
object, but does not prove the original type name or declaration.

Retained REA evidence is animation
`ev_380287bfea6a4f582b8e8ee477b5c7d470de69c6555f3ab997e0f5f7d4650b2d`
and clear-surface
`ev_017375bcddb7d6708aadc8ec0d071b77e9d37c7f877f9da584462f4e561360db`.
Both are complete closed October 7 dossiers. No new provider invocation is
needed. Original instruction boundaries come from REA, while the emitted COFF
is decoded locally.

One canonical MT compile restores all 180 original operations. Fourteen branches,
ten calls and 40 relocation bindings correspond through explicit frame roles
and instruction-index branch mapping. Every instruction's registers, operands,
API arguments and branch destination agree after that mapping. The seven width
differences are actual disp8/disp32 EBP encodings: two request stores grow by
three bytes each, while five descriptor/pixel accesses shrink by three each.
Original/current frames now both contain 236 bytes, versus 136 previously.
The complete comparison improves from 682/711 bytes with 604 differences to
702/711 with 570. These remain strict, unmasked differences; no exact claim is
made and no declaration/name/scope trials are used to force stack locations.

The generated aliases change after the declaration: 37 complete literal
bindings and 15 owner-local code labels are reconciled. Literals retain their
complete old/new/original bytes and every prior `data_hex` attestation. Code
labels retain their owning COMDAT and original entry-relative value; the whole
intro-key body, including its switch data, remains exact. Thirty-six moved
animation relocation offsets are grounded in the corresponding original
instruction operands. The stale-alias comparison rejection is resolved from
the completed object without another compilation. All 15 exact intro bodies,
3,864 bytes, and other candidate byte/metadata comparison results are unchanged;
only their generated binding names may change.

The unchanged focused oracle passes one direct point initialization, 36 timed
and retry updates, 36 separately compared preparations, and 58 separate
connected splash/menu/key checks. It compares complete point/wave/palette/pixel
buffers, state and ordered API calls. Native and MinGW rebuild; the matching
MT intro object links with 35 verified unchanged VC4 objects and no extra
legacy source compilation. Physical graphics/audio and the full campaign
remain unproved.

Counts stay 283 source-present, 270 classified authored, 247 historical scoped
semantic entries and 206 exact / 44,406 code / 136 metadata bytes. The immutable
checkpoint is `.analysis/checkpoints/intro-unused-fill-writes-283-206/`.
