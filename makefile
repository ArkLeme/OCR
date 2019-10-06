#Makefile


CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
LDLIBS = -lSDL_image -lm

# SRC contain all the file we must built
SRC = preprocessing/preprocessing.c sdl_tools/sdl_tools.c
OBJ = $(SRC:.c=.o)
DEP = ${SRC:.c=.d}
EXEC = main

all: main

main: $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP)

properclean: clean
	rm $(EXEC)

-include $(DEP)
