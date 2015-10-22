PROJECT=dsPIC33F
default: hardware-lib
# Default Options
export ARCH   = dsPIC33F
export ROBOT ?= gros
export SDL   ?= no
export DEBUG ?= _ALWAYS_

PARENT_DIR = ../../

include $(PARENT_DIR)/hardware/common.mk

################################################################################
# Fichiers du projet


################################################################################
# Fichiers source

SRC     = placebo.c
OBJ     = $(addprefix $(BUILD_DIR)/, $(SRC:%.c=%.o) )

#Librairies
LDFLAGS+=
CFLAGS += -I.

################################################################################
# Cibles du projet

_libHardware: $(BUILD_DIR)/libHardware.a

$(BUILD_DIR)/libHardware.a: $(OBJ)

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

