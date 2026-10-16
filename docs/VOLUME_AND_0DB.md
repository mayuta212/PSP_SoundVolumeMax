# Reaching the nominal “0 dB” codec setting

**On the observed PSP-3000 (04g), with AV cable disconnected:** from maximum volume, turn the **headphone down 3 steps** or the **built-in speaker down 5 steps**. These are derived estimates of a nominal codec-control 0 dB-equivalent, **not** an output level measurement or a guarantee of undistorted sound.

- Headphone at max−3: original codec argument `−9` → boosted by 9 → **0**.
- Speaker at max−5: original codec argument `−8` → `+1`, with the speaker path's observed one-step equivalent offset → **nominal 0 dB**.
- Maximum setting: the adjustment argument is clamped at `+6` (headphone nominal +6; speaker nominal +5 after offset). The software limit does **not** ensure no distortion or hardware safety.
- Explicit mute (`−127`) is preserved.

**Do not confuse** nominal internal gain with **0 dBFS** (full-scale digital peak), **0 dBu** (0.775 Vrms analog reference), or **dB SPL** (acoustic sound pressure). They are different quantities; this plugin measures none of them.

The observed XMB selection-tone level was approximately **−15 dB with AV connected** and **−10 dB on the boosted path**, according to the same test meter in one setup. This does not mean that adding +15 dB to every AV recording is safe: different content can clip. **AV-connected output is deliberately unchanged.** There is no universal in-plugin “make AV output 0 dBFS” setting. Adjust recording interface input gain with suitable headroom and monitor actual peaks/distortion instead.

See [external equipment safety](EXTERNAL_AUDIO_SAFETY.md) and the [full Japanese explanation](VOLUME_AND_0DB_ja.md).
