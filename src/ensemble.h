#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include "world.h"
#include "geometry.h"
#include "neighbors.h"

// The position_info includes the positions in the begin (initial)
// the allowed moves and the where the peaces are at the moment
struct position_info;

// Initialize current pieces for black and white.
// Furthermore it sets the world the beginning position.
void init_players(struct world_t* b);

// Is a bool function and returns 1 if new_idx is a neighbor to ex_idx.
int is_newex_neighbor(int ex_idx,int new_idx);

// Is a help/bool function, which returns 1 if the 
int is_allowed_tomove(struct world_t world, int ex_idx, int new_idx);

// If conditions are ok, a piece moves.
void move_player(struct world_t world, int player,struct positions_info infos, int ex_idx, int new_idx);


// We need to create some functions here, which we define later.


#endif // __ENSEMBLE_H__
