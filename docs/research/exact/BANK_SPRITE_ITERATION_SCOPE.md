# Sprite-bank iteration lifetime

The bank loader now declares each sprite's width, height, baseline, code,
pixel count, file pixel buffer and allocated record inside the existing sprite
iteration. All seven values are produced and consumed there; the pixel buffer
is released before the next iteration, and the record is published to its slot.
Types, names, relative declaration order, reads, writes and calls are unchanged.
The surface API workspace and upload counters retain their existing scopes.

The complete matching function stays 1,475 bytes, with 425 instructions and
a 180-byte frame. Differing positions fall from 72 to 70, with no new ones.
The two removed positions are stack displacements in multiplication groups;
they do not establish matching scalar homes or original operand order. Surface
description, result, pixel and key retain EBP−180/−72/−68/−64.

One eight-input matching compilation compares all seventeen complete resource
functions. Fifteen accepted companions retain 3,572 exact bytes; the other
sixteen code identities are unchanged. The bank's `rb` literal receives its
actual new COFF label after complete content and original-address checks.

All 238 exact closures and all 35 candidates verify. The other 34 candidate
code identities remain unchanged. Native and MinGW build; VC4 compiles the
separate production `/MT` resource object and links it with 36 verified existing
objects. Ten unchanged bank cases and three live callback cases pass.
No game run accompanies this change.

Original REA Evidence is
`ev_b55c6def4c1b4af6c165acfb1623311bffa077753d93fab01531787dca6b6d70`.
Source and instruction proofs are in `.analysis/bank-sprite-iteration-scope-20261013/`;
current integration receipts are in `.analysis/bank-iteration-integration-20261013/`.
Totals remain 238 exact functions / 62,514 code bytes / 136 metadata bytes.

Independent review seals all current inputs, products and ledgers. Verified
gzip cleanup preserves 112 completed bank and rejected floating-point carriers,
releasing 9,437,184 allocated bytes including its receipt. Current products,
unique snapshots and numeric failure witnesses remain available.
