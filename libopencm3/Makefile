PROJECT=libopencm3
default: lib
# Default Options
export ARCH   = libopencm3
export ROBOT ?= gros
export SDL   ?= no
export DEBUG ?= _ALWAYS_

PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.mk

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
lib:
	@echo "Todo Lucien !"


$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

