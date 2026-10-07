# Reconstruction workflow

Work against the single English DX-Ball v1.07 executable in `config/target.toml`.
Run repository Python with `scripts/repo-python`, which attests loaded analysis
packages and their native engines before selecting an interpreter.

1. Read the handoff and relevant owner evidence; inspect `git status`.
2. Verify target, toolchain, and tracking. Attest Ghidra before semantic queries.
3. Select one entry from `config/functions.csv`. Reconcile control flow,
   embedded tables, epilogues, and padding; imported sizes are provisional.
4. Inspect exact instructions, data references, producers, and independent
   consumers. Keep decompiler hypotheses under ignored `.analysis/`.
5. Reconstruct natural shared C source with explicit state ownership and ABI.
   A portable dependency bridge validates call effects, not its missing backend.
6. Replay the appropriate target-machine differential oracle and legacy compiler
   unit. Exact comparison applies every reviewed COFF relocation and compares
   all bytes; nothing is masked or ignored.
7. Promote exactness only after a cold, configured zero-difference replay.
   Source presence, semantic acceptance, and exactness are independent ledgers.
8. Update the knowledge base and handoff, validate ledgers, regenerate progress,
   and commit the bounded result with an English `gpt-6.1-sol: ...` subject.

The observed PE linker is 3.00. VC4.0 compiler 10.00.5270 / linker 3.00.5270 is
the first hash-pinned candidate. Per-unit matching establishes emission
compatibility; the entire original compiler configuration remains unproven.

Never patch or publish original binaries/assets. Never transcribe generated
decompiler output into source. Never add source profile selectors, inert locals,
copied code bytes, arbitrary padding, or assembly to force a match.
