# Reconstruction workflow

Work against the single English DX-Ball v1.07 executable in `config/target.toml`.
Run repository Python with `scripts/repo-python`, which attests loaded analysis
packages and their native engines before selecting an interpreter.

1. Read the handoff and relevant owner evidence; inspect `git status`.
2. Verify target, toolchain, and tracking. Use `scripts/rea` for new binary
   analysis; it attests the pinned REA runtime and Ghidra/JDK inputs. Read
   `docs/REA.md`; retain returned Evidence IDs and limitations.
3. Select a related batch of entries from `config/functions.csv`. Reconcile control flow,
   embedded tables, epilogues, and padding; imported sizes are provisional.
4. Inspect exact instructions, data references, producers, and independent
   consumers through REA. Keep complete evidence and reusable snapshots under
   ignored `.analysis/rea/`; promote reviewed observations into owner documents.
5. Reconstruct natural shared C source with explicit state ownership and ABI.
   A portable dependency bridge validates call effects, not its missing backend.
6. Once the batch's source is stable, replay its target-machine differential
   oracles and cold-build its configured legacy compiler units together.
   Do not cold-replay each individual function during reconstruction. Reuse
   completed reports while their complete inputs remain unchanged, and rerun
   affected units after subsequent shared-input changes.
   Exact comparison applies every reviewed COFF relocation and compares
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
