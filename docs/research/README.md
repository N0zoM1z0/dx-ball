# Research notes

## Current results

- [Progress](../PROGRESS.md): authored exact coverage, build and remaining validation.
- [Current VC4 build](CURRENT_VC4_BUILD.md): compiler inputs, executable and delivery identities.
- [October 22 playability](PLAYABILITY_20261022.md): completed live checks and unresolved focus recovery.
- [Exact reconstruction](exact/README.md): accepted source families and compiler evidence.

The subsystem notes below retain original observations and dated reconstruction
checkpoints. Their counts and product identities belong to those checkpoints.
Use [the source map](../../src/README.md) to locate the current implementation.

## Gameplay and modes

- [Ball physics and gameplay frame](CORE_OWNER.md), [projectile queues](CORE_QUEUES.md)
- [Board hits](GAMEPLAY_OWNER.md), [power-ups](POWERUPS_OWNER.md), [particles and bonus production](ENTITIES_OWNER.md)
- [Brick animations](EFFECTS_OWNER.md), [lightning and frame drawing](DISPLAY_OWNER.md)
- [Game lifecycle](RUNTIME_OWNER.md), [menu and splash](INTRO_OWNER.md), [startup UI](STARTUP_UI_OWNER.md)
- [Editor](EDITOR_OWNER.md), [game-over and high scores](GAMEOVER_OWNER.md)

## Graphics, resources and platform

- [Sprites, fonts, PCX and palettes](RESOURCE_OWNER.md), [bitmap loading](BITMAP_INVESTIGATION.md)
- [Software rasterization](RASTER_INVESTIGATION.md), [sprite rotation](ROTATION_INVESTIGATION.md)
- [Palette transitions and surface recovery](DEVICE_OWNER.md)
- [Windows startup and input](PLATFORM_OWNER.md), [Windows adapter](WINDOWS_ADAPTER.md)
- [DirectSound and WAV loading](SOUND_OWNER.md), [sound parameters](SOUND_CONTROLS.md), [MDS music](MIDI_OWNER.md)
- [Embedded resources](EMBEDDED_RESOURCES.md)

## Runtime and reconstruction method

- [Compiler matching](BUILD_MATCHING.md), [runtime dependencies](CRT_PROVENANCE.md)
- [Heap ownership](ALLOCATOR_OWNER.md), [CRT termination](TERMINATION_OWNER.md)
- [Dependency frontier](DEPENDENCY_FRONTIER.md), [origin audit](ORIGIN_AUDIT.md), [origin review](ORIGIN_REVIEW.md)
- [Target observations](KNOWLEDGE_BASE.md), [oracle matrix](ORACLES.md)

## Earlier live checks

- [Original-board campaign attempts](ORIGINAL_CAMPAIGN.md)
- [Round transition and focus diagnostics](ROUND_FOCUS_RUNTIME.md)
- [Terminal round and adjacent storage](TERMINAL_RUNTIME.md)
- [Original-backed input policy](CONTACT_POLICY.md)
