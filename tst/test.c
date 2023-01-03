
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "triangular_world.h"
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
    // We know in the beginning in the middle of the world there are no PAWNS.
    if (world_get(world,WIDTH+(WIDTH/2)) == NO_COLOR && world_get_sort(world,WIDTH+(WIDTH/2)) == NO_SORT) {
        printf("World_get_Test1 passed.\n");
    }
    if (world_get(world,WIDTH+(WIDTH/2)) != NO_COLOR || world_get_sort(world,WIDTH+(WIDTH/2)) != NO_SORT) {
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

void test_move_tower_white_1(struct world_t* world, struct positions_info infos) {
    // Check forward move with tower
    int a = 20;
    int b = 29;
    world_set_sort(world, a, TOWER);
    world_set_sort(world, b, NO_SORT);
    world_set(world, b, NO_COLOR);
    // print_world(world);
    // printf("\n");
    // Test player White x-move
    if (is_allowed_tower_move(world, PLAYER_WHITE, a)) {
        tower_move(world, PLAYER_WHITE, &infos, a);
        if (world_get_sort(world, a) == 0 && world_get_sort(world, b) == 2) {
            printf("Test1 for move tower passed.\n");
        }
        else {
            printf("Test1 for move tower failed.\n");
        }
    }
    // print_world(world);
    // printf("\n");
}


void test_move_tower_white_2(struct world_t* world, struct positions_info infos) {
    // Check forward move with tower
    int a = 29;
    int b = 39;
    world_set_sort(world, a, TOWER);
    world_set(world, a, WHITE);
    world_set_sort(world, b, NO_SORT);
    world_set(world, b, NO_COLOR);
    // print_world(world);
    // printf("\n");
    if (is_allowed_tower_move(world, PLAYER_WHITE, a)) {
        tower_move(world, PLAYER_WHITE, &infos, a);
        if (world_get_sort(world, a) == 0 && world_get_sort(world, b) == 2) {
            printf("Test2 for move tower passed.\n");
        }
        else {
            printf("Test2 for move tower failed.\n");
        }
    }
    // print_world(world);
    // printf("\n");
}

void test_move_tower_white_y(struct world_t* world, struct positions_info infos) {
    world_set(world, 83, 2);
    world_set_sort(world, 83, TOWER);
    world_set(world, 84, 2);
    world_set_sort(world, 84, PAWN);
    world_set(world,13,1);
    world_set_sort(world,13, PAWN);
    // print_world(world);
    // printf("\n");
    if (is_allowed_tower_move(world, PLAYER_WHITE, 83)) {
       tower_move(world, PLAYER_WHITE, &infos, 83);
       if (world_get(world, 23) == WHITE && world_get_sort(world, 23) == TOWER) {
        printf("Test3 for move tower passed.\n");
       }
       else {
        printf("Test3 for move tower failed.\n");
       }
    } 
    // print_world(world);
    // printf("\n");
}

void test_move_tower_black_1(struct world_t* world, struct positions_info infos) {
    // Check forward move with tower
    int a = 59;
    int b = 50;
    world_set_sort(world, a, TOWER);
    world_set_sort(world, b, NO_SORT);
    world_set(world, b, NO_COLOR);
    // print_world(world);
    // printf("\n");
    if (is_allowed_tower_move(world, PLAYER_BLACK, a)) {
        tower_move(world, PLAYER_BLACK, &infos, a);
        if (world_get_sort(world, a) == 0 && world_get_sort(world, b) == 2) {
            printf("Test4 for move tower passed.\n");
        }
        else {
            printf("Test4 for move tower failed.\n");
        }
    }
    // print_world(world);
    // printf("\n");
}


void test_init_tower_elephant(struct world_t* world) {
    for (int i = 0; i < WORLD_SIZE; ++i) {
        if (i == 0 || i == WORLD_SIZE-WIDTH || i == WIDTH-1 || i == WORLD_SIZE-1) {
            if (world_get_sort(world, i) == TOWER) {
                printf("Test tower passed.\n");
            }
            else {
                printf("Test tower failed.\n");
            }
        }
        if (i == WIDTH || i == WORLD_SIZE-(WIDTH*2) || i == WIDTH*2-1 || i == WORLD_SIZE-WIDTH-1) {
            if (world_get_sort(world, i) == ELEPHANT) {
                printf("Test elephant passed.\n");
            }
            else {
                printf("Test elephant failed.\n");
            } 
        }
    }
}
void test_print_triangular_world(struct world_t* world){
     for(int i=0; i < WORLD_SIZE; ++i ){
        if(i%WIDTH == WIDTH -1){
            if(world_get(world ,i) < MAX_COLOR){
                printf(" %d\n", world_get(world ,i));
            }
            else{
                printf("  \n");
            }
        }
        else{
            //printf(" %d", world_get_sort(world ,i));
            if(world_get(world ,i) < MAX_COLOR){
                printf(" %d", world_get(world ,i));
            }
            else{
                printf("  ");
            }
        }
    }
}


void print_neighbors(struct neighbors_t neighbors){
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        printf("%d est voisin de 76 dans la direction %s\n", neighbors.n[j].i, dir_to_string(neighbors.n[j].d));
    }
}


