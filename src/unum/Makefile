CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g

all: unum.o test.bin

test.bin: test.cpp bitfields.hpp Makefile
	$(CC) $(CFLAGS) $< -o $@

unum.o: unum.cpp Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.bin

.PHONY: all clean
