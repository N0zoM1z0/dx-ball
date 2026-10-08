# Software sprite rotation: investigation in progress

The imported function inventory leaves `0x004026A0` unclassified. Its saved REA
dossier provides a contiguous 1,572-byte body ending at `0x00402CC3`, with
Evidence ID
`ev_1dfa14e3428cac399a6bc2876da74d5bbc4a5edc8a8e03a6af79783e189daf26`.
The complete record is retained in the closed 10-33 interactive run; reusing it
requires no additional Ghidra import. This investigation has not promoted a
function, origin, semantic case or exact unit.

## Observed instructions

The body reads sprite width/height through the established bank at `0x425980`
and selected-bank scalar at `0x421088`. It obtains and locks the active surface
at `0x4265CC`, then obtains and locks the selected sprite's source surface.
Both descriptor requests set size 108 and flags 14. Each lock retries until its
result is zero; no finite failure recovery is established on this edge.

The inferred pseudocode prototype lists three parameters. Instructions read
`[EBP+0x14]` and pass it to the already reviewed sine/cosine helpers, establishing
a fourth stack argument. They add 270 before obtaining the row-direction
coefficients. Pseudocode loses both the fourth argument and that phase offset.
The body converts the first two coordinates through zero-extended 64-bit
integers before floating-point arithmetic.

Nonzero source pixels are considered only when the transformed coordinates
are strictly inside the destination's zero and width/height-minus-one bounds.
Instructions compute biased and unbiased X/Y integers through `__ftol`.
The first write uses biased X and biased Y; when either integer pair differs,
the second write uses the same biased X with unbiased Y. Thus the computed
unbiased X controls a branch without becoming a destination column.
Source traversal advances one byte per pixel and skips pitch padding at each
sprite-row boundary. Unlock order is destination, then source.

The recorded caller is a separate contiguous 40-byte entry at `0x00404280`.
The new wrapper dossier confirms four cdecl arguments `(slot, center_x,
center_y, angle)`, forwarded as `(center_x, center_y, slot, angle)`. Its inferred
three-argument pseudocode still omits the last argument. Direct references
are reviewed below; actual use by game controllers remains unestablished.

## Floating-point storage and traversal

The same retained instructions establish separate double stores at
`0x4028AC` and `0x4028FE` for initial X, then `0x40295F` and `0x4029B4` for
initial Y. Let `R64` denote a store to double, `W`/`H` the unsigned sprite
dimensions, and `C`/`S` the already reviewed table-based cosine/sine results.
With the backing divisor bytes now confirmed through REA, the observed sequence is:

```text
first_x = R64(unsigned_center_x - W*C(angle)/2.0)
row_x   = R64(first_x - W*S(angle)/2.0)
first_y = R64(unsigned_center_y + H*S(angle)/2.0)
row_y   = R64(first_y - H*C(angle)/2.046)
```

Both X terms use width. The differing Y divisor and the intermediate stores
are part of the observed sequence; replacing them with a conventional rotation
formula would change behavior. The backing values and rounding bias are
recorded in the focused data review below.

Column steps are `C(angle)` and `-S(angle)`; row steps are `C(angle+270)` and
`-S(angle+270)`. Each pixel advances X/Y before transparency and bounds checks.
Each coordinate update and row-origin update stores a double. Source traversal
uses one byte per column and a pitch-minus-width adjustment at the row boundary.
The signed row/column loop tests and unsigned conversions require an explicit
bounded dimension/arithmetic domain in the eventual oracle.

The existing [trig evidence](POWERUPS_OWNER.md) already establishes a useful
boundary: negative multiples of 360 select table entry 360, so cosine(-360)
is 1023/1024 while cosine(360) is one. Rotation tests must retain that difference.
The shared rotation fixture set has 344 fixtures covering angle wrap,
multiple banks/slots, unsigned coordinates, rectangular/empty dimensions,
transparent pixels, pitch padding and independent finite destination/source
lock retries. The original-machine probe now executes every fixture, checking
complete destination storage and guards, unchanged source/record/bank storage,
padding and ordered surface calls. C comparison remains pending; these fixtures
do not increase the accepted direct-owner case count.

## Original-machine reference data

```bash
scripts/repo-python tests/probe_rotation.py
```

The probe runs the unmodified original trig initializer at `0x402250`, then the
rotation body, original table lookups, x87 division and integer conversion.
It supplies no host math or maintained rotation replacement. The initializer
uses no controlled API/allocator boundary; its two complete 361-entry tables
also agree with the previously validated maintained initializer. Table hashes
are recorded, and all rotation fixtures leave both tables unchanged.

The controlled dependencies are DirectDraw surface descriptors, backing
storage and finite per-surface lock results. Five further callback scenarios
change the active surface or selected bank during API boundaries. They confirm
that dimensions are captured before the first call, while surface pointers are
read again for each descriptor/lock/unlock. Complete buffers match stable
original controls using the captured dimensions and newly selected backing.
Changing the bank during destination unlock even makes the subsequent source
unlock address a different surface from the one originally locked. Capturing
one surface pointer for the entire function would change these observed effects.
The private C draft now reflects these reloads and the confirmed 0.5 bias,
but remains uncompiled and unaccepted. These are controlled callback effects, not
claims about a physical DirectDraw driver's behavior.

