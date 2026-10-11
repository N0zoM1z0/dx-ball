# Current VC4 digital sound delivery

The current VC4 game delivers nonzero stereo audio to the host PulseAudio
service during the ongoing original-bank campaign. This adds actual backend
evidence to the [sound owner](SOUND_OWNER.md); no game rebuild or new exact/
semantic acceptance is involved. Physical playback, original-equivalent mixing
and asynchronous MIDI remain unverified.

The observed game executable SHA-256 is
`7c44dc20c84a7b3c96670200c6a772b1a9263b85c44e58cd057dd0864292a551`.
Its Linux PID, boot ID and process start ticks agree with the existing campaign
identity before and after recording. PulseAudio identifies that same PID as
the owner of one uncorked, unmuted sink input on
`dxball_reconstruction_silent`. Another application also uses this sink.
The recorder selects the game's individual input with `--monitor-stream`,
alongside the sink's monitor source. It makes no target writes or routing changes.

The installed `parec`/`pacat` binary is hashed. Explicit `--record`,
`--format=float32le`, `--rate=44100`, `--channels=2`, `--no-remix` and
`--no-remap` describe the retained host samples. The game input itself reports
float32 stereo at44100Hz. Six seconds of wall observation yield
5.948458 seconds of complete stereo frames:

| Channel index | Finite samples | Nonzero samples | Peak absolute amplitude | RMS |
| --- | ---: | ---: | ---: | ---: |
| 0 | 262,327 | 44,651 | 1.0 | 0.101348 |
| 1 | 262,327 | 44,539 | 1.0 | 0.071733 |

These samples establish signal presence from the selected game stream. They
are host floating PCM after Wine/Pulse conversion, not original WAV bytes or
a synchronized original/source comparison. No waveform, clipping, pan,
frequency, latency, every-voice or physical-speaker fidelity claim follows.
The recorder exits0 after the observation interval; the campaign game continues.

The original2,098,616 PCM bytes have SHA-256
`999f94181be9ada3ce66a23fba20573e13666cbc802a7174c21caedaa03059e0`.
Byte-exact gzip decompression is verified before removing the raw copy;
the retained compressed file is199,929bytes. No extra gameplay run or other
application's audio is recorded.

Private `.analysis/current-vc40-campaign/audio-monitor*` retains the driver,
before/after routing identities, PCM gzip, complete statistics and logs.
One local Pulse schema preflight failed before launching a recorder; its source
and traceback are preserved separately. The corrected driver performs the
single completed recording. `audio-compression.json` preserves both content
digests. `audio-verification.json` verifies the PCM, tool/driver identity,
unchanged products and input closures. The independent completed seal is
`.analysis/checkpoints/current-digital-audio-285-206/sha256.json`.

The full50-board campaign is a separate live task. Its runtime files and REA
capture must remain until that producer terminates. Only immutable audio seal/
before duplicates are shared with the immediately preceding game-over seal;
current/public files remain independent of archives.
