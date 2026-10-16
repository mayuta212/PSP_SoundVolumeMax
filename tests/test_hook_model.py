"""Check relocation model against extracted PSP-3000 04g 6.61 prologues."""

def prologue(a, b):
    if a & 0xffff0000 != 0x27bd0000: return False
    frame = (-((a & 0xffff) - 0x10000 if a & 0x8000 else a & 0xffff)) & 0xffffffff
    if frame < 16 or frame > 512 or frame & 15: return False
    if b & 0xffe00000 != 0xafa00000: return False
    offset = b & 0xffff
    return offset <= frame - 4 and offset & 3 == 0

def jump(frm, dst):
    if frm & 3 or dst & 3 or (frm+4 ^ dst) & 0xf0000000: return None
    return 0x08000000 | ((dst >> 2) & 0x03ffffff)

assert prologue(0x27bdffe0, 0xafb3000c)   # HP
assert prologue(0x27bdfff0, 0xafb10004)   # speaker
assert prologue(0x27bdffc0, 0xafbf003c)   # common alternative valid prologue
assert not prologue(0x03e00008, 0)          # JR
assert not prologue(0x27bdffe0, 0x8fb3000c)  # load not store
assert not prologue(0x27bdfff0, 0xafb10020)  # outside frame
assert jump(0x8800058c, 0x88801000) == 0x0a200400
assert jump(0x8800058c, 0x08801000) is None
assert jump(0x8800058c, 0x88801001) is None
print('PASS: known 04g prologues and MIPS J relocation model')
