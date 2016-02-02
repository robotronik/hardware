################################################################################
# Makefile générique, appelé par la lib et les projets parallèles
################################################################################
# Compilateur C et linker

CROSS_COMPILE ?= arm-uclinuxeabi-
CFLAGS += -march=armv7-m -mtune=cortex-m4 -mlittle-endian -mthumb -ffast-math
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -fno-common --param max-inline-insns-single=1000
CFLAGS += -Wl,-elf2flt=-s -Wl,-elf2flt=16384

CC      = $(CROSS_COMPILE)gcc -std=c99
++		  = $(CROSS_COMPILE)g++ -std=c++11
AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib
GDB     = $(CROSS_COMPILE)gdb
LD      = $(CROSS_COMPILE)ld
OBJ2HEX =
LINKER  =

# Précise la carte cible
TARGET  =

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=0 -Os -g

LDFLAGS+= -Wl,--gc-sections -lm

#	-Wl,--gc-sections – enable garbage collection of unused input sections

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"



ifeq ($(SDL),yes)
	CFLAGS  += -DUSE_SDL=1 -Wno-deprecated
	LDFLAGS +=
endif

# Exécution pour le PC.
run: $(BUILD_DIR)/$(EXEC)
	$^
