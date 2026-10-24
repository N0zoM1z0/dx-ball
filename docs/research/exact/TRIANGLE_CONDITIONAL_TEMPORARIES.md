# Exact triangle conditional temporaries

October 22, 2026. The complete1710-byte triangle at `0x0040AB90` and its entire
160-byte exception metadata are byte-exact. All nine previously accepted raster
functions remain exact. Authored coverage becomes267/270 functions and
81,477/84,968 complete exact code bytes; three functions/3491 bytes remain.

## Shared source recovery

Four existing named integer clamp pairs become equivalent conditional arguments:

```cpp
dxball_fill_horizontal_span(pixels,
    0 <= (DxBallInt)left ? (DxBallInt)left : 0,
    639 < (DxBallInt)right ? 639 : (DxBallInt)right, color);
```

The conversion still only reads `value >> 16`. Both alternatives preserve the
original clipping limits and conversion/call effects. Compiler-owned conditional
result storage follows the actual class temporaries, recovering the original
frame homes without additional declarations. The four real root FixedPoint
objects, scalar declarations and constructor/destructor sequence stay unchanged.
The complete triangle definition moves after `dxball_fixed_divide`, before
`DxBallFixedPoint::operator<`; every other definition is byte-identical source.
The five actual source/header inputs and ten compiler flags retain their recipe.
Portable and legacy builds consume this same implementation.

Historical direct conditional arguments already had the original homes, but
their arm ordering differed. Inverse predicates retain200 differences. Commuting
the primitive comparisons to literal-first `<=` and `<` leaves12 differences in
four scanline comparison producers. Four real scalar declaration positions all
retain1710/12. Moving the whole definition before the span or after constructors
gives1710/12 and1710/9; placing it before comparison gives1710/0. The fourth
frozen position after all methods is left uncompiled once exactness is reached.
Three private reference/inline clipping-helper probes are rejected: they add
storage/instructions and give1807/1618 or1790/1114. None enters maintained source.
Exactly12 distinct successful compiler runs occur; retained historical outputs
are read without recompilation. No unique original spelling, source order or
compiler record identity is claimed.

## Complete closure and native evidence

All ten complete original raster functions compare through94 code bindings and
25 attached metadata bindings. All296 metadata bytes are compared, including
the triangle's160 bytes. The61 non-FILE symbols have a complete identity
bijection. Every raw auxiliary record is checked, mapping only actual
associative parent section indices. Complete global/noncode payloads and actual
relocations remain identical. Generated symbols are mapped once by their real
section/value/type/storage/auxiliary identity; equal40-byte metadata sections
are distinguished by their actual associated function. Complete comparisons
retain strict local-target checks and use no displacement or branch masks.

Native rebuild changes only raster.cpp/link. All60 companion objects and all63
compile command configurations remain unchanged. Exactly144 existing triangle
cases pass: shapes0..3 and6..9 from the unchanged differential suite, all six
point permutations and three pitch/color pairs. They include ordinary and flat
triangles, degeneracy, negative/left/right clipping and the bottom edge. Full
guarded frames, row padding, ordered API effects, scratch/input storage and SEH
restoration compare; original code and IAT bytes remain unchanged. The verified
fixture cache is unchanged and requires zero preparation.

Work runs serially on CPU0 at35%, memory high/max384/512MiB. Compiler peak is
156,250,112 bytes; native build/check peaks are43,245,568/59,162,624 bytes.
No memory limit events occur. The historical249 semantic scopes retain their
case counts, ordering and oracle identities; only current dependency hashes
refresh. They are not replayed for this adoption.

## Retained checkpoint

Private evidence lives under
`.analysis/triangle-conditional-storage-20261022/`: frozen input plans, successful
producer receipts, full comparisons, complete symbol/metadata proof, native144,
adoption and installed comparison. Closed evidence is archived and member size,
SHA256 and mode verified before obsolete copied inputs/objects are retired.
Cleanup verifies160 members and retires105 obsolete files, releasing512,000
allocated bytes net before small receipts. Current accepted objects, the tested
native library and useful caches remain.

The accepted source SHA256 is
`08d9c320dfeb5bfa01e6e0e971c8521572190d25b14acb585b3a3666241cd98a`;
object SHA256 is
`0a70bf1d12921e74b031b8522d3d65246abca811abe673ca6a0544f0a35c83fd`.
The full resolved triangle SHA256 is
`602d7dca26ada2bd7abf31d191f1c7e6985c82160b069f9035f4f5099d86cfd1`.

No game relink or play run follows this recovery. The retained October20 game
build/play evidence applies to its recorded image, as described in
[the build status](../CURRENT_VC4_BUILD.md). Complete authored exact recovery
remains active: last-brick, PCX loading and rotated-sprite rendering are next.
