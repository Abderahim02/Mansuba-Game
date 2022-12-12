#include "pawns.h"

// To get the end position of the field on the x-axle.
unsigned int give_end_position_x(enum players player, unsigned int ex_idx) {
    unsigned int a = ex_idx;
    switch (player) {
    case PLAYER_BLACK:
        while (a % HEIGHT != 0) {
            --a; 
        }
        break;
    case PLAYER_WHITE:
        while (a % HEIGHT-1 != 0) {
            ++a; 
        }
        break;
    default:
        break;
    }
    return a;
}

// To get the end position of the field on the y-axle.
unsigned int give_top_position_y(unsigned int ex_idx) {
    unsigned int a = ex_idx;
    while (a > WIDTH) {
        a = a - WIDTH; 
    }
    return a;
}

unsigned int give_down_position_y(unsigned int ex_idx) {
    unsigned int a = ex_idx;
    while (a < (WORLD_SIZE - WIDTH)) {
        a = a + WIDTH; 
    }
    return a;
}


void tower_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx) {
    unsigned int p = ex_idx;
    switch (player) {
    case PLAYER_BLACK:
        unsigned int p_x = give_end_position_x(PLAYER_BLACK, ex_idx);
        // We prefer the move on the x-axle.
        for (int i = p; i < p_x; --i) {
            // Checking where the next PAWN is.
            if (world_get(world, i) != NO_COLOR) {
                world_set(world, i+1, BLACK);
                world_set(world, ex_idx, NO_COLOR);
                world_set_sort(world, i+1, TOWER);
                world_set_sort(world, ex_idx, NO_SORT);
                update_current_pieces(player, infos, ex_idx, i+1);
                return;
            }
        }
        // After we prefer the move to the top.
        unsigned int p_y = give_top_position_y(ex_idx);
        for (int i = p; i > WIDTH; i = i - WIDTH) {
            // Checking where the next PAWN is.
            if (world_get(world, i) != NO_COLOR) {
                world_set(world, i+1, BLACK);
                world_set(world, ex_idx, NO_COLOR);
                world_set_sort(world, i+1, TOWER);
                world_set_sort(world, ex_idx, NO_SORT);
                update_current_pieces(player, infos, ex_idx, i+1);
                return;
            }
        }
        // Move downwards.
        p_y = give_down_position_y(ex_idx);
        for (int i = p; i < (WORLD_SIZE - WIDTH); i = i + WIDTH) {
            // Checking where the next PAWN is.
            if (world_get(world, i) != NO_COLOR) {
                world_set(world, i+1, BLACK);
                world_set(world, ex_idx, NO_COLOR);
                world_set_sort(world, i+1, TOWER);
                world_set_sort(world, ex_idx, NO_SORT);
                update_current_pieces(player, infos, ex_idx, i+1);
                return;
            }
        }
        break;
    case PLAYER_WHITE:
        unsigned int p_x = give_end_position_x(PLAYER_WHITE, ex_idx);
        // We prefer the move on the x-axle.
        for (int i = p; i < p_x; ++i) {
            // Checking where the next PAWN is.
            if (world_get(world, i) != NO_COLOR) {
                world_set(world, i+1, WHITE);
                world_set(world, ex_idx, NO_COLOR);
                world_set_sort(world, i+1, TOWER);
                world_set_sort(world, ex_idx, NO_SORT);
                update_current_pieces(player, infos, ex_idx, i+1);
                return;
            }
        }
        // After we prefer the move to the top.
        unsigned int p_y = give_top_position_y(ex_idx);
        for (int i = p; i > WIDTH; i = i - WIDTH) {
            // Checking where the next PAWN is.
            if (world_get(world, i) != NO_COLOR) {
                world_set(world, i+1, WHITE);
                world_set(world, ex_idx, NO_COLOR);
                world_set_sort(world, i+1, TOWER);
                world_set_sort(world, ex_idx, NO_SORT);
                update_current_pieces(player, infos, ex_idx, i+1);
                return;
            }
        }
        // Move downwards.
        p_y = give_down_position_y(ex_idx);
        for (int i = p; i < (WORLD_SIZE - WIDTH); i = i + WIDTH) {
            // Checking where the next PAWN is.
            if (world_get(world, i) != NO_COLOR) {
                world_set(world, i+1, WHITE);
                world_set(world, ex_idx, NO_COLOR);
                world_set_sort(world, i+1, TOWER);
                world_set_sort(world, ex_idx, NO_SORT);
                update_current_pieces(player, infos, ex_idx, i+1);
                return;
            }
        }
        break;
    default:
        break;
    }
}

// int main() {
//     unsigned int b = 12;
//     printf("%d is end position for black", give_end_position_x(PLAYER_BLACK, 12));
//     printf("%d is end position for white", give_end_position_x(PLAYER_WHITE, 12));
// }