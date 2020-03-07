CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
LDLIBS = -lm
VPATH = src

OBJ = main.o nbc.o
BIN = nbc

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(BIN) $(OBJ)
