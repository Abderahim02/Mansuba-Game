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

pawns.o: src/pawns.c
	gcc -c $(CFLAGS) src/pawns.c
triangular_world.o: src/triangular_world.c
	gcc -c $(CFLAGS) src/triangular_world.c

game.o: src/game.c
	gcc -c $(CFLAGS) src/game.c

chess_world.o: src/chess_world.c
	gcc -c $(CFLAGS) src/chess_world.c

complement_ensemble.o: src/complement_ensemble.c
	gcc -c $(CFLAGS) src/complement_ensemble.c

project: src/game.c src/ensemble.o src/neighbors.o src/world.o src/geometry.o src/pawns.o src/triangular_world.o src/chess_world.o src/complement_ensemble.o
	$(GCC) $(CFLAGS) src/game.c src/ensemble.o  src/neighbors.o src/world.o src/geometry.o src/triangular_world.o src/pawns.o src/chess_world.o src/complement_ensemble.o -o project

test: tst/test.c src/ensemble.o src/neighbors.o src/world.o src/geometry.o src/pawns.o src/triangular_world.o src/chess_world.o src/complement_ensemble.o
	$(GCC) $(CFLAGS)  -I src tst/test.c src/ensemble.o  src/pawns.o src/neighbors.o  src/triangular_world.o src/chess_world.o src/geometry.o src/world.o src/complement_ensemble.o -o test

clean:
	rm -f project tst/*.o  src/*.o *~



#gcc test.c ../src/geometry.c -o test
