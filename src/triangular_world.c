#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "triangular_world.h"
#define UINT_MAX 1000

void print_triangular_world(struct world_t* world){
  printf("\n");
   printf("\n");
  for (int i=0; i< WORLD_SIZE ; ++i){
    enum color_t color = world_get(world, i);
    if( i%HEIGHT == 0 && i != 0 ){
            if( color == WHITE ){ // we use green color for white pieces 
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\n\033[31m* \033[0m"); //we use the symbol * for pawn 
                    break;
                case TOWER:
                    printf("\n\033[31m> \033[0m");//we use the symbol > for white tower 
                    break;
                case ELEPHANT:
                    printf("\n\033[31m& \033[0m"); //we use the symbol & for elephant 
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
    // Cases for having a neighbour.we eliminate the east and west directions 
    else{
      switch (d){
    case NORTH:
        return get_neighbor(idx - WIDTH, d); 
        break;
    case SOUTH:
        return get_neighbor(idx + WIDTH, d);
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

//we suppose that idx is a playable position 
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

