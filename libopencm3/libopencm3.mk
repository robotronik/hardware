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
LINKER  = $(HARDW_DIR)/stm32f4-discovery.ld

# Précise la carte cible
TARGET  =

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=0 --static \
	-DSTM32F4 -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16

LDFLAGS+= -L$(HARDW_DIR)/$(BUILD_DIR) -L$(HARDW_DIR)	\
		-T$(LINKER) -lopencm3_stm32f4 -lm -lc -lgcc -lnosys -nostartfiles

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"
CFLAGS += \
		-I$(HARDW_DIR)/include \
		-I$(HARDW_DIR)/libopencm3/include \
        -O3

################################################################################
#               Constantes de compilation

# Emplacement du fichier de config de OpenOCD
OPENOCD_CFG = /usr/share/openocd/scripts/board/stm32f4discovery.cfg


################################################################################
# Arch-dependant targets

HEX = $(BUILD_DIR)/$(EXEC).hex

$(HEX): $(BUILD_DIR)/$(EXEC)
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

