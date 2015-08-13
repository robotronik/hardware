# Permet d'inclure les headers "d'interface" des différents projets

# Le dossier parent des différents dépôts est PARENT_DIR et doit être fourni par les
# différents Makefile.

# Options de compilations
CFLAGS += -W -Wall -std=c99 $(TARGET) $(INCLUDE) -DDEBUG=$(DEBUG)

# Options pour l'édition de liens
LDFLAGS+= -W -Wall -std=c99

# Les différents projets
export ASSER_DIR = $(PARENT_DIR)/asservissement/
export CARTO_DIR = $(PARENT_DIR)/cartographie/
export COMMON_DIR= $(PARENT_DIR)/common_code/
export COMMUNICATION_DIR= $(COMMON_DIR)/communication/
export HARDW_DIR = $(PARENT_DIR)/hardware/

export STRAT_DIR = $(PARENT_DIR)/strategie/Robot_$(ROBOT)

# Le dossier de build, dans chaque dépôt
export BUILD_DIR = build/$(ARCH)/$(DEBUG)

################################################################################
# Architecture dependent parameters
export HARDW_LIB_DIR = $(HARDW_DIR)/$(ARCH)/
export HARDW_LIB = $(HARDW_LIB_DIR)/$(BUILD_DIR)/lib$(ARCH).a

include $(HARDW_DIR)/$(ARCH)/$(ARCH).mk

################################################################################
# Common Rules

hardware_lib:
	make -C $(HARDW_LIB_DIR) $(BUILD_DIR)/lib$(ARCH).a


# Compile an object file
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

# Compile a static library
%.a:
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@rm -f $@
	@$(AR) -r $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

################################################################################
# Clean the current working directory
.PHONY: clean mrproper clean-all

clean:
	@echo "	Cleaning $(PROJECT) directory…"
	@rm -rf build/

clean-all:
	@make clean -C $(ASSER_DIR)
	@make clean -C $(CARTO_DIR)
	@make clean -C $(COMMON_DIR)
	@make clean -C $(COMMUNICATION_DIR)
	@make clean -C $(HARDW_LIB_DIR)
	@make clean -C $(STRAT_DIR)

