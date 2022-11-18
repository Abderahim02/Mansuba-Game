#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"


struct position_info {
    int initial_White[HEIGHT];
    int initial_Black[HEIGHT];
    int allowed_moves_White[HEIGHT];
    int allowed_moves_Black[HEIGHT];
    int current_pieces_White[HEIGHT];
    int current_pieces_Black[HEIGHT];
};

// _________________________
void init_players(struct world_t* b) {
    struct position_info position_info;
    for (int i = 0; i <= WORLD_SIZE; ++i) {
        // In the begin we put the white pieces to the left and the black pieces to the right.
        if (i % WIDTH == 0) {
            world_set(b,i,WHITE);
            world_set_sort(b,i,1);
            position_info.initial_White[i] = i;
            position_info.current_pieces_White[i] = i;
        }
        else if (i % WIDTH-1 == 0) {
            world_set(b,i,BLACK);
            world_set_sort(b,i,1);
            position_info.initial_Black[i] = i;
            position_info.current_pieces_Black[i] = i;
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


// ________________________
// void update_current_pieces() {}


int main() {
    return 0;
}

