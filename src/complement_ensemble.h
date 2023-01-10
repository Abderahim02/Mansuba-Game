#ifndef __COMPLEMENT_ENSEMBLE_H__
#define __COMPLEMENT_ENSEMBLE_H__
#include "chess_world.h"


//  A function testing if  a position idx is an initial position for the player 
int is_initial_position(enum players player, struct positions_info* infos, unsigned int idx);

//make a piece free
void escape_piece(enum players player , struct positions_info* infos, unsigned int idx );

// A function giving the neighbors of idx depending on the world
struct neighbors_t get_neighbors_world(unsigned int idx);
#endif