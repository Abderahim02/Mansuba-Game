#ifndef __NEIGHBORS_H__
#define __NEIGHBORS_H__

#include "geometry.h"

/** The number of relations in the code */
#define MAX_RELATIONS 1
/** The maximum number of neighbors for a place */
#define MAX_NEIGHBORS 8

/** A struct representing a vector towards a neighbor of a place
    It contains the index of the neighbor, and the direction it's in */
struct vector_t {
  unsigned int i; // the index of the place the vector is pointing to
  enum dir_t d;   // the direction towards this place
};

/** A list of neighbors, terminated by UINT_MAX

    For example, the list of neighbors { 2, 3 } can be written as
    { .n = { 2, 3, UINT_MAX, 0, 0, 0, 0, 0 } }
*/
struct neighbors_t {
  struct vector_t n[MAX_NEIGHBORS];
};

/** Initializes the relation between the neighbors, based on an
    integer `seed`. `seed` must be less than MAX_RELATIONS.
    Can be called multiple times. */
void init_neighbors(unsigned int seed);

/** Returns the seed set by the latest call to `init_neighbors`. */
unsigned int get_neighbors_seed();

/** Returns the neighbor of the place `idx`, in direction `d`, and
    UINT_MAX if there is no such neighbor (or any other kind of error) */
unsigned int get_neighbor(unsigned int idx, enum dir_t d);

/** Returns the list of the neighbors of the place `idx`, terminated
    by UINT_MAX.  */
struct neighbors_t get_neighbors(unsigned int idx);

#endif // __NEIGHBORS_H__
