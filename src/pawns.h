#ifndef __PAWNS_H__
#define __PAWNS_H__

#include "ensemble.h"



//..............
int is_cardinal_dir(enum dir_t dir);
int is_allowed_to_simple_move_aux(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);
int is_allowed_elephant_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);
void elephant_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);


// Help functions for the tower move. 
int give_end_position_x(enum players player, unsigned int ex_idx);
int give_top_position_y(unsigned int ex_idx);
int give_down_position_y(unsigned int ex_idx);

// Return 1 if the tower is allowed to move else 0.
int is_allowed_tower_move(struct world_t* world, enum players player, unsigned int ex_idx);

// Check if a move for tower is possible.
int tower_move(struct world_t* world, enum players player, struct positions_info* infos, int ex_idx);

#endif // __ENSEMBLE_H__