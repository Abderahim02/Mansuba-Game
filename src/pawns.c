#include <stdio.h>
#include <string.h>
#include "pawns.h"

int is_cardinal_dir(enum dir_t dir){
    if( dir == EAST || dir == WEST || dir == NORTH || dir == SOUTH ){
        return 1;
    }
    return 0;
}

//redefine a new is allowed .....
int is_allowed_to_simple_move_aux(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx){
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
  if (is_new_ex_neighbor(ex_idx, new_idx) == 0){ // if new_ex is a neighbor we can't do elephant move , simple move only 
    struct neighbors_t neighbors = get_neighbors(ex_idx); // we get the neighbors of ex_idx  
    int num_ex_idx_neighbors = number_of_neighbors(neighbors); // we get their number
    if(num_ex_idx_neighbors > 0 ){ // we check if it has no neighbors , in this case the jump is impossible, just to prevent possible bugs
      for(int j=0; j < num_ex_idx_neighbors ; ++j){  //we see all existants neighbors of ex_idx 
            unsigned int tmp_position = neighbors.n[j].i; 
            enum dir_t tmp_dir = neighbors.n[j].d;;
            if(is_cardinal_dir( tmp_dir)){ 
                  //printf("tumber of neighbors de %d : %d\n",tmp_position, num_tmp_position_neighbors);
                  struct neighbors_t tmp_neighbors = get_neighbors(tmp_position);
                  int num_tmp_position_neighbors = number_of_neighbors(tmp_neighbors); 
                  //printf("le num de voisins %d\n", num_tmp_position_neighbors);
                  for(int k=0; k < num_tmp_position_neighbors ; ++k){
                        enum dir_t tmp_dir_2 = tmp_neighbors.n[k].d ;
                        if(is_cardinal_dir(tmp_dir_2 )){
                          if(is_allowed_to_simple_move_aux(world, player, tmp_position ,tmp_neighbors.n[k].i) && tmp_neighbors.n[k].i == new_idx){
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
            world_set(world, new_idx, WHITE);
            world_set(world, ex_idx, NO_COLOR);
            world_set_sort(world, ex_idx, NO_SORT);
            world_set_sort(world, new_idx, ELEPHANT);
            update_current_pieces(player, infos, ex_idx, new_idx);  
            }
      break;
    case PLAYER_BLACK:
        if(is_allowed_elephant_move(world,player, infos, ex_idx, new_idx)){
            world_set(world, new_idx, BLACK);
            world_set(world, ex_idx, NO_COLOR);
            world_set_sort(world, ex_idx, NO_SORT);
            world_set_sort(world, new_idx,ELEPHANT);
            update_current_pieces(player, infos, ex_idx, new_idx);  
      }
      break;
    default:
      break;
  }
}

// // Is tower allowed to move
// int is_allowed_tower_move(struct world_t* world, enum players player, unsigned int ex_idx) {
//     switch (player) {
//     case PLAYER_WHITE:
//         // Check if a forward or sideways move is possible. If the next field is free, the move is already possible.
//         if (world_get(world, ex_idx+1) == NO_COLOR || world_get(world, ex_idx - WIDTH) == NO_COLOR || world_get(world, ex_idx + WIDTH) == NO_COLOR) {
//             return 1;
//         }
//         return 0;        
//         break;
//     case PLAYER_BLACK:
//         // Almost same if function for Black, but in the other direction.
//         if (world_get(world, ex_idx-1) == NO_COLOR || world_get(world, ex_idx - WIDTH) == NO_COLOR || world_get(world, ex_idx + WIDTH) == NO_COLOR) {
//             return 1;
//         }
//         return 0;        
//         break;
//     default:
//         break;
//     }
//     return 0;
// }

// To get the end position of the field on the x-axle.
int give_end_position_x(enum players player, unsigned int ex_idx) {
    int a = ex_idx;
    switch (player) {
    case PLAYER_BLACK:
        while (a % WIDTH != 0) {
            --a; 
        }
        break;
    case PLAYER_WHITE:
        while (a % WIDTH != WIDTH - 1) {
            ++a; 
        }
        break;
    default:
        break;
    }
    return a;
}

// To get the end position of the field on the y-axle.
int give_top_position_y(unsigned int ex_idx) {
    int a = ex_idx;
    while (a > WIDTH) {
        a = a - WIDTH; 
    }
    return a;
}

int give_down_position_y(unsigned int ex_idx) {
    int a = ex_idx;
    while (a < (WORLD_SIZE - WIDTH)) {
        a = a + WIDTH; 
    }
    return a;
}


// Is tower allowed to move
int is_allowed_tower_move(struct world_t* world, enum players player, unsigned int ex_idx) {
    // int top = give_top_position_y(ex_idx);
    // int down = give_down_position_y(ex_idx);
    // if (ex_idx == )
    switch (player) {
    case PLAYER_WHITE:
        // Check if a forward or sideways move is possible. If the next field is free, the move is already possible.
        if (world_get(world, ex_idx+1) == NO_COLOR || world_get(world, ex_idx - WIDTH) == NO_COLOR || world_get(world, ex_idx + WIDTH) == NO_COLOR) {
            return 1;
        }
        return 0;        
        break;
    case PLAYER_BLACK:
        // Almost same if function for Black, but in the other direction.
        if (world_get(world, ex_idx-1) == NO_COLOR || world_get(world, ex_idx - WIDTH) == NO_COLOR || world_get(world, ex_idx + WIDTH) == NO_COLOR) {
            return 1;
        }
        return 0;        
        break;
    default:
        break;
    }
    return 0;
}


//.......................
int tower_move(struct world_t* world, enum players player, struct positions_info* infos, int ex_idx) {
    int p = ex_idx;
    int px = give_end_position_x(player, p);
    int py_top = give_top_position_y(ex_idx);
    int py_down = give_down_position_y(ex_idx);
    switch (player) {    
    case PLAYER_BLACK:
        if (p != px) {
            if (world_get(world, p-1) == NO_COLOR) {
            // We prefer the move on the x-axle.
                for (int i = p-1; i >= px; --i) {
                    // printf("i is %d\n", i);
                    // Checking where the next PAWN is.
                    if (world_get(world, i) != NO_COLOR) {
                        world_set(world, i+1, BLACK);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i+1, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i+1);
                        return 1;
                    }
                    else if (i == px && world_get(world, i) == NO_COLOR) {
                        world_set(world, i, BLACK);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i);
                        return 1;
                    }
                }
            }
        }
        // After we prefer the move to the top.
        if (p != py_top) {
            if (world_get(world, p - WIDTH) == NO_COLOR) {
                for (int i = p - WIDTH; i >= py_top; i = i - WIDTH) {
                    // Checking where the next PAWN is.
                    if (world_get(world, i) != NO_COLOR) {
                        world_set(world, i + WIDTH, BLACK);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i + WIDTH, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i + WIDTH);
                        return 1;
                    }
                    else if (i == py_top) {
                        // printf("I go to %d\n", j);
                        world_set(world, i, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i);
                        return 1;
                    }
                }
            }
        }
        // Move downwards.
        if (p != py_down) {
            if (world_get(world, p + WIDTH) == NO_COLOR) {
                for (int i = p + WIDTH; i <= py_down; i = i + WIDTH) {
                    // Checking where the next PAWN is.
                    if (world_get(world, i) != NO_COLOR) {
                        world_set(world, i - WIDTH, BLACK);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i - WIDTH, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i - WIDTH);
                        return 1;
                    }
                    else if (i == py_down) {
                        // printf("I go to %d\n", i);
                        world_set(world, i, BLACK);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i);
                        return 1;
                    }
                }
            }
        }
        break;
    case PLAYER_WHITE:
        // We prefer the move on the x-axle.
        if (p != px) {
            if (world_get(world, p+1) == NO_COLOR) {
                // printf("White x Move\n");
                for (int i = p+1; i <= px; ++i) {
                    if (world_get(world, i) != NO_COLOR) {
                        // printf("Free position is %d\n", i-1);
                        world_set(world, i-1, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i-1, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i-1);
                        return 1;
                    }
                    else if (i == px && world_get(world, i) == NO_COLOR) {
                        // printf("I go to %d\n", i);
                        world_set(world, i, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i);
                        return 1;
                    }
                }
            }
        }
        // Move to the top.
        if (p != py_top) {
            if (world_get(world, p - WIDTH) == NO_COLOR) {
                // printf("White up Move\n");
                for (int j = p - WIDTH; j >= py_top; j = j - WIDTH) {
                    // Checking where the next PAWN is.
                    if (world_get(world, j) != NO_COLOR) {
                        // printf("top move: NEW POSITION is %d\n", j+WIDTH);
                        world_set(world, j+WIDTH, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, j+WIDTH, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, j+WIDTH);
                        return 1;
                    }
                    else if (j == py_top) {
                        // printf("I go to %d\n", j);
                        world_set(world, j, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, j, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, j);
                        return 1;
                    }
                }
            }
        }
        // Move downwards.
        if (p != py_down) {
            if (world_get(world, p + WIDTH) == NO_COLOR) {
                // printf("White down Move\n");
                for (int i = p + WIDTH; i <= py_down; i = i + WIDTH) {
                    // Checking where the next PAWN is.
                    if (world_get(world, i) != NO_COLOR) {
                        // printf("down move: NEW POSITION is %d\n", i - WIDTH);
                        world_set(world, i - WIDTH, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i - WIDTH, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i - WIDTH);
                        return 1;
                    }
                    else if (i == py_down) {
                        // printf("I go to %d\n", i);
                        world_set(world, i, WHITE);
                        world_set(world, ex_idx, NO_COLOR);
                        world_set_sort(world, i, TOWER);
                        world_set_sort(world, ex_idx, NO_SORT);
                        update_current_pieces(player, infos, ex_idx, i);
                        return 1;
                    }
                }
            }
        }   
        break;
    default:
        break;
    }
    return 0;
}
