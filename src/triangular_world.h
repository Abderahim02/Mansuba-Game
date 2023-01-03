#ifndef __TRIANGULAR_WORLD_H__
#define __TRIANGULAR_WORLD_H__
#include "pawns.h"
void print_triangular_world(struct world_t* world);
unsigned int get_neighbor_triangular(unsigned int idx, enum dir_t d);
struct neighbors_t get_neighbors_triangular( unsigned int idx);
void init_players_triangular(struct world_t* b);
int is_playable_position(struct world_t* world, unsigned int idx);
int is_allowed_bishop_move(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);
void bishop_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);
int is_allowed_simple_move_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);
void simple_move_triangular(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);
int is_allowed_simple_jump_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);
void simple_jump_triangular(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);
#endif 