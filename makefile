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

# avoid make main
all: main

main: main.c $(OBJ)

testsegm: testsegm.c $(OBJ)

segmA: segmA.c $(OBJ)

# Clean

clean:
	$(RM) $(OBJ) $(DEP) *.o *.d

mrproper: clean
	$(RM) $(EXEC) $(BMP)
