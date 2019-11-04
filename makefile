#Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl`

# SRC contain all the file we must built

SRC = $(shell find ./src -type f -name "*.c")
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

BMP = $(shell find . -type f -name "*.bmp") 

EXEC = main testsegm segmA

all: main

test:
	echo $(DIR2)

main: main.c $(OBJ)

testsegm: testsegm.c $(OBJ)

segmA: segmA.c $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP) *.o *.d


mrproper: clean
	$(RM) $(EXEC) $(BMP)

-include $(DEP)
