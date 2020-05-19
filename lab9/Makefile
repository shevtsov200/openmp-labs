CC=mpicc
CFLAGS=-g
SOURCES=lab9.c

SIZE=4

all: program

program: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o program.o

clean:
	rm program
run: program
	mpiexec -np $(SIZE) ./program.o $(ARGS)