The normal CRT division branch
is selected and x87 control word `0x037F` is explicit. Each call verifies cdecl
stack/register preservation. Zero-key/empty sprites and very large unsigned
centers leave the destination unchanged; every fixture preserves row padding,
32-byte guards, source pixels, source record and bank storage. Lock scripts are
fully consumed before destination-then-source unlock.

The private report `build/reports/rotation-investigation/original.json` binds
ten input hashes, original and complete REA dossier identities, table hashes,
every fixture and its ordered calls. All 344 references retain their complete
guarded destination buffers. Identical buffers share a digest-keyed record
after complete-byte equality checks: 146 unique baseline buffers plus five
additional callback buffers share one report, rather than repeated complete
buffer records. Including the offset references below, the report is about
626 KiB. No original game asset,
raw long-run stream, executable or compiler object is generated by this probe.

This is original-only reference evidence. The focused REA session below
resolves the backing constants and wrapper ABI; maintained-C comparison,
semantic promotion, origin classification and exactness remain open.

## Related width-only offset candidate

The same closed REA run retains `0x00402CD0` under Evidence ID
`ev_274065db33e0f5af45f91e84ec3c68bf86d6b31f20e54434e568a1cca50290f5`.
Its inferred no-argument prototype misses instructions reading `[EBP+8]` and
`[EBP+0xC]`: sprite slot and angle. The body reads signed sprite width twice,
calls cosine with angle plus 45 and plus 135, divides before integer conversion,
takes each absolute value and returns the negative maximum. It does not read
sprite height or call a surface boundary. Callers and intended positioning
role remain open.

The saved division-workaround immediates decode to double 1.3. REA now confirms
its backing bytes at `0x420058..0x42005F`. Using that value,
329 additional original-only cases agree with the instruction-derived model:

```text
-max(abs(trunc(width*cos(angle+45)/1.3)),
     abs(trunc(width*cos(angle+135)/1.3)))
```

The model uses the original quantized cosine table and exact rational arithmetic
to avoid inserting an unintended double store before truncation. For width 13
and angle -45, original execution returns -9: the extended quotient is below
ten. A double intermediate would round 13/1.3 to ten and change the result.
The tested domain covers bounded signed widths, wrap/phase boundaries, all
three banks and multiple slots. Original cdecl preservation and unchanged
record/bank/table storage are checked; no INT_MIN or overflow claim is made.
These model comparisons are not maintained-C differential acceptance.

The dossier reports 254 owned bytes across two ranges spanning 259 bytes.
The five-byte gap at `0x402DBF..0x402DC3` needs extent reconciliation before
configuring an exact unit. The helper has no accepted source name or origin.

## Focused REA data and reference review

After retaining the interrupted original campaign, the shared session was
released for eight focused graphics queries. Complete records survive in two
closed runs: the first retained three successful operations before an uppercase
address was rejected; the second resumed only the five outstanding queries.
The public request files now use the documented lowercase address format.
No original bytes or pinned provider were changed.

REA `read_bytes` Evidence
`ev_3981d4fe3871c6d5f4976aaec23007d066c24f80aedca23dd51270d63c19de71`
returns all 40 requested initialized bytes at `0x420038..0x42005F`:

| Address | Type | Complete little-endian bytes | Value |
| --- | --- | --- | --- |
| `0x420038` | float | `00000040` | 2.0 |
| `0x420040` | double | `91ed7c3f355e0040` | 2.046 |
| `0x420048` | double | `0000000000000000` | 0.0 |
| `0x420050` | double | `000000000000e03f` | 0.5 |
| `0x420058` | double | `cdccccccccccf43f` | 1.3 |

The 40-byte wrapper dossier is Evidence
`ev_dde2cbb37732ea0f72b15ecd2949441abe7c8b5a5a28b2762bdf8dd403d7ebe6`.
Instructions push `[EBP+0x14]`, `[EBP+8]`, `[EBP+0x10]`, `[EBP+0xC]`, call the
renderer and discard 16 argument bytes. This establishes the forwarding order
above independently of its incomplete inferred prototype.

Focused `xrefs` Evidence
`ev_bf74724302d018c94f01b8e55bb4cd572a116c62ae1427b376522f7b81cd9f1d`
finds `0x404296` as the renderer's only direct reference. Wrapper Evidence
`ev_4f47d78c082f084ce0155af78b909aeac10de28b9ff78c37dd12f9b01e99c4c7`
and offset-helper Evidence
`ev_3d075ede72783d1c97cc24ae8bcad20e4375dcaca578e7aee080ca2822af61ea`
return no direct address references. These are Ghidra reference-manager results;
indirect or dynamically constructed uses remain outside that bounded observation.
No active gameplay use is claimed.

```bash
scripts/rea session config/rea-rotation.json
```

Reuse the existing renderer/offset dossiers; this request set contains only
the missing constant bytes, wrapper body and direct references.

## Work remaining

- Recover natural shared C with the observed double-storage boundaries and
  table-based trig, without changing asymmetric pixel writes or clipping.
- Compare unmodified original execution with complete destination buffers,
  descriptor/lock/unlock calls, source bytes, pitch padding and retry scripts.
- Include the five callback scenarios; preserve captured dimensions and later
  global reloads, including final unlocks.
- Compare maintained C for the 329 width-offset cases, including the extended
  13/1.3 truncation boundary, and test wrapper forwarding.
- Reconcile the offset helper's five-byte body gap before any exact unit.
- Keep direct reference coverage distinct from a claim of active gameplay use.
