#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
#define UINT_MAX 100
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
  unsigned int initial_WHITE[HEIGHT]; // initial positions of the player with white pawns
  unsigned int current_pieces_WHITE[HEIGHT]; // current positions of the player with white pawns
  unsigned int initial_BLACK[HEIGHT];  // initial positions of he player with black pawns
  unsigned int current_pieces_BLACK[HEIGHT]; //current positions of the player with black pawns
  unsigned int MAX_TURNS; // Maximum allowed turns = WORLD SIZE
  unsigned int TURNS;  // Played turns in the game.
};

//____________________________________________________________________________________________

//this function initialize the infomations about players , we will initialize our world and informations separatly 
struct positions_info init_infos(){
  struct positions_info infos;
  int a = 0;
  int b = HEIGHT-1;
  for (int i=0; i < HEIGHT ; ++i){
    infos.current_pieces_BLACK[i] = a;
    infos.initial_BLACK[i] = a;
    infos.current_pieces_WHITE[i] = b;
    infos.initial_WHITE[i] = b;
    a = a + HEIGHT;
    b = b + HEIGHT;
  }
  infos.MAX_TURNS = WORLD_SIZE;
  infos.TURNS = 0;
  return infos;
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
        }
        else if ((i% WIDTH)  == WIDTH - 1) {
            world_set(b, i, BLACK);
            world_set_sort(b, i, 1);
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
void move_player(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx ){
  switch (player){
  case PLAYER_BLACK : //player with black_pawns
    if(is_allowed_to_simple_move(world, ex_idx, new_idx) == 1){
      world->colors[new_idx] = BLACK;  // We update the information about the world 
      world->colors[ex_idx] = NO_COLOR ;
      world->sorts[ex_idx] = NO_SORT;
      world->sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx); // We update the information about the current pieces here, because there is a problem with the index.
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
  ++infos.TURNS;
}
//_______________________________________________ the jump function_____________________________
//this first auxillary gives us the number of neighbors of a position , it will help us with the loops 
int number_of_neighbors(struct neighbors_t neighbors){
  int c=0;
  for(int j=0; j < MAX_NEIGHBORS; ++j){
      if(neighbors.n[j].i < UINT_MAX){
      ++c;
    }
  }
  return c;
}
// this one tells us if the jump is possible
int is_allowed_simple_jump(struct world_t* world, unsigned int ex_idx, unsigned int new_idx){
  if (is_new_ex_neighbor(ex_idx, new_idx) == 0){ // if new_ex is a neighbor we can't jump on it only simple move 
    struct neighbors_t neighbors = get_neighbors(ex_idx); // we get the neighbors of ex_idx  
    int num_ex_idx_neighbors = number_of_neighbors(neighbors); // we get their number
    if(num_ex_idx_neighbors > 0){ // we check if it has no neighbors , in this case the jump is impossible
      for(int j=0; j < num_ex_idx_neighbors ; ++j){  //we see all existants neighbors of ex_idx 
            unsigned int tmp_position = neighbors.n[j].i; // we use tmporary variables to reduce complexity
            enum dir_t tmp_dir = neighbors.n[j].d;
            if(world->sorts[tmp_position] == PAWN){  //if the neighbor position is filled with a pawn
                struct neighbors_t neighbors_of_tmp = get_neighbors(tmp_position); // we get neighbors of this tmp_position
                unsigned int neighbor_in_same_dir = get_neighbor(tmp_position, tmp_dir); // we get the position that is a neighbor of this tmp_neighbor in the 
                      //same direction that tmp_neighbor is neighbor of ex_idx (we got the neighbor of the neighbor of ex_idx in the same direction)
                if((neighbor_in_same_dir == new_idx)  && (world->sorts[neighbor_in_same_dir] == 0) ){ /*we check if it is the position that we want to go in 
                and if it is empty so that we can jump there */
                  return 1;
               }
            }
    
      }
    }
  }
    return 0;
}
// it our main jump function 
void simple_jump(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx){
  switch (player){
    case PLAYER_WHITE:
      if(is_allowed_simple_jump(world, ex_idx, new_idx)){
            world->colors[new_idx] = WHITE;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = PAWN;
            update_current_pieces(player, infos, ex_idx, new_idx);   
      }
      break;
    case PLAYER_BLACK:
        if(is_allowed_simple_jump(world, ex_idx, new_idx)){
            world->colors[new_idx] = BLACK;
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


//____________________________________________________
//this one print our world so we that we can see changes every time
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


//________________________________________________test functions _________________________
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

// Simple win function: the winner is the first player to reach with one of his pieces 
// one of the other player's starting positions before MAX_TURNS turns.
int simple_win(enum players player, struct positions_info infos) {
  if (infos.TURNS <= infos.MAX_TURNS) {
    switch (player)
    {
    case PLAYER_WHITE:
      // PLAYER_WHITE has to reach init_position of PLAYER_BLACK to win.
      for (int i = 1; i < WORLD_SIZE; ++i) {
        for (int j = 0; j <= HEIGHT; ++j) {
          if (infos.current_pieces_WHITE[i] == infos.initial_BLACK[j]) {
            return 0;
          }
        }
      } 
      break;
    case PLAYER_BLACK:
      // PLAYER_BLACK has to reach init_position of PLAYER_WHITE to win.
      for (int i = 0; i < WORLD_SIZE; ++i) {
        if ((infos.current_pieces_BLACK[i] % WIDTH) == 0) {
          return 1;
        }
      } 
      break;
    default:
      break;
    }
  }
  return 0;
}

// The winner is the first player to cover all the other player's starting positions 
// with his pieces before MAX_TURNS turns.
int complex_win(enum players player, struct positions_info infos) {
  if (infos.TURNS <= infos.MAX_TURNS) {
    switch (player)
    {
    case PLAYER_WHITE:
      // PLAYER_WHITE has to reach all init_position of PLAYER_BLACK to win.
      for (int i = 1; i < WORLD_SIZE; ++i) {
        for (int j = 0; j <= HEIGHT; ++j) {
          if (infos.current_pieces_WHITE[i] == infos.initial_BLACK[j]) {
            return 0;
          }
        }
      } 
      break;
    case PLAYER_BLACK:
      // PLAYER_BLACK has to reach all init_position of PLAYER_WHITE to win.
      for (int i = 0; i < WORLD_SIZE; ++i) {
        for (int j = 0; j <= HEIGHT; ++j) {
          if (infos.current_pieces_BLACK[i] == infos.initial_WHITE[j]) {
            return 0;
          }
        }
      } 
      break;
    default:
      break;
    }
    // The function must reach this line to fulfill all requested conditions of winning.
    return 1;
  }
  return 0;
}


// ________________________a test with two rounds game
int main(){
  struct world_t* world = world_init();
  struct positions_info positions = init_infos();
  init_players(world, positions);
  
  printf("initial board: \n");
  print_world(world);
  printf("\n");
  printf("1st round: \n");
  move_player(world, PLAYER_WHITE, positions, 0, 11);
  print_world(world);
  printf("\n");

  printf("2nd round: \n");
  simple_jump(world, PLAYER_WHITE, positions, 10, 12);
  print_world(world);
  printf("\n");
  
  printf("3rd round: \n");
  simple_jump(world, PLAYER_WHITE, positions, 11, 13);
  print_world(world);
  printf("\n");


  printf("4th round: \n");
  simple_jump(world, PLAYER_WHITE, positions, 12, 14);
  print_world(world);
  printf("\n");
  
  
  struct neighbors_t nei = get_neighbors(0);

    return 0;
  }
