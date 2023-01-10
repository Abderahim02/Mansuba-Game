
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess_world.h"
#include "complement_ensemble.h"
//#define UINT_MAX WORLD_SIZE 

// Simple test function for get neighbors of the position 5
void test_get_neighbors( struct neighbors_t neighbors){
    for(int j; j < HEIGHT ; ++j){
        if(neighbors.n[j].i ==4  || neighbors.n[j].i ==14 || neighbors.n[j].i ==16 || neighbors.n[j].i ==15 || neighbors.n[j].i ==6){
            printf("%d is neighbor of 5 in direction %d\n test passed\n", neighbors.n[j].i, neighbors.n[j].d);
        }
    }
}

// A test for the world_get function.
void test_world_get() {
    struct world_t* world = world_init();
    // We know in the beginning in the middle of the world there are no PAWNS.
    if (world_get(world,WIDTH+(WIDTH/2)) == NO_COLOR && world_get_sort(world,WIDTH+(WIDTH/2)) == NO_SORT) {
        printf("World get Test1 PASSED.\n");
    }
    if (world_get(world,WIDTH+(WIDTH/2)) != NO_COLOR || world_get_sort(world,WIDTH+(WIDTH/2)) != NO_SORT) {
        printf("World get Test1 FAILED.\n");
    }
}

// A test for the world_set function.
void test_world_set() {
    struct world_t* world = world_init();
    world_set(world, 15, BLACK);
    world_set_sort(world, 18, PAWN);
    if (world_get(world,15) == BLACK && world_get_sort(world,18) == PAWN) {
        printf("World set Test1 PASSED.\n");
    }
    if (world_get(world,15) != BLACK || world_get_sort(world,18) != PAWN) {
        printf("World set Test1 FAILED.\n");
    }
}

// A test for the movment of the white tower.
void test_move_tower_white_1() {
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    init_players_1(world);
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
            printf("Test1 for move tower PASSED.\n");
        }
        else {
            printf("Test1 for move tower FAILED.\n");
        }
    }
    // print_world(world);
    // printf("\n");
}

// A function doing a test for the auxilary function move_tower_white_2
void test_move_tower_white_2() {
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    init_players_1(world);
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
            printf("Test2 for move tower PASSED.\n");
        }
        else {
            printf("Test2 for move tower FAILED.\n");
        }
    }
    // print_world(world);
    // printf("\n");
}

// Another test for the tower move.
void test_move_tower_white_y() {
    struct world_t* world = world_init();
    struct positions_info infos;
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
        printf("Test3 for move tower PASSED.\n");
       }
       else {
        printf("Test3 for move tower FAILED.\n");
       }
    } 
    // print_world(world);
    // printf("\n");
}

// Another test for the tower move.
void test_move_tower_black_1() {
    struct world_t* world = world_init();
    struct positions_info infos;
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
            printf("Test4 for move tower PASSED.\n");
        }
        else {
            printf("Test4 for move tower FAILED.\n");
        }
    }
    // print_world(world);
    // printf("\n");
}

// Test for the elephant move.
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

// A function for print test. 
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


// Test for the simple move triangular world.
void test_simple_move_triangular_world() {
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    world_set_sort(world, 34, PAWN);
    world_set(world, 34, WHITE);
    infos.current_pieces_WHITE[0] = 34; 
    world_set_sort(world, 25, PAWN);
    world_set(world, 25, BLACK);
    world_set_sort(world, 14, PAWN);
    world_set(world, 14, BLACK);
    world_set_sort(world, 45, PAWN);
    world_set(world, 45, BLACK);
    infos.current_pieces_BLACK[0] = 45;
    world_set_sort(world, 54, PAWN);
    world_set(world, 54, BLACK);
    // print_triangular_world(world);
    // Testing achiev 3: Taking a prisoner.
    if (is_allowed_simple_move_triangular_world(world, &infos, PLAYER_WHITE, 34, 45) == 1) {
        printf("Test1 for simple move triangular world PASSED!\n");
        simple_move_triangular(world,PLAYER_WHITE, &infos, 34, 45);
        if (is_prisoner(PLAYER_BLACK, &infos, 45) == 1) {
            printf("Test2 is PRISONER for simple move triangular world PASSED!\n");
        }
        else {
            printf("Test2 is PRISONER for simple move triangular world FAILED!\n");
        }
    }
    // print_triangular_world(world);
    if (is_allowed_simple_move_triangular_world(world, &infos, PLAYER_WHITE, 21, 32)) {
        simple_move_triangular(world, PLAYER_WHITE, &infos, 21, 32);
        if (world_get(world, 32) == WHITE) {
            printf("Test3 for simple move triangular world PASSED!\n");
        }
        else {
            printf("Test3 for simple move triangular world FAILED!\n");
        }
    }
    // print_triangular_world(world);
}

// Test for the simple jump in the triangular world.
void test_simple_jump_triangular_world() {
    struct world_t* world = world_init();
    struct positions_info infos;
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
    if (is_allowed_simple_jump_triangular_world(world, &infos, PLAYER_WHITE, 34, 16)) {
        printf("Test 1 simple jump triangular world PASSED!\n");
    }
    if (is_allowed_simple_jump_triangular_world(world, &infos, PLAYER_WHITE, 34, 56)) {
        printf("Test 2 simple jump triangular world PASSED!\n");
    }
    if (is_allowed_simple_jump_triangular_world(world, &infos, PLAYER_WHITE, 34, 74)) {
        printf("Test 3 simple jump triangular world PASSED!\n");
    }
    if (is_allowed_simple_jump_triangular_world(world, &infos, PLAYER_WHITE, 34, 14) == 0) {
        printf("Test 4 simple jump triangular world PASSED!\n");
    }
    else {
        printf("One or more test of simple jump triangular world FAILED!\n");
    }
}

