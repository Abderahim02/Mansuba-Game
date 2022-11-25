WIDTH ?= 10
HEIGHT ?= 10
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

# all: project

all: world geometry

compile: # test
	cc -std=c99 -Wall -o world world.c


# Test for the Makefile
world.o: world.h world.c 
	cc $(CFLAGS) -c world.c

geometry.o: geometry.h geometry.c
	cc $(CFLAGS) -c geometry.c

neighbors.o: neighbors.h neighbors.c
	cc $(CFLAGS) -c neighbors.c 

ensemble.o: ensemble.h ensemble.c
	cc $(CFLAGS) -c ensemble.c 

project: world.o geometry.o neighbors.o ensemble.o main.c
	cc $(CFLAGS) -o project main.c world.o geometry.o neighbors.o ensemble.o

%.o: %.c
	gcc -c $(CFLAGS) $<

#project: # (Add your dependency here, e.g "project.o")
#	# (Add your compile command here, e.g "gcc $(CFLAGS) project.o -o project")

test_project: # (Add your dependency here, e.g "test.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) test.o -o test_project")

clean:
	rm -f *.o project
