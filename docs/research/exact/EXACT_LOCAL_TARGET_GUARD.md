# Exact comparisons and local COFF destinations

A byte-equal relocated section must also preserve the object's actual internal
destinations. The comparator now verifies this before returning a zero-difference
section. An internal symbol's declared original target must equal the original
section address plus its COFF offset relative to the section anchor.

The [brick-hit review](EXACT_BRICK_POWERS.md#complete-hit-correspondence-and-internal-binding-repair-october-17)
found two incorrectly declared case targets in a nonexact comparison. A focused
follow-up finds a separate acceptance gap: the old comparator writes declared
targets into relocation fields but does not check the corresponding internal
COFF definitions. A wrong mapping could therefore conceal a changed switch
destination even when the reported complete byte difference is zero.

## Real object counterexample

The current complete `game-over-key` exact unit has 302 bytes. In a private copy
of its verified object, changing only the `$L1343` symbol value from51 to56
redirects its linker destination by five bytes. Code and relocation-table bytes
stay identical; only one byte in the COFF symbol table changes.

The old comparator still returns the identical exact result. The new comparator
rejects that object: declared original destination `0x406A23` disagrees with its
actual local definition at `0x406A28`. The unchanged canonical object retains its
complete exact result. No mutant is linked, executed or used in production.

The check runs only for a zero-difference section. Nonexact candidates can have
different instruction lengths and explicitly mapped local positions, so they
retain their honest comparisons. External and other-section targets still need
independent evidence; this check does not establish them. Code and attached
data sections use the same rule. There is no new exact or semantic acceptance.

## Focused verification

Four isolated COFF fixtures check the matching definition, wrong internal
definition, external target and nonexact-candidate paths:

```bash
scripts/repo-python tests/test_exact_local_targets.py
```

The wrong-definition test fails against the old comparator and all four pass
after the repair. The real-object counterexample independently verifies the
same rejection with the current production comparator.

A definition-only audit checks all380 accepted units and their203 internal
binding sites, plus eleven currently exact attached metadata sections. All
pass. A separate bounded collision scan covers all34 authored candidates and
their35 internal sites; no distinct definitions currently share a declared
original target. Running that diagnostic against the retained pre-repair
manifest identifies exactly the two known brick-hit groups. Collision absence
does not prove arbitrary candidate target correctness.

The audit verifies cached object/source closures; it does not repeat complete
code comparisons. No compilation, REA/provider call, game, relink or full replay
runs. Source, executable, manifests, existing reports and acceptance ledgers stay
unchanged. Totals remain475 source /380 exact /95 complete candidates.

Private `.analysis/exact-local-target-guard-20261017/` retains the before/after
counterexample, failed-before/passing-after tests, current definition audit and
input identities. The unique mutant object is retained in a byte-verified gzip
carrier before removing its disposable uncompressed copy.
