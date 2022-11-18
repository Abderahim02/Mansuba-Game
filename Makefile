WIDTH ?= 10
HEIGHT ?= 10
GCC = gcc
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

all: project

neighbors.o: src/neighbors.c
	gcc -c $(CFLAGS) src/neighbors.c
world.o: src/world.c
	gcc -c $(CFLAGS) src/world.c

ensemble.o: src/ensemble.c
	gcc -c $(CFLAGS) src/ensemble.c

geometry.o: src/geometry.c
	gcc -c $(CFLAGS) src/geomerty.c



project: src/project.c
	$(GCC) $(CFLAGS) src/project.c -o project

test: tst/test.c src/ensemble.o src/neighbors.o src/world.o src/geometry.o 
	$(GCC) $(CFLAGS)  tst/test.c src/ensemble.o  src/neighbors.o src/geometry.o src/world.o -o test

clean:
	rm -f project test *.o *~



#gcc test.c ../src/geometry.c -o test
