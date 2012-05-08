all:
	make -C src lib tools
	
clean:
	rm -f src/*.o src/*.so bin/*

.PHONY: all
