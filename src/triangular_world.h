#ifndef __TRIANGULAR_WORLD_H__
#define __TRIANGULAR_WORLD_H__
#include "pawns.h"
void print_triangular_world(struct world_t* world);
unsigned int get_neighbor_triangular(unsigned int idx, enum dir_t d);
struct neighbors_t get_neighbors_triangular( unsigned int idx);

#endif 