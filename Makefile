PREFIX ?= /usr/local

all:
	make -C src lib tools

install: all
	cp bin/* $(PREFIX)/bin
	cp lib/* $(PREFIX)/lib
	
clean:
	rm -f src/*.o src/*.so bin/* lib/*

.PHONY: all
