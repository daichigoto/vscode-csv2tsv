CMD=	csv2tsv.exe
SRCS=	csv2tsv.c util.c
OBJS=	$(SRCS:.c=.o)

CFLAGS+=-g

CC=	clang

build: $(CMD)

$(CMD): $(OBJS)
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS)

.c.o:
	$(CC) -c $< -o $@

clean:
	rm -f "$(CMD)"
	rm -f *.o
	rm -f *.ilk
	rm -f *.pdb
