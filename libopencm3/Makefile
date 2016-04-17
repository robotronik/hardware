PROJECT=libopencm3
default: hardware-lib
# Default Options
export ARCH   = libopencm3
export DEBUG ?= _ALWAYS_

PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.rules

################################################################################
# Fichiers du projet


################################################################################
# Fichiers source
LIB_DIR = lib/
SRC_DIR = src/
SRC     = $(shell find $(SRC_DIR) -name *.c)
OBJ     = $(addprefix $(BUILD_DIR)/, $(SRC:src/%.c=%.o) )

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


##### Compilation des librairies
lib-stm32f4:
	@$(MAKE) -C libopencm3 lib/stm32/f4
	cp libopencm3/lib/libopencm3_stm32f4.a  .
	cp libopencm3/lib/libopencm3_stm32f4.ld .

lib-stm32f0:
	@$(MAKE) -C libopencm3 lib/stm32/f0
	cp libopencm3/lib/libopencm3_stm32f0.a  .
	cp libopencm3/lib/libopencm3_stm32f0.ld .

hardware-lib: lib-stm32f4 lib-stm32f0 | $(BUILD_DIR)


$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

