#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
python3 tests/test_reference.py
python3 tests/test_source_constraints.py
python3 tests/test_hook_model.py
command -v psp-config >/dev/null || { echo 'PSPDEV (psp-config) not found' >&2; exit 2; }
command -v psp-gcc >/dev/null || { echo 'PSPDEV (psp-gcc) not found' >&2; exit 2; }
sdk="$(psp-config --pspsdk-path)"
test -f "$sdk/include/systemctrl.h" || { echo 'psp-cfw-sdk header missing' >&2; exit 2; }
test -f "$sdk/lib/libpspsystemctrl_kernel.a" || { echo 'psp-cfw-sdk library missing' >&2; exit 2; }
make clean
make
sha256sum SoundVolumeMax_minimal.prx | tee SoundVolumeMax_minimal.sha256
printf 'BUILT; NOT HARDWARE-TESTED: %s/SoundVolumeMax_minimal.prx\n' "$PWD"
