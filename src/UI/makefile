#Makefile


CC = gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS = -fsanitize=address -g -Wall -Wextra -std=c99
LDFLAGS = -fsanitize=address
LDLIBS = `pkg-config --libs gtk+-3.0`

# SRC contain all the file we must built
SRC = testUI.c callback.c error.c
OBJ = $(SRC:.c=.o)
DEP = ${SRC:.c=.d}
EXEC = testUI

all: $(EXEC)

$(EXEC): $(OBJ)

clean:
	$(RM) $(OBJ) $(DEP)

properclean: clean
	$(RM) $(EXEC) 

-include $(DEP)
