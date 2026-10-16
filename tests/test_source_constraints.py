"""Simple static assertions, not a PSP runtime test."""
from pathlib import Path
source = Path('src/main.c').read_text()
assembly = Path('src/hooks.S').read_text()
assert 'sceKernelDevkitVersion' not in source
assert source.count('sctrlHENFindFunction("sceWM1801_Driver"') == 2
assert '0x49C13ACFu' in source and '0xEACF7284u' in source
assert '0xB2BEADB8u' in source
assert 'INPUT_CEILING  6' in source and 'BOOST_STEPS    9' in source
assert '0x80->0xff' in source  # documentation only; no codec check bypass code
assert 'svm_headphone_entry' in assembly and 'svm_speaker_entry' in assembly
assert assembly.count('jal   svm_adjust_volume') == 2
assert assembly.count('j     svm_') == 2
print('PASS: exactly two codec hooks, no firmware gate or codec-range bypass')
