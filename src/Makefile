# Variables
OPTS    = -g -fpermissive -fPIC
HEADERS = MobiBook.h MobiDumper.h Utils.h Ebook.h
OBJS    = BitReader.o MobiBook.o MobiDumper.o Locale.o
TOBJS   = bookdump.o bookinfo.o
TOOLS	= ${TOBJS:.o=}
SONAME  = libebook.so

# Target
lib: $(OBJS) $(HEADERS)
	$(CXX) -shared -Wl,-soname,libebook.so -o ../lib/$(SONAME) $(OBJS)

tools: $(TOOLS)
$(TOOLS): lib $(TOBJS)
	$(CXX) -o ../bin/$@ $@.o ../lib/$(SONAME)

.cpp.o:
	g++ $(OPTS) -c $< -o $@

.PHONY: lib tools