// A function printing neghbors of idx
void print_neighbors(unsigned int idx) {
    struct neighbors_t neighbors= get_neighbors_world(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i != UINT_MAX){
        printf("%d est voisin de %d dans la direction %s \n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
         }
    }
}

// A function test for 
void test_get_neighbors_world() {
    int idx = 1;
    struct neighbors_t neighbors= get_neighbors_world(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i == 11 || neighbors.n[j].i == 10){
            printf("%d est voisin de %d dans la direction %s  : test get_neighbors_world passed !\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
        }
        
    }
    printf("\n");
    idx = 56;
    neighbors= get_neighbors_world(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i == 65 || neighbors.n[j].i == 76 || neighbors.n[j].i == 67 || neighbors.n[j].i == 45 || neighbors.n[j].i == 36|| neighbors.n[j].i == 47 ){
            printf("%d est voisin de %d dans la direction %s  : test get_neighbors_world passed !\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
        }
    }
     printf("\n");
    idx = 49;
    neighbors= get_neighbors_world(idx);
    for(int j=0; j< MAX_NEIGHBORS ; ++j ){
        if(neighbors.n[j].i == 29 || neighbors.n[j].i == 38 || neighbors.n[j].i == 58|| neighbors.n[j].i == 69 ){
            printf("%d est voisin de %d dans la direction %s  : test get_neighbors_world passed !\n", neighbors.n[j].i, idx , dir_to_string(neighbors.n[j].d));
        }
    }

}

// A test for simple move in the chess world.
void test_simple_move_chess() {
    struct world_t* world = world_init();
    struct positions_info infos;
    // In the beginning at position 30 is a simple pawn.
    if (is_allowed_simple_move_chess(world, &infos, PLAYER_WHITE, 30, 41)) {
        printf("Test1 simple move chess PASSED.\n");
        simple_move_chess(world, PLAYER_WHITE, &infos, 30, 41);
        if (world_get(world, 30) == NO_COLOR && world_get_sort(world, 30) == NO_SORT &&
            world_get(world, 41) == WHITE && world_get_sort(world, 41) == PAWN) {
                printf("Test2 simple move chess PASSED. \n");
            }
        else {
            printf("Test2 simple move chess FAILED. \n");
        }
    }
    else {
            printf("Test1 simple move chess FAILED. \n");
    }
}

// A test for simple jump in the chess world.
void test_simple_jump_chess() {
    struct world_t* world = world_init();
    struct positions_info infos;
    simple_move_chess(world, PLAYER_WHITE, &infos, 30, 41);
    if (is_allowed_simple_jump_chess(world, PLAYER_WHITE, &infos, 50, 32)) {
        printf("Simple jump chess Test1 PASSED.\n");
        simple_jump_chess(world, PLAYER_WHITE, &infos, 50, 32);
        if (world_get(world, 50) == NO_COLOR && world_get_sort(world, 50) == NO_SORT &&
            world_get(world, 32) == WHITE && world_get_sort(world, 32) == PAWN) {
                printf("Simple jump chess Test2 PASSED. \n");
            }
        else {
            printf("Simple jump chess Test2 FAILED. \n");
        }
    }
    else {
            printf("Simple jump chess Test1 FAILED. \n");
    }
}

void test_elephant_move(){
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    init_players_1(world);
    print_world(world);
    printf("is 12 prisoner? %d", is_prisoner(PLAYER_BLACK, &infos, 12));
    is_allowed_elephant_move(world, PLAYER_WHITE, &infos,  10,12 );
    if(is_allowed_elephant_move(world, PLAYER_WHITE, &infos, 10,21 )){
        printf("test is_allowed_elephant_move: TEST PASSED %d!\n ", is_allowed_elephant_move(world, PLAYER_WHITE,&infos, 10,21 ));
    }
}

// Test of the tower for achiev3.
void test_tower_achiev3() {
    struct world_t* world = world_init();
    struct positions_info infos;
    init_infos(&infos);
    init_neighbors(6);
    init_players_triangular(world);
    // print_triangular_world(world);
    test_get_neighbors_world();
    test_simple_move_triangular_world(world, infos);
    test_simple_jump_triangular_world(world, infos);
    // print_triangular_world(world);
    init_players_1(world);
    // print_world(world);
    // Now the white tower at pos 0 should take the black tower at pos 9 as a prisoner.
    if(is_allowed_tower_move(world, PLAYER_WHITE, 0)) {
        tower_move(world, PLAYER_WHITE, &infos, 0);
        // The conditions to pass the test:
        if(world_get(world, 9) == WHITE && world_get_sort(world, 9) == TOWER && is_prisoner(PLAYER_BLACK, &infos, 9)) {
            printf("Tower test for achiev3 PASSED!\n");
        }
        else {
            printf("Tower test for achiev3 FAILED!\n");
        }
        // printf("is pris: %d\n", is_prisoner(PLAYER_BLACK, &infos, 9));
    }
    // print_world(world);
}


// The main function for the tests.
// In the test functions we are redefining the world because every time we are modifing it.
int main() {
    test_world_get();
    test_world_set();
    test_move_tower_white_1();
    test_move_tower_white_2();
    test_move_tower_white_y();
    test_move_tower_black_1();
    test_simple_move_triangular_world();
    test_simple_jump_triangular_world();
    test_simple_move_chess();
    test_simple_jump_chess();
    test_elephant_move();
    test_tower_achiev3();
    return 0;
}
