#ifndef __CHESS_WORLD_H__
#define __CHESS_WORLD_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chess_world.h"
#include "triangular_world.h"

//a function printing the chess_world
void print_world_chess( struct world_t* world) ;

//get_neghbors for the chess_world
struct neighbors_t get_neighbors_chess( unsigned int idx);

//a function testing if its possible to do bishop move in chess_world
int is_allowed_bishop_move_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

//the bishop move in a chess_world
void bishop_move_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir);

//a function to initialize positions at the begenning of the game
void init_players_chess(struct world_t* b);
#endif 