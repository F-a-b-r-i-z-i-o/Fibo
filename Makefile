CC = gcc
CFLAGS = -Wall -Werror -pedantic
OBJ = esercizio2.o

.PHONY: clean

all: main

esercizio2.o: esercizio2.c
	@ echo "~~COMPILAZIONE ESERCIZIO"
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o fib $^ $(CFLAGS)
	@ echo "~~FINE COMPILAZIONE"

clean :
	-rm *.o
	-rm fib
