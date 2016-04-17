PROJECT=LibStm32f407
default: all
# Default Options
export ARCH  = stm32f407
export ROBOT = gros
export SDL   = no
export DEBUG = _WARNING_

export PARENT_DIR = ../../../
include $(PARENT_DIR)/hardware/common.rules

################################################################################
# Chemin du dépôt stm32f407
PathSTM32 = ../

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"
# Répertoires pour les headers requis (core_cm4.h, stm32f4xx.h, stm32f4xx_hal_conf.h, ...)
INCLUDE = -I$(STM32Cube)Drivers/CMSIS/Device/ST/STM32F4xx/Include/ \
          -I$(STM32Cube)Drivers/CMSIS/Include/                     \
          -I$(STM32Cube)Projects/STM32F4-Discovery/Templates/Inc/  \
          $(shell find $(STM32Cube)Drivers/ -path "*" -printf "-I%h/\n"|sort -u)

################################################################################
# Fichiers source

SRC_HAL_Driver = $(shell find $(STM32Cube)Drivers/STM32F4xx_HAL_Driver/ -name *.c)
SRC_CMSIS      = $(shell find $(STM32Cube)Drivers/CMSIS/                -name *.c)
SRC_BSP        = $(shell find $(STM32Cube)Drivers/BSP/                  -name *.c)

# Fichiers objets
OBJ_HAL_Driver = $(SRC_HAL_Driver:.c=.o)
OBJ_CMSIS      = $(SRC_CMSIS:.c=.o)
OBJ_BSP        = $(SRC_BSP:.c=.o)


#################
#     Règles    #
#################

all: libs

libs: libHAL_Driver.a libBSP.a libCMSIS.a
libHAL_Driver.a: $(OBJ_HAL_Driver)
libCMSIS.a:      $(OBJ_CMSIS)
libBSP.a:        $(OBJ_BSP)

%.a:
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@rm -f $@
	@$(AR) -r $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

%.o: %.c
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) -Wno-unused-parameter -Wno-unused-variable $(CFLAGS) -c -o $@ $^

################################################################################
# Cibles génériques

.PHONY: clean

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@find $(BUILDIR) -name '*.o' -delete
	@rm -f libHAL_Driver.a libBSP.a libCMSIS.a
