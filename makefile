#Makefile


CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
LDLIBS = -lSDL_image -lm

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
