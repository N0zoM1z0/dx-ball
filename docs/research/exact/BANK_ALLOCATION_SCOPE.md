# Sprite-record allocation scope

The bank loader's temporary record pointer now belongs to its allocation,
null check and publication block. After publication, every record access reads
the live bank slot; the pointer has no later consumer. The file pixel buffer
still spans reading, upload and release. This changes one existing declaration's
scope without changing its type, name, executable operations or failure cleanup.

The complete candidate improves from **1,475 bytes / 70 differences** to
**1,475 / 66**, including all 77 actual bindings and the full `rb` literal.
It remains nonexact. All fifteen resource exact companions preserve 3,572 bytes;
the other sixteen complete function identities, including PCX, stay unchanged.
One matching compilation covers all seventeen functions and eight project inputs.

## Instruction and lifetime evidence

Both loader bodies contain 425 instructions and reserve 180 frame bytes.
The only fifteen changed bytes are actual EBP displacement fields. They rotate
three disjoint DWORD homes:

| Value | Previous home | Current home | Original home |
| --- | --- | --- | --- |
| Width | EBP−56 | EBP−52 | EBP−52 |
| Height | EBP−52 | EBP−48 | EBP−28 |
| Temporary record | EBP−48 | EBP−56 | EBP−12 |

Five width accesses now match. One formerly coincident displacement in the
commuted width/height product becomes different, giving the net reduction of
four. All other complete instruction bytes remain identical, including branches,
calls and the descriptor, result, upload-pointer and color-key homes.
Original height/record homes, scalar allocation and two multiplication operand
orders remain unresolved. This does not recover the original declaration scope.

The original evidence remains
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`,
operation 01 in `2026-10-10T17-22-54.305Z-requests-825249`. No new provider query runs.
The [preceding iteration scope](BANK_SPRITE_ITERATION_SCOPE.md) retains its
historical source, product and test counts.

## Focused validation and VC4 integration

Ten existing bank cases pass against the unmodified original: seven supplied
banks, a small sprite stream, creation failure and an empty stream. Three
existing callback scenarios also pass, checking live bank changes during
color-key/descriptor calls and the pitch snapshot before Lock. Ordered calls,
defined bank/record state, pixel bytes and ownership effects agree.
No new semantic cases are added. The 235 historical input inventories receive
the changed source hash; their other cases are not rerun.

The native incremental build compiles this owner and its pending raster owner,
then links the library. The restored-CRT builder reuses all 116 source objects
and only relinks; its resource producer already uses the same `/ML` recipe.
There is no second VC4 source compilation or GUI run. The approved nineteen
original CRT members remain unchanged.

The new image SHA-256 is
`ebe4a4ff8e6557fe0a89a32a064365941103b574f7373460e8e7cd5f51b2eb56`.
All 1,091 mapped addresses are unchanged. A complete comparison with the preceding
executed image finds only the fifteen bank displacement bytes and twelve bytes
inside six parsed COFF/resource-directory timestamp fields. Resource payloads
and all other image bytes are identical. The linked 1,475-byte body verifies
after all 77 relocations. Earlier GUI observations remain evidence for their
recorded preceding image; they are not claimed as new executions of this image.

Private `.analysis/bank-allocation-scope-20261017/` retains source reversal,
before/after products and reports, complete comparisons, instruction changes,
existing case drivers/results and the whole-image delta. Preparation first
found a repeated allocation block in capture; it stopped before compilation
and was restricted to the selected loader. The first image verifier's narrower
timestamp assumption is retained with the parsed resource-field correction;
neither correction repeats a compiler or game run.

Nineteen frozen input/report files are archived and both matching objects are
compressed after complete byte checks, releasing 5,382,144 allocated bytes.
Current cache objects and the linked/native products remain available.

Totals remain **475 source / 380 exact / 95 complete candidates**, including
34 authored candidates. No full replay runs. Heavy work remains serial under
CPU 35%, memory high 640 MiB / maximum 768 MiB. This is a partial source improvement;
original campaign and physical-driver fidelity remain open.
