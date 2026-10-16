# Sound Volume Max — Minimal

A minimal, independently written PSP custom-firmware (CFW) volume plugin inspired by the behavior of neur0n's historical **Audio Boost**. It hooks **only two** codec volume functions: headphone and built-in speaker. No firmware-number gate, extra audio-route hooks, polling thread, or PCM modification.

**Status: hardware-tested alpha (Minimal alpha1).** A user-built PRX has been tested successfully on a **PSP-3000 (04g), reported 6.61 / ARK-5 environment**: both headphone and built-in speaker volume increased; the AV-connected XMB selection tone remained around **−15 dB on the test meter** and behaved the same after unplug/replug. This observation does **not** establish support for all PSP models or firmwares, or a universal analog output level.

**[日本語 README](README_ja.md)** · [0 dB reference / how to set it](docs/VOLUME_AND_0DB.md) · [Safe use with external equipment](docs/EXTERNAL_AUDIO_SAFETY.md)

## Behavior

- **AV cable not connected:** codec argument `min(original + 9, +6)`, preserving the `−127` explicit mute value.
- **AV cable connected / status unavailable:** pass Sony's original argument unchanged.
- Resolve the two codec functions by NID at runtime, and patch only if the function prologues are compatible with the supported relocation pattern. Unsupported layouts are **not** patched.
- These are *codec register-control values*, **not dBFS, dBu, output voltage, SPL, distortion, or safe listening limits**.

## How to reach the *nominal codec 0 dB setting*

On the analyzed PSP-3000 **04g** volume table, in the **AV-disconnected** case:

| Output | PSP volume setting (count down from the maximum) | Interpretation |
| --- | --- | --- |
| Headphones | **3 steps below maximum** | Calculated codec-control equivalent of approximately 0 dB |
| Internal speaker | **5 steps below maximum** | Approximately 0 dB after the speaker path's one-step offset |

This is **NOT** a way to produce **0 dBFS** in a recorder or **0 dBu** at a physical output. At the maximum setting the calculated control references are about **+6** (headphone) and **+5** (speaker), without claims about clean or safe acoustic power. More details and limitations: [VOLUME_AND_0DB.md](docs/VOLUME_AND_0DB.md).

**AV output is deliberately not boosted.** The observed `−15 dB (meter reading)` XMB tone is content- and measurement-specific; this plugin cannot be used to make AV output universally 0 dBFS.

## Installation (CFW / ARK-5)

1. Back up your previously working volume plugin; turn off other plugins modifying codec/volume.
2. Copy your built **`SoundVolumeMax_minimal.prx`** to `ms0:/SEPLUGINS/` (or the appropriate storage path for your model).
3. Enable this PRX for **VSH only** for the first test using ARK-5's plugin manager or its corresponding plugin configuration.
4. Fully power off, restart, and **start at the lowest available volume**, with headphones **off the ears** and external amplifiers turned down.
5. Test volume adjustment and mute. If anything goes wrong, disable the plugin and cold-restart. Do not hot-unload a live kernel-hook plugin.

No Flash0 writes are required. See [external equipment safety](docs/EXTERNAL_AUDIO_SAFETY.md) before connecting to powered speakers, amplifiers, headphones or recording devices.

## Build with Ubuntu / WSL

Requires [PSPDEV](https://github.com/pspdev/pspdev), `psp-cfw-sdk`, `make`, and Python 3. The build wrapper locates the installed CFW SDK through `psp-config --pspsdk-path`.

```bash
cd /mnt/c/Users/hujay/Downloads/SoundVolumeMax_GitHub_alpha1
bash build_wsl.sh
```

For other installations, run `bash build_wsl.sh` from the repository root. Expected output: `SoundVolumeMax_minimal.prx` and `SoundVolumeMax_minimal.sha256`. The build script's generic `NOT HARDWARE-TESTED` message is a reminder that **each build artifact** needs validation; the specific alpha1 user-built artifact listed below has been tested.

### Reproducibility / verified build

The tested user's PSPDEV GCC 15.2.0 build reported this SHA-256:

```text
5a322c22bd2658cdd6ed6118cde592e7ea11584c4917e23ae34446b20530f465  SoundVolumeMax_minimal.prx
```

The tested PRX is **not included** in this source repository or source ZIP, because its bytes were not supplied for packaging. Do not treat a CI build or another machine's output as hardware-tested merely because the source is the same. Release a binary only after verifying its hash or testing that exact binary.

## Validation / compatibility

- Source tests: 3/3 PASS; user's PSPDEV compilation, linking and `psp-prxgen` completed with no warnings in the recorded alpha1 build.
- Hardware: headphone boost, speaker boost and AV bypass after cable reconnection **reported PASS on one PSP-3000 (04g)**.
- Other hardware / firmware revisions: **not verified**. Runtime lookup is *not* a guarantee of cross-firmware compatibility.
- Run tests locally with `python3 tests/test_reference.py && python3 tests/test_source_constraints.py && python3 tests/test_hook_model.py`; GitHub Actions runs those **source tests**, not real PSP hardware tests.

## Provenance and license

This repository is an independently authored source implementation inspired by observed behavior and exported interfaces. neur0n's original Audio Boost plugin is **credited but not bundled**; its original license is not sufficiently confirmed to redistribute its code or PRX. See [NOTICE.md](NOTICE.md). Newly authored source in this repository is released under the [MIT License](LICENSE). No original PRX, binary patch, or firmware dump is included.
