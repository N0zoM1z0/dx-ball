# Complete MDS loading and parsing cleanup

The later [MDS controller states](EXACT_MDS_CONTROLLER_STATES.md) make loading
and playback exact across522/513 bytes, completing all eight MIDI bodies.
The byte parameters and candidate comparisons below belong to this earlier epoch.

The subsequent [workspace recovery](EXACT_MDS_WORKSPACES.md) closes the parser's
remaining forty storage differences and makes the event converter exact too.
The loader remains a530/522-byte candidate. The results below describe the
earlier cleanup-flow checkpoint.

The shared C++ MIDI owner now uses the original error gotos in both the loader
and parser. Five loader failures and three block-header/capacity/conversion
failures reach their common cleanup labels. The compiler naturally produces
the original continuation jumps, including unreachable scope-exit jumps and
the cleanup stubs. No machine bytes, padding or unused locals are introduced.

| Complete unit | Previous bytes / differences | Current bytes / differences |
| --- | ---: | ---: |
| Open, original 522 | 480 / 406 | 530 / 443 |
| Parse, original 868 | 838 / 341 | 868 / 40 |

Both remain candidates. All actual relocations are applied across their full
spans. The larger raw loader difference count reflects shifted instructions
and frame storage; it is not an exactness improvement. Release (149 bytes) and
pause (133 bytes) remain fully exact. All 186 current exact identities preserve
33,001 code bytes and 136 accepted metadata bytes. The unchanged converter
source remains 343/343 bytes, now with 41 differences after canonical local-home
reassignment; its preceding 38-difference receipt remains historical.

The complete loader has 135 original and 140 current instructions. Ordinary
operands and all thirty direct branch targets correspond through nine frame
references and three explicit low-byte input-normalization groups. Ten complete
five-byte jumps to common cleanup retain fifty original bytes, including the
25 bytes outside Ghidra's imported ownership. The extra eight current bytes
come from the existing unsigned-byte parameter's zero-extension sequence.
Low-two-bit predicate equivalence does not recover the original parameter
declaration, signedness or EAX residue through arbitrary external callees.

The complete parser has 231 original/current instructions at identical offsets
and widths. Every operand and direct CFG target corresponds through a bijective
mapping of twelve frame references. Descriptor and block field relationships
remain intact; no operand-reversed comparisons or differing register residue
remain. Sixteen complete five-byte common-cleanup jumps retain eighty original
bytes, including all forty provider-unowned bytes. Its remaining forty unmasked
differences concern frame storage; they are not masked or repaired with layout
trials. Original identifiers and declaration order remain unproved.

The loader dossier is
`ev_b065fc674d2df0514ae7b30b49b895ceb361f5ec770b3c4e0ec21eb8512ef3ed`.
The complete 522- and 868-byte observations are
`ev_a7b7f4ce05473f020601101338f2392f0e732597eaed9078a2bd13128a77a584`
and `ev_cbd6ebc9417a27d9bf6922089d77670686db275fa07f8514db31928b07dc2ded`.
Both ranges match every byte of the SHA-bound original executable. Their
original Ghidra ownership stays 497/522 and 828/868, respectively. Closed
evidence is reused without another provider session.

Whole-slot reads followed by byte masks initially suggested a wider parameter
interface. Two explicit narrowing hypotheses produced extra comparison
instructions without proving the original source type. Both are reverted.
The six compiled header consumers differ from their prior objects only in
COFF timestamps; their canonical objects are restored without recompilation.
The final change is confined to eight actual error gotos in `src/midi.cpp`;
headers, other production sources, tests and case matrices remain unchanged.
There are ten actual matching compilations: two diagnostic MIDI compilations,
six diagnostic header consumers, one valid loader-only stage and one final
connected loader/parser stage. These exploratory costs are recorded explicitly.

The final library passes 253 existing parser cases, 284 loader cases, eighty
direct wrapper cases and 134 separate connected checks, including replacement,
restart, cleanup failures and all six original songs. Their constructors,
matrices, ordered effects, payload/context comparisons and callback ABI checks
remain intact. The loader-only stage has its own retained product and receipt;
it is not relabeled as a final-parser result. Native and MinGW rebuild only
the MIDI owner in each valid stage. Final VC4 links one matching MIDI object
and 35 verified unchanged game objects, without additional compilation.
The 235 affected historical semantic input inventories are refreshed, not
rerun. Private receipts and the immutable checkpoint are
`.analysis/source-dataflow-frontier/` and
`.analysis/checkpoints/mds-cleanup-flow-283-186/`. Hardware audio delivery,
exceptional execution and complete original-source fidelity remain unproved.
