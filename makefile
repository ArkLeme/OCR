#Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl`

# SRC contain all the file we must built

DIR = matrix preprocessing sdl_tools segmentation segmentation/comp_labeling string XOR

DIR2 = $(shell find ./ -type f -name "*.c" \
	|sed -r 's|/[^/]+$$||' \
	|sed -r 's|\.+$$||' \
	|sort \
	|uniq )

BMP = $(shell find . -type f -name "*.bmp") 

SRC = $(foreach dir, $(DIR2), $(wildcard $(dir)/*.c))
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

EXEC = main testsegm segmA

all: main

test:
	echo $(DIR2)

main: main.c $(OBJ)

testsegm: testsegm.c $(OBJ)

segmA: segmA.c $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP) $(EXEC).c $(EXEC).o

mrproper: clean
	$(RM) $(EXEC) $(BMP)

-include $(DEP)
