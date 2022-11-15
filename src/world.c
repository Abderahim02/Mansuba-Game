#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "world.h"
struct world_t{ 
  enum color_t colors[WORLD_SIZE];
  enum sort_t sorts[WORLD_SIZE];
};

struct world_t* world_init(){
  struct world_t world;
  for(int i=0; i < WORLD_SIZE; ++i){ 
      world.colors[i] = NO_COLOR;   
      world.sorts[i] = NO_SORT;
  }
    return 0 ;
}
enum color_t world_get( const struct world_t* b, unsigned int idx){
  enum color_t color = b->colors[idx];
  return color;
}
// j'ai rencontré un problème lorsque je veux créer un monde du au fait que world_get prend un const struct world_t* 
void world_set(struct world_t* b, unsigned int idx, enum color_t c){
  b->colors[idx] = c;
}
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
  enum sort_t sort = b->sorts[idx];
  return sort;
}
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
  b->sorts[idx] = c;
}

int main(int argc, char *argv[]){
    return 0;
    }
