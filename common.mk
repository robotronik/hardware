# Permet d'inclure les headers "d'interface" des différents projets

# Le dossier parent des différents dépôts est PARENT_DIR et doit être fourni par les
# différents Makefile.

# Le dossier de build, dans chaque dépôt
export BUILD_DIR = build/$(ARCH)/$(DEBUG)

# Les différents projets
export ASSER_DIR = $(PARENT_DIR)/asservissement/
libAsser:
	@$(MAKE) -C $(ASSER_DIR) _libAsser

export STRAT_DIR = $(PARENT_DIR)/strategie/Robot_$(ROBOT)
libStrat:
	@$(MAKE) -C $(STRAT_DIR) _libStrat

export CARTO_DIR = $(PARENT_DIR)/cartographie/
libCarto:
	@$(MAKE) -C $(CARTO_DIR) _libCarto

export COMMU_DIR = $(PARENT_DIR)/common_code/communication/
libCommAsser:
	@$(MAKE) -C $(COMMU_DIR) _libCommAsser
libCommStrat:
	@$(MAKE) -C $(COMMU_DIR) _libCommStrat


export HARDW_DIR = $(PARENT_DIR)/hardware/$(ARCH)/
include $(HARDW_DIR)/$(ARCH).mk
libHardware:
	@$(MAKE) -C $(HARDW_DIR) _libHardware


export SIMU_DIR  = $(PARENT_DIR)/simulation/


################################################################################
# Architecture independent parameters

ifeq ($(ROBOT),petit)
	CFLAGS  += -DGROS=0 -DPETIT=1
else
	CFLAGS  += -DGROS=1 -DPETIT=0
endif

# Options de compilations
CFLAGS += -W -Wall $(TARGET) $(INCLUDE) -I$(HARDW_DIR) -I$(HARDW_DIR)/.. \
	-DDEBUG=$(DEBUG)

# Options pour l'édition de liens
LDFLAGS+= 	-L$(ASSER_DIR)/$(BUILD_DIR)/	\
			-L$(CARTO_DIR)/$(BUILD_DIR)/	\
			-L$(COMMU_DIR)/$(BUILD_DIR)/	\
			-L$(HARDW_DIR)/$(BUILD_DIR)/	\
			-L$(STRAT_DIR)/$(BUILD_DIR)/


################################################################################
# Common Rules

# Compile an object file
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(ARCH)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

# Compile a static library
$(BUILD_DIR)/%.a:
	@echo "	AR	$(PROJECT)|$(ARCH)|$(notdir $@)"
	@rm -f $@
	@$(AR) -r $@ $^
	@echo "	RANLIB	$(PROJECT)|$(ARCH)|$(notdir $@)"
	@$(RANLIB) $@

################################################################################
# Clean the current working directory
.PHONY: clean clean-all

clean:
	@echo "	Cleaning $(PROJECT) directory…"
	@rm -rf build/

clean-all:
	@make clean -C $(ASSER_DIR)
	@make clean -C $(CARTO_DIR)
	@make clean -C $(COMMU_DIR)
	@make clean -C $(HARDW_DIR)
	@make clean -C $(STRAT_DIR)
	@make clean -C $(SIMU_DIR)
