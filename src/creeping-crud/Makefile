N=10000000
START=-500000.0
ADDEND=0.1
REAL=float
EXCEPT=0

CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=gnu11 -O0 \
	-frounding-math -fsignaling-nans
# The last two are necessary to enable full IEEE 754 support in GCC.
# See also https://gcc.gnu.org/wiki/FloatingPointMath
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
		-DEXCEPT="$(EXCEPT)" \
		$< -o $@ $(LDFLAGS)

clean:
	rm -f *.bin

.PHONY: all clean Makefile
