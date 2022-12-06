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
// we define a structure that will give us all the data about the move
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
    unsigned int i = 1000;
    srand(time(0));
    switch (current_player) {
    case PLAYER_WHITE:
        i = rand() % HEIGHT;
        printf("\nchoosed: %d\n\n",infos.current_pieces_WHITE[i] );
        return infos.current_pieces_WHITE[i];
        break;
    case PLAYER_BLACK:
        i = rand() % HEIGHT;
        printf("\nchoosed: %d\n\n", infos.current_pieces_BLACK[i]);
        return infos.current_pieces_BLACK[i];
        break;    
    default:
        break;
    }
    return 0;
}

//a function that test if there is no winner 
int nobody_has_won(struct world_t* world, struct positions_info infos){
    return (simple_win(world, PLAYER_WHITE, infos) || simple_win(world, PLAYER_BLACK, infos))==0;
}

//this function generate a random possible move for the random choosen piece ex_idx
struct move choose_random_move_for_piece(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx){
    struct move move; 
    move.ex_idx = ex_idx;
    unsigned int i = 45;
    while(is_allowed_simple_jump(world, ex_idx, i)==0 && is_allowed_to_simple_move(world, player, infos, ex_idx, i) == 0 
        && is_multi_jump_allowed(world, player, infos, ex_idx) == 0){
        i = rand() % WORLD_SIZE;
        if (is_multi_jump_allowed(world, player, infos, ex_idx)) { /*we favorises the multiple jump mouvement*/
            move.type = MULTIPLE_JUMP;
            return move;
        }
        else if(is_allowed_simple_jump(world, ex_idx, i)){ /* if it's not possible we go for the simple jump*/
            move.new_idx = i;
            move.type = SIMPLE_JUMP;
            return move;
        }
        else if (is_allowed_to_simple_move(world, player, infos, ex_idx, i)){ /*else we do a simple move*/
            move.new_idx = i;
            move.type = SIMPLE_MOVE;
            return move;
        }
        
    } 
    return move;
}

//_________________simple moves only test______
struct move choose_random_simple_move_for_piece(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx){
    struct move move; 
    move.ex_idx = ex_idx;
    unsigned int i=15; /*we were putting initializing i with 0 and we had a problem of 
number of pieces increasing*/
    while(is_allowed_to_simple_move(world,player, infos,  ex_idx, i)==0 ){
        i = rand() % WORLD_SIZE;
        if (is_allowed_to_simple_move(world,player, infos,  ex_idx, i)){
            move.new_idx = i;
            move.type = SIMPLE_MOVE;
            return move;
        } 
    } 
    return move;
}

//simple moves only
void simple_move_current_player(struct world_t* world, enum players player, struct positions_info* infos, struct move move){
    if(move.type ==SIMPLE_MOVE){
            simple_move_player(world, player, infos, move.ex_idx, move.new_idx);
            //update_current_pieces(current_player, &infos, move.ex_idx, move.new_idx);
    }
    }


//this function does the move
void move_current_player(struct world_t* world, enum players player, struct positions_info* infos, struct move move){
    if (move.type != 0) {
        switch (move.type){
            case MULTIPLE_JUMP:
                multi_jump(world, player, infos, move.ex_idx);
                printf("I did a multiple JUMP!! \n");
                move.new_idx = multi_jump(world, player, infos, move.ex_idx);
                //update_current_pieces(current_player, &infos, move.ex_idx, move.new_idx);
                break;
            case SIMPLE_JUMP:
                simple_jump(world, player, infos, move.ex_idx, move.new_idx);
                // printf("I did a simple JUMP!! \n");
                //update_current_pieces(current_player, &infos, move.ex_idx, move.new_idx);
                break;
            case SIMPLE_MOVE:
                simple_move_player(world, player, infos, move.ex_idx, move.new_idx);
                // printf("I did a simple MOVE!! \n");
                //update_current_pieces(current_player, &infos, move.ex_idx, move.new_idx);
                break;
            default:
                break;
        }
        printf("Player %d move with %d from %d to %d\n",player , move.type, move.ex_idx, move.new_idx);
    }
}


//in function mulyi jump we must use just a copy of ex_idx 
//is allowed to multi jump should return another value like -1 if its not possible, else it should return the position where to go


//The game :
int main(){
    struct world_t* world = world_init();
    struct positions_info infos;
    srand(time(0));
    init_infos_2(&infos);
    init_players(world, infos);
    enum players current_player = get_random_player();
    while(nobody_has_won(world, infos) /*&& infos.TURNS < 100*/){
        unsigned int p = choose_random_piece_belonging_to(infos, current_player);
        struct move random_move = choose_random_move_for_piece(world, current_player, &infos, p);
        move_current_player( world, current_player, &infos, random_move);
        //if(is_allowed_to_simple_move(world, current_player, infos, random_move.ex_idx, random_move.new_idx)){
        //simple_move_current_player( world, current_player, &infos, random_move);
        //update_current_pieces(current_player, &infos, random_move.ex_idx, random_move.new_idx);
        print_current_pieces(infos);
        print_world(world);
        printf("\n");
        printf("_____________________________\n");
        //}
        if(simple_win(world, current_player, infos)){
            char *victor = (current_player == PLAYER_WHITE)? "PLAYER_WHITE" : "PLAYER_BLACK" ;
            printf("the winner is : %s\n", victor);
            return 1;
        }
        if (count_pieces(world) != 10) {
            printf("ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("%d\n", count_pieces(world));
            printf("Choosen peace was: %d\n", p);
            // print("Jump from %d to %d", random_move.ex_idx, random_move.new_idx);
            // printf()

            return 1;
        }
        else {
            current_player = next_player(current_player);
        //usleep(400 * 1000);
        usleep(50 * 1000);
        ++infos.MAX_TURNS;
        }
    }
    return 0;
}
/*

int main(){
  struct world_t* world = world_init();
  struct positions_info positions ;
  init_infos_2(&positions);
  init_players(world, positions);
  printf("initial board: \n");
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("1st round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions, 0, 11);
  //update_current_pieces(PLAYER_WHITE,&positions,  0, 11);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");
  

  printf("2nd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions, 11, 12);
  //update_current_pieces(PLAYER_WHITE, &positions, 11,12);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,12, 13);
  //update_current_pieces(WHITE, &positions, 12,13);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,13, 14);
  //update_current_pieces(WHITE, &positions, 13,14);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,14, 15);
  //update_current_pieces(WHITE, &positions, 14,15);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,15, 16);
  //update_current_pieces(WHITE, &positions, 15,16);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,16, 17);
  //update_current_pieces(WHITE, &positions, 16,17);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,17, 18);
  //update_current_pieces(WHITE, &positions, 17,18);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");

  printf("3rd round: \n");
  simple_move_player(world, PLAYER_WHITE, &positions,18, 19);
  //update_current_pieces(WHITE, &positions, 18,19);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");


  printf("3rd round: \n");
  simple_move_player(world, PLAYER_BLACK, &positions,19, 0);
  //update_current_pieces(WHITE, &positions, 19,0);
  print_current_pieces(positions);
  print_world(world);
  printf("\n");
  //update_current_pieces(WHITE, &positions, 30,1);
  printf("%d", positions.TURNS);
  return 0;
}

int main(){
    struct neighbors_t nei= get_neighbors(2);
    for(int j=0; j < MAX_NEIGHBORS; ++j){
        printf("%d\n", nei.n[j].i);
    }

    return 0;
}*/