# Exact paddle contact precision

Paddle rebound at `0x411410` now matches all 681 original bytes, including
its fifty relocations and eight complete floating constants. The original
28-byte frame and 181 instructions agree. Three exact ball companions retain
965 bytes, bringing the complete ball owner to four exact functions and
1,646 bytes.

The source reuses one float for the paddle left edge, contact offset and
normalized contact. A chained assignment preserves the intermediate offset
store at `0x411476`. The first threshold compares the live x87 quotient at
`0x411497`, before its float store at `0x41149D`. The remaining six thresholds
read that stored value through `const volatile float` lvalues referring to the
same object. These accesses prevent the GNU optimizer from carrying the
extended quotient into later comparisons.

This distinction affects real contacts:

| Contact | First or later check | Original angle |
| --- | --- | ---: |
| 7 / 100 | First threshold, before float rounding | 150 |
| 12 / 60 | Later threshold, after float rounding | 120 |

A plain chained assignment matches VC4 but fails one of these contacts in each
previous GNU precision model. Making the entire local volatile passes both
native contacts but adds eighteen VC4 bytes at the two assignment sites.
Qualifying only the six later reads preserves the original assignment emission
and both native results. No extra object, alias variable or copied instruction
is introduced.

The owner is now `src/balls.cpp`, with its existing public declarations enclosed
in C linkage. C++17 sequences the nested assignment. GNU builds compile this
file with `-O2 -mfpmath=387 -fexcess-precision=fast`; the source-specific
`-Wno-sequence-point` suppresses GCC's older warning for the defined C++17
expression. The VC4 recipe retains `/Od /Ob0 /Oi- /Oy- /Gd /MT /Gy`.
These are the verified GNU x86 and legacy VC4 numeric models.

One eighteen-input VC4 compilation supplies the matching object. Canonical
inputs are byte-identical to that retained producer; no duplicate matching
compile is needed. All 239 exact functions retain 63,195 code bytes and
136 metadata bytes. The other 34 candidate code identities are unchanged.

Native and MinGW products build. VC4 links the matching ball object with
36 verified existing objects. A private native product passes 831 existing
ball cases and four live audio controls. Its allocated object sections,
relocations and symbol tables match the canonical native object, and the other
36 linked objects are identical. This evidence is reused for the current
product; both numeric contacts also pass against the canonical library.
No game run accompanies this function recovery.

Original REA Evidence is
`ev_6055fe1d318fa3f71d76b5cdbbbe862a3944dd9890035a53264b8ccfa2d7a074`.
Full source, compiler and precision proofs are retained in
`.analysis/rebound-stored-contact-reads-20261013/`; current product and ledger
receipts are in `.analysis/rebound-contact-integration-20261013/`.

Independent review seals the current inputs, products and ledgers. Verified
gzip cleanup of ten completed negative and archival carriers releases
1,179,648 allocated bytes; accepted producers and current products remain.
