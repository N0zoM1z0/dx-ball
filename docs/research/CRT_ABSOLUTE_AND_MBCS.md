# Independent CRT absolute definitions and MBCS data

Three previously unknown entries are now proved to be complete sections from
the pinned VC4 CRT library. This separates dependencies from the remaining game
source frontier. It does not add reconstructed source or game exact acceptances.

| Original entry | Object-local symbol | Complete bytes | Actual relocations |
| --- | --- | ---: | ---: |
| `0x0041BF10` | `_x_ismbbtype` | 58 | 2 |
| `0x0041C6E0` | `_setSBCS` | 44 | 5 |
| `0x0041C0D0` | `_parse_cmdline` | 466 | 4 |

The maintained verifier compares every byte and applies every actual COFF
relocation using independently established bindings. All three whole sections
match with zero differences. Each imported entry covers its complete section;
an imported boundary alone was not used as proof. The symbols have COFF storage
class 3: they remain local to their archive members and are not exported into
the shared name-to-address map.

## Absolute values are not target storage

The archive independently defines external COFF ABS symbols `__except_list=0`
and `__tls_array=44`. The verifier checks the exact member name, archive offset,
SHA-256, unique symbol definition, section -1 and external storage class 2.
Wrong values, duplicate declarations and initialized definitions presented as
ABS are rejected. Established conflicting bindings cannot be overwritten.

These are link-time constants. They do not place target data, identify another
function, or independently prove operating-system ABI or executed behavior.
Adding just these two constants retains the preceding 62 complete code sections
but discovers no additional whole-section match.

## Place a complete initialized section independently

The relocation-free 536-byte initialized section in `mbctype.obj` occurs exactly
once in the original PE, at `0x00423948`. A fresh REA 6.3.0/Ghidra 12.1.4 read
returns all 536 bytes and agrees with both the carrier and complete library
section. Only after that comparison passes are its actual external definitions
published:

| Definition | Original address | Offset in section |
| --- | --- | ---: |
| `__mbctype` | `0x00423948` | 0 |
| `___mbcodepage` | `0x00423A4C` | 260 |
| `___mblcid` | `0x00423A50` | 264 |
| `___mbulinfo` | `0x00423A58` | 272 |

This establishes a section extent, not a fictional 536-byte extent for the first
variable. The new placement basis requires the entire actual initialized
section, nonzero content, at least 16 bytes, no relocations, exactly one carrier
occurrence and the declared address. Existing symbol-seeded placement remains
separate. Zero-filled locale storage remains ambiguous (4,102 occurrences);
pointer-bearing I/O data and unresolved BSS globals are not placed by resemblance.

The MBCS definitions unlock the three code sections above. Their 11 relocations
use verified MBCS data and the preceding independently verified ctype data;
none requires guessed operands or a global binding for another member's static
symbol.

## Evidence and validation scope

- New complete data Evidence:
  `ev_104ef247786de4c59b88d8fe5100bd85eda25345a62adc1dd1d224263a7e1ada`.
- Reused complete original code Evidence:
  `ev_c709f0f7ebf372bf89a419cba70fa6a08db03b6de34d5c13b625afa16360ab12`.
- `config/runtime-origin-sections.json` pins actual members and placement bases;
  `scripts/verify-runtime-origin-sections.py` implements the maintained checks.
- Private `.analysis/crt-absolute-frontier/` retains discovery, before-state,
  stage-specific hashed inputs, provider timing and seven rejection controls.
- Final `build/reports/runtime-origin-sections.json`: 65 complete code sections,
  7,229 bytes, 69 distinct origin rows including three import forwarders; three
  complete initialized sections / 1,130 bytes. ABS constants are reported
  separately. All earlier complete sections remain accepted.

Seven actual-verifier controls reject wrong ABS value, non-ABS definition,
duplicate ABS, shifted unique-section address, zero self-placement,
pointer-bearing self-placement and a partial section. Each rejects with its
expected reason without producing an acceptance report. No original payload
is changed for these controls.

Origins become 270 authored / 79 runtime / 42 compiler-generated / 137 unknown.
Source-present 283, scoped semantic 247, and game exact 186 / 33,001 code bytes /
136 accepted metadata bytes remain unchanged. Current source, tests, 36 game
objects and all four products retain the preceding `7462948` identities. No game
compilation, gameplay replay or new physical-runtime observation occurs here.

REA performed one fresh byte request and closed its saved session. The logged
read took 39,544.76 ms; open/close took 1,076.03/2,116.71 ms. This first-read
latency is observed, but its cause is not isolated. Performance and usability
feedback is appended only to the existing shared `/tmp` feedback document.

These runtime proofs do not establish the complete authored denominator or
complete game fidelity. A future static-callee closure must bind verified
definitions within the same hash-identified archive member, rather than flatten
object-local names into a global map. Full campaign, synchronized rendering and
hardware audio remain separate outstanding scopes.
