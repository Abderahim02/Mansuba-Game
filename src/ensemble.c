#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "ensemble.h"
#define UINT_MAX WORLD_SIZE 


// //this function will destroy the allocated space in memory 
// void destroyWorld (struct world_t* world) {
//     free(world);
// }



// I think that "struct positions_info* init_infos()" was making a lot of problems.
// If you use this function for the initializing, the update function works.
void init_infos(struct positions_info* infos) {
  int a = 0;
  int b = HEIGHT-1;
  for (int i = 0; i < HEIGHT ; ++i){
    infos->current_pieces_BLACK[i] = b;
    infos->initial_BLACK[i] = b;
    infos->current_pieces_WHITE[i] = a;
    infos->initial_WHITE[i] = a;
    a = a + HEIGHT;
    b = b + HEIGHT;
  }
  infos->MAX_TURNS = WORLD_SIZE;
  infos->TURNS = 0;
}

/* it's the function that give for each player his initial positions , we suppose the initially the player with white pawns 
will take the last column at the left edge and the other player will take the last column at the right edge */
void init_players(struct world_t* b) {
    //struct positions_info positions_info;
    for (int i = 0; i < WORLD_SIZE; ++i) {
        // In the begin we put the white pieces to the left and the black pieces to the right.
        if (i % WIDTH == 0) {
            world_set(b,i,WHITE);
            world_set_sort(b,i,1);
        }
        else if ((i% WIDTH)  == WIDTH - 1) {
            world_set(b, i, BLACK);
            world_set_sort(b, i, 1);
        }
    }
}

// A list of functions that will help us for the move_player function :
// this one verify if new_idx is a neighbor of ex_idx.
int is_new_ex_neighbor(unsigned int ex_idx, unsigned int new_idx){
  struct neighbors_t neighbors = get_neighbors(ex_idx); //we use get_neighbor to get the neighbors list of ex_idx 
  for ( int j=0; j < MAX_NEIGHBORS; ++j){
    if(neighbors.n[j].i == new_idx){
      return 1;
    }
  }
  return 0;
}

// For Black peaces we only want to go to the left / west.
int is_neighbor_black(unsigned int ex_idx, unsigned int new_idx) {
  if (new_idx == get_neighbor(ex_idx, NEAST) || new_idx == get_neighbor(ex_idx, EAST) || new_idx == get_neighbor(ex_idx, SEAST)) {
    return 0;
  }
  return 1;
}

// For White peaces we only want to go to the right / east.
int is_neighbor_white(unsigned int ex_idx, unsigned int new_idx) {
  if (new_idx == get_neighbor(ex_idx, NWEST) || new_idx == get_neighbor(ex_idx, WEST) || new_idx == get_neighbor(ex_idx, SWEST)) {
    return 0;
  }
  return 1;
}

// Next two functions are help functions.
int is_current_piece_White( struct positions_info infos, unsigned int ex_idx) {
  for (int i = 0; i < HEIGHT; ++i) {
    if (infos.current_pieces_WHITE[i] == ex_idx) {
      return 1;
    }
  }
  return 0;
}

int is_current_piece_Black( struct positions_info infos, unsigned int ex_idx) {
  for (int i = 0; i < HEIGHT; ++i) {
    if (infos.current_pieces_BLACK[i] == ex_idx) {
      return 1;
    }
  }
  return 0;
}


// This one verify if it is an allowed simple move.
int is_allowed_to_simple_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx){
  switch (player) {
  case PLAYER_WHITE:
    if (is_current_piece_White(*infos, ex_idx)) {
      if (is_new_ex_neighbor(ex_idx, new_idx) && is_neighbor_white(ex_idx, new_idx)) { // we check if new_ex is a neighbor 
        if( world->sorts[new_idx] == 0){ //we check if new_ex is a free position
        return 1;
        }
      }
    }
    break;
  case PLAYER_BLACK:
    if (is_current_piece_Black(*infos, ex_idx) && is_neighbor_black(ex_idx, new_idx)) {
      if (is_new_ex_neighbor(ex_idx, new_idx)){ // we check if new_ex is a neighbor 
        if( world->sorts[new_idx] == 0){ //we check if new_ex is a free position
        return 1;
        }
      }
    }
  
  default:
    break;
  }
  return 0;
}

// This function update player's information after every move.
void update_current_pieces(enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx){
switch (player){
  case PLAYER_BLACK:
      for(int i=0; i < HEIGHT; ++i){
      if( infos->current_pieces_BLACK[i] == ex_idx ){
	        infos->current_pieces_BLACK[i] = new_idx;
          ++infos->TURNS;
        }
      }
      break;
  case PLAYER_WHITE:
      for(int i=0; i < HEIGHT; ++i){
      if( infos->current_pieces_WHITE[i] == ex_idx ){ //we replace the position ex_idx it new_idx
	        infos->current_pieces_WHITE[i] = new_idx;
          ++infos->TURNS;
       }
    }
    break;
  default:
    break;
  }
}

