#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
#include "ensemble.h"
#define UINT_MAX 100

// For creating a real random number.
#include <time.h>

// current player can be 0 = WHITE or 1 = BLACK.
unsigned int current_player = 0;

// function for getting a random player
unsigned int get_random_player() {
    srand(time(0));
    // % will help us to get either 0 or 1.
    int rand_player = rand() % 2;
    return rand_player;
}

// function to get the next player.
unsigned int next_player(int current_player) {
    if (current_player == 0) {
        return 1;
    }
    return 0;
}

// Choosing a random pieces depending on the player.
unsigned int choose_random_piece_belonging_to(struct positions_info infos, unsigned int current_player) {
    unsigned int i = 0;
    srand(time(0));
    switch (current_player) {
    case PLAYER_WHITE:
        i = rand() % HEIGHT;
        return infos.current_pieces_WHITE[i];
        break;
    case PLAYER_BLACK:
        i = rand() % HEIGHT;
        return infos.current_pieces_BLACK[i];
        break;    
    default:
        break;
    }
}

int main() {
    current_player = get_random_player();
    // printf("Random player: %d\n", get_random_player());
    printf("Current player is: %d\n", current_player);
    printf("Next player is: %d\n", next_player(current_player));
}
