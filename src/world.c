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
// //function returning a pointer to a triangular world
// struct world_t world_2;
// struct world_t* world_init_triangular(){
//     unsigned int start = 0;
//     for(int i=1; i <= HEIGHT; ++i){
//         if(i%2==0){
//             for(int j = start; j < i*WIDTH ;){
//                 world_set_sort(&world_2, j, NO_SORT);
//                 world_set(&world_2, j, NO_COLOR);
//                 world_set_sort(&world_2, j+1, MAX_SORT); // id its not playable its sorts = MAX_SORTS
//                 world_set(&world_2, j+1, MAX_COLOR);
//                 j=j+2; // id its not playable its color = MAX_color
//             }
//         }
//         else{
//             for(int j = start; j < i*WIDTH;){
//                 world_set_sort(&world_2, j+1, NO_SORT);
//                 world_set(&world_2, j+1, NO_COLOR);
//                 world_set_sort(&world_2, j, MAX_SORT); // id its not playable its sorts = MAX_SORTS
//                 world_set(&world_2, j, MAX_COLOR);
//                 j=j+2; // id its not playable its color = MAX_color
//             }
//         }
//         start = start + WIDTH ;
//     }
//     return &world_2;
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
