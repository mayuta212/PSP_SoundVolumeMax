# Connecting PSP audio to headphones, speakers and external equipment

**The plugin boosts the headphone / internal-speaker codec volume request. It does not guarantee safe sound pressure, undistorted output, or a particular output voltage.**

### Internal speaker

Avoid sustained maximum-volume listening. If the built-in speaker buzzes, rattles or distorts, lower the volume immediately. A codec register ceiling is **not** a speaker safety limit.

### Headphones / earphones

For first playback or after changing plugins, keep headphones **off your ears**, set PSP volume low, and raise it slowly. Efficient earphones can become very loud quickly.

### Powered speakers, amplifiers, mixers or audio interfaces

1. Reduce external volume / input gain to **minimum**; mute or turn off the powered amp before connecting when practical.
2. Use a compatible **line input**. Never connect two outputs together, and do not drive passive loudspeakers directly from the PSP headphone jack.
3. Start playback at low PSP volume and raise the external volume / input gain **gradually**, watching for clipping or unexpectedly high levels.
4. Mute/reduce level before plugging and unplugging to avoid loud transients.
5. **Headphone output to a line input** may overload downstream equipment after boost. Reduce PSP volume or disable the plugin if needed.
6. **AV-cable output is not boosted by this plugin**, but the observed XMB tone at about −15 dB on the test meter is specific to one test, not a universal safe signal level.

An internal codec “0 dB-equivalent” does not imply 0 dBFS on an interface meter or 0 dBu at an analog output. See [the level explanation](VOLUME_AND_0DB.md).
