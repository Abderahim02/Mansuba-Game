#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
#include "ensemble.h"
#include <unistd.h>
#include <getopt.h>
// For creating a real random number.
#include <time.h>

#define UINT_MAX 100

enum move_types{ 
SIMPLE_MOVE = 1,
SIMPLE_JUMP = 2,
MULTIPLE_JUMP = 3, 
};

//we add the types of victory
enum victory{
    COMPLEX_WIN = 1,
    SIMPLE_WIN = 2,
};

// We define a structure that will give us all the data about the move.
struct move{
    unsigned int ex_idx;
    unsigned int new_idx;
    enum move_types type;   
};

// Current player can be 0 = WHITE or 1 = BLACK.
enum players current_player = PLAYER_WHITE;

// Function for getting a random player
enum players get_random_player() {
    // srand(time(0));
    // % will help us to get either 0 or 1.
    int rand_player = (rand() % 2) + 1;
    return rand_player;
}

// Function to get the next player.
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

// A function that test if there is no winner. 
int nobody_has_won(struct world_t* world, struct positions_info infos){
    return (simple_win(world, PLAYER_WHITE, infos) || simple_win(world, PLAYER_BLACK, infos))==0;
}

// This function generate a random possible move for the random choosen piece ex_idx.
struct move choose_random_move_for_piece(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx){
    struct move move; 
    move.ex_idx = ex_idx;
    unsigned int i = 45;
    while(is_allowed_simple_jump(world, ex_idx, i)==0 && is_allowed_to_simple_move(world, player, infos, ex_idx, i) == 0 
        && is_multi_jump_allowed(world, player, ex_idx) == 0){
        i = rand() % WORLD_SIZE;
        if (is_multi_jump_allowed(world, player, ex_idx)) { /*we favorises the multiple jump mouvement*/
            move.type = MULTIPLE_JUMP;
            return move;
        }
        else if(is_allowed_simple_jump(world, ex_idx, i)){ /*if it's not possible we go for the simple jump*/
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

// Simple moves only test.
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

// Simple moves only
void simple_move_current_player(struct world_t* world, enum players player, struct positions_info* infos, struct move move){
    if(move.type ==SIMPLE_MOVE){
            simple_move_player(world, player, infos, move.ex_idx, move.new_idx);
            //update_current_pieces(current_player, &infos, move.ex_idx, move.new_idx);
    }
    }


// This function does the move
void move_current_player(struct world_t* world, enum players player, struct positions_info* infos, struct move move){
    if (move.type == 1 || move.type == 2 || move.type == 3) {
        switch (move.type){
            // Here we are favorising the Multiple Jump after it, the simple jump.
            case MULTIPLE_JUMP:
                multi_jump(world, player, infos, move.ex_idx);
                printf("I did a multiple JUMP!! \n");
                move.new_idx = multi_jump(world, player, infos, move.ex_idx);
                break;
            case SIMPLE_JUMP:
                simple_jump(world, player, infos, move.ex_idx, move.new_idx);
                // printf("I did a simple JUMP!! \n");
                break;
            case SIMPLE_MOVE:
                simple_move_player(world, player, infos, move.ex_idx, move.new_idx);
                break;
            default:
                break;
        }
        printf("Player %d move with %d from %d to %d\n",player , move.type, move.ex_idx, move.new_idx);
    }
}

//we do a function that do the simple game
int simple_win_game(struct world_t* world, struct positions_info infos , unsigned int MAX_TURNS, enum players current_player){
    while(nobody_has_won(world, infos) && infos.TURNS < MAX_TURNS) {
        unsigned int p = choose_random_piece_belonging_to(infos, current_player);
        struct move random_move = choose_random_move_for_piece(world, current_player, &infos, p);
        move_current_player( world, current_player, &infos, random_move);
        print_current_pieces(infos);
        print_world(world);        
        printf("\n");
        printf("PLayed turns: %d\n", infos.TURNS);
        printf("\n");
        printf("_____________________________\n");
        if(simple_win(world, current_player, infos)){
            char *victor = (current_player == PLAYER_WHITE)? "PLAYER_WHITE" : "PLAYER_BLACK" ;
            printf("the winner for the simple game is : %s\n", victor);
            return 1;
        }
        // We leave this If funtion here, because it's usefull for fixing further problems
        // And helped us fixing old problems.
        if (count_pieces(world) != 10) {
            printf("ERROR!!!!!!!!!!!!!!!!!!!! \n");
            printf("%d\n", count_pieces(world));
            printf("Choosen peace was: %d\n", p);
            return 1;
        }
        else {
            current_player = next_player(current_player);
        usleep(50* 1000);
        ++infos.MAX_TURNS;
        }
    }
    printf("There is no Winner.\n");
    return 0;
}
//we do a function that do the complex game, we did it we int output so as if there is an error 
//the game stop
int complex_win_game(struct world_t* world, struct positions_info infos, unsigned int MAX_TURNS , enum players current_player){
    while(nobody_has_won(world, infos) && infos.TURNS < MAX_TURNS) {
        unsigned int p = choose_random_piece_belonging_to(infos, current_player);
        struct move random_move = choose_random_move_for_piece(world, current_player, &infos, p);
        move_current_player( world, current_player, &infos, random_move);
        print_current_pieces(infos);
        print_world(world);        
        printf("\n");
        printf("PLayed turns: %d\n", infos.TURNS);
        printf("\n");
        printf("_____________________________\n");
        if(complex_win(world, current_player, infos)){
            char *victor = (current_player == PLAYER_WHITE)? "PLAYER_WHITE" : "PLAYER_BLACK" ;
            printf("the winner for the complex is : %s\n", victor);
            return 1;
        }
        // We leave this If funtion here, because it's usefull for fixing further problems
        // And helped us fixing old problems.
        if (count_pieces(world) != 10) {
            printf("ERROR!!!!!!!!!!!!!!!!!!!! \n");
            printf("%d\n", count_pieces(world));
            printf("Choosen peace was: %d\n", p);
            return 1;
        }
        else {
            current_player = next_player(current_player);
        usleep(50* 1000);
        ++infos.MAX_TURNS;
        }
    }
    printf("There is no Winner.");
    return 0;
}



// The game:
int main(int argc, char *const argv[]){
   // int MAX_TURNS= atoi(argv[1]);
    struct world_t* world = world_init();
    struct positions_info infos;
    srand(time(0));
    init_infos(&infos);
    init_players(world);
    enum players current_player = get_random_player();
    //unsigned int MAX_TURNS = (argc > 1) ? atoi(argv[1]) : 2*WORLD_SIZE ;
    enum victory victory_type = SIMPLE_WIN; //we take by default a SIMPLE_WIN game
    unsigned int MAX_TURNS = 2*WORLD_SIZE; // we take as default MAX_TURNS = 2*WORLD_SIZE
    int s = rand(); 
    int opt;
    //we use getopt to take arguments -s -t -m from command line
    while((opt = getopt(argc, argv, "s:m:t:")) != -1) //the ser of argument we have is s m t
    {  //getopt return -1 when there is no more argument from the command line
        switch(opt) 
        { 
            case 's': 
                //printf("optarg s :%s\n", optarg);
                if(optarg == NULL){ //if there is no value for the argument
                    s=rand()%WORLD_SIZE; //we set a random value
                }
                else{
                    s = atoi(optarg) ;
                }
                break;
            case 'm':
                //printf("optarg m :%s\n", optarg);
                MAX_TURNS = (optarg != NULL) ? atoi(optarg) : 2*WORLD_SIZE ;
                break;
            case 't': 
                //printf("optarg t:%s\n", optarg);
                //note that optarg which is the value of the argument -t is a char* type 
                if(strlen(optarg)==1 && optarg[0] == 'c'){
                    victory_type = COMPLEX_WIN;
                }
                else{
                    victory_type = SIMPLE_WIN ;
                }
                break;
            default:
                break;
        } 
    } 
    printf("s=%d\n", s);
    printf("m = %d\n", MAX_TURNS );
    printf("vic type %d\n", victory_type);
    
    switch (victory_type){
        case COMPLEX_WIN:
            complex_win_game(world, infos, MAX_TURNS, current_player);
            break;
        default:
            simple_win_game(world, infos, MAX_TURNS, current_player);
            break;
    }
    //free(world);
    //destroyWorld(world); // we free the allocated memory space for world at the end
    return 0;
}