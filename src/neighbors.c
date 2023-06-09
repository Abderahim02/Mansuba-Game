#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neighbors.h"
#define UINT_MAX WORLD_SIZE

static unsigned int s;
/* This function gives the type of world we are in , we did another function get_neighbors_world which is 
defined in complement_ensemble.c , this function returns the list of neighbors depending on the world */
void init_neighbors(unsigned int seed) {
  switch (seed)
  {
  case 8:
    printf("---------WE ARE IN THE CLASSIC WORLD !-----------\n");
    s=seed;
    break;
  case 6:
    printf("---------WE ARE IN THE TRIANGULAR WORLD!----------\n");
    s=seed;
    break;
  case 4:
    printf("---------WE ARE IN THE CHESS WORLD!---------------\n");
    s=seed;
    break;
  default:
    printf("---------------INVALID WORLD!------------------ \n");
    break;
  }
}

unsigned int get_neighbors_seed(){
    return s;
};


unsigned int get_neighbor(unsigned int idx, enum dir_t d) {
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
    // Cases for having a neighbour.
    else{
      switch (d){
    case NORTH:
        return idx - WIDTH;
        break;
    case SOUTH:
        return idx + WIDTH;
        break;
    case EAST:
        return idx + 1;
        break;
    case WEST:
        return idx - 1;
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

struct neighbors_t get_neighbors( unsigned int idx){
  // We initialize the variable neigbors with the UINT_MAX, 0, so that the variable will be static.
  struct neighbors_t neighbors={.n={{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0}}}; 
  enum dir_t dir = SEAST;
  int j=0;
  while( j < MAX_NEIGHBORS && dir < MAX_DIR){
    unsigned int test = get_neighbor(idx, dir);
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
