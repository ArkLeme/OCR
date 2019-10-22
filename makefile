#Makefile

CC = gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl`

# SRC contain all the file we must built
SRC = main.c preprocessing/preprocessing.c sdl_tools/sdl_tools.c segmentation/segmentation.c matrix/matrix.c matrix/matrix_image.c segmentation/rlsa.c segmentation/xy_cut.c segmentation/comp_labeling/union_find.c segmentation/comp_labeling/comp_labeling.c segmentation/separate_matrix.c string/string_operation.c segmentation/segmentation_image.c
OBJ = $(SRC:.c=.o)
DEP = ${SRC:.c=.d}
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP)

properclean: clean
	$(RM) $(EXEC) 

-include $(DEP)
