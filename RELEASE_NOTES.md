# Minimal alpha1 — GitHub source publication

**Status: hardware-tested alpha; source-only archive.**

- Independent C/MIPS assembly implementation focused on exactly two codec volume hooks, without FW runtime-number gates.
- Verified on PSP-3000 (04g) / ARK-5 in the reported environment: internal speaker boost, headphone boost, AV-bypass after reconnection.
- AV connection keeps Sony's requested gain; headphone/speaker code is bounded and explicit mute preserved.
- Added bilingual README and separate guides for nominal codec 0 dB settings and safe connection to powered speakers, amplifiers and recording interfaces.
- Working implementation (`src/`, `Makefile`, `exports.exp` and all three Python tests) unchanged from the tested Minimal alpha1 source package.
- Binary **not enclosed**: recorded user-generated PRX hash `5a322c22bd2658cdd6ed6118cde592e7ea11584c4917e23ae34446b20530f465`.
- Other FW/models remain unverified. Do not infer broad compatibility from a single successful device.
