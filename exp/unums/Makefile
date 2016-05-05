CXX=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g

all: unum.o test.bin

test.bin: test.cpp bitfields.hpp unum.o unum.hpp Makefile
	$(CXX) $(CFLAGS) test.cpp unum.o -o $@

unum.o: unum.cpp Makefile
	$(CXX) $(CFLAGS) -c $<

bitfields.o:
	gcc -nostdlib -c $<

show_bitfields.o: bitfields.o Makefile
	objdump --disassemble $<

clean:
	rm -f *.o
	rm -f *.bin

.PHONY: all clean show_bitfields.o
