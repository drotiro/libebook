# Variables

PKGS = libxml-2.0 libzip
OPTS    = -g -fpermissive -fPIC
FLAGS = $(shell pkg-config ${PKGS} --cflags) ${OPTS}
LIBS = $(shell pkg-config ${PKGS} --libs)
OBJS    = BitReader.o MobiBook.o MobiDumper.o Locale.o Epub.o Zip.o Xml.o Ebook.o
HEADERS = $(OBJS:.o=.h) Utils.h
TOBJS   = bookdump.o bookinfo.o
TOOLS	= ${TOBJS:.o=}
SONAME  = libebook.so

# if we are on win...
UNAME = $(shell uname -s)
ifeq ($(findstring MINGW,$(UNAME)), "MINGW")
    SONAME = libebook.so
else
    SONAME = libebook.dll
endif


# Dependencies (g++ -MM)
BitReader.o: BitReader.cpp BitReader.h Utils.h
bookdump.o: bookdump.cpp MobiBook.h Utils.h Ebook.h MobiDumper.h Epub.h \
 Zip.h
bookinfo.o: bookinfo.cpp MobiBook.h Utils.h Ebook.h Epub.h Zip.h Locale.h
Epub.o: Epub.cpp Epub.h Ebook.h Zip.h Xml.h
Locale.o: Locale.cpp Locale.h
MobiBook.o: MobiBook.cpp MobiBook.h Utils.h Ebook.h BitReader.h \
 MobiDumper.h
MobiDumper.o: MobiDumper.cpp MobiDumper.h MobiBook.h Utils.h Ebook.h
Xml.o: Xml.cpp Xml.h
Zip.o: Zip.cpp Zip.h
Ebook.o: Ebook.cpp Ebook.h Utils.h


# Target
lib: $(OBJS) $(HEADERS)
	$(CXX) -shared -Wl,-soname,$(SONAME) -o ../lib/$(SONAME) $(OBJS) $(FLAGS) $(LIBS)

tools: $(TOOLS)
$(TOOLS): lib $(TOBJS)
	$(CXX) -o ../bin/$@ $@.o -L../lib -lebook  $(LIBS)

.cpp.o:
	g++ $(FLAGS) -c $< -o $@

.PHONY: lib tools
