#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"

// _____________________
struct positions_info {
  int initial_WHITE[HEIGHT];
  //int allowed_moves_WHITE[HEIGHT];
  int current_pieces_WHITE[HEIGHT];
  int initial_BLACK[HEIGHT];
  //int allowed_moves_BLACK[HEIGHT];
  int current_pieces_BLACK[HEIGHT];
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
    else if (i % WIDTH-1 == 0) {
      worldt->colors[i] = BLACK;
      worldt->sorts[i] = 1;
    }
}
}
int is_newex_neighbor(int ex_idx,int new_idx){
  for (enum dir_t dir = SWEST ; i < MAX_DIR; ++dir){
    if(get_neighbors[i][0]==new_idx){
      return 1;
    }
  }
  return 0;
}

  
int is_allowed_tomove(struct world_t world, int ex_idx, int new_idx){
  if (is_newex_neighbor(ex_idx, new_idx)){
    if(world.sorts[new_idx] == 0){
      return 1;
    }
  }
  return 0;
}

void move_player(struct world_t world, int player,struct positions_info infos, int ex_idx, int new_idx ){
  switch (player){
  case 0 : //player_black_pawns
    if(is_allowed_tomove(world, ex_idx, new_idx)){
      world.colors[new_idx] = BLACK;
      world.colors[ex_idx] = NO_COLOR ;
      world.sorts[ex_idx] = NO_SORT;
      world.sorts[new_idx] = SORT;
      infos.current_pieces_BLACK[new_id] = player.current[ex_id]; 
    }
  }


  // ________________________
  void update_current_pieces(int player, struct positions_info infos,int ex_idx, int new_idx){
    if(player==0){
      for(int i=0; i < HEIGHT; ++i){
      	if( infos.current_pieces_BLACK[i]==ex_idx ){
	  infos.current_pieces_BLACK[i] = new_idx;
	}
      }
    }
    else{
      for(int i=0; i < HEIGHT; ++i){
      	if( infos.current_pieces_WHITE[i] == ex_idx ){
	  infos.current_pieces_WHITE[i] = new_idx;
	}
      }
    }
  }
 

  int main() {
    return 0;
  }

