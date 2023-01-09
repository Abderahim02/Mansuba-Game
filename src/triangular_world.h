#ifndef __TRIANGULAR_WORLD_H__
#define __TRIANGULAR_WORLD_H__
#include "pawns.h"
// A function printing the triangular world
void print_triangular_world(struct world_t* world);
//a function defining the triangular world
void world_init_triangular(struct world_t* world);
// The get_neighbor function in the triangular world
unsigned int get_neighbor_triangular(unsigned int idx, enum dir_t d);

// The get_neighbors function in the triangular world
struct neighbors_t get_neighbors_triangular( unsigned int idx);

// The function initializing the triabgular world
void init_players_triangular(struct world_t* b);

// Function testing if the idx is a playable position in the board
int is_playable_position(struct world_t* world, unsigned int idx);

// Function testing if the bishop move froem ex_idx to new_idx is possible
int is_allowed_bishop_move(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

// The bishop move function
void bishop_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

// Function testing if the simple move in a triangular world from ex_idx to new_idx is possible 
int is_allowed_simple_move_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);

// The simple move for triangular world
void simple_move_triangular(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// Function testing if the simple jump in a triangular world frome ex_idx to new_idx is possible 
int is_allowed_simple_jump_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);

// The simple jump for triangular world
void simple_jump_triangular(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// Is allowed function for multiply jump triangular world.
int is_allowed_multi_jump_triangular_world(struct world_t* world, enum players player, unsigned int ex_idx);

// Multiply jump function for triangular world. Returns the end position of the multiply jump.
int multi_jump_triangular_world(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx);


#endif 