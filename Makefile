PSPSDK := $(shell psp-config --pspsdk-path)
TARGET = SoundVolumeMax_minimal
OBJS = src/main.o src/hooks.o
CFLAGS = -O2 -G0 -Wall -Wextra -fno-pic -std=c99
ASFLAGS = -G0
BUILD_PRX = 1
PRX_EXPORTS = exports.exp
USE_KERNEL_LIBC = 1
USE_KERNEL_LIBS = 1
LDFLAGS = -nostartfiles
LIBS = -lpspsystemctrl_kernel
PSP_FW_VERSION = 661
include $(PSPSDK)/lib/build.mak
