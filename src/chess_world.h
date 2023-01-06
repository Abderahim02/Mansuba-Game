#ifndef __CHESS_WORLD_H__
#define __CHESS_WORLD_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "triangular_world.h"


// A function printing the chess_world
void print_world_chess( struct world_t* world) ;

// Get_neghbors for the chess_world
struct neighbors_t get_neighbors_chess( unsigned int idx);

// A function testing if its possible to do bishop move in chess_world
int is_allowed_bishop_move_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

// The bishop move in a chess_world
void bishop_move_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

// A function to initialize positions at the begenning of the game
void init_players_chess(struct world_t* b);

// Get the neighbor of a direction. In this world you only have the directions SWEST, SEAST, NEAST and NWEST.
unsigned int get_neighbor_chess(unsigned int idx, enum dir_t d);

// A bool function returns if a simple move for pawn is possible or not.
int is_allowed_simple_move_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);

// The simple move function for a Pawn in chess world.
void simple_move_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// A bool function which returns if a simple jump in chess world is allowed or not.
int is_allowed_simple_jump_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx);

// Simple jump function for the chess world.
void simple_jump_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// A bool function which returns if a multiply jump in chess world is allowed or not.
int is_allowed_multi_jump_chess(struct world_t* world, enum players player, unsigned int ex_idx);

// Multiply jump function for chess world. Returns the end position of the multiply jump.
int multi_jump_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx);

#endif 