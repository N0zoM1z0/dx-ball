# Compiling back to the original

The original executable gives us both behavior to recover and emitted code to
compare. We compile the reconstructed source with the pinned Visual C++ 4.0
toolchain, then compare each complete function with its original bytes.

Calls and global references acquire addresses during linking. The comparison
reads the COFF relocations and maps them to the original executable's functions,
imports and data. It also checks the literal data and any declared metadata.
An exact unit has zero differences across that complete comparison.

## What a difference teaches us

A different argument width can change a load or call. A missing state write
can remove instructions. Evaluation order can change register use. We return
to REA's instructions, callers and data consumers to resolve those questions,
then revise the source and compare again.

Some recovered routines still differ in compiler storage or scheduling. Their
full comparison remains available while work continues on the game.

## Reproduce a comparison

[`config/match-units.toml`](../config/match-units.toml) records the source,
compiler inputs, original extent, and relocation bindings for each unit.
Select the units affected by the source change:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit append-projectile --unit append-fire-effect \
  --report build/reports/projectile-appends.json
```

The [projectile-list example](REA.md#a-worked-example-appending-a-projectile)
shows how one 146-byte function was recovered. The
[exact research notes](research/exact/README.md) contain the other comparisons.
