#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "neighbors.h"
#define UINT_MAX 1000
// _______________________
void init_neighbors(unsigned int seed) {
    // For the first it should does nothing.
   }

// ________________________ (Maybe we need to add to the idx MINUS 1)
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
  struct neighbors_t neighbors={.n={{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0},{UINT_MAX,0}}}; 
  enum dir_t dir = SEAST;
  int j=0;
  /*while( j <= MAX_NEIGHBORS && dir < MAX_DIR){
    if( get_neighbor(idx, dir) != UINT_MAX ){
      neighbors.n[j].i = get_neighbor(idx, dir);  //la boucle va remplir neighbors avec les voisins de idx avec j voisins 
      neighbors.n[j].d = dir;
      dir = dir +1;
      ++j;
    }
    else{
      dir = dir +1;
      ++j;
    }
  }

  
  }*/
  while( j < MAX_NEIGHBORS && dir < MAX_DIR){
    unsigned int test = get_neighbor(idx, dir);
    if( test!= UINT_MAX ){
      neighbors.n[j].i = test;  //la boucle va remplir neighbors avec les voisins de idx avec j voisins 
      neighbors.n[j].d = dir;
      dir = dir +1;
      ++j;
    }
    else{
      dir = dir +1;
    }
  }
 
  /*if( j < MAX_NEIGHBORS) {
    int k=j;
    while( k < MAX_NEIGHBORS){
    neighbors.n[k].i = UINT_MAX; /* we fill the left positions with UINT_MAX everywere 
    because is we put 0 there we will have problems after because 0 is already a position in the world 
    neighbors.n[k].d = NO_DIR;
    ++k;
      }
  }*/
  return neighbors;
}

/*int main(){
  struct neighbors_t nei = get_neighbors(2);
  for (int j=0; j < MAX_NEIGHBORS; ++j){
      printf("le voisin :%d , sa direction : %d\n", nei.n[j].i, nei.n[j].d );
  }

  return 0;
}*/
