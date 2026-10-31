# Current VC4 game build

October 22, 2026. The `vc40-restored-crt` game is built from source checkpoint
`ecfc475715238c43241a5979b1745a163749b9dc`, which completes all 270 authored exact
functions. [Build instructions](../BUILD.md) explain how to reproduce it;
[October 22 playability](PLAYABILITY_20261022.md) describes that image's original
checks. The [October 31 update](PLAYABILITY_20261031.md) adds windowed play,
Windows manual feedback and a native Windows source build without changing game source.

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

## Native Windows rebuild, October 31

`Build Reconstruction.cmd` compiles all 141 units with the same VC4 recipes and
extracts the same 19 approved original CRT members. All 270 authored functions
and 84,968 code bytes pass the complete comparisons across 53 compiler closures
using the native objects; no source was changed to obtain this result.

The Windows 11 linker child needs `WIN7RTM` compatibility. This setting applies
only to `link.exe`, without elevation or registry edits. The source compiler
context remains unchanged. A clean compilation was followed by hash-verified
object reuse while resolving the linker issue; the normal recording launcher
always compiles all units again. English progress, compiler logs and
`build-report.json` accompany the native package.

The native EXE is 166,400 bytes with SHA-256
`526b890eed0e3fe53bd86add6a883770aceff45dbf54e9060aa976940d4c4afd`.
Only 18 bytes in six PE/resource build timestamp fields differ from the tested
October 22 image. Every code/data/import/relocation section otherwise agrees,
with the same RVAs and sizes. The build does not launch the game.

Retained proof is under `.analysis/native-windows-build-20261101/`, including
`authored-comparison.json`, `image-comparison.json`, the compiler transcript and
native build receipt. The repo-local copy is `build/dxball-native-windows.exe`;
the Windows package writes `build/game/dxball.exe` and preserves its existing
tested `game/dxball.exe`. [Build and play](../BUILD.md#native-windows-source-build)
explains packaging and the recording launcher.
