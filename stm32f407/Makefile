PROJECT=stm32f407
default: lib
# Default Options
export ARCH   = stm32f407
export DEBUG ?= _ALWAYS_

PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.rules

################################################################################
# Fichiers du projet


################################################################################
# Fichiers source
LIB_DIR = lib/
SRC_DIR = src/
SRC_S   = $(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
SRC     = $(shell find $(SRC_DIR) -name *.c)
OBJ     = $(addprefix $(BUILD_DIR)/, $(SRC:src/%.c=%.o) )
OBJ_S   = $(SRC_S:.s=.o)

#Librairies
LDFLAGS+=
CFLAGS += -Iheaders/

################################################################################
# Cibles du projet

_libHardware: $(BUILD_DIR)/libHardware.a

$(BUILD_DIR)/libHardware.a: $(OBJ) $(OBJ_S)

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

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

