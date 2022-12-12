#include <stdio.h>
#include <string.h>
#include "ensemble.h"
#include "geometry.h"
int is_cardinal_dir(enum dir_t dir){
    if( dir == EAST || dir == WEST || dir == NORTH || dir == SOUTH ){
        return 1;
    }
    return 0;
}
//redefine a new is allowed .....
int is_allowed_to_simple_move_aux(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx){
  switch (player) {
  case PLAYER_WHITE:
      if (is_new_ex_neighbor(ex_idx, new_idx)) { // we check if new_ex is a neighbor 
        if( world->sorts[new_idx] == 0){ //we check if new_ex is a free position
        return 1;
        }
    }
    break;
  case PLAYER_BLACK:
      if (is_new_ex_neighbor(ex_idx, new_idx)){ // we check if new_ex is a neighbor 
        if( world->sorts[new_idx] == 0){ //we check if new_ex is a free position
        return 1;
        }
      }
  default:
    break;
  }
  return 0;
}

//we can add is_elephant(unsigned int ex_idx); 
int is_allowed_elephant_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx){
  if (is_new_ex_neighbor(ex_idx, new_idx) == 0){ // if new_ex is a neighbor we can't jump on it only simple move 
    struct neighbors_t neighbors = get_neighbors(ex_idx); // we get the neighbors of ex_idx  
    int num_ex_idx_neighbors = number_of_neighbors(neighbors); // we get their number
    if(num_ex_idx_neighbors > 0 ){ // we check if it has no neighbors , in this case the jump is impossible
      for(int j=0; j < num_ex_idx_neighbors ; ++j){  //we see all existants neighbors of ex_idx 
            unsigned int tmp_position = neighbors.n[j].i; // we use tmporary variables to reduce complexity
            enum dir_t tmp_dir = neighbors.n[j].d;
            // printf("\n");
            // printf("tmp_position : %d\n", tmp_position);
            // printf("tmp_dir : %d\n", tmp_dir);
            // printf("iscardinal : %d\n", is_cardinal_dir(tmp_dir));
            if(is_cardinal_dir( tmp_dir)){ 
                  //printf("tumber of neighbors de %d : %d\n",tmp_position, num_tmp_position_neighbors);
                  struct neighbors_t tmp_neighbors = get_neighbors(tmp_position);
                  int num_tmp_position_neighbors = number_of_neighbors(tmp_neighbors); 
                  //printf("le num de voisins %d\n", num_tmp_position_neighbors);
                  for(int k=0; k < num_tmp_position_neighbors ; ++k){
                        enum dir_t tmp_dir_2 = tmp_neighbors.n[k].d ; 
                        unsigned int tmp_position_2 = tmp_neighbors.n[k].i;
                        // printf("tmp_position_2 : %d\n", tmp_position_2);
                        // printf("tmp_dir_2 : %d\n", tmp_dir_2);
                        // printf("iscardinal_tmp2 : %d\n", is_cardinal_dir(tmp_dir_2));
                        if(is_cardinal_dir(tmp_dir_2 )){
                          if(is_allowed_to_simple_move_aux(world, player,infos, tmp_position ,tmp_neighbors.n[k].i) && tmp_neighbors.n[k].i == new_idx){
                                  return 1;
                      }
                  }
               }
           }
    }
  }
    return 0;
  }
}
//.................................... 

void elephant_move(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx) {
  switch (player){
    case PLAYER_WHITE:
      if(is_allowed_elephant_move(world , player, infos, ex_idx, new_idx)){
            world->colors[new_idx] = WHITE;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = ELEPHANT;
            update_current_pieces(player, infos, ex_idx, new_idx);   
      }
      break;
    case PLAYER_BLACK:
        if(is_allowed_elephant_move(world,player, infos, ex_idx, new_idx)){
            world->colors[new_idx] = BLACK;
            world->colors[ex_idx] = NO_COLOR ;
            world->sorts[ex_idx] = NO_SORT;
            world->sorts[new_idx] = ELEPHANT;
            update_current_pieces(player, infos, ex_idx, new_idx);
      }
      break;
    default:
      break;
  }
}