OBJS=		csv2tsv.o util.o
CMD=		csv2tsv.exe

CFLAGS+=	-g

CC=		clang

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS)

csv2tsv.o: csv2tsv.c
	$(CC) $(CFLAGS) -c csv2tsv.c -o csv2tsv.o

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o

clean:
	rm -f "$(CMD)"
	rm -f *.o
	rm -f *.ilk
	rm -f *.pdb
