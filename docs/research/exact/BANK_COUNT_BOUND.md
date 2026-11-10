# Sprite-bank count bound

October 19, 2026. The live record-loop guard now expresses the original low32
increment followed by a signed comparison:

```cpp
for (i = 1; i < (DxBallInt)((DxBallUInt)count + 1); i = i + 1) {
```

The previous signed `count + 1`
had undefined overflow for INT_MAX. The new expression preserves the target
bit pattern on supported VC4/GNU x86 conversions, without changing the count
object, file operation or signed predicate. Historical cast spelling is unknown.

Count is still reread at every guard, including after callbacks that could have
retained its escaped address. No bound is cached. For every signed guard bound,
an entered iteration has i at most INT_MAX−1, so the existing iterator increment
does not overflow. This remains true when a later callback changes count.

## Actual bounded counterexample

The witness contains count INT_MAX followed by a complete one-pixel record.
The unmodified original consumes only the four-byte count header: its bound
wraps to INT_MIN, it skips every record, closes the file and restores the previous
bank selector. Existing bank metadata remains unchanged. The restored actual
native loader follows that same path, with identical bank state and no extra
open file descriptor.

The old actual native loader instead enters the one-pixel record, reaches the
existing forced CreateSurface failure, and returns with a partial bank and open
stream. Its instrumented comparison has no signed-overflow diagnostic; actual
path divergence supplies the counterexample. This is not general damaged-file
safety or a requirement for new input validation.

An initial four-byte-only witness allowed the old path to read unspecified
locals after ignored short reads, and its fixture attempted a large surface.
The retained MemoryError/fd mismatch is a failed witness. The corrected bounded
payload and existing creation-failure callback avoid that path; both compiled
products are reused without another compiler invocation.

## Complete source comparison

One resource VC4 compile compares all18 complete bodies,262 actual bindings and
six full literals. All11 accepted functions/2577 bytes survive. Sixteen complete
resolved code identities are unchanged, including both glyph candidates. Bank
remains1475 bytes and improves64→63 raw differing positions. PCX remains979/850
with a different digest; its scheduling change is not a new source operation.
Current totals remain393 exacts/84633 code bytes/244 metadata bytes, with248
authored exacts and22 complete authored candidates.

Native rebuilds only resources and relinks its library. The ten unchanged bank
cases pass: seven supplied SBKs, small-stream, empty-bank and creation-failure
cases. Historical semantic scope/counts are unchanged. The additional bounded
count witness remains separate private evidence. No full replay is run.

Compiler and
probe trees use one allowed CPU, CPU35%, memory high384MiB/max512MiB.

The subsequent [current VC4 build and play check](../CURRENT_VC4_BUILD.md)
links this complete current resource object into the delivery and passes the
existing actual gameplay/editor/save/reload/exit flow. The earlier18-body source
comparison and bounded count witness retain their separate scopes.
