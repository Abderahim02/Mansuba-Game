#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "world.h"
struct world_t{ 
  enum color_t colors[WORLD_SIZE];
  enum sort_t sorts[WORLD_SIZE];
};

struct world_t world;
struct world_t* world_init(){
  for(int i=0; i < WORLD_SIZE; ++i){ 
      world.colors[i] = NO_COLOR;   
      world.sorts[i] = NO_SORT;
  }
    return &world ;
}

enum color_t world_get( const struct world_t* b, unsigned int idx){
  return b->colors[idx] ;
}
// j'ai rencontré un problème lorsque je veux créer un monde du au fait que world_get prend un const struct world_t* 
void world_set(struct world_t* b, unsigned int idx, enum color_t c){
  b->colors[idx] = c;
}
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
  return b->sorts[idx] ;
}
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
  b->sorts[idx] = c;
}


/*
int main(int argc, char *argv[]){
    return 0;
    }



Version 2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"world.h"

// ____________________________________
struct world_t
{
    // The available places in the Game.
    // Using two Arrays for defining the color and the sort on a position;
    enum color_t colors[WORLD_SIZE];
    enum sort_t sorts[WORLD_SIZE];

};

// ____________________________________
struct world_t* world_init() 
{
    struct world_t world;
    // No color, no sort everywhere in the begining.
    for (int i = 0; i <= WORLD_SIZE; ++i) {
        world.colors[i] = NO_COLOR;
        world.sorts[i] = NO_SORT;
    }
    return 0;
}


// ___________________________________
enum color_t world_get(const struct world_t* b, unsigned int idx)
{
    return b->colors[idx];
}


// ___________________________________
void world_set(struct world_t* b, unsigned int idx, enum color_t c)
{
    b->colors[idx] = c;
}


// ____________________________________
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx)
{
    return b->sorts[idx];
}


//_____________________________________
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c)
{
    b->sorts[idx] = c;
}

*/

/*
// The main function, mainly for testing.
int main(int argc, char *argv[])
{
    struct world_t world;
    // Initializing a world with NO_COLORS and NO_SORTS.
    world_init();
    for (int i = 0; i < 4; ++i) {
        // A Test for world_get
        // printf("The color of the position %d is: %d\n", i, world.colors[i]);
        printf("The color of the position %d is: %d\n", i, world_get(world.colors,i));

    }
    
    // A Test for world_set
    world_set(world.colors, 2, BLACK);
    printf("The color of the position %d is: %d\n", 2, world_get(world.colors,2));
    


    printf("world.c is compiling.\n"); // Test for Makefile
    return 0;
}
*/