void print_current_pieces(struct positions_info infos){
    for(int i=0 ; i < HEIGHT; ++i){
          printf("%d   %d\n \n", infos.current_pieces_BLACK[i], infos.current_pieces_WHITE[i]);
    }
}

// This is our function that do the move if it is allowed.
void simple_move_player(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx){
  switch (player){
  case PLAYER_BLACK : //player with black_pawns
    if(is_allowed_to_simple_move(world, player, infos, ex_idx, new_idx)){
      world_set(world, new_idx, BLACK);
      world_set(world, ex_idx, NO_COLOR);
      world_set_sort(world, ex_idx, NO_SORT);
      world_set_sort(world, new_idx, PAWN);
      update_current_pieces(player, infos, ex_idx, new_idx);
      // We update the information about the current pieces here, because there is a problem with the index.
    }
    break;
  case PLAYER_WHITE: //player with white_pawn
    if(is_allowed_to_simple_move(world, player, infos, ex_idx, new_idx)){
      world_set(world, new_idx, WHITE);
      world_set(world, ex_idx, NO_COLOR);
      world_set_sort(world, ex_idx, NO_SORT);
      world_set_sort(world, new_idx, PAWN);
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;
  default:
    break;
  }

}
//______________________________________________the jump function_____________________________
// This first auxillary gives us the number of neighbors of a position, it will help us with the loops. 
int number_of_neighbors(struct neighbors_t neighbors) {
  int c=0;
  for(int j=0; j < MAX_NEIGHBORS; ++j){
      if(neighbors.n[j].i < UINT_MAX){
      ++c;
    }
  }
  return c;
}

// This one tells us if the jump is possible
int is_allowed_simple_jump(struct world_t* world, unsigned int ex_idx, unsigned int new_idx){
  if (is_new_ex_neighbor(ex_idx, new_idx) == 0){ // if new_ex is a neighbor we can't jump on it only simple move 
    struct neighbors_t neighbors = get_neighbors(ex_idx); // we get the neighbors of ex_idx  
    int num_ex_idx_neighbors = number_of_neighbors(neighbors); // we get their number
    if(num_ex_idx_neighbors > 0){ // we check if it has no neighbors , in this case the jump is impossible
      for(int j=0; j < num_ex_idx_neighbors ; ++j){  //we see all existants neighbors of ex_idx 
            unsigned int tmp_position = neighbors.n[j].i; // we use tmporary variables to reduce complexity
            enum dir_t tmp_dir = neighbors.n[j].d;
            if(world->sorts[tmp_position] == PAWN){  //if the neighbor position is filled with a pawn
                // struct neighbors_t neighbors_of_tmp = get_neighbors(tmp_position); // we get neighbors of this tmp_position
                unsigned int neighbor_in_same_dir = get_neighbor(tmp_position, tmp_dir); // we get the position that is a neighbor of this tmp_neighbor in the 
                      //same direction that tmp_neighbor is neighbor of ex_idx (we got the neighbor of the neighbor of ex_idx in the same direction)
                if((neighbor_in_same_dir == new_idx)  && (world->sorts[neighbor_in_same_dir] == 0) ){ /*we check if it is the position that we want to go in 
                and if it is empty so that we can jump there */
                  return 1;
               }
            }
    
      }
    }
  }
    return 0;
}

// It's our main jump function.
void simple_jump(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx) {
  switch (player){
    case PLAYER_WHITE:
      if(is_allowed_simple_jump(world, ex_idx, new_idx)){
            world->colors[new_idx] = WHITE;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = PAWN;
            update_current_pieces(player, infos, ex_idx, new_idx);   
      }
      break;
    case PLAYER_BLACK:
        if(is_allowed_simple_jump(world, ex_idx, new_idx)){
            world->colors[new_idx] = BLACK;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = PAWN;
            update_current_pieces(player, infos, ex_idx, new_idx);
      }
      break;
    default:
      break;
  }
}

// Test function is multiple jump is possible.
unsigned int is_multi_jump_allowed(struct world_t* world, enum players player, unsigned int ex_idx) {
unsigned int new_idx= ex_idx;
int a = 1;
  switch (player) {
  case PLAYER_WHITE:
    // We check if two jumps are possible to return true or false.
    for (int b = 0; b < 2; ++b) {
      a = 0;
      // Forward move: For white it means to jump +2
      if (is_allowed_simple_jump(world, new_idx, new_idx+ 2)) {
        a = 1;
        new_idx = new_idx + 2;
      }
      // Forward left move: means to jump 2*width-2.
      else if (is_allowed_simple_jump(world, new_idx, new_idx - (2*WIDTH-2))) {
        a = 1;
        new_idx = new_idx- (2*WIDTH-2);
      }
      // Forward right move: means to jumo 2*width+2.
      else if (is_allowed_simple_jump(world, new_idx, new_idx + (2*WIDTH+2))) {
        a = 1;
        new_idx = new_idx + (2*WIDTH+2);
      }
    }
    return a;
    break;
  case PLAYER_BLACK:
    for (int b = 0; b < 2; ++b) {
      a = 0;
      // Forward move: is the same as with player white only mirror-inverted. 
      if (is_allowed_simple_jump(world, new_idx, new_idx - 2)) {
        a = 1;
        new_idx = new_idx - 2;
      }
      // Forward left move
      else if (is_allowed_simple_jump(world, ex_idx, ex_idx + (2*WIDTH-2))) {
        a = 1;
        new_idx = new_idx + (2*WIDTH-2);
      }
      // Forward right move
      else if (is_allowed_simple_jump(world, new_idx, new_idx- (2*WIDTH+2))) {
        a = 1;
        new_idx = new_idx - (2*WIDTH+2);
      }
    }
    return a;
    break;
  default:
    break;
  }
  return a;
}

// Multiple jump function: it will return the ending position of the multi jump.
unsigned int multi_jump(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx) {
  unsigned int new_idx = ex_idx;
  int a = 1;
  switch (player) {
  case PLAYER_WHITE:
    while (a) {
      a = 0;
      // Forward move: For white it means to jump +2.
      if (is_allowed_simple_jump(world, new_idx, new_idx + 2)) {
        simple_jump(world, PLAYER_WHITE, infos, new_idx, new_idx + 2);
        a = 1;
        new_idx = new_idx + 2;
      }
      // Forward left move: means to jump 2*width-2.
      else if (is_allowed_simple_jump(world, new_idx, new_idx - (2*WIDTH-2))) {
        simple_jump(world, PLAYER_WHITE, infos, new_idx, new_idx - (2*WIDTH-2));
        a = 1;
        new_idx = new_idx - (2*WIDTH-2);
      }
      // Forward right move: means to jumo 2*width+2.
      else if (is_allowed_simple_jump(world, new_idx, new_idx + (2*WIDTH+2))) {
        simple_jump(world, PLAYER_WHITE, infos, new_idx, new_idx + (2*WIDTH+2));
        a = 1;
        new_idx = new_idx + (2*WIDTH+2);
      }
    }
    break;
  case PLAYER_BLACK:
    while (a) {
      a = 0;
      // Forward move: Is the same as with player white only mirror-inverted. 
      if (is_allowed_simple_jump(world, new_idx, new_idx - 2)) {
        simple_jump(world, PLAYER_BLACK, infos, new_idx, new_idx - 2);
        a = 1;
        new_idx = new_idx - 2;
      }
      // Forward left move.
      else if (is_allowed_simple_jump(world, new_idx, new_idx + (2*WIDTH-2))) {
        simple_jump(world, PLAYER_BLACK, infos, new_idx, new_idx + (2*WIDTH-2));
        a = 1;
        new_idx = new_idx + (2*WIDTH-2);
      }
      // Forward right move.
      else if (is_allowed_simple_jump(world, new_idx, new_idx - (2*WIDTH+2))) {
        simple_jump(world, PLAYER_BLACK, infos, new_idx, new_idx - (2*WIDTH+2));
        a = 1;
        new_idx= new_idx - (2*WIDTH+2);
      }
    }
    break;
  default:
    break;
  }
  return new_idx;
}

// This one print our world so we that we can see changes every time
void print_world( struct world_t* world) {
  for (int i=0; i< WORLD_SIZE ; ++i){
    if( i%HEIGHT == 0 && i != 0 ){
      //printf("\n%d ", world->colors[i]);
      //printf("\n \033%d", world->colors[i]);    
      if(world->colors[i]==WHITE ){ //with red 
        //printf("\n\033[31m%d \033[0m", world->colors[i]);
        switch (world->sorts[i]){
          case PAWN:
              printf("\n\033[31m* \033[0m");
              break;
          case TOWER:
              printf("\n\033[31m> \033[0m");
              break;
          case ELEPHANT:
              printf("\n\033[31m& \033[0m");
              break;
          default:
              break;
        }
      }
      else if(world->colors[i]==BLACK ){
        //printf("\n\033[32m%d \033[0m", world->colors[i]);
        //printf("\n\033[32m* \033[0m");
        switch (world->sorts[i]){
          case PAWN:
              printf("\n\033[1;32m* \033[0m");
              break;
          case TOWER:
              printf("\n\033[1;32m< \033[0m");
              break;
          case ELEPHANT:
             printf("\n\033[1;32m& \033[0m");
              break;
          default:
              break;
        }
      }
      else{
        //printf("\n\033[37m%d \033[0m", world->colors[i]);
        printf("\n\033[1;37m0 \033[0m");
      }
    }
    else {
      //printf("%d ", world->colors[i]);
      // printf(" \033%d", world->colors[i]); 
      //printf("\033[31m%d ", world->colors[i]);      
      if(world->colors[i]==WHITE ){
        //printf("\033[31m%d \033[0m", world->colors[i]);
        //printf("\033[31m* \033[0m");
        switch (world->sorts[i]){
          case PAWN:
              printf("\033[1;31m* \033[0m");
              break;
          case TOWER:
              printf("\033[1;31m> \033[0m");
              break;
          case ELEPHANT:
             printf("\033[1;31m& \033[0m");
              break;
          default:
              break;
        }
        
      }
      else if(world->colors[i]==BLACK ){
        //printf("\033[32m%d \033[0m", world->colors[i]);
        //printf("\033[32m* \033[0m");
        switch (world->sorts[i]){
          case PAWN:
              printf("\033[1;32m* \033[0m");
              break;
          case TOWER:
             printf("\033[1;32m< \033[0m");
              break;
          case ELEPHANT:
             printf("\033[1;32m& \033[0m");
              break;
          default:
              break;
        }
        
      }
      else{
        //printf("\033[37m%d \033[0m", world->colors[i]);
        printf("\033[1;37m0 \033[0m");
      }    
    }
  }
  printf("\n");
}

// Test functions.
void print_init_players(struct positions_info positions) {
  for(int i=0; i<HEIGHT; ++i){
    printf("%d   %d\n ", positions.current_pieces_BLACK[i], positions.current_pieces_WHITE[i]);

  }
}

void print_current(struct positions_info positions) {
  for(int i=0; i<HEIGHT; ++i ){
    printf("%d   %d\n ", positions.current_pieces_BLACK[i], positions.current_pieces_WHITE[i]);
  }
}

// Simple win function: The winner is the first player to reach with one of his pieces 
// one of the other player's starting positions before MAX_TURNS turns.
int simple_win(struct world_t* world, enum players player, struct positions_info infos) {
  if (infos.TURNS <= infos.MAX_TURNS) {
    switch (player)
    {
    case PLAYER_WHITE:
      // PLAYER_WHITE has to reach init_position of PLAYER_BLACK to win.
      for (int i = 1; i < HEIGHT; ++i) {
        if (world->colors[infos.initial_BLACK[i]] == WHITE) {
          return 1;
        }
      }
      break;
    case PLAYER_BLACK:
      // PLAYER_BLACK has to reach init_position of PLAYER_WHITE to win.
      for (int i = 0; i < HEIGHT; ++i) {
        if (world->colors[infos.initial_WHITE[i]] == BLACK) {
          return 1;
        }
      } 
      break;
    default:
      break;
    }
  }
  return 0;
}

// The winner is the first player to cover all the other player's starting positions 
// with his pieces before MAX_TURNS turns.
int complex_win(struct world_t* world, enum players player, struct positions_info infos) {
  if (infos.TURNS <= infos.MAX_TURNS) {
    switch (player)
    {
    case PLAYER_WHITE:
      // PLAYER_WHITE has to reach all init_position of PLAYER_BLACK to win.
      for (int i = 1; i < WORLD_SIZE; ++i) {
        if (world->colors[infos.initial_BLACK[i]] != WHITE) {
          return 0;
        }
      } 
      break;
    case PLAYER_BLACK:
      // PLAYER_BLACK has to reach all init_position of PLAYER_WHITE to win.
      for (int i = 0; i < WORLD_SIZE; ++i) {
        if (world->colors[infos.initial_WHITE[i]] != BLACK) {
          return 0;
        }
      } 
      break;
    default:
      break;
    }
    // The function must reach this line to fulfill all requested conditions of winning.
    return 1;
  }
  return 0;
}

// Used this function to be sure the peaces are updated.
int count_pieces(struct world_t* world) {
    int b = 0;
    int w = 0;
    for (int i = 0; i < WORLD_SIZE; ++i) {
        if (world->colors[i] == BLACK) {
          ++b;
        }
        if (world->colors[i] == WHITE) {
          ++w;
        }
    }
    if (b == 10) {
      if (w == 10) {
        return w;
      }
      return w;
    }
    return b;
}
