CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=gnu11
LDFLAGS=-lm

all: bank.bin
	./bank.bin

%.bin: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f *.bin

.PHONY: all clean Makefile
