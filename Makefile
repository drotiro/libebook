PREFIX ?= /usr/local

all:
	make -C src lib tools

install:
	cp bin/* $(PREFIX)/bin
	cp lib/* $(PREFIX)/lib
	
clean:
	rm -f src/*.o src/*.so bin/*

.PHONY: all
