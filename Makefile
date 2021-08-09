CMD=	csv2tsv.exe

CFLAGS+=-g

SRCS=	$(wildcard *.c)
OBJS=	$(SRCS:.c=.o)

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
