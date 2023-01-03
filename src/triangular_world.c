#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "triangular_world.h"
#define UINT_MAX 1000

//A function printing the triangular world 
void print_triangular_world(struct world_t* world){
  printf("\n");
   printf("\n");
  for (int i=0; i< WORLD_SIZE ; ++i){
    enum color_t color = world_get(world, i);
    if( i%HEIGHT == 0 && i != 0 ){
            if( color == WHITE ){ // we use green color for white pieces 
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\n\033[1;31m* \033[0m"); //we use the symbol * for pawn 
                    break;
                case TOWER:
                    printf("\n\033[1;31m> \033[0m");//we use the symbol > for white tower 
                    break;
                case ELEPHANT:
                    printf("\n\033[1;31m& \033[0m"); //we use the symbol & for elephant 
                    break;
                case BISHOP:
                    printf("\n\033[1;31m# \033[0m"); //we use the symbol & for elephant 
                    break;
                default:
                    break;
                }
            }
            else if(color == BLACK ){ // we use red color for white pieces 
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\n\033[1;32m* \033[0m");
                    break;
                case TOWER:
                    printf("\n\033[1;32m< \033[0m");
                    break;
                case ELEPHANT:
                    printf("\n\033[1;32m& \033[0m");
                    break;
                case BISHOP:
                    printf("\n\033[1;32m# \033[0m");
                    break;
                default:
                    break;
                }
            }
            else if( color == NO_COLOR){
                printf("\n\033[1;37m0 \033[0m");
            }
            else{
                printf("\n\033[1;37m  \033[0m");
            }
         }
    else  {   
            if(color == WHITE ){
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\033[1;31m* \033[0m");
                    break;
                case TOWER:
                    printf("\033[1;31m> \033[0m");
                    break;
                case ELEPHANT:
                    printf("\033[1;31m& \033[0m");
                    break;
                case BISHOP:
                    printf("\033[1;31m# \033[0m");
                    break;
                default:
                    break;
                }
                
            }
            else if(world_get(world, i) == BLACK ){
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\033[1;32m* \033[0m");
                    break;
                case TOWER:
                    printf("\033[1;32m< \033[0m");
                    break;
                case ELEPHANT:
                    printf("\033[1;32m& \033[0m");
                    break;
                case BISHOP:
                    printf("\033[1;32m# \033[0m");
                    break;
                default:
                    break;
                }
            }
            else if(color == NO_COLOR){
                printf("\033[1;37m0 \033[0m");
            }    
            else{
                printf("\033[1;37m  \033[0m");
            }
    }
  }
  printf("\n");
}

/*A function returning the neighbor of idx in direction d in the triangular board ,
we suppose that idx is a playable position */
unsigned int get_neighbor_triangular(unsigned int idx, enum dir_t d) {
    // Case for beeing on North or South edge of the playing field.
    if ((idx < WIDTH && (d == NORTH || d == NEAST || d == NWEST)) || 
        (idx > WORLD_SIZE - WIDTH && (d == SOUTH || d == SWEST || d == SEAST))) {
            return UINT_MAX;
        }
    // Case for beeing on the West edge of the playing field.
    else if ( idx % WIDTH == 0  && (d == WEST || d == NWEST || d == SWEST)) {
        return UINT_MAX;
    }
    // Case for beeing on the East edge of the playing field.
    else if ( idx % WIDTH == WIDTH-1 && (d == EAST || d == NEAST || d == SEAST)) {
        return UINT_MAX;
    }
    else if ( (idx == 0  || idx == WIDTH - 1) && d == NORTH){
      return UINT_MAX;
    }
    else if ( (idx == WORLD_SIZE - WIDTH || idx == WORLD_SIZE - 1) &&  d == SOUTH){
      return UINT_MAX;
    }
    // Cases for having a neighbour. NB: we eliminate the east and west directions 
    else{
      switch (d){
    case NORTH:
        return get_neighbor(idx - WIDTH, d); //we got the neighbor of idx - width in the same direction
        break;
    case SOUTH:
        return get_neighbor(idx + WIDTH, d); // same
        break;
    case NEAST:
        return idx - (WIDTH-1);
        break;
    case NWEST:
        return idx - (WIDTH+1);
        break;
    case SEAST:
        return idx + (WIDTH+1);
        break;
    case SWEST:
      return idx + (WIDTH-1);
      break;
    default: 
      return UINT_MAX;
      }
    }
}

/*A function returning the list of neghbors of idx in the triangular board ,
we suppose that idx is a playable position */

struct neighbors_t get_neighbors_triangular( unsigned int idx){
  // We initialize the variable neigbors with the UINT_MAX, 0, so that the variable will be static.
  struct neighbors_t neighbors={.n={{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0}}}; 
  enum dir_t dir = SEAST;
  int j=0;
  while( j < MAX_NEIGHBORS && dir < MAX_DIR){
    unsigned int test = get_neighbor_triangular(idx, dir);
    if( test!= UINT_MAX ){
      neighbors.n[j].i = test;  // The while loop fills the first j positions with the neigbors. 
      neighbors.n[j].d = dir;
      dir = dir +1;
      ++j;
    }
    else{
      dir = dir +1;
    }
  }
  return neighbors;
}

//A function returning 1 if idx  is a playable position in the board 
int is_playable_position(struct world_t* world, unsigned int idx){
    if(world_get_sort(world,idx) == MAX_SORT){
        return 0;
    }
    return 1;
}

//Initialize the positions of players at the beginning of the game 
void init_players_triangular(struct world_t* b) {
    for (unsigned int i = 0; i < WORLD_SIZE; ++i) {
        // In the begin we put the white pieces to the left and the black pieces to the right.
        if (i % WIDTH == 0 && is_playable_position(b, i)) {
            world_set(b,i,WHITE);
            // Two towers in the edge of the world.
            if (i == WIDTH || i == WORLD_SIZE-WIDTH) {
              world_set_sort(b,i,BISHOP);
            }
            // Two elephants next to the towers.
            // else if (i == 3*WIDTH || i == WORLD_SIZE-3*WIDTH ) {
            //   world_set_sort(b, i, ELEPHANT);
            // }
            else {
              world_set_sort(b,i,PAWN);  
            }
        }
        else if ((i% WIDTH)  == WIDTH - 1 && is_playable_position(b, i)) {
            world_set(b, i, BLACK);
            if (i == WIDTH-1 || i == WORLD_SIZE - WIDTH - 1) {
              world_set_sort(b,i,BISHOP);
            }
            // Two elephants next to the towers.
            // else if (i == WIDTH*3 - 1 || i == WORLD_SIZE- 3*WIDTH - 1) {
            //   world_set_sort(b, i, ELEPHANT);
            // }
            else {
              world_set_sort(b,i,PAWN);  
            }
        }
    }
}

// this one verify if new_idx is a neighbor of ex_idx in a triangular world.
int is_new_ex_neighbor_triangular(unsigned int ex_idx, unsigned int new_idx){
  struct neighbors_t neighbors = get_neighbors_triangular(ex_idx); //we use get_neighbor to get the neighbors list of ex_idx 
  for ( int j=0; j < MAX_NEIGHBORS; ++j){
    if(neighbors.n[j].i == new_idx){
      return 1;
    }
  }
  return 0;
}

int is_valid_cardinal_dir(enum dir_t dir){
    if( dir == NORTH || dir == SOUTH ){
        return 1;
    }
    return 0;
}

//Im not sure about this ............................. there is a problem with the elephant move in this world
int is_allowed_to_simple_move_aux_triangular(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx){
  //if(is_playable_position(new_idx)){ // the new position must be playable
        switch (player) {
        case PLAYER_WHITE:
            if (is_new_ex_neighbor_triangular(ex_idx, new_idx)) { // we check if new_ex is a neighbor 
                if( world_get_sort(world, new_idx) == 0){ //we check if new_ex is a free position
                return 1;
                }
            }
            break;
        case PLAYER_BLACK:
            if (is_new_ex_neighbor_triangular(ex_idx, new_idx)){ // we check if new_ex is a neighbor 
                if( world_get_sort(world, new_idx) == 0){ //we check if new_ex is a free position
                return 1;
                }
            }
        default:
            break;
        }
 // }
  return 0;
}

int is_allowed_bishop_move(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir){
    switch (player){
      case PLAYER_WHITE:
          if(dir == SEAST || dir == NEAST){
            unsigned int start = get_neighbor_triangular( ex_idx, dir);
            unsigned int copy = ex_idx;
            while(is_allowed_to_simple_move_aux_triangular(world, player, copy, start)){
              if(start == new_idx ){
              return start;
              } 
              int tmp = start;
              start = get_neighbor_triangular(start, dir);
              copy = tmp;
            }
          }
            return -1; 
          break;
      case PLAYER_BLACK:
            if(dir == SWEST || dir == NWEST){
            unsigned int start = get_neighbor_triangular( ex_idx, dir);
            unsigned int copy = ex_idx;
            while(is_allowed_to_simple_move_aux_triangular(world, player, copy, start)){
            //   printf("start = %d\n", start);
            //   print_neighbors(start); 
              if(start == new_idx ){
              return start;
              } 
              //printf("\n");
              int tmp = start;
              start = get_neighbor_triangular(start, dir);
              //printf("new_start = %d\n", start);
              copy = tmp;
            }
          }
          return -1;
          break;
      default:
          return -1;
          break;
      }
}

void bishop_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir){
  switch (player){
    case PLAYER_WHITE:
      if(is_allowed_bishop_move(world, player,ex_idx, new_idx, dir) ){
            world_set(world, new_idx, WHITE);
            world_set(world, ex_idx, NO_COLOR);
            world_set_sort(world, ex_idx, NO_SORT);
            world_set_sort(world, new_idx, BISHOP);
            update_current_pieces(player, infos, ex_idx, new_idx);   
      }
      break;
    case PLAYER_BLACK:
        if(is_allowed_bishop_move(world,player, ex_idx, new_idx, dir)){
            world_set(world, new_idx, BLACK);
            world_set(world, ex_idx, NO_COLOR);
            world_set_sort(world, ex_idx, NO_SORT);
            world_set_sort(world, new_idx, BISHOP);
            update_current_pieces(player, infos, ex_idx, new_idx);
      }
      break;
    default:
      break;
  }
}
