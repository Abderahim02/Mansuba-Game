#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"

// _____________________
enum players{
  PLAYER_WHITE = 0,
  PLAYER_BLACK = 1,
};
struct position_info {
    int initial[HEIGHT];
    int allowed_moves[HEIGHT];
    int current_pieces[HEIGHT];
};

struct player {
  struct position_info position_info;
  enum players player;
};

// _________________________
void init_players(struct world_t* worldt) {
  for (int i = 0; i < WORLD_SIZE; ++i) {
    // In the begin we put the white pieces to the left and the black pieces to the right.
    if (i % WIDTH == 0) {
      worldt->colors[i] = WHITE;
      worldt->sorts[i] = 1;
    }
    else if (i % WIDTH-1 == 0) {
      worldt->colors[i] = BLACK;
      worldt->sorts[i] = 1;
    }
  }
}
int is_newex_neighbor(int ex_idx,int new_idx){
  for (int i=0; i < MAX_NEIGHBORS; ++i){
    if(nei
  }
}

  
int is_allowed_tomove(int ex_idx,int new_idx){
  if () 
}

void move_player(struct world_t world, struct player player, int ex_idx, int new_idx ){
  switch (player.player){
  case PLAYER_WHITE :
    world.colors[new_idx] = world.colors[ex_idx];
    player.current[new_id]=player.current[ex_id]; 
  }
}


int main() {
    return 0;
}

