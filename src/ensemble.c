#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"

// _____________________
struct world_t{ 
  enum color_t colors[WORLD_SIZE];
  enum sort_t sorts[WORLD_SIZE];
};


enum players{
  PLAYER_WHITE = 2 ,
  PLAYER_BLACK = 1 ,
};
struct positions_info { 
  /*  at this poin we don't have to define a structure for possible mouvements of each player */
  int initial_WHITE[HEIGHT]; // initial positions of he player with white pawns
  int current_pieces_WHITE[HEIGHT]; // current positions of the player with white pawns
  int initial_BLACK[HEIGHT];  // initial positions of he player with black pawns
  int current_pieces_BLACK[HEIGHT]; //current positions of the player with black pawns
};

//____________________________________________________________________________________________

//this function initialize informations at the begining of the game , we initialize the current pieces with WORLD_SIZE everywere , 
//this will be useful for the function add_to_current_piece */
struct positions_info init_infos(){
  struct positions_info infos;
  for (int i=0; i < HEIGHT ; ++i){
    infos.current_pieces_BLACK[i] = WORLD_SIZE;
    infos.current_pieces_WHITE[i] = WORLD_SIZE;
    infos.initial_BLACK[i] = WORLD_SIZE;
    infos.initial_BLACK[i] = WORLD_SIZE;
  }
  return infos;
}
/* this function add the position idx to current pieces for the player , we will need it just at the begining of the game */
void add_to_current_piece(struct positions_info positions_info, enum players player, unsigned int idx){
  switch (player){
  case PLAYER_WHITE:
        for (int i=0; i < HEIGHT; ++i){
             if((positions_info.current_pieces_WHITE[i] == WORLD_SIZE) && (positions_info.initial_WHITE[i] == WORLD_SIZE)){
                      positions_info.current_pieces_WHITE[i] = idx;
                      positions_info.initial_WHITE[i] = idx;
                      break;
          }
        }
        
    case PLAYER_BLACK:
        for (int i=0; i < HEIGHT; ++i){
              if((positions_info.current_pieces_BLACK[i] == WORLD_SIZE) && (positions_info.initial_WHITE[i] == WORLD_SIZE)){
                      positions_info.current_pieces_BLACK[i] = idx;
                      positions_info.initial_BLACK[i] = idx;
                          break;
           }

        }
        break;
      default:
        break;
  }
}
/* it's the function that give for each player his initial positions , we suppose the initially the player with white pawns 
will take the last column at the left edge and the other player will take the last column at the right edge */
void init_players(struct world_t* b, struct positions_info positions_info) {
    //struct positions_info positions_info;
    for (int i = 0; i < WORLD_SIZE; ++i) {
        // In the begin we put the white pieces to the left and the black pieces to the right.
        if (i % WIDTH == 0) {
            world_set(b,i,WHITE);
            world_set_sort(b,i,1);
            add_to_current_piece(positions_info, PLAYER_WHITE, i);
        }
        else if ((i% WIDTH)  == WIDTH - 1 ) {
            world_set(b, i, BLACK);
            world_set_sort(b, i, 1);
            add_to_current_piece(positions_info, PLAYER_BLACK, i);
        }
    }
}

//_____________________________a list of functions that will help us for the move_player function :
/*this one verify if new_idx is a neighbor of ex_idx*/

int is_new_ex_neighbor(unsigned int ex_idx, unsigned int new_idx){
  struct neighbors_t neighbors = get_neighbors(ex_idx); //we use get_neighbor to get the neighbors list of ex_idx 
  for ( int j=0; j < MAX_NEIGHBORS; ++j){
    if(neighbors.n[j].i == new_idx){
      return 1;
    }
  }
  return 0;
}
/*this one verify if it is an allowed simple move */
  
int is_allowed_to_simple_move(struct world_t* world, unsigned int ex_idx, unsigned int new_idx){
  if (is_new_ex_neighbor(ex_idx, new_idx)){ // we check if new_ex is a neighbor 
    if( world->sorts[new_idx] == 0){ //we check if new_ex is a free position
      return 1;
    }
   }

  //at the moment we do just simple moves
  return 0;
}

