#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include "world.h"
#include "geometry.h"
#include "neighbors.h"


struct world_t;

enum players;

// The position_info includes the positions in the begin (initial)
// the allowed moves and the where the peaces are at the moment
struct position_info;


struct positions_info init_infos();

void add_to_current_piece(struct positions_info positions_info, enum players player, unsigned int idx);

// Initialize current pieces for black and white.
// Furthermore it sets the world the beginning position.
void init_players(struct world_t* b, struct positions_info positions_info);

// Is a bool function and returns 1 if new_idx is a neighbor to ex_idx.
int is_newex_neighbor(int ex_idx,int new_idx);

// Is a help/bool function, which returns 1 if the 
int is_allowed_to_simple_move(struct world_t* world, unsigned int ex_idx, unsigned int new_idx);


void update_current_pieces(enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx);


// If conditions are ok, a piece moves.
void move_player(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx );

void print_world( struct world_t* world );

// We need to create some functions here, which we define later.


#endif // __ENSEMBLE_H__
