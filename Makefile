CMD=	csv2tsv.exe

SRCS=	$(wildcard *.c)
OBJS=	$(SRCS:.c=.o)

CC=	clang
CFLAGS+=-g

build: $(CMD)

$(CMD): $(OBJS)
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS)

.c.o:
	$(CC) -c $< -o $@

test:
	pwsh .\tests\test001.ps1

clean:
	rm -f $(CMD)
	rm -f $(OBJS)
	rm -f *.ilk
	rm -f *.pdb
