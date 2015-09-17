PROJECT=Simulation
default: hardware-lib
# Default Options
export ARCH   = PC
export ROBOT ?= gros
export SDL   ?= yes
export DEBUG ?= _ALWAYS_

export PARENT_DIR = ../../
include $(PARENT_DIR)/hardware/common.mk

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

hardware-lib: $(BUILD_DIR)/lib$(ARCH).a

$(BUILD_DIR)/lib$(ARCH).a: $(OBJ_LIB) $(OBJ_S)

##### Compilation des sources
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $^

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p


run: simulation
	./simulation


simulation: $(OBJ)
#	@make -C $(ASSER_DIR) asser_robot
	@echo "	++	$(PROJECT)|$(notdir $@)"
	@$(++) $(CFLAGS) -o $@ $^ $(LDFLAGS)
