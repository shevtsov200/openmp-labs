CC=gcc
CFLAGS=-Wall -fopenmp
SOURCES=lab9.c

all: program

program: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	rm program
run: program
	./program $(ARGS)
