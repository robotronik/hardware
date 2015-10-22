################################################################################
# Makefile générique, appelé par la lib et les projets parallèles
################################################################################
# Compilateur C et linker
CC      = arm-none-eabi-gcc -std=c99
AR      = arm-none-eabi-ar
RANLIB  = arm-none-eabi-ranlib
GDB     = arm-none-eabi-gdb
LD      = arm-none-eabi-ld
OBJ2HEX = arm-none-eabi-objcopy
LINKER  = $(STM32Cube)/Projects/STM32F4-Discovery/Templates/TrueSTUDIO/STM32F4-Discovery/STM32F407VG_FLASH.ld

# Précise la carte cible
TARGET  = 

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=0 \
	-mthumb -mcpu=cortex-m4 -DSTM32F407xx	\
	-mfloat-abi=hard -mfpu=fpv4-sp-d16		\
	-fno-builtin-sscanf -fdata-sections -Wl,--gc-sections


LDFLAGS+= -T$(LINKER) -Wl,--gc-sections -lc -lrdimon \
		  -lHAL_Driver -lCMSIS -lBSP -L$(HARDW_DIR)/lib/

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"
CFLAGS +=   $(shell find $(STM32Cube)/Drivers/ -path "*" -printf "-I%h/\n" | sort -u)  \
            -O3

################################################################################
#               Constantes de compilation

# Emplacement des librairies STM32CubeF4
STM32Cube   = $(abspath $(HARDW_DIR)/lib/STM32Cube)/
# Emplacement du fichier de config de OpenOCD
OPENOCD_CFG = $(abspath $(HARDW_DIR)/lib/openocd/stm32f4discovery.cfg)


################################################################################
# Arch-dependant targets

%.hex:
	@echo "	HEX	$(PROJECT)|$@"
	@$(OBJ2HEX) -Oihex $^ $@

##### Envoi du binaire sur le STM32
flash: $(HEX)
	@echo ""
	@echo "Flashing the STM32 Discovery Board !"
	@echo ""
	@sudo openocd -f $(OPENOCD_CFG) \
		-c "init" \
		-c "reset init" \
		-c "flash write_image erase $^" \
		-c "reset" \
		-c "shutdown"

##### Débug
debug:
	debug1
	debug2

debug1:
	xterm -e "openocd -f ./lib/openocd/stm32f4discovery.cfg" &

debug2:
	$(GDB) $(ELF) \
		--eval-command="target remote localhost:3333" \
		--eval-command="monitor reset halt" \
		--eval-command="load" \
		--eval-command="b main" \
		--eval-command="c"

