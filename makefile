#Makefile


CC = gcc
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDLIBS = -lSDL -lSDL_image -lm
LDFLAGS = -fsanitize=address

# SRC contain all the file we must built
SRC = main.c preprocessing/preprocessing.c sdl_tools/sdl_tools.c
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
