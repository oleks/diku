CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11

all: sum.bin

sum.bin: sum.c Makefile
	$(CC) $(CFLAGS) sum.c -o sum.bin

clean:
	rm -f *.bin

.PHONY: all clean
