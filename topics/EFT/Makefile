DEPENDS=Makefile

all: index.html

%.html: %.skb $(DEPENDS)
	skribilo --target=html $< -o $@

clean:
	rm -f *.html

.PHONY: all clean
