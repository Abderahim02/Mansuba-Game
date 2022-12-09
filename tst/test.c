// gtest is normaly for C++ but can used for C as well.
// #include <gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensemble.h"

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


// The main function for the tests.
int main() {
    struct world_t* world = world_init();
    test_world_get(world);
    test_world_set(world);
    return 0;
}
