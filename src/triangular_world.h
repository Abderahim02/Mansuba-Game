#ifndef __TRIANGULAR_WORLD_H__
#define __TRIANGULAR_WORLD_H__
#include "pawns.h"
// a function printing the triangular world
void print_triangular_world(struct world_t* world);

// the get_neighbor function in the triangular world
unsigned int get_neighbor_triangular(unsigned int idx, enum dir_t d);

// the get_neighbors function in the triangular world
struct neighbors_t get_neighbors_triangular( unsigned int idx);

//the function initializing the triabgular world
void init_players_triangular(struct world_t* b);

//function testing if the idx is a playable position in the board
int is_playable_position(struct world_t* world, unsigned int idx);

//function testing if the bishop move froem ex_idx to new_idx is possible
int is_allowed_bishop_move(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

//the bishop move function
void bishop_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

//function testing if the simple move in a triangular world frome ex_idx to new_idx is possible 
int is_allowed_simple_move_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);

//the simple move for triangular world
void simple_move_triangular(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

//function testing if the simple jump in a triangular world frome ex_idx to new_idx is possible 
int is_allowed_simple_jump_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);

//the simple jump for triangular world
void simple_jump_triangular(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);
#endif 