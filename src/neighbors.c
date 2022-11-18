#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "neighbors.h"
#define UINT_MAX 10
// _______________________
void init_neighbors(unsigned int seed) {
    // For the first it should does nothing.
   }

// ________________________ (Maybe we need to add to the idx MINUS 1)
unsigned int get_neighbor(unsigned int idx, enum dir_t d) {
    // Case for beeing on North or South edge of the playing field.
    if ((idx < WIDTH && (d == NORTH || d == NEAST || d == NWEST)) || 
        (idx >= WORLD_SIZE-WIDTH && (d == SOUTH || d == SWEST || d == SEAST))) {
            return UINT_MAX;
        }
    // Case for beeing on the West edge of the playing field.
    else if ((idx % WIDTH == 0 && idx < WORLD_SIZE) && (d == WEST || d == NWEST || d == SWEST)) {
        return UINT_MAX;
    }
    // Case for beeing on the East edge of the playing field.
    else if ((idx % (WIDTH-1) && idx <= WORLD_SIZE) && (d == EAST || d == NEAST || d == SEAST)) {
        return UINT_MAX;
    }
    // Cases for having a neighbour.
    switch (d)
    {
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
      break;
    }
}

struct neighbors_t get_neighbors( unsigned int idx){
  struct neighbors_t neighbors;
  enum dir_t dir = SEAST;
  int j=0;
  while( j < MAX_NEIGHBORS && dir < MAX_DIR){
    if( get_neighbor(idx, dir) != UINT_MAX ){
      neighbors.n[j].i = get_neighbor(idx, dir);  //la boucle va remplir neighbors avec les voisins de idx avec j voisins 
      neighbors.n[j].d = dir;
      ++dir;
      ++j;
    }
  }
  neighbors.n[j+1].i = UINT_MAX; //à  la fin on ajoute l element UNINT_MAX a la j+1 ieme position  
  neighbors.n[j+1].d = NO_DIR;
  return neighbors;
}

/*int main(){
  struct world_t world={{1,1,1,2,1,2,0,0,1},{1,1,1,1,1,1,1,0,0,1}};

  struct neighbors_t neighbors={.n = { {2, NORTH}, {3, SOUTH}, {UINT_MAX, NO_DIR}} } ;
  int i = 0;
  while(i < 3 && neighbors.n[i].d !=UINT_MAX){
    printf("la case %d est un voisin de %d située à %d",i, 2, get_neighbors(2).n.d);
  }
  return 0;
}
*/
int main(){
  return 0;
}
