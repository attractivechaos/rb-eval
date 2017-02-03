CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -Wc++-compat -O2
CXXFLAGS=	$(CFLAGS)
EXE=		rb-c rb-c-mp btree-c rb-cpp rb-map

.SUFFIXES:.c .cpp .o
.PHONY:all clean depend

.c.o:
		$(CC) -c $(CFLAGS) $< -o $@

.cpp.o:
		$(CXX) -c $(CXXFLAGS) $< -o $@

all:$(EXE)

rb-c:rb.o rb-c.o
		$(CC) $^ -o $@

rb-c-mp:rb.o rb-c-mp.o
		$(CC) $^ -o $@

btree-c:btree-c.o
		$(CC) $^ -o $@

rb-cpp:rb-cpp.o
		$(CXX) $^ -o $@

rb-map:rb-map.o
		$(CXX) $^ -o $@

clean:
		rm -fr *.o a.out $(EXE) *~ *.a *.dSYM session*

depend:
		(LC_ALL=C; export LC_ALL; makedepend -Y -- $(CFLAGS) $(DFLAGS) -- *.c)

# DO NOT DELETE

btree-c.o: kbtree.h
rb-c-mp.o: rb.h klist.h
rb-c.o: rb.h
rb.o: rb.h
