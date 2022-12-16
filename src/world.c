#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
// enum status_t {
//   PLAYABLE  = 1,
//   NOT_PLAYABLE = 0,

// };

struct world_t{ 
  enum color_t colors[WORLD_SIZE];
  enum sort_t sorts[WORLD_SIZE];
  //enum status_t status[WORLD_SIZE];
};

// We used malloc, because we can't return a pointer which we defined inside the function.
struct world_t monde ;
struct world_t* world_init(){
  //struct world_t* monde = malloc(sizeof(struct world_t));
  for(int i=0; i < WORLD_SIZE; ++i){ 
      monde.colors[i] = NO_COLOR;   
      monde.sorts[i] = NO_SORT;
  }
    return  &monde;
}
// //this function will destroy the allocated space in memory 
// void destroyWorld (struct world_t* world) {
//     free(world->colors);   
//     free(world->sorts);
//     free(world);
// }

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
//enum world_get_status(struct world_t* b, unsigned int idx, enum sort_t c);
