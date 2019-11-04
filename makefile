#Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl`

# SRC contain all the file we must build
SRC = $(shell find ./src -type f -name "*.c")
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
-include $(DEP)

# All bmp file generate by the program
BMP = $(shell find ./image_data -type f -name "*.bmp") 

# All exec we want to clean
EXEC = main testsegm segmA

# doxygen documentation
define generate_doxygen
	doxygen
endef

# Create shortcut to index.html
define generate_shortcut
	ln -s doxygen/html/index.html doc
endef

# Open documentation in browser
define open_doc
	x-www-browser doc
endef

# avoid make main
all: main



.PHONY: doxygen
doxygen:
ifeq ($(wildcard doc),)
	$(call generate_doxygen)
	$(call generate_shortcut)
else
	echo "You already generate doxygen"
endif

.PHONY: doc
doc: doxygen
	$(call open_doc)

main: main.c $(OBJ)

testsegm: testsegm.c $(OBJ)

segmA: segmA.c $(OBJ)

# Clean

clean:
	$(RM) $(OBJ) $(DEP) *.o *.d

mrproper: clean
	$(RM) $(EXEC) $(BMP)
