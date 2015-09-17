# Permet d'inclure les headers "d'interface" des différents projets

# Le dossier parent des différents dépôts est PARENT_DIR et doit être fourni par les
# différents Makefile.

# Les différents projets
export ASSER_DIR = $(PARENT_DIR)/asservissement/
export CARTO_DIR = $(PARENT_DIR)/cartographie/
export COMMUNICATION_DIR= $(PARENT_DIR)/common_code/communication/
export HARDW_DIR = $(PARENT_DIR)/hardware/
export SIMU_DIR  = $(PARENT_DIR)/simulation/

export STRAT_DIR = $(PARENT_DIR)/strategie/Robot_$(ROBOT)

# Le dossier de build, dans chaque dépôt
export BUILD_DIR = build/$(ARCH)/$(DEBUG)

ifeq ($(ROBOT),petit)
	CFLAGS  += -DGROS=0 -DPETIT=1
else
	CFLAGS  += -DGROS=1 -DPETIT=0
endif

################################################################################
# Architecture dependent parameters
export HARDW_LIB_DIR = $(HARDW_DIR)/$(ARCH)/
export HARDW_LIB = $(HARDW_LIB_DIR)/$(BUILD_DIR)/lib$(ARCH).a

include $(HARDW_DIR)/$(ARCH)/$(ARCH).mk

# Options de compilations
CFLAGS += -W -Wall -std=c99 $(TARGET) $(INCLUDE) -DDEBUG=$(DEBUG)\
		-I$(HARDW_LIB_DIR)

# Options pour l'édition de liens
LDFLAGS+= 	-L$(HARDW_LIB_DIR)/$(BUILD_DIR)/	\
			-L$(CARTO_DIR)/$(BUILD_DIR)/		\
			-L$(COMMUNICATION_DIR)/$(BUILD_DIR)/\



################################################################################
# Common Rules

hardware_lib: ;
	@$(MAKE) -C $(HARDW_LIB_DIR) $(BUILD_DIR)/lib$(ARCH).a

common_lib:
	@$(MAKE) -C $(COMMON_DIR) libCommon


# Compile an object file
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

# Compile a static library
$(BUILD_DIR)/%.a:
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@rm -f $@
	@$(AR) -r $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

%.hex:
	@echo "	HEX	$(PROJECT)|$@"
	@$(OBJ2HEX) -Oihex $^ $@

################################################################################
# Clean the current working directory
.PHONY: clean mrproper clean-all

clean:
	@echo "	Cleaning $(PROJECT) directory…"
	@rm -rf build/

clean-all:
	@make clean -C $(ASSER_DIR)
	@make clean -C $(CARTO_DIR)
	@make clean -C $(COMMUNICATION_DIR)
	@make clean -C $(HARDW_LIB_DIR)
	@make clean -C $(STRAT_DIR)
	@make clean -C $(SIMU_DIR)

mrproper-all:
	@make mrproper -C $(ASSER_DIR)
	@make mrproper -C $(CARTO_DIR)
	@make mrproper -C $(COMMUNICATION_DIR)
	@make mrproper -C $(HARDW_LIB_DIR)
	@make mrproper -C $(STRAT_DIR)
	@make mrproper -C $(SIMU_DIR)
