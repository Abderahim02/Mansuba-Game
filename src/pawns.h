#ifndef __PAWNS_H__
#define __PAWNS_H__

#include "ensemble.h"

// Check if a move for tower is possible.
int tower_move(struct world_t* world, enum players player, struct positions_info* infos, int ex_idx);

int give_end_position_x(enum players player, unsigned int ex_idx);

int is_allowed_tower_move(struct world_t* world, enum players player, unsigned int ex_idx);

#endif // __ENSEMBLE_H__