#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"


struct world_t{ 
  enum color_t colors[WORLD_SIZE];
  enum sort_t sorts[WORLD_SIZE];
};

struct world_t monde ;
struct world_t* world_init(){
  //struct world_t* monde = malloc(sizeof(struct world_t));
  for(int i=0; i < WORLD_SIZE; ++i){ 
      monde.colors[i] = NO_COLOR;   
      monde.sorts[i] = NO_SORT;
  }
    return  &monde;
}

enum color_t world_get( const struct world_t* b, unsigned int idx){
  return b->colors[idx] ;
}

void world_set(struct world_t* b, unsigned int idx, enum color_t c){
  b->colors[idx] = c;
}

enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
  return b->sorts[idx] ;
}

void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
  b->sorts[idx] = c;
}
