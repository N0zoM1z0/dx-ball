# Exact CRT absolute value

The full10-byte function at0x00416780 matches the pinned LIBC `_abs` member,
whose COFF file record names `abs.c`. Direct REA assembly evidence
`ev_d9b6b3ea9ea591f8c9bec57a2a57ea2f3846ea61b2d0ba246d3b7248d8b05b94`
establishes sign extension, XOR, subtraction and return, with no relocations
or attached metadata.

The shared signed C absolute-value expression compiles to all10 original bytes
with zero differences. The original CRT contract requires a result representable
in int: INT_MIN is not valid input. The PE happens to wrap it; the reconstructed
C API does not claim defined behavior outside that contract.

An unsigned sign-mask model produces14 bytes/10 differences, and unsigned
conditional negation produces11 bytes/seven differences. Restoring the signed
operation produces the exact body. Three VC4/native/i686 compilation sets
completed; no runtime or game checks ran. All315 preceding exacts and104
candidate products retain their verified inputs. Receipts and unique objects
are in `.analysis/runtime-absolute-20261014/`.
