WIDTH ?= 5
HEIGHT ?= 4
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

# all: project

all: world geometry

compile: # test
	cc -std=c99 -Wall -o world world.c

world:
	cc -std=c99 -Wall -o world world.c

geometry:
	cc -std=c99 -Wall -o geometry geometry.c


%.o: %.c
	gcc -c $(CFLAGS) $<

project: # (Add your dependency here, e.g "project.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) project.o -o project")

test_project: # (Add your dependency here, e.g "test.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) test.o -o test_project")

clean:
	rm -f *.o *~
