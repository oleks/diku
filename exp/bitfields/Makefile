CXX=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g

all: test.bin

test.bin: test.cpp bitfields.hpp Makefile
	$(CXX) $(CFLAGS) $< -o $@

bitfields.o: bitfields.c
	gcc -nostdlib -c $<

show_bitfields.o: bitfields.o Makefile
	objdump --disassemble $<

clean:
	rm -f *.o
	rm -f *.bin

.PHONY: all clean show_*
