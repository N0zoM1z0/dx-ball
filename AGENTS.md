# DX-Ball reconstruction rules

Reconstruct the hash-pinned English DX-Ball v1.07 executable in
`config/target.toml`. Use REA through `scripts/rea` and its Ghidra provider for
all new binary analysis. REA 4.1.0 and Ghidra 12.1.4 are pinned separately in
`config/rea.lock.json`. Read `docs/REA.md` and the installed REA skill. Preserve
REA Evidence IDs, limitations and snapshots under ignored `.analysis/rea/`.
Never patch target bytes. The old Ghidra 12.1.3 database and wrapper are historical
evidence retained for the existing inventory; do not use them for new queries.

Use `scripts/repo-python` for repository Python commands. Read
`docs/RE_HANDOFF.md`, `docs/RE_WORKFLOW.md`, and relevant owner evidence before
changing reconstruction state. Run target, toolchain, and tracking checks first.
Treat the 528 imported function extents as provisional, including embedded
switch tables and fall-through. Check an entry against `config/functions.csv`.

Keep mapping, source presence, semantic validation, and exact matching separate.
Do not mechanically paste decompiler output into source. Preserve explicit ABI,
data widths, ownership, and uncertainty. One maintained source is shared by the
portable and legacy compiler builds. Do not add profile-selected layouts or
function bodies, copied machine bytes, fake locals, padding, or assembly to force
a match. A host dependency bridge does not prove the dependency implementation.

Every exact claim needs a configured unit, a verified compiler, reconciled
extent, explicit relocation mapping, and reproducible zero differences against
the verified target. Never ignore or mask relocations or promote a percentage
comparison to exactness. Rerun accepted units after shared-source changes.

Keep private originals under `original/`, toolchains under `.tools/`, generated
products under `build/`, decompiler experiments under `.analysis/`, and private
databases under `ghidra-project/`. Never publish those files. Store reviewable
observations in `docs/` and accepted names/origins in `config/`.

Use one writable analysis/compiler session at a time. Work in bounded families
and commit stable checkpoints frequently. All commit subjects must be English
and start with `gpt-6.1-sol: `. The user has authorized a public GitHub `dx-ball`
repository and publishing these reconstruction sources.

Write detailed English commit bodies for subsequent work: describe the actual
REA operations/evidence used, resulting implementation, and validation. Mention
REA naturally when relevant; keep the required subject prefix.
