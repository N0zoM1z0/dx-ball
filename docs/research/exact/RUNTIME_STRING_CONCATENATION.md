# String copy and concatenation

The complete232-byte pinned strcat.obj code section matches0x4177F0..0x4178D7
without relocations. Its two actual function definitions are `_strcpy` at0 and
`_strcat` at8. The former's imported7-byte range is only its entry jump to the
shared copy tail at0x417859. Its ledger span is corrected to232 bytes; strcat
retains224 bytes. These physical spans overlap and are not independent byte
coverage or new exact bytes. The strict source-function oracle is unchanged.

Shared typed source restores both complete operations. Concatenation finds the
destination NUL through byte alignment and32-bit zero-byte detection. Both copy
through a byte-alignment prefix, two actual reads per source word and exact1/2/3/4
byte terminating stores. Readable terminator-word tails and nonoverlapping backed
buffers follow the original physical contract. A shared source macro represents
the common tail without inventing a callable C address for its register ABI.

One VC4/native/i686 set yields copy198/232 with232 differences and append291/224
with276 differences. Neither is exact. All335 preceding exacts,111 candidates
and249 semantic rows retain their current input/product identities. Source457/
candidates113; exact335/code69,718/metadata136 and all origins are unchanged.

Fresh full strcat assembly is
`ev_a7262c8148561af5c01678d47a3fc568d30142196f15c533c94b10d6a6d203f4`,
closed run `2026-10-14T02-38-17.740Z-interactive-2512982`. Retained strcpy-entry
assembly and the complete pinned shared section establish its out-of-range jump.
Receipts: `.analysis/runtime-string-concatenation-20261014/verification.json`.
No runtime/game tests run. The prior aggregate-initialization trial fails VC4
C2552; its source is restored by hash and unique failure evidence retained in
`.analysis/list-aggregate-initialization-20261014/`. No initializer spelling sweep.
