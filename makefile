#Makefile


CC = gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl`

# SRC contain all the file we must built
SRC = main.c preprocessing/preprocessing.c sdl_tools/sdl_tools.c segmentation/segmentation.c matrix/matrix.c
OBJ = $(SRC:.c=.o)
DEP = ${SRC:.c=.d}
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP)

properclean: clean
	rm $(EXEC) 

-include $(DEP)
