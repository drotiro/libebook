# Variables

PKGS = libxml-2.0 libzip
OPTS    = -g -fpermissive -fPIC
FLAGS = $(shell pkg-config ${PKGS} --cflags) ${OPTS}
LIBS = $(shell pkg-config ${PKGS} --libs)
OBJS    = BitReader.o MobiBook.o MobiDumper.o Locale.o Epub.o Zip.o Xml.o \
    JsonObj.o Ebook.o Utils.o
HEADERS = $(OBJS:.o=.h) 
TOBJS   = bookdump.o bookinfo.o
TOOLS	= ${TOBJS:.o=}
SONAME  = libebook.so

LIBDIR  = ../lib
BINDIR  = ../bin

# if we are on win...
UNAME = $(shell uname -s)
ifeq ($(findstring MINGW,$(UNAME)), MINGW)
    SONAME = libebook.dll
else
    SONAME = libebook.so
endif


# Dependencies (g++ -MM)
bookdump.o: bookdump.cpp MobiBook.h Utils.h Ebook.h MobiDumper.h Epub.h Zip.h
bookinfo.o: bookinfo.cpp MobiBook.h Utils.h Ebook.h Epub.h Zip.h Locale.h
BitReader.o: BitReader.cpp BitReader.h Utils.h
Ebook.o: Ebook.cpp Ebook.h Utils.h
Epub.o: Epub.cpp Epub.h Ebook.h Zip.h Xml.h
JsonObj.o: JsonObj.cpp JsonObj.h Utils.h
Locale.o: Locale.cpp Locale.h
MobiBook.o: MobiBook.cpp MobiBook.h Utils.h Ebook.h BitReader.h MobiDumper.h \
	JsonObj.h
MobiDumper.o: MobiDumper.cpp MobiDumper.h MobiBook.h Utils.h Ebook.h JsonObj.h
Utils.o: Utils.cpp Utils.h
Xml.o: Xml.cpp Xml.h
Zip.o: Zip.cpp Zip.h


# Targets
lib: $(OBJS) $(HEADERS)
	@mkdir -p $(LIBDIR)
	$(CXX) -shared -Wl,-soname,$(SONAME) -o $(LIBDIR)/$(SONAME) $(OBJS) $(FLAGS) $(LIBS)

tools: $(TOOLS)
$(TOOLS): lib $(TOBJS)
	@mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)/$@ $@.o -L$(LIBDIR) -lebook  $(LIBS)

.cpp.o:
	g++ $(FLAGS) -c $< -o $@

.PHONY: lib tools
