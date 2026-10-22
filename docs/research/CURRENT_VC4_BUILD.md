# Current VC4 game build

October 22, 2026. The `vc40-restored-crt` game is built from source checkpoint
`ecfc475715238c43241a5979b1745a163749b9dc`, which completes all 270 authored exact
functions. [Build instructions](../BUILD.md) explain how to reproduce it;
[playability results](PLAYABILITY_20261022.md) describe the tested behavior.

## Products

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| `build/vc40-restored-crt/dxball.exe` | 166,400 | `bdd425241ba51d6fe671bb0184b4ad86062326fc9e1eb407d2536235b93df79c` |
| `build/delivery/dxball-v1.07-vc40-reconstructed.zip` | 474,899 | `00a6d9799327a71c11a2b9afa71ae38c1db34249c98259303c00e2f3b5e6ba4d` |

The ZIP contains the tested EXE, 48 unchanged original assets and extraction
instructions. All 50 members are checked by size, SHA-256 and ZIP CRC. It uses
the original score table. The adjacent manifest links the build, individual
members and expanded validation, including the unresolved focus checks.
Extract the complete folder and run `dxball.exe` there.

## Link inputs

VC4 compiler 10.00.5270/linker 3.00.5270 link 138 source objects and three
integration objects, plus 19 original CRT members under `/NODEFAULTLIB`.
Four objects required compilation; 137 were reused after checking compiler,
flags, recursive source/header inputs and object hashes. Resources and DirectX
import libraries are included in the receipt.

All 53 authored compiler recipes retain the objects accepted by the closing
exact audit. The last link takes 22.362 seconds at 35% CPU, with peak memory
176,939,008 bytes and zero memory-limit/OOM events.

| Record | SHA-256 |
| --- | --- |
| `build/vc40-restored-crt/build.json` | `1551821330f892615e78cb0fa0d3a16d525a4074b5503fd93627c14695bf2891` |
| `build/vc40-restored-crt/dxball.map` | `524f10a78f63422fc8ca79bf665180efb79ff098bfb79be6c86a4d4c686390f2` |

## Retained evidence

- Authored audit: `.analysis/pcx-file-prefix-source-search-20261022/completion-audit.json`.
- Link/basic/editor/round checkpoint: `.analysis/current-vc4-exact270-20261022/current-checkpoint.json`.
- Expanded playability and cleanup: `.analysis/playability-exact270-20261022/current-checkpoint.json`.
- Public verification metadata: [playability-status.json](../../config/playability-status.json).

Earlier images, cold builds and failed runs are described in the
[preceding build record](https://github.com/N0zoM1z0/dx-ball/blob/9752a6954ec1bea5da2885ba236ca51a5c8976a0/docs/research/CURRENT_VC4_BUILD.md).
