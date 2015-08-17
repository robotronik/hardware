PROJECT=PC
default: lib
# Default Options
export ARCH   = PC
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
SRC     = UART.c
HDR     = $(shell find . -name "*.h")
OBJ     = $(addprefix $(BUILD_DIR)/, $(SRC:%.c=%.o) )

#Librairies
LDFLAGS+=
CFLAGS += -I.

################################################################################
# Cibles du projet

hardware-lib: $(BUILD_DIR)/lib$(ARCH).a

$(BUILD_DIR)/lib$(ARCH).a: $(OBJ) $(OBJ_S)



##### Compilation des sources
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $^

%.o: %.s
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $^

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p
