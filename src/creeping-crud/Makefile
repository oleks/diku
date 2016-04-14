N=10000000
START=-500000.0
ADDEND=0.1
REAL=float

CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11 -O0
LDFLAGS=-lm

all: sum_DOWNWARD.bin sum_UPWARD.bin sum_TONEAREST.bin sum_TOWARDZERO.bin
	./sum_DOWNWARD.bin
	./sum_UPWARD.bin
	./sum_TONEAREST.bin
	./sum_TOWARDZERO.bin

sum_%.bin: sum.c Makefile
	$(CC) $(CFLAGS) \
		-DROUND=FE_$* \
		-DREAL=$(REAL) \
		-DN="$(N)" \
		-DSTART="$(START)" \
		-DADDEND="$(ADDEND)" \
		$< -o $@ $(LDFLAGS)

clean:
	rm -f *.bin

.PHONY: all clean Makefile
