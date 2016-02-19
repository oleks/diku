OUT=$(patsubst %.c,%.bin,$(wildcard *.c))

CC=gcc
CFLAGS=-Werror -Wextra -Wall -pedantic -std=c11 -g

all: $(OUT)

%.bin: %.c Makefile
	$(CC) $(CFLAGS) -o $*.bin $*.c

clean:
	rm -f $(OUT)

.PHONY: all clean
