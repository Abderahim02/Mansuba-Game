
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensemble.h"
#define UINT_MAX WORLD_SIZE 

//simple test function for get neighbors of the position 5
void test_get_neighbors( struct neighbors_t neighbors){
    for(int j; j < HEIGHT ; ++j){
        if(neighbors.n[j].i ==4  || neighbors.n[j].i ==14 || neighbors.n[j].i ==16 || neighbors.n[j].i ==15 || neighbors.n[j].i ==6){
            printf("%d is neighbor of 5 in direction %d\n test passed\n", neighbors.n[j].i, neighbors.n[j].d);
        }
    }
}

// A test for the world_get() function.
void test_world_get(struct world_t* world) {
    if (world_get(world,20) == NO_COLOR && world_get_sort(world,10) == NO_SORT) {
        printf("World_get_Test1 passed.\n");
    }
    if (world_get(world,20) != NO_COLOR || world_get_sort(world,10) != NO_SORT) {
        printf("World_get_Test1 failed.\n");
    }
}

// A test for the world_set function.
void test_world_set(struct world_t* world) {
    world_set(world, 15, BLACK);
    world_set_sort(world, 18, PAWN);
    if (world_get(world,15) == BLACK && world_get_sort(world,18) == PAWN) {
        printf("World_get_Test1 passed.\n");
    }
    if (world_get(world,15) != BLACK || world_get_sort(world,18) != PAWN) {
        printf("World_get_Test1 failed.\n");
    }
}

// void test_is_allowed_elephant_move( struct world_t* world, enum players player, struct positions_info* infos){
//     printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, infos, PLAYER_WHITE, infos, 0,2 ));
// }

// The main function for the tests.
int main() {
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    init_players(world);
    /*test_world_get(world);
    test_world_set(world);
    struct neighbors_t neighbors = get_neighbors(5);
    test_get_neighbors(neighbors);
    */
    //simple_move_player(world, PLAYER_WHITE, &infos, 0, 1);
    print_world(world);
    // test_is_allowed_elephant_move(world, PLAYER_WHITE, &infos );
    //simple_move_player(world, PLAYER_WHITE, &infos, 20,21);
    printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, PLAYER_WHITE, &infos , 0, 2));
    return 0;
}
