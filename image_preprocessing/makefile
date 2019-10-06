#Makefile


CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
DEPS = test.h
OBJ = test.o
EXEC = test
LDLIBS = -lSDL_image -lm

%.o: %.c %(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

clean:
	rm -rf *.o

properclean: clean

