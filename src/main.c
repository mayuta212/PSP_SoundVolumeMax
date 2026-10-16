/* Sound Volume Max — minimal clean-room implementation for PSP CFW.
 * Reference behavior: user-verified SoundVolumeMax v1.0.0 on PSP-3000 04g.
 * SPDX-License-Identifier: MIT
 */
#include <pspkernel.h>
#include <pspsdk.h>
#include <systemctrl.h>

PSP_MODULE_INFO("SoundVolumeMaxMin", 0x1007, 2, 1);

/* Resolved by exported library NID, not by firmware version or fixed address. */
#define HP_NID         0x49C13ACFu
#define SP_NID         0xEACF7284u
#define CABLE_NID_660  0xB2BEADB8u
#define CABLE_NID_OLD  0xC1777D84u
#define BOOST_STEPS    9
#define INPUT_CEILING  6
#define MUTE_VALUE     (-127)

typedef int (*cable_getter_t)(void);

/* Assembly entries preserve original argument registers before calling C. */
extern void svm_headphone_entry(void);
extern void svm_speaker_entry(void);
extern unsigned int svm_headphone_resume[];
extern unsigned int svm_speaker_resume[];

static volatile unsigned int *hp_target;
static volatile unsigned int *sp_target;
static unsigned int hp_saved[2];
static unsigned int sp_saved[2];
static unsigned int hp_patch;
static unsigned int sp_patch;
static int installed;

/* This function is called only when Sony updates the codec volume, not per PCM sample.
 * No cable or an unknown cable state => fail closed to Sony's original request. */
int svm_adjust_volume(int original)
{
    cable_getter_t cable = (cable_getter_t)sctrlHENFindFunction(
        "sceHP_Remote_Driver", "sceHprm_driver", CABLE_NID_660);
    if (!cable)
        cable = (cable_getter_t)sctrlHENFindFunction(
            "sceHP_Remote_Driver", "sceHprm_driver", CABLE_NID_OLD);
    if (!cable || cable() != 0)
        return original;

    /* Keep the Sony table's explicit mute sentinel intact. */
    if (original <= MUTE_VALUE)
        return original;
    /* Avoid the invalid register values caused by the legacy 0x80->0xff patch. */
    if (original >= INPUT_CEILING - BOOST_STEPS)
        return INPUT_CEILING;
    return original + BOOST_STEPS;
}

static unsigned int make_j(unsigned int from, unsigned int dest)
{
    if ((from & 3u) || (dest & 3u)) return 0;
    if (((from + 4u) ^ dest) & 0xF0000000u) return 0;
    return 0x08000000u | ((dest >> 2u) & 0x03FFFFFFu);
}

/* Minimal structural check instead of exact firmware bytes.
 * First instruction: addiu sp,sp,-frame (16..512, 16-byte aligned).
 * Second instruction: sw register,offset(sp) inside frame.
 * Both are position independent and can be safely relocated to a J delay slot. */
static int relocatable_prologue(unsigned int a, unsigned int b)
{
    unsigned int frame, offset;
    if ((a & 0xFFFF0000u) != 0x27BD0000u) return 0;
    frame = (unsigned int)(-(short)(a & 0xffffu));
    if (frame < 16 || frame > 512 || (frame & 15u)) return 0;
    if ((b & 0xFFE00000u) != 0xAFA00000u) return 0;
    offset = b & 0xffffu;
    return (offset <= frame - 4u) && ((offset & 3u) == 0);
}

static int kernel_address(unsigned int addr)
{
    return !(addr & 3u) && addr >= 0x88000000u && addr < 0xC0000000u;
}

static void cache_sync(void)
{
    sceKernelDcacheWritebackInvalidateAll();
    sceKernelIcacheClearAll();
}

static void setup_resume(unsigned int *resume, const unsigned int saved[2],
                         unsigned int target_addr)
{
    resume[0] = saved[0];
    resume[1] = make_j((unsigned int)&resume[1], target_addr + 8u);
    resume[2] = saved[1];   /* original second instruction executes as J delay slot */
    resume[3] = 0;
}

int module_start(SceSize argc, void *argv)
{
    unsigned int hp, sp;
    unsigned int hreturn, sreturn;
    int irq;
    (void)argc; (void)argv;

    /* Same two Sony codec routes as the working legacy PRX. */
    hp = sctrlHENFindFunction("sceWM1801_Driver", "sceCodec_driver", HP_NID);
    sp = sctrlHENFindFunction("sceWM1801_Driver", "sceCodec_driver", SP_NID);
    if (!kernel_address(hp) || !kernel_address(sp) || hp == sp) return 1;

    hp_target = (volatile unsigned int *)hp;
    sp_target = (volatile unsigned int *)sp;
    hp_saved[0] = hp_target[0]; hp_saved[1] = hp_target[1];
    sp_saved[0] = sp_target[0]; sp_saved[1] = sp_target[1];
    if (!relocatable_prologue(hp_saved[0], hp_saved[1]) ||
        !relocatable_prologue(sp_saved[0], sp_saved[1])) return 1;

    hp_patch = make_j(hp, (unsigned int)svm_headphone_entry);
    sp_patch = make_j(sp, (unsigned int)svm_speaker_entry);
    hreturn = make_j((unsigned int)&svm_headphone_resume[1], hp + 8u);
    sreturn = make_j((unsigned int)&svm_speaker_resume[1], sp + 8u);
    if (!hp_patch || !sp_patch || !hreturn || !sreturn) return 1;

    /* Fill code trampolines BEFORE redirecting Sony code to this module. */
    setup_resume(svm_headphone_resume, hp_saved, hp);
    setup_resume(svm_speaker_resume, sp_saved, sp);
    cache_sync();

    irq = sceKernelCpuSuspendIntr();
    if (hp_target[0] != hp_saved[0] || hp_target[1] != hp_saved[1] ||
        sp_target[0] != sp_saved[0] || sp_target[1] != sp_saved[1]) {
        sceKernelCpuResumeIntr(irq);
        return 1;
    }
    hp_target[0] = hp_patch; hp_target[1] = 0;
    sp_target[0] = sp_patch; sp_target[1] = 0;
    cache_sync();
    installed = 1;
    sceKernelCpuResumeIntr(irq);
    return 0;
}

int module_stop(SceSize argc, void *argv)
{
    int irq;
    (void)argc; (void)argv;
    if (!installed) return 0;
    irq = sceKernelCpuSuspendIntr();
    /* If another plugin has chained a hook, do not overwrite it or unload. */
    if (hp_target[0] != hp_patch || hp_target[1] != 0 ||
        sp_target[0] != sp_patch || sp_target[1] != 0) {
        sceKernelCpuResumeIntr(irq);
        return 1;
    }
    hp_target[0] = hp_saved[0]; hp_target[1] = hp_saved[1];
    sp_target[0] = sp_saved[0]; sp_target[1] = sp_saved[1];
    cache_sync();
    installed = 0;
    sceKernelCpuResumeIntr(irq);
    return 0;
}
