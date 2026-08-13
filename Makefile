CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address,undefined -Iinclude -g -O0

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = psexpl

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

.PHONY: all clean

