# VC4 owner recipes and verified object reuse

The legacy game builder now uses the maintained comparison recipes for the
allocator, typed lists and resource owner. Previously these three files used
the common board flags, despite their dedicated compiler products:

| Source | Restored recipe difference | Product used |
| --- | --- | --- |
| `allocator.c` | `/O2` rather than `/Od` | Accepted eight-function allocator object |
| `list_initializers.cpp` | `/Ob1` rather than `/Ob0` | Accepted constructor/list object |
| `resources.cpp` | `/ML` rather than `/MT` | Accepted resource object |

The earlier raster, RNG and actual C++ allocation overrides remain. These are
the maintained emission recipes, without a claim that they identify the unique
original project settings.

The resource recipe initially exposed duplicate `LIBC`/`LIBCMT` CRT definitions
at link time. Both game and diagnostic links now exclude default `LIBC`,
retaining one `LIBCMT` runtime. The successful game map contains no `LIBC`
members. The resource object retains its verified compiler lowering; no source
operations or callback bodies change to resolve the link.

## Reuse and receipts

`build-legacy.py` first checks complete owner objects in the current exact
report. Compiler identity, manifest hash, owner flags, every recorded project
input and the actual object hash must agree. Recursive quoted project includes
also have to be covered by the receipt. Files without that matching recipe are
compiled normally.

Subsequent builds can also reuse game/adapter objects from `build/vc40/build.json`.
These require the same compiler and toolchain configuration, exact flags,
current source/header closure and product hash. Accepted owner products take
precedence. Copies replace destination files through a separate inode, keeping
canonical objects intact. Fifteen bounded validity controls reject changed
headers, products, flags, compiler identity, invocation helper and stale receipts.

Each object now has its own input, flag, hash, action and producer receipt.
The top-level inputs cover the actual linked sources and headers, including
host/entry files, and the build tools/manifest. Unlinked standalone CRT owners
no longer invalidate a game product merely by changing source. The optional
`--game-only` skips the two diagnostic executables; the default still requests
the game and both tools.

The first game build reuses 30 objects and compiles seven. After the per-file
recipe corrections, the successful game build reuses all **37 objects**, with
no compiler invocation for those objects. It still verifies the toolchain,
resources and imports and performs a real link.

## Actual linked code and runtime evidence

The final game map binds both actual C++ allocation operators to
`cpp_allocator.obj`. All eight allocator bodies, 42 constructor/list bodies
and both C++ operators match their complete compiler spans after resolving
every relocation to the actual linked image addresses: **52 linked body
checks, all zero differences**. Resource recipe/object identity and its map
linkage also agree. This checks integration of existing functions; it adds no
original-target exact acceptances and makes no whole-image byte-exact claim.

A coarse window/input/exit observer passed, but its screenshot labelled
"board" still showed the opening title. Pixel change was insufficient scene
evidence. That raw observation is retained with an explicit review, rather
than being accepted as a first-board check.

The follow-up uses the existing read-only state observer against the current
map and executable. Its 78 reads establish opening mode 4, menu mode 0, game
mode 1 with an attached ball, paddle positions 480/200 following real mouse
input, ball release and subsequent movement, return to menu and real exit 0
with the window gone. The reviewed screenshot shows the first board, bricks
and paddle. No target memory is written or hooked. Original assets remain
unchanged; the temporary silent audio sink is removed afterwards.

Only VC4 runs in a 640x480x24 Wine/Xvfb display. No original/MinGW controls,
pause/editor campaign or physical Windows/audio check is repeated. The
standalone recovered CRT entry and remaining runtime owners are still outside
this game link; complete final CRT/game integration and function recovery
remain open.

Function source 464, exact 376, exact code 76,908 bytes, attached metadata
244 bytes, complete candidates 88 and semantic rows 249 are unchanged.
Every existing acceptance ledger and both original-target comparison reports
are byte-identical. No provider or full replay runs. Compiler/link/Wine commands
run serially on one allowed CPU under the 35% CPU/768 MiB scope.

Private raw controls, rejected mixed-CRT link, successful game products/maps,
52 body comparisons, both runtime observations and scene review are retained in
`.analysis/legacy-owner-reuse-20261016/`.
