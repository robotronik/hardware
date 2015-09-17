################################################################################
# Makefile générique, appelé par la lib et les projets parallèles
################################################################################
# Compilateur C et linker
CC      = gcc -std=c99
++		= g++ -std=c++11
AR      = ar
RANLIB  = ranlib
GDB     = gdb
LD      = ld
OBJ2HEX =
LINKER  =

# Précise la carte cible
TARGET  =

# Options de compilation spécifiques à la plateforme
CFLAGS += -DPIC_BUILD=0 -Os -g

LDFLAGS+= -Wl,--gc-sections -lm -lpthread
#	-Wl,--gc-sections – enable garbage collection of unused input sections

#               Includes
# Indique au compilateur dans quels répertoires chercher les headers appelés
# avec la directive de préprocesseur "#include <header.h>"



ifeq ($(SDL),yes)
	CFLAGS  += -DUSE_SDL=1 -Wno-deprecated
	LDFLAGS +=
endif
