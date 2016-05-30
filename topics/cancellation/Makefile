DEPENDS=Makefile

all: README.html

%.html: %.org $(DEPENDS)
	emacs $< --batch -f org-html-export-to-html --kill

clean:
	rm -f *.html

.PHONY: all clean
