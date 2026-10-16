# Validation and release evidence — Minimal alpha1

## Confirmed by user on 2026-10-16 (Japan)

- Platform: PSP-3000 (04g), ARK-5, user-described FW 6.61 environment.
- Build host: WSL Ubuntu; PSPDEV `psp-gcc (GCC) 15.2.0`, `psp-cfw-sdk` installed.
- Build steps: Python tests 3/3 PASS; C and assembler compilation, PRX link, `psp-fixup-imports`, `psp-prxgen` completed without warnings in the final alpha1 build log.
- Generated PRX path: `SoundVolumeMax_Minimal/SoundVolumeMax_minimal.prx`.
- User-reported SHA-256: `5a322c22bd2658cdd6ed6118cde592e7ea11584c4917e23ae34446b20530f465`.
- Hardware result: **internal speaker louder, headphones louder, AV output selection-tone ~−15 dB (meter reading), same after unplug/replug**.

## Scope / limitations

- This is a record of **one hardware/test environment** and one user-reported build hash; no claim that a file matching it is enclosed here.
- Measured tone peaks and codec-control values are not output voltage, THD, safe listening level or maximum output power measurements.
- This repository has **not** been validated on every FW revision, PSP hardware revision, PSP Go, POPS, games, or plugin combinations.
- GitHub Actions checks source-model tests, not a PSP hardware test. Do not equate green CI with proven functionality on a device.
- Binary artifact **not included** in source repo; source and basic test files are byte-for-byte copied from the working alpha1 source ZIP. The user-built PRX was not available to embed.

## Release procedure for binary assets

1. On a known PSPDEV environment run `bash build_wsl.sh`.
2. Compare the PRX checksum with the known tested hash **where build inputs are identical**. Different compiler/toolchain versions may produce different bytes.
3. If hash differs, do not describe that new binary as the verified one until it has been tested on hardware.
4. Verify device model, AV bypass, speaker/headphone boost, mute and unplug/replug before promoting beyond alpha.
5. Do not distribute the historical Audio Boost PRX or patched derivatives; this repo is source-only.
