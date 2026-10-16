/* Small shared-ABI bridge. No firmware addresses or additional hooks.
 * The first two instructions of each original codec routine live in .text
 * trampolines, not in a possibly non-executable data buffer.
 * SPDX-License-Identifier: MIT
 */
    .set noreorder
    .set noat
    .text
    .align 4
    .globl svm_headphone_entry
    .ent svm_headphone_entry
svm_headphone_entry:
    addiu $sp, $sp, -48
    sw    $ra, 44($sp)
    sw    $gp, 40($sp)
    sw    $a0, 0($sp)
    sw    $a1, 4($sp)
    sw    $a2, 8($sp)
    sw    $a3, 12($sp)
    jal   svm_adjust_volume
    nop
    move  $a0, $v0
    lw    $a1, 4($sp)
    lw    $a2, 8($sp)
    lw    $a3, 12($sp)
    lw    $gp, 40($sp)
    lw    $ra, 44($sp)
    addiu $sp, $sp, 48
    j     svm_headphone_resume
    nop
    .end svm_headphone_entry

    .align 4
    .globl svm_speaker_entry
    .ent svm_speaker_entry
svm_speaker_entry:
    addiu $sp, $sp, -48
    sw    $ra, 44($sp)
    sw    $gp, 40($sp)
    sw    $a0, 0($sp)
    sw    $a1, 4($sp)
    sw    $a2, 8($sp)
    sw    $a3, 12($sp)
    jal   svm_adjust_volume
    nop
    move  $a0, $v0
    lw    $a1, 4($sp)
    lw    $a2, 8($sp)
    lw    $a3, 12($sp)
    lw    $gp, 40($sp)
    lw    $ra, 44($sp)
    addiu $sp, $sp, 48
    j     svm_speaker_resume
    nop
    .end svm_speaker_entry

    /* Self-modified RX code: original addiu SP, original SW in J delay slot. */
    .align 4
    .globl svm_headphone_resume
svm_headphone_resume:
    .word 0, 0, 0, 0
    .align 4
    .globl svm_speaker_resume
svm_speaker_resume:
    .word 0, 0, 0, 0
