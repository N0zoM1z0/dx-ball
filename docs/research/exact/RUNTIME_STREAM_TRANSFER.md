# CRT stream transfer and retirement

Six complete bodies now cover stream closure, bulk reading, slot acquisition,
input/output refill and terminal flags. Closure, input refill and terminal flags are exact.

| Entry | Original/current bytes | Differences |
| --- | ---: | ---: |
| `fclose`, `0x417A30` | 112/112 | 0 |
| `fread`, `0x417AA0` | 326/324 | 218 |
| `_getstream`, `0x41A5A0` | 126/126 | 2 |
| `_filbuf`, `0x418220` | 240/240 | 0 |
| `_flsbuf`, `0x41A620` | 328/328 | 50 |
| `_isatty`, `0x41DFA0` | 42/42 | 0 |

Output refill improves328/67 to328/50 through the conditional safe-record
selection established by shipped `internal.h`. The negative buffer-acquisition
guard from `_flsbuf.c` gives an identical complete result. All actual relocations
are refreshed; three owner exacts, fread324/218 and getstream126/2 remain fully
unchanged. Two compiler sets, no runtime/provider work; all349 exacts/72,681 code
bytes and249 semantic rows remain. Receipt
`.analysis/output-refill-original-safe-record-20261015/verification.json`.
The separate original fread assignment/update-order trial gives324/223 and is
rejected, with its source restored before these output-refill compilations.

Input refill now matches all240 bytes and four actual relocations. The shipped
CRT `_filbuf.c` establishes its local register stream and zero/-1 error exit;
`internal.h` establishes conditional safe-record selection before reading flags.
The local declaration alone gives240/8; conditional selection closes the last
load-order difference. Its first retained object is re-consumed after actual
fread call-offset changes, without recompiling. A separate scalar fread trial
gives324/223 and is rejected; selected fread324/218, both owner exacts and two
other candidates remain byte-identical. Three compiler sets, no runtime tests;
totals341 exact/70,555 code bytes, candidates108, all340 prior exacts preserved.
Receipt `.analysis/input-buffer-register-owner-20261014/verification.json`.

Closure preserves flush/free/descriptor-close order, clears stream flags even
on failure, and releases the temporary name only after successful close.
All112 bytes and four actual call relocations agree. Slot acquisition rereads
the registry after allocation and resets only six observed fields; capacity
and the character buffer are not initialized. Following its nonnull/unused
branch order reduces48 differences to2; loop comparison commutation remains.
Terminal flags return64 rather than a normalized boolean, without publishing
errno or checking the open bit. Its signed-byte promotion restores42 bytes.
Declaring the lower-I/O boundary before the stream's CRT includes avoids the
MinGW errno macro collision; in this final shared context all42 terminal bytes
and both data bindings match. No existing consumer header changes.

Output write-count initialization now starts only on the active write path.
Initial invalid-stream and read-without-EOF failures own their flag writes and
returns; the final write-mismatch exit stays separate. This improves288/311 to
320/277; not exact. Deferred-count-only292/281 and write-mode-entry316/279 are
retained; the latter is rejected. Both owner exacts and three other candidates
remain unchanged. Three VC4/native/i686 sets, retained REA, no runtime/game tests.
That checkpoint is retained under `.analysis/stream-output-write-lifetime-20261014/`.

The shipped CRT `_flsbuf.c` establishes the genuine register stream, expected
count and written count, plus their chained active-path initialization. EOF
success and final write mismatch own their respective transitions/returns.
Restoring those declarations and branches improves320/328/277 to328/328/67.
Both bodies contain122 instructions; stream/descriptor register allocation,
record-address scheduling and error epilogues remain different. Two compiler
sets preserve both owner exacts and all three other candidates, with all340
old exacts/249 semantic rows unchanged. No runtime tests or provider work;
receipt `.analysis/output-buffer-register-owner-20261014/verification.json`.

Input distinguishes zero/-1 from other counts, detects text Ctrl-Z state and
expands the owned512-byte buffer to4096. Output retains read-to-write EOF
transition, standard stdout/stderr terminal exceptions, append seeking and
single-byte writes. Bulk reads use the original32-bit size product, buffered
copy, capacity-sized direct reads and final byte refill. The three-field read
transfer record contains only consumed destination/total/capacity state.
The original memcpy is intrinsic; this owner's `/Oi /ML` recipe is isolated.
Loop orientation, minimum operand orientation and grouped read state do not
change their closed comparisons. Neither these trials nor the terminal
zero-first arm establish additional exacts.

The closed REA run `2026-10-13T14-18-34.422Z-interactive-1719079` retains all18
info/pseudo/assembly records. Assembly Evidence IDs respectively:
`ev_e90ec22d7310954a5e9277b07e81c8b043d45252a2a27ed5006cf7030eb985df`,
`ev_2c3ef6dadb7fe8e79f5377c686891fa9f7960a56a3e3833e4295fc293d9986c7`,
`ev_a7491a8c4445f083b3f7afa2cf201a5108e0ad674c288ea8ad9802083fe3db79`,
`ev_91a9310cf92dca9150512376bee0f195b30c53103dc2cd532fc2d0a44a101e26`,
`ev_fa18ebc65c1908d327efbd23b5f10599c53122af843b8caa2a4939037a46e4b4`,
`ev_7c4c07745b7758561f7c8cbda368ee20bbbc5a606518bafceb7516e3cbab8721`.
All six complete pinned CRT sections independently agree with the original
after every relocation. Private proof and producer receipts are under
`.analysis/runtime-stream-transfer-20261013/`.

Source presence330; exact257/64,185 code bytes; metadata136 unchanged.
All255 preceding exacts and57 candidates retain their inputs/products/results.
Current candidates61:34 authored/27 runtime. Native/i686 standalone compilation
covers this new owner; no runtime tests or game builds run. Registry, standard
stream/error storage and game integration remain open. The standard stream
array declaration has no invented capacity or initialized-data claim.
