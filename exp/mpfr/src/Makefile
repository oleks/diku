.PHONY: all clean

BIN=$(patsubst %.c,%.bin,$(wildcard *.c))

all: $(BIN)

%.bin: %.c Makefile
	gcc $< -o $@ -lmpfr

clean:
	rm -rf $(BIN)
