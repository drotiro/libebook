OPTS=-g
LOPTS=-g
OBJS=src/BitReader.o src/MobiDoc.o
TOOL_OBJS=src/mobidump.o src/mobiinfo.o

all: $(OBJS) $(TOOL_OBJS)
	g++ $(LOPTS) -o mobidump $(OBJS) src/mobidump.o
	g++ $(LOPTS) -o mobiinfo $(OBJS) src/mobiinfo.o

clean:
	rm -f src/*.o *.exe mobidump mobiinfo

.cpp.o:
	g++ $(OPTS) -c $< -o $@



