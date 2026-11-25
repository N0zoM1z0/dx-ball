# Position independence in DX-Ball

Position independence (PI) means that code and data can move within the image
at link time while references still reach their intended function, object, or
field. ReC98 tracks unresolved numeric address candidates in 16-bit assembly.
DX-Ball uses i386 COFF and PE, so check compiler relocations, their addends, and
the resulting bindings after moving the destinations. A linked PE can encode an
absolute address calculated by the linker. PE base relocations cover moving
the entire image at load time. [ReC98 FAQ](https://rec98.nmlgc.net/faq)

The VC4 checks follow the same criteria as TH08. Verify code and initialized
pointer data against their symbols, preserve the identity of shared storage,
check the bounds of bulk operations, and exercise the affected paths after
relinking. Original addresses in comparison manifests and source comments
identify the reference executable.

## VC4 layout experiment

From the repository root, run this after preparing the `vc40-restored-crt`
build. It uses the current build receipt and its existing objects.

```bash
systemd-run --user --scope --quiet \
  -p CPUQuota=35% -p MemoryHigh=384M -p MemoryMax=512M \
  scripts/repo-python scripts/verify-vc40-pi.py
```

The verifier checks the normal PE and map against the build receipt. It then
reverses the order of source objects without CRT subsection contributions in
their existing argument slots. It retains the CRT subsection contributors, the
19 approved CRT members and the library order. It links a temporary,
resource-free diagnostic DLL with no entrypoint, at the same image base of
`0x00400000` and with 8 KiB section alignment. The experiment recompiles no
objects. The verifier removes its temporary output on exit.

The November 25, 2026 run against the baseline identified in the
[current build record](research/CURRENT_VC4_BUILD.md) reversed 135 objects.

| Symbol | Regular RVA | Reordered RVA |
| --- | ---: | ---: |
| `dxball_load_editor_board` | `0x0064D0` | `0x017E40` |
| `dxball_render_ops` | `0x01FCB8` | `0x020FD8` |
| `dxball_board_aux` | `0x037680` | `0x037FB0` |
| `dxball_board_storage` | `0x03A000` | `0x03C000` |
| `_FPinit` | `0x01F9AC` | `0x021334` |
| `__xc_a` | `0x01F000` | `0x020000` |

Each image passes 11 complete code and data comparisons covering 41 COFF
relocations and their addends. The checked data includes the render dispatch
table, floating-point initialization hooks, initial conversion callbacks, and
pretermination callbacks. The linked CRT startup helper follows the relocated
initializer range boundaries.

Each image also passes 27 x86 emulation cases covering board load, store and
initialization at indices 0, 49 and 50, with three storage patterns. The
verifier checks the full 20,432-byte board storage, the auxiliary grid and
the selected index. At index 50 the 400-byte copies overlap by 368 bytes.
The seven storage symbols move together while the linked storage metadata
and relative offsets retain the adjacency contract. The CRT conversion
setup writes all six expected callback pointers at their new addresses.
[Board storage evidence](research/exact/INDEPENDENT_BOARD_STORAGE.md#production-acceptance-october-17)

This result covers the listed VC4 references and exercised paths. Whole-image
coverage still requires checking the other pointer-bearing data, callback
consumers, the remaining linked CRT and SDK code, and live behavior in a
perturbed Windows layout. MinGW and native ELF products need their own checks.
