CXX=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g
DEPENDS=Makefile

all: test.bin

test.bin: test.cpp bitfields.hpp $(DEPENDS)
	$(CXX) $(CFLAGS) $< -o $@

bitfields.o: bitfields.c $(DEPENDS)
	gcc -nostdlib -c $<

show_bitfields.o: bitfields.o $(DEPENDS)
	objdump --disassemble $<

clean:
	rm -f *.o
	rm -f *.bin

.PHONY: all clean show_*
