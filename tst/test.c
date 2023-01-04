
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess_world.h"

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





void test_world_init_2(struct world_t* world){
    print_triangular_world(world);
}

// void test_is_allowed_elephant_move( struct world_t* world, enum players player, struct positions_info* infos){
//     printf("le mouvement elephant est: %d\n", is_allowed_elephant_move(world, infos, PLAYER_WHITE, infos, 0,2 ));
// }

// Test for the simple move triangular world.
void test_simple_move_triangular_world(struct world_t* world, struct positions_info infos) {
    world_set_sort(world, 34, PAWN);
    world_set(world, 34, WHITE);
    world_set_sort(world, 25, PAWN);
    world_set(world, 25, BLACK);
    world_set_sort(world, 14, PAWN);
    world_set(world, 14, BLACK);
    world_set_sort(world, 45, PAWN);
    world_set(world, 45, BLACK);
    world_set_sort(world, 54, PAWN);
    world_set(world, 54, BLACK);
    if (is_allowed_simple_move_triangular_world(world, PLAYER_BLACK, 34, 45) == 0) {
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

// Test for the simple jump in the triangular world.
void test_simple_jump_triangular_world(struct world_t* world, struct positions_info infos) {
    world_set_sort(world, 34, PAWN);
    world_set(world, 34, WHITE);
    world_set_sort(world, 25, PAWN);
    world_set(world, 25, BLACK);
    world_set_sort(world, 14, PAWN);
    world_set(world, 14, BLACK);
    world_set_sort(world, 45, PAWN);
    world_set(world, 45, BLACK);
    world_set_sort(world, 54, PAWN);
    world_set(world, 54, BLACK);
    if (is_allowed_simple_jump_triangular_world(world, PLAYER_WHITE, 34, 16)) {
        printf("Test 1 simple jump triangular world PASSED!\n");
    }
    if (is_allowed_simple_jump_triangular_world(world, PLAYER_WHITE, 34, 56)) {
        printf("Test 2 simple jump triangular world PASSED!\n");
    }
    if (is_allowed_simple_jump_triangular_world(world, PLAYER_WHITE, 34, 74)) {
        printf("Test 3 simple jump triangular world PASSED!\n");
    }
    if (is_allowed_simple_jump_triangular_world(world, PLAYER_WHITE, 34, 14) == 0) {
        printf("Test 4 simple jump triangular world PASSED!\n");
    }
    else {
        printf("One or more test of simple jump triangular world FAILED!\n");
    }
}

void print_neighbors(unsigned int idx){
    struct neighbors_t neighbors= get_neighbors_triangular(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i != UINT_MAX){
        printf("%d est voisin de %d dans la direction %s\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
         }
    }
}

void test_get_neighbors_triangular(){
    int idx = 1;
    struct neighbors_t neighbors= get_neighbors_triangular(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i == 11 || neighbors.n[j].i == 10){
            printf("%d est voisin de %d dans la direction %s : test_passed\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
        }
        
    }
    printf("\n");
    idx = 56;
    neighbors= get_neighbors_triangular(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i == 65 || neighbors.n[j].i == 76 || neighbors.n[j].i == 67 || neighbors.n[j].i == 45 || neighbors.n[j].i == 36|| neighbors.n[j].i == 47 ){
            printf("%d est voisin de %d dans la direction %s : test_passed\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
        }
    }
     printf("\n");
    idx = 49;
    neighbors= get_neighbors_triangular(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i == 29 || neighbors.n[j].i == 38 || neighbors.n[j].i == 58|| neighbors.n[j].i == 69 ){
            printf("%d est voisin de %d dans la direction %s : test_passed\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
        }
    }

}

// The main function for the tests.
int main() {
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    //init_players_triangular(world);
    // test_simple_move_triangular_world(world, infos);
    // test_simple_jump_triangular_world(world, infos);
    init_players_chess(world);
    //elephant_move(world, PLAYER_WHITE, &infos, 0,2);
    print_world_chess(world);
    /*test_world_get(world);
    test_world_set(world);
    struct neighbors_t neighbors = get_neighbors(5);
    test_get_neighbors(neighbors);

    simple_move_player(world, PLAYER_WHITE, &infos, 0, 1);
    
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
    //print_triangular_world(world);
    //test_world_init_2(world);
    //print_triangular_world(world);
   // printf("le voisin de 12 est   %d\n", get_neighbor_triangular(12,SOUTH));
    //print_neighbors(76);
    //printf("bishpo movt is %d\n", is_allowed_bishop_move(world, PLAYER_BLACK, 9, 18, SWEST ));
    // bishop_move(world, PLAYER_BLACK, &infos, 9, 18, SWEST );
    // print_triangular_world(world);
    // bishop_move(world, PLAYER_WHITE, &infos, 10, 54, SEAST );
    // print_triangular_world(world);
    // bishop_move(world, PLAYER_BLACK, &infos, 89, 98, SWEST );
    // print_triangular_world(world);
    // printf("le voisin de 12 est   %d\n", get_neighbor_triangular(12,SOUTH));
    //struct neighbors_t neighbors = get_neighbors_chess(0);
    //print_neighbors(56);
    printf("bishpo movt in chess_world is %d\n", is_allowed_bishop_move_chess(world, PLAYER_BLACK, 19, 73, SWEST ));
    test_get_neighbors_triangular();
    bishop_move_chess(world, PLAYER_BLACK, &infos, 19, 73, SWEST);
    print_world_chess(world);
    return 0;
}
