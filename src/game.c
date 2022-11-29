#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
#define UINT_MAX 100
#include <time.h>

enum move_types{
SIMPLE_MOVE = 1;
SIMPLE_JUMP = 2;
MULTIPLE_JUMP = 3; 
};

struct move{
    unsigned int ex_idx;
    unsigned int new_idx;
    enum move_types type;   
};


int nobody_has_won(struct world_t* world, enum players player, struct positions_info infos){
    return (simple_win(world, PLAYER_WHITE, infos) || simple_win(world, PLAYER_BLACK, infos))==0;
}


struct move choose_random_move_for_piece(struct world_t* world, enum players player, struct positions_info infos){
    struct move move; 
    unsigned int ex_idx = choose_random_piece_belonging_to(world, player);
    move.ex_idx = ex_idx;
    unsigned int i=0;
    while(i < WORLD_SIZE){
    if(is_allowed_simple_jump(world, player, infos, ex_idx, i)){
        move.new_ex = i;
        move.type = SIMPLE_JUMP;
        return move;
        }
    else if (is_allowed_to_simple_move(world, player, infos, ex_idx, i)){
        move.new_ex = i;
        move.type = SIMPLE_MOVE;
        -return move;
        }
    else{
        ++i;
        }
    } 
    return move;
}

void move_current_player(struct world_t* world, enum players player, struct positions_info infos, struct move move){
    switch (move.type){
        case SIMPLE_JUMP:
            simple_jump(world, player, infos, move.ex_idx, move.new_ex);
            break;
        case SIMPLE_JUMP:
            simple_move_player(world, player, infos, move.ex_idx, move.new_ex);
            break;
        default:
            break;
    }

}

int main(){
    struct world_t* world = world_init();
    struct positions_info positions = init_infos();
    init_players(world, positions);
    enum players current_player = get_random_player();
    while(nobody_has_has_won(world, current_player, infos)){
        unsigned int p = choose_random_piece_belonging_to();
        struct move random_move = choose_random_move_for_piece(world,current_player, infos);
        move_current_player( world, current_player, infos, random_move);
        print_world(world);
        current_player = next_player(current_player);
    }
    return 0;
}
