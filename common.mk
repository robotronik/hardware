# Permet d'inclure les headers "d'interface" des différents projets

# Le dossier parent des différents dépôts est PARENT_DIR et doit être fourni par les
# différents Makefile.

# Le dossier de build, dans chaque dépôt
export BUILD_DIR = build/$(ARCH)/$(DEBUG)

# Les différents projets
export ASSER_DIR = $(PARENT_DIR)/asservissement/


export STRAT_DIR = $(PARENT_DIR)/strategie/Robot_$(ROBOT)


export CARTO_DIR = $(PARENT_DIR)/cartographie/
export CARTO_LIB = $(CARTO_DIR)/libCartographie.a
libCarto:
	@$(MAKE) -C $(CARTO_DIR) _libCarto


export COMM_DIR = $(PARENT_DIR)/common_code/communication/
export COMM_LIB_ASSER = $(COMM_DIR)/$(BUILD_DIR)/libCommAsser.a
export COMM_LIB_STRAT = $(COMM_DIR)/$(BUILD_DIR)/libCommStrat.a
libCommAsser:
	@$(MAKE) -C $(COMM_DIR) _libCommAsser
libCommStrat:
	@$(MAKE) -C $(COMM_DIR) _libCommStrat


export HARDW_DIR = $(PARENT_DIR)/hardware/$(ARCH)/
export HARDW_LIB = $(HARDW_DIR)/$(BUILD_DIR)/libHardware.a
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
LDFLAGS+= 	-L$(HARDW_DIR)/$(BUILD_DIR)/	\
			-L$(CARTO_DIR)/$(BUILD_DIR)/	\
			-L$(COMM_DIR)/$(BUILD_DIR)/


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
.PHONY: clean mrproper clean-all

clean:
	@echo "	Cleaning $(PROJECT) directory…"
	@rm -rf build/

clean-all:
	@make clean -C $(ASSER_DIR)
	@make clean -C $(CARTO_DIR)
	@make clean -C $(COMM_DIR)
	@make clean -C $(HARDW_DIR)
	@make clean -C $(STRAT_DIR)
	@make clean -C $(SIMU_DIR)

mrproper-all:
	@make mrproper -C $(ASSER_DIR)
	@make mrproper -C $(CARTO_DIR)
	@make mrproper -C $(COMM_DIR)
	@make mrproper -C $(HARDW_DIR)
	@make mrproper -C $(STRAT_DIR)
	@make mrproper -C $(SIMU_DIR)
