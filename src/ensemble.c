#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"

// _____________________
struct position_info {
    int initial[HEIGHT];
    int allowed_moves[HEIGHT];
    int current_pieces[HEIGHT];
};

struct player {
    struct position_info position_info;

};

struct players {
    struct player player1;
    struct player player2;
};

// _________________________
void init_players(struct world_t* b) {
    // struct world_t *world = world_init();
    for (int i = 0; i <= WORLD_SIZE; ++i) {
        // In the begin we put the white pieces to the left and the black pieces to the right.
        if (i % WIDTH == 0) {
            world_set(b,i,WHITE);
            world_set_sort(b,i,1);
        }
        else if (i % WIDTH-1 == 0) {
            world_set(b,i,BLACK);
            world_set_sort(b,i,1);       
        }
    }

}


// ________________________
// void update_current_pieces() {}


int main() {
    return 0;
}

