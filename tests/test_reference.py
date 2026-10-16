"""Reference model: last seven positions of observed Sony 04g volume tables.

Not a measurement of amplifier voltage, distortion or all 31 table contents.
"""
HP_LAST7 = {24: 15, 25: 13, 26: 11, 27: 9, 28: 7, 29: 5, 30: 3}
SP_LAST7 = {24: 9, 25: 8, 26: 7, 27: 6, 28: 5, 29: 4, 30: 3}

def adjust(original, cable):
    if cable != 0 or original <= -127:
        return original
    return min(original + 9, 6)

assert len(HP_LAST7) == len(SP_LAST7) == 7
assert list(HP_LAST7) == list(SP_LAST7) == list(range(24, 31))
for value in list(HP_LAST7.values()) + list(SP_LAST7.values()):
    original = -value
    assert adjust(original, 1) == original  # AV connected
    assert adjust(original, -1) == original # unknown state
    assert adjust(original, 0) == min(original + 9, 6)
assert adjust(-127, 0) == -127
assert adjust(-9, 0) == 0       # headphone max-3
assert adjust(-8, 0) == 1       # speaker max-5, minus speaker's 1-step offset
assert adjust(-3, 0) == 6       # max input register-safe ceiling
assert adjust(2, 0) == 6
print('PASS: 04g final 7/31 table positions, +9/clamp +6, mute, AV bypass')
