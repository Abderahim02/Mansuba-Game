#ifndef __ENSEMBLE_H__
#define __ENSEMBLE_H__

#include "world.h"
#include "neighbors.h"
#define UINT_MAX WORLD_SIZE

enum players{
  PLAYER_WHITE = 2 ,
  PLAYER_BLACK = 1 ,
};

// Use this enum to verify if a piece is a prisoner or not.
enum status{
  NON_PRISONER = 0,
  PRISONER = 1,
};

struct world_t* world_init_2();
enum status_t world_get_status(struct world_t* b, unsigned int idx);
void world_set_status(struct world_t* b, unsigned int idx, enum status_t s);
// The position_info includes the positions in the begin (initial)
// the allowed moves and the where the peaces are at the moment
struct positions_info { 
  /*  at this poin we don't have to define a structure for possible mouvements of each player */
  unsigned int initial_WHITE[HEIGHT]; // initial positions of the player with white pawns
  unsigned int current_pieces_WHITE[HEIGHT]; // current positions of the player with white pawns
  enum status status_pieces_WHITE[HEIGHT]; // Tells us if a piece of white is a prisoner (1) or not (0).
  unsigned int initial_BLACK[HEIGHT];  // initial positions of he player with black pawns
  unsigned int current_pieces_BLACK[HEIGHT]; //current positions of the player with black pawns
  enum status status_pieces_BLACK[HEIGHT]; // Tells us if a piece of black is a prisoner (1) or not (0).
  unsigned int MAX_TURNS; // Maximum allowed turns = WORLD SIZE
  unsigned int TURNS;  // Played turns in the game.
};

// Furthermore it sets the world the beginning position.
void init_players_0(struct world_t* b);
//for the achievement 1
void init_players_1(struct world_t* b);
// Is a bool function and returns 1 if new_idx is a neighbor to ex_idx.
int is_new_ex_neighbor(unsigned int ex_idx, unsigned int new_idx);

// Initialize current pieces for black and white.
void init_infos(struct positions_info* infos);

//a function testing if a pièce is prisoner 
int is_prisoner(enum players player, struct positions_info* infos, unsigned int idx );

// Is a help/bool function, which returns 1 if the 
int is_allowed_to_simple_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// Updated the current pieces.
void update_current_pieces(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// If conditions are ok, a piece moves.
void simple_move_player(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// Simple win function: the winner is the first player to reach with one of his pieces 
// one of the other player's starting positions before MAX_TURNS turns.
int simple_win(struct world_t* world, enum players player, struct positions_info infos);

// Gives back the number of neighbors.
int number_of_neighbors(struct neighbors_t neighbors);

// Bool function. Jump is allowed or not.
int is_allowed_simple_jump(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// simple jump function.
void simple_jump(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx);

// Test function is multiple jump is possible.
unsigned int is_multi_jump_allowed(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx);

// Jumps as long as it is possible.
unsigned int multi_jump(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx);

// Test function to print the world.
void print_world( struct world_t* world);

// Help function.
void print_init_players(struct positions_info positions);

// Help function.
void print_current(struct positions_info positions);

// Bool function for the simple win.
int simple_win(struct world_t* world, enum players player, struct positions_info infos);

// The winner is the first player to cover all the other player's starting positions 
// with his pieces before MAX_TURNS turns.
int complex_win(struct world_t* world, enum players player, struct positions_info infos);

// Another help function.
void print_current_pieces(struct positions_info infos);

// To fix an error.
int count_pieces(struct world_t* world);

//a function testing if idx is a prisonned piece which belongs to the player
// int is_prisoner(enum players player, struct positions_info* infos, unsigned int idx ); 


#endif // __ENSEMBLE_H__