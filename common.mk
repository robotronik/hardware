# Permet d'inclure les headers "d'interface" des différents projets

# Le dossier parent des différents dépôts est PARENT_DIR et doit être fourni par les
# différents Makefile.

# Options de compilations
CFLAGS += -W -Wall -std=c99 $(TARGET) $(INCLUDE) -DDEBUG=$(DEBUG)

# Options pour l'édition de liens
LDFLAGS+= -W -Wall -std=c99

# Les différents projets
export ASSER_DIR = $(PARENT_DIR)/asservissement/
export STRAT_DIR = $(PARENT_DIR)/strategie/
export CARTO_DIR = $(PARENT_DIR)/cartographie/

export HARDW_DIR = $(PARENT_DIR)/hardware/

export COMMON_DIR= $(PARENT_DIR)/common_code/
export COMMUNICATION_DIR= $(COMMON_DIR)/communication/
export STM32_DIR = $(HARDW_DIR)/stm32f407/

# Le dossier de build, dans chaque dépôt
export BUILD_DIR = build/$(ARCH)/$(DEBUG)

################################################################################
# Architecture dependent parameters

export HARDW_LIB = $(HARDW_DIR)/$(ARCH)/lib$(ARCH).a

include $(HARDW_DIR)/$(ARCH).mk


################################################################################
# Common Rules

hardware_lib: $(HARDW_LIB)
	cd $(ARCH) && make -C lib$(ARCH).a


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

################################################################################
# Clean the current working directory
.PHONY: clean mrproper

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@rm -rf build/
# clean:
# 	@echo "Cleaning $(PROJECT) directory…"
# 	@find $(BUILD_DIR) -name '*.o' -delete
# 	@find $(BUILD_DIR) -name '*.a' -delete
# 	@rmdir -p --ignore-fail-on-non-empty $(BUILD_DIR)/*/* 2>/dev/null || true
