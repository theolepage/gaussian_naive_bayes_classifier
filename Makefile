CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
LDLIBS = -lm
VPATH = src

OBJ = main.o
BIN = nbn

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDLIBS)

clean:
	$(RM) $(BIN) $(OBJ)
