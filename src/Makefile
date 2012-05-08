# Variables

PKGS = libxml-2.0 libzip
OPTS    = -g -fpermissive -fPIC
FLAGS = $(shell pkg-config ${PKGS} --cflags) ${OPTS}
LIBS = $(shell pkg-config ${PKGS} --libs)
HEADERS = MobiBook.h MobiDumper.h Utils.h Ebook.h Epub.h Zip.h
OBJS    = BitReader.o MobiBook.o MobiDumper.o Locale.o Epub.o Zip.o
TOBJS   = bookdump.o bookinfo.o
TOOLS	= ${TOBJS:.o=}
SONAME  = libebook.so

# Target
lib: $(OBJS) $(HEADERS)
	$(CXX) -shared -Wl,-soname,libebook.so -o ../lib/$(SONAME) $(FLAGS)
	$(AR) r ../lib/$(SONAME:.so=.a) $(OBJS)

tools: $(TOOLS)
$(TOOLS): lib $(TOBJS)
	$(CXX) -o ../bin/$@ $@.o -L../lib -lebook $(LIBS)

.cpp.o:
	g++ $(FLAGS) -c $< -o $@

.PHONY: lib tools
