CC=gcc
CFLAGS=-Wall -fopenmp
SOURCES=lab6.c

all: my

program: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	rm program
run: program
	./program
