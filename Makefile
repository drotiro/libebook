OPTS=-g -fpermissive
LOPTS=$(OPTS)
OBJS=src/BitReader.o src/MobiBook.o src/MobiDumper.o src/Locale.o
TOOL_OBJS=src/bookdump.o src/bookinfo.o

.PHONY: all

all: $(OBJS) $(TOOL_OBJS)
	g++ $(LOPTS) -o bookdump $(OBJS) src/bookdump.o
	g++ $(LOPTS) -o bookinfo $(OBJS) src/bookinfo.o

clean:
	rm -f src/*.o *.exe bookinfo bookdump

.cpp.o:
	g++ $(OPTS) -c $< -o $@
