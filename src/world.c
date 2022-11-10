#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"world.h"

// ____________________________________
struct world_t
{
    // The available places in the Game.
    int position[WORLD_SIZE-1];
    // The two players of the Game.
    enum current_player{Player1 = 1, Player2 = 2};
    enum next_player{Playe1 = 1, Playe2 = 2};
    // Maximum of allowed Moves.
    int MAX_TURNS;

};

// ____________________________________
struct world_t* world_init() 
{
    struct world_t world;
    // Define maximum of turns.
    world.MAX_TURNS = 2*WORLD_SIZE;
    // No color, no sort everywhere in the begining.
    for (int i = 0; i <= WORLD_SIZE; ++i) {
        world.position[i] = 0;
    }
}

/*
// ___________________________________
enum color_t world_get(const struct world_t* b, unsigned int idx)
{

}

// ___________________________________
void world_set(struct world_t* b, unsigned int idx, enum color_t c)
{

}

// ____________________________________
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx)
{

}

//_____________________________________
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c)
{

}
*/

// The main function. (mainly for testing)
int main(int argc, char *argv[])
{
    printf("world.c is compiling.\n"); // Test for Makefile
    return 0;
}