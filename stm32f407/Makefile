PROJECT=stm32f407
default: all
# Default Options
export ARCH   = stm32f407
export ROBOT ?= gros
export SDL   ?= no
export DEBUG ?= _ALWAYS_

export PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.mk

################################################################################
# Fichiers du projet


################################################################################
# Fichiers source
LIB_DIR = lib/
SRC_DIR = src/
HDR_DIR = headers/
SRC_S   = $(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
SRC     = $(shell find $(SRC_DIR) -name *.c)
HDR     = $(shell find $(HDR_DIR) -name *.h)
OBJ     = $(addprefix $(BUILD_DIR)/, $(SRC:src/%.c=%.o) )
OBJ_S   = $(SRC_S:.s=.o)

#Librairies
LDFLAGS+= -lHAL_Driver -lCMSIS -lBSP

################################################################################
# Cibles du projet

all: lib$(ARCH).a

lib$(ARCH).a: $(OBJ) $(OBJ_S)


##### Compilation des sources
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $^

%.o: %.s
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $^


##### Compilation des librairies
lib: $(LIB_DIR)libBSP.a $(LIB_DIR)libCMSIS.a $(LIB_DIR)libHAL_Driver.a

lib/%.a:
	@$(MAKE) -C $(LIB_DIR)






#all: $(HEX)
#	@echo "La compil' est terminée, la coupe est à nous !"

#%.hex: %.elf
#	@$(OBJ2HEX) -Oihex $^ $@


$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p



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


################################################################################
# Cibles génériques

mrproper: clean
	@echo "Hard-cleaning $(PROJECT) directory…"
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) clean -C $(COMMUNICATION_DIR)
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) clean -C $(COMMON_DIR)
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) clean -C $(CARTO_DIR)
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) clean -C $(STRAT_DIR)/Robot2A