//this function update player's information after every move 

void update_current_pieces(enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx){
  if( player == 1){
    for(int i=0; i < HEIGHT; ++i){
      if( infos.current_pieces_BLACK[i] == ex_idx ){
	        infos.current_pieces_BLACK[i] = new_idx;
      }
    }
  }
  else{
    for(int i=0; i < HEIGHT; ++i){
      if( infos.current_pieces_WHITE[i] == ex_idx ){ //we replace the position ex_idx it new_idx
	        infos.current_pieces_WHITE[i] = new_idx;
      }
    }
  }
}
// this is our function that do the move if it is allowed

void simple_move_player(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx ){
  switch (player){
  case PLAYER_BLACK : //player with black_pawns
    if(is_allowed_to_simple_move(world, ex_idx, new_idx) == 1){
      world->colors[new_idx] = BLACK;
      world->colors[ex_idx] = NO_COLOR ;
      world->sorts[ex_idx] = NO_SORT;
      world->sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;
  case PLAYER_WHITE: //player with white_pawn
    if(is_allowed_to_simple_move(world, ex_idx, new_idx) == 1){
      world->colors[new_idx] = WHITE;
      world->colors[ex_idx] = NO_COLOR ;
      world->sorts[ex_idx] = NO_SORT;
      world->sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;
  default:
    break;
  }
}


int is_allowed_simple_jump(struct world_t* world, unsigned int ex_idx, unsigned int new_idx){
  if (is_new_ex_neighbor(ex_idx, new_idx) == 0){
    struct neighbors_t neighbors = get_neighbors(ex_idx);
    int j=0;
    while( j < MAX_NEIGHBORS ){  //we see all existants neighbors of ex_idx 
        //struct neighbors_t neighbors_tmp = get_neighbors(neighbors.n[j].i);
        //if(neighbors_tmp.n[])
        if(world->sorts[neighbors.n[j].i] != 0){
            unsigned int neighbor_tmp = get_neighbor(neighbors.n[j].i, neighbors.n[j].d);
            return  is_allowed_to_simple_move(world, neighbors.n[j].i, neighbor_tmp);
            break;
        }
        else{
          ++j;
        }
        } 
      //position to its  neighbors positions , it means we see if a neighbor 
    }
    return 0;
  }
void simple_jump(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx){
  switch (player){
    case PLAYER_WHITE:
      if(is_allowed_simple_jump(world, ex_idx, new_idx)){
            world->colors[new_idx] = WHITE;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = PAWN;
            update_current_pieces(player, infos, ex_idx, new_idx);
            break;
      }
    case PLAYER_BLACK:
        if(is_allowed_simple_jump(world, ex_idx, new_idx)){
            world->colors[new_idx] = BLACK;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = PAWN;
            update_current_pieces(player, infos, ex_idx, new_idx);
            break;
      }
    default:
            break;
  }
}


void print_world( struct world_t* world ){
  for (int i=0; i< WORLD_SIZE ; ++i){
    if( i%HEIGHT == 0 && i != 0 ){
      printf("\n%d ", world->colors[i]);    
    }
    else {
      printf("%d ", world->colors[i]);
    
    }
  }
}


void print_init_players(struct positions_info positions){
  for(int i=0; i<HEIGHT; ++i ){
    printf("%d\n ", positions.initial_BLACK[i]);

  }
}


void print_current(struct positions_info positions){
  for(int i=0; i<HEIGHT; ++i ){
    printf("%d\n ", positions.current_pieces_BLACK[i]);

  }
}


// ________________________a test with two rounds game

 
int main() {
  struct world_t* world = world_init();
  struct positions_info positions = init_infos();
  init_players(world, positions);
  printf("First round: \n");
  print_world(world);
  printf("\n");
  
  move_player(world, PLAYER_WHITE, positions, 0, 11);
  printf("second round\n");

  print_world(world);
  printf("\n");
  move_player(world, PLAYER_BLACK, positions, 9, 8);
  printf("third round:\n");
  print_world(world);
  printf("\n");
  //print_init_players(positions);
  //print_current(positions);
  printf("le mouvement est %d\n", allowed_simple_jump(world,10,22));
  return 0;
}