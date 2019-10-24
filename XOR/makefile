#Makefile XOR NEtwork


CC = gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl`

# SRC contain all the file we must built
SRC = ../matrix/matrix.c f_b_Propagation.c tools.c xor.c init_Network.c 
OBJ = $(SRC:.c=.o)
DEP = ${SRC:.c=.d}
EXEC = xor 

all: $(EXEC)

$(EXEC): $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP)

properclean: clean
	rm $(EXEC) 

-include $(DEP)
