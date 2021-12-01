CMD=	csv2tsv.exe

SRCS=	$(wildcard *.c)
OBJS=	$(SRCS:.c=.o)

CC=	clang
CFLAGS+=-g
EXIST=	cmd.exe //C if exist

build: $(CMD)

$(CMD): $(OBJS)
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS)

.c.o:
	$(CC) -c $< -o $@

test: test-kyua

test-kyua: $(CMD)
	cd tests; kyua test

test-original: $(CMD) 
	pwsh .\tests\test.ps1

report: $(CMD) clean-report
	cd tests; kyua report-html

clean: clean-report
	$(EXIST) $(CMD) del $(CMD)
	$(EXIST) main.o del $(OBJS)
	$(EXIST) $(CMD:.exe=.ilk) del $(CMD:.exe=.ilk)
	$(EXIST) $(CMD:.exe=.pdb) del $(CMD:.exe=.pdb)
	$(EXIST) nul del *.tmp
	$(EXIST) csv2tsv.exe.stackdump del csv2tsv.exe.stackdump

clean-report:
	$(EXIST) .\tests\html rmdir .\tests\html //S //Q
