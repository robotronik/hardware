PROJECT=Simulation
default: hardware-lib
# Default Options
export ARCH   = PC
export DEBUG ?= _ALWAYS_

export PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.rules

################################################################################
# Fichiers du projet


################################################################################
# Fichiers source



_SRC    = $(shell find -name "*.c")
SRC 	= $(_SRC:./%=%)
HDR     = $($(shell find -name "*.h"):./%=%)
OBJ     = $(addprefix  $(BUILD_DIR)/, $(SRC:%.c=%.o) )
OBJ_LIB = $(filter-out $(BUILD_DIR)/main.o,$(OBJ))

#Librairies
CFLAGS += -I.  -Wno-deprecated
LDFLAGS+=

################################################################################
# Cibles du projet

_libHardware: $(BUILD_DIR)/libHardware.a

$(BUILD_DIR)/libHardware.a: $(OBJ_LIB) $(OBJ_S)

##### Compilation des sources
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $^

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p


simulation: $(OBJ)
#	@make -C $(ASSER_DIR) asser_robot
	@echo "	++	$(PROJECT)|$(notdir $@)"
	@$(++) $(CFLAGS) -o $@ $^ $(LDFLAGS)
