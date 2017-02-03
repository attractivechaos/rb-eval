CC=			gcc
CXX=		g++
CFLAGS=		-g -Wall -Wc++-compat -O2
CXXFLAGS=	$(CFLAGS)
EXE=		rb-cpp rb-c rb-c-mp btree-c

.SUFFIXES:.c .cpp .o
.PHONY:all clean depend

.c.o:
		$(CC) -c $(CFLAGS) $< -o $@

.cpp.o:
		$(CXX) -c $(CXXFLAGS) $< -o $@

all:$(EXE)

rb-c:rb.o rb-c.o
		$(CC) $(CFLAGS) $^ -o $@

rb-c-mp:rb.o rb-c-mp.o
		$(CC) $(CFLAGS) $^ -o $@

btree-c:btree-c.o
		$(CC) $(CFLAGS) $^ -o $@

rb-cpp:rb-cpp.o
		$(CXX) $(CFLAGS) $^ -o $@

clean:
		rm -fr *.o a.out $(EXE) *~ *.a *.dSYM session*

depend:
		(LC_ALL=C; export LC_ALL; makedepend -Y -- $(CFLAGS) $(DFLAGS) -- *.c)

# DO NOT DELETE

rb-c-mp.o: rb.h klist.h
rb-c.o: rb.h
rb.o: rb.h
