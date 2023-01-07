#ifndef __COMPLEMENT_ENSEMBLE_H__
#define __COMPLEMENT_ENSEMBLE_H__
#include "ensemble.h"

//a function testing if a pièce is prisoner 
int is_prisoner(enum players player, struct positions_info* infos, unsigned int idx );

//  A function testing if  a position idx is an initial position for the player 
int is_initial_position(enum players player, struct positions_info* infos, unsigned int idx);

//make a piece free
void escape_piece(enum players player , struct positions_info* infos, unsigned int idx );

#endif