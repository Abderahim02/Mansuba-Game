// gtest is normaly for C++ but can used for C as well.
// #include <gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensemble.h"

// }
//simple test function for get neighbors of the position 5
void test_get_neighbors(struct world_t* world){
    struct neighbors neighbors = get_neighbors(5);
    for(int j; j<HEIGHT; ++j){
        if(neighbors.n[j].i != UINT_MAX || neighbors.n[j].i ==4 || 14 || neighbors.n[j].i ==15 || neighbors.n[j].i ==16 || neighbors.n[j].i ==15 || neighbors.n[j].i ==6){
            printf("%d is neighbor of 5 in direction %d\n test passed", neighbors.n[j].i, neighbors.n[j].d);
        }
    }
}

