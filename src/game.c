#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
#include "ensemble.h"
// For creating a real random number.
#include <time.h>

#define UINT_MAX 100

enum move_types{
SIMPLE_MOVE = 1,
SIMPLE_JUMP = 2,
MULTIPLE_JUMP = 3, 
};

struct move{
    unsigned int ex_idx;
    unsigned int new_idx;
    enum move_types type;   
};

// current player can be 0 = WHITE or 1 = BLACK.
enum players current_player = PLAYER_WHITE;

// function for getting a random player
enum players get_random_player() {
    // srand(time(0));
    // % will help us to get either 0 or 1.
    int rand_player = (rand() % 2) + 1;
    return rand_player;
}

// function to get the next player.
enum players next_player(int current_player) {
    if (current_player == 1) {
        return 2;
    }
    return 1;
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

int nobody_has_won(struct world_t* world, struct positions_info infos){
    return (simple_win(world, PLAYER_WHITE, infos) || simple_win(world, PLAYER_BLACK, infos))==0;
}


struct move choose_random_move_for_piece(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx){
    struct move move; 
    move.ex_idx = ex_idx;
    unsigned int i=0;
    while(is_allowed_simple_jump(world, ex_idx, i)==0 && is_allowed_to_simple_move(world, ex_idx, i) == 0){
        i = rand() % WORLD_SIZE;
        if (is_multi_jump_allowed(world, player, infos, ex_idx)) {
            move.type = MULTIPLE_JUMP;
            return move;
        }
        if(is_allowed_simple_jump(world, ex_idx, i)){
            move.new_idx = i;
            move.type = SIMPLE_JUMP;
            return move;
        }
        else if (is_allowed_to_simple_move(world, ex_idx, i)){
            move.new_idx = i;
            move.type = SIMPLE_MOVE;
            return move;
        }
        
    } 
    return move;
}

void move_current_player(struct world_t* world, enum players player, struct positions_info infos, struct move move){
    switch (move.type){
        case MULTIPLE_JUMP:
            // multi_jump(world, player, infos, move.ex_idx);
            printf("I did a multiple JUMP!! \n");
            move.new_idx = multi_jump(world, player, infos, move.ex_idx);
            break;
        case SIMPLE_JUMP:
            simple_jump(world, player, infos, move.ex_idx, move.new_idx);
            update_current_pieces(player, &infos, move.ex_idx, move.new_idx);
            break;
        case SIMPLE_MOVE:
            simple_move_player(world, player, infos, move.ex_idx, move.new_idx);
            update_current_pieces(player, &infos, move.ex_idx, move.new_idx);
            break;
        default:
            break;
    }

}



int main(){
    struct world_t* world = world_init();
    struct positions_info infos;
    srand(time(0));
    init_infos_2(&infos);
    init_players(world, infos);
    enum players current_player = get_random_player();
    while(nobody_has_won(world, infos)){
        unsigned int p = choose_random_piece_belonging_to(infos, current_player);
        struct move random_move = choose_random_move_for_piece(world, current_player, infos, p);
        move_current_player( world, current_player, infos, random_move);
        print_world(world);
        printf("\n");
        //printf("Current player:%d Next player %d\n", current_player, next_player(current_player));
        //printf("Choose random peace: %d belonging to: %d\n",choose_random_piece_belonging_to(infos, current_player), current_player);
        update_current_pieces(current_player, &infos, random_move.ex_idx, random_move.new_idx);
        printf("_______________________________________\n");
        print_current_pieces(infos);
        printf("\n");
        current_player = next_player(current_player);
        usleep(500 * 1000);
    }
    return 0;
}

/*
int main(){
  struct world_t* world = world_init();
  struct positions_info positions;
//   struct positions_info* p = init_infos();
  init_infos_2(&positions);
  init_players(world, positions);
  printf("initial board: \n");
  print_world(world);
  printf("\n");

  printf("1st round: \n");
  simple_move_player(world, PLAYER_WHITE, positions, 0, 11);
  update_current_pieces(PLAYER_WHITE, &positions, 0, 11);
  print_world(world);
  printf("\n");
  print_current_pieces(positions);

  printf("2nd round: \n");
  // simple_jump(world, PLAYER_WHITE, positions, 10, 12);
  multi_jump(world, PLAYER_WHITE, positions, 10);
  print_world(world);
  printf("\n");
  //update_current_pieces(WHITE, &positions, 30,1);
  update_current_pieces(PLAYER_WHITE, &positions, 0, 44);
  print_current_pieces(positions);
  printf("%d", positions.TURNS);
  return 0;
}
*/