void test_world_init_2(struct world_t* world){
    print_triangular_world(world);
}

// void test_is_allowed_elephant_move( struct world_t* world, enum players player, struct positions_info* infos){
//     printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, infos, PLAYER_WHITE, infos, 0,2 ));
// }

// Test for the simple move triangular world.
void test_simple_move_triangular_world(struct world_t* world, struct positions_info infos) {
    world_set_sort(world, 44, PAWN);
    world_set(world, 44, WHITE);
    world_set_sort(world, 35, PAWN);
    world_set(world, 35, BLACK);
    world_set_sort(world, 24, PAWN);
    world_set(world, 24, BLACK);
    world_set_sort(world, 55, PAWN);
    world_set(world, 55, BLACK);
    world_set_sort(world, 64, PAWN);
    world_set(world, 64, BLACK);
    if (is_allowed_simple_move_triangular_world(world, PLAYER_BLACK, 44, 55) == 0) {
        printf("Test1 for simple move triangular world passed!\n");
    }
    if (is_allowed_simple_move_triangular_world(world, PLAYER_WHITE, 21, 32)) {
        simple_move_triangular(world, PLAYER_WHITE, &infos, 21, 32);
        if (world_get(world, 32) == WHITE) {
            printf("Test2 for simple move triangular world passed!\n");
        }
        else {
            printf("Test2 for simple move triangular world failed!\n");
        }
    }
}

// The main function for the tests.
int main() {
    struct world_t* world = world_init_2();
    struct positions_info infos;
    init_infos(&infos);
    init_players_triangular(world);
    test_simple_move_triangular_world(world, infos);
    //init_players_1(world);
    /*test_world_get(world);
    test_world_set(world);
    struct neighbors_t neighbors = get_neighbors(5);
    test_get_neighbors(neighbors);

    simple_move_player(world, PLAYER_WHITE, &infos, 0, 1);
    //print_world(world);
     printf("\n");

    // ***********************************
    test_move_tower_white_1(world, infos);
    test_move_tower_white_2(world, infos);
    test_move_tower_white_y(world, infos);
    test_move_tower_black_1(world, infos);
    // ***********************************
    print_world(world);
    printf("\n");
    simple_move_player(world, PLAYER_WHITE, &infos, 20,21);
    printf("\n");
    print_world(world);
    //printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, PLAYER_WHITE, 0, 2));
    elephant_move(world, PLAYER_WHITE, &infos, 0,2);
    printf("\n");
    print_world(world);

    printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, PLAYER_BLACK, 19,8 ));
    elephant_move(world, PLAYER_BLACK, &infos, 19,8);
    print_world(world);

   printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, PLAYER_WHITE , 22, 33));
    tower_move(world, PLAYER_WHITE, &infos, 10);
    print_world(world);
    printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, PLAYER_WHITE , 2, 22));
    elephant_move(world, PLAYER_WHITE, &infos, 2,22);
    print_world(world);

    printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, PLAYER_WHITE, 22, 33));
    elephant_move(world, PLAYER_WHITE, &infos, 22,33);
    print_world(world);*/
    print_triangular_world(world);
    //test_world_init_2(world);
    //print_triangular_world(world);
    // printf("le voisin de 12 est   %d\n", get_neighbor_triangular(12,SOUTH));
    // struct neighbors_t neighbors = get_neighbors_triangular(76);
    // print_neighbors(neighbors);
    return 0;
}
