################################################################################
# Makefile générique, appelé par la lib et les projets parallèles
# Default Options
#export ARCH  = STM32F407
#export ROBOT
#export SDL
#export DEBUG
STM32_DIR = $(HARDW_LIB_DIR)
################################################################################
# Compilateur C et linker
CC      = arm-none-eabi-gcc
AR      = arm-none-eabi-ar
RANLIB  = arm-none-eabi-ranlib
GDB     = arm-none-eabi-gdb
LD      = arm-none-eabi-ld
OBJ2HEX = arm-none-eabi-objcopy
LINKER  = $(STM32Cube)/Projects/STM32F4-Discovery/Templates/TrueSTUDIO/STM32F4-Discovery/STM32F407VG_FLASH.ld

# Précise la carte cible
TARGET  = -mcpu=cortex-m4 -DSTM32F407xx

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=0 -mthumb -mfloat-abi=soft -mlittle-endian -fno-builtin-printf \
-fno-builtin-sscanf -fdata-sections -Wl,--gc-sections
#-mthumb-interwork
LDFLAGS+= -T$(LINKER) -Wl,--gc-sections -lc -lrdimon -lHAL_Driver -lCMSIS -lBSP -L$(STM32_DIR)/lib/

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"
CFLAGS +=   $(shell find $(STM32Cube)/Drivers/ -path "*" -printf "-I%h/\n" | sort -u)  \
            $(shell find $(STM32_DIR)/headers/ -path "*" -printf "-I%h/\n" | sort -u)  \

ifeq ($(ROBOT),petit)
	CFLAGS  += -DGROS=0 -DPETIT=1
else
	CFLAGS  += -DGROS=1 -DPETIT=0
endif

################################################################################
#               Constantes de compilation

# Emplacement des librairies STM32CubeF4
STM32Cube   = $(abspath $(STM32_DIR)/lib/STM32Cube)/
# Emplacement du fichier de config de OpenOCD
OPENOCD_CFG = $(abspath $(STM32_DIR)/lib/openocd/stm32f4discovery.cfg)


################################################################################
# Arch-dependant targets

##### Envoi du binaire sur le STM32
flash: $(HEX)
	@echo ""
	@echo "Flashing the STM32 Discovery Board !"
	@echo ""
	@sudo openocd -f $(OPENOCD_CFG) \
		-c "init" \
		-c "reset init" \
		-c "flash write_image erase $(HEX)" \
		-c "reset" \
		-c "shutdown"
