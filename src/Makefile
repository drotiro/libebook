# Variables

PKGS = libxml-2.0 libzip
OPTS    = -g -fpermissive
FLAGS = $(shell pkg-config ${PKGS} --cflags) ${OPTS}
LIBS = $(shell pkg-config ${PKGS} --libs)
OBJS    = BitReader.o MobiBook.o MobiDumper.o Locale.o Epub.o Zip.o Xml.o
HEADERS = $(OBJS:.o=.h) Utils.h 
TOBJS   = bookdump.o bookinfo.o
TOOLS	= ${TOBJS:.o=}
SONAME  = libebook.so

# Target
lib: $(OBJS) $(HEADERS)
	$(CXX) -shared -Wl,-soname,$(SONAME) -o ../lib/$(SONAME) $(FLAGS)
	$(AR) rcs ../lib/$(SONAME:.so=.a) $(OBJS)

tools: $(TOOLS)
$(TOOLS): lib $(TOBJS)
	$(CXX) -o ../bin/$@ $@.o -L../lib -lebook  $(LIBS)

.cpp.o:
	g++ $(FLAGS) -c $< -o $@

.PHONY: lib tools
