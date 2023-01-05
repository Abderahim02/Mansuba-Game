#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chess_world.h"
#define UINT_MAX 1000
// This one print our chess_world so we that we can see changes every time
void print_world_chess( struct world_t* world) {
  printf("\n");
  unsigned int start = 0;
    for(int i=1; i <= HEIGHT; ++i){
        if(i%2==0){
            for(int j = start; j < i*WIDTH ;){
                enum sort_t sort_1 = world_get_sort(world,j);
                switch (sort_1){
                    case PAWN:
                         if(world_get(world, j) == WHITE){
                            printf("\033[0;47m\033[1;31m *  \033[0m");
                         }
                         else{
                            printf("\033[0;47m\033[1;32m *  \033[0m");
                         }
                        break;
                    case BISHOP:
                        //printf("\033[0;47m\033[1;31m &  \033[0m");
                        if(world_get(world, j) == WHITE){
                            printf("\033[0;47m\033[1;31m #  \033[0m");
                         }
                         else{
                            printf("\033[0;47m\033[1;32m #  \033[0m");
                         }
                        break;
                    default:
                        printf("\033[0;47m\033[1;31m    \033[0m");
                        break;
                }
                enum sort_t sort_2 = world_get_sort(world,j+1);
                switch (sort_2){
                    case PAWN:
                        //printf("\033[0;40m\033[1;31m *  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;40m\033[1;31m *  \033[0m");
                         }
                         else{
                            printf("\033[0;40m\033[1;32m *  \033[0m");
                         }
                        break;
                    case BISHOP:
                        //printf("\033[0;40m\033[1;31m &  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;40m\033[1;31m #  \033[0m");
                         }
                         else{
                            printf("\033[0;40m\033[1;32m #  \033[0m");
                         }
                        break;
                    default:
                        printf("\033[0;40m\033[1;31m    \033[0m");
                        break;
                }
            j=j+2;
        }
        
        }
        else{
            for(int j = start; j < i*WIDTH;){
                enum sort_t sort_1 = world_get_sort(world,j);
                enum color_t color_1 = world_get(world, j);
                switch (sort_1){
                    
                    case PAWN:
                        //printf("\033[0;40m\033[1;31m *  \033[0m");
                        if( color_1 == WHITE){
                            printf("\033[0;40m\033[1;31m *  \033[0m");
                        }
                        else{
                            printf("\033[0;40m\033[1;32m *  \033[0m");
                        }
                        break;
                    case BISHOP:
                        //printf("\033[0;40m\033[1;31m &  \033[0m");
                        if(color_1 == WHITE){
                            printf("\033[0;40m\033[1;31m #  \033[0m");
                        }
                        else{
                            printf("\033[0;40m\033[1;32m #  \033[0m");
                        }
                        break;
                    default:
                        printf("\033[0;40m\033[1;31m    \033[0m");
                        break;
                }
                enum sort_t  sort_2 = world_get_sort(world,j+1);
                enum color_t color_2 = world_get(world, j+1);
                switch (sort_2){
                    
                    case PAWN:
                        //printf("\033[0;47m\033[1;31m *  \033[0m");
                        if( color_2 == WHITE){
                            printf("\033[0;47m\033[1;31m *  \033[0m");
                        }
                        else{
                            printf("\033[0;47m\033[1;32m *  \033[0m");
                        }
                        break;

                    case BISHOP:
                        //printf("\033[0;47m\033[1;31m &  \033[0m");
                        if(color_2 == WHITE){
                            printf("\033[0;47m\033[1;31m #  \033[0m");
                        }
                        else{
                            printf("\033[0;47m\033[1;32m #  \033[0m");
                        }
                        break;
                    default:
                        printf("\033[0;47m\033[1;31m    \033[0m");
                        break;
                }
                j=j+2; 
            }
        }
        start = start + WIDTH ;
        printf("\n");
    } 
  printf("\n");
}



//Initialize the positions of players at the beginning of the game 
void init_players_chess(struct world_t* world) {
    world_set_sort(world, WIDTH, BISHOP);
    unsigned white = WIDTH;
    unsigned int black = 2*WIDTH - 1;
    while(black < WORLD_SIZE && white < WORLD_SIZE){
        world_set(world, white, WHITE);
        world_set(world, black, BLACK);
        if(black == 2*WIDTH - 1 || black == WORLD_SIZE - 1){
            world_set_sort(world, black, BISHOP);
        }
        else if(white == WIDTH || white == (WORLD_SIZE - WIDTH) ){
            world_set_sort(world, white, BISHOP);
        }
        else{
            world_set_sort(world, white, PAWN);
            world_set_sort(world, black, PAWN);
        }
        
        white += 2*WIDTH;
        black += 2*WIDTH;
    }
    //la boucle s arrete avant de remplir la derniere position start donc il faut le faire manuellement
    world_set_sort(world, WORLD_SIZE - WIDTH, BISHOP );
}

//a booleen function returng a positive int if the bishop mouvement frome ex_idx to new_idx is possible, -1 else.
int is_allowed_bishop_move_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir){
    switch (player){
      case PLAYER_WHITE:
          if(dir == SEAST || dir == NEAST){
            unsigned int start = get_neighbor( ex_idx, dir);
            unsigned int copy = ex_idx;
            while(is_allowed_to_simple_move_aux(world, player, copy, start)){
              if(start == new_idx ){
              return start;
              } 
              int tmp = start;
              start = get_neighbor(start, dir);
              copy = tmp;
            }
          }
            return -1; 
          break;
      case PLAYER_BLACK:
            if(dir == SWEST || dir == NWEST){
            unsigned int start = get_neighbor( ex_idx, dir);
            unsigned int copy = ex_idx;
            while(is_allowed_to_simple_move_aux(world, player, copy, start)){
            //   printf("start = %d\n", start);
            //   print_neighbors(start); 
              if(start == new_idx ){
              return start;
              } 
              //printf("\n");
              int tmp = start;
              start = get_neighbor(start, dir);
              //printf("new_start = %d\n", start);
              copy = tmp;
            }
          }
          return -1;
          break;
      default:
          return -1;
          break;
      }
}
//the bishop move function
void bishop_move_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx, enum dir_t dir){
  switch (player){
    case PLAYER_WHITE:
      if(is_allowed_bishop_move_chess(world, player,ex_idx, new_idx, dir) ){
            world_set(world, new_idx, WHITE);
            world_set(world, ex_idx, NO_COLOR);
            world_set_sort(world, ex_idx, NO_SORT);
            world_set_sort(world, new_idx, BISHOP);
            update_current_pieces(player, infos, ex_idx, new_idx);   
      }
      break;
    case PLAYER_BLACK:
        if(is_allowed_bishop_move_chess(world,player, ex_idx, new_idx, dir)){
            world_set(world, new_idx, BLACK);
            world_set(world, ex_idx, NO_COLOR);
            world_set_sort(world, ex_idx, NO_SORT);
            world_set_sort(world, new_idx, BISHOP);
            update_current_pieces(player, infos, ex_idx, new_idx);
      }
      break;
    default:
      break;
  }
}


// In this world you only have the directions SWEST, SEAST, NEAST and NWEST.
unsigned int get_neighbor_chess(unsigned int idx, enum dir_t d) {
    // Case for beeing on North or South edge of the playing field.
    if ((idx < WIDTH && (d == NEAST || d == NWEST)) || 
        (idx > WORLD_SIZE - WIDTH && (d == SWEST || d == SEAST))) {
            return UINT_MAX;
        }
    // Case for beeing on the West edge of the playing field.
    else if ( idx % WIDTH == 0  && (d == NWEST || d == SWEST)) {
        return UINT_MAX;
    }
    // Case for beeing on the East edge of the playing field.
    else if ( idx % WIDTH == WIDTH-1 && (d == NEAST || d == SEAST)) {
        return UINT_MAX;
    }
    // Cases for having a neighbour. NB: we eliminate the east, west, south and north directions.
    else{
      switch (d){
    case NEAST:
        return idx - (WIDTH-1);
        break;
    case NWEST:
        return idx - (WIDTH+1);
        break;
    case SEAST:
        return idx + (WIDTH+1);
        break;
    case SWEST:
      return idx + (WIDTH-1);
      break;
    default: 
      return UINT_MAX;
      }
    }
}


// A bool function returns if a simple move for pawn is possible or not.
int is_allowed_simple_move_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx) {
    switch (player)
    {
    case PLAYER_WHITE:
        // White player is not allowed to move in any west direction.
        if (get_neighbor_chess(ex_idx, NEAST) == new_idx || get_neighbor_chess(ex_idx, SEAST) == new_idx) {
            // New position must be empty.
            if (world_get(world, new_idx) == NO_COLOR) {
                return 1;
            }
        }
        break;
    case PLAYER_BLACK:
        // Black player is not allowed to move in any east direction.
        if (get_neighbor_chess(ex_idx, NWEST) == new_idx || get_neighbor_chess(ex_idx, SWEST) == new_idx) {
            // New position must be empty.
            if (world_get(world, new_idx) == NO_COLOR) {
                return 1;
            }
        }
        break;
    default:
        break;
    }
    return 0;
}

// The simple move function for a Pawn in chess world.
void simple_move_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx) {
  switch (player)
  {
  case PLAYER_WHITE:
    if (is_allowed_simple_move_chess(world, player, ex_idx, new_idx)) {
      world_set(world, new_idx, WHITE);
      world_set(world, ex_idx, NO_COLOR);
      world_set_sort(world, ex_idx, NO_SORT);
      world_set_sort(world, new_idx, PAWN);
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;
  case PLAYER_BLACK:
    if (is_allowed_simple_move_chess(world, player, ex_idx, new_idx)) {
      world_set(world, new_idx, BLACK);
      world_set(world, ex_idx, NO_COLOR);
      world_set_sort(world, ex_idx, NO_SORT);
      world_set_sort(world, new_idx, PAWN);
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;    
  default:
    break;
  }
}


// A bool function which returns if a simple jump in chess world is allowed or not.
int is_allowed_simple_jump_chess(struct world_t* world, enum players player, unsigned int ex_idx, unsigned int new_idx) {
  switch (player)
  {
  case PLAYER_BLACK:
    // Checking if ex_idx has a neighbour and the new_idx is empty.
    if (get_neighbor_chess(get_neighbor_chess(ex_idx,SWEST), SWEST) == new_idx ||
        world_get_sort(world, get_neighbor_chess(ex_idx,SWEST)) != NO_SORT ||
        get_neighbor_chess(get_neighbor_chess(ex_idx,NEAST), NWEST) == new_idx ||
        world_get_sort(world, get_neighbor_chess(ex_idx,NEAST)) != NO_SORT) {
            if (world_get_sort(world, new_idx) == NO_SORT) {
                return 1;
            }
    }
    break;
  case PLAYER_WHITE:
    // Checking if ex_idx has a neighbour and the new_idx is empty.
    if (get_neighbor_chess(get_neighbor_chess(ex_idx,SEAST), SEAST) == new_idx ||
        world_get_sort(world, get_neighbor_chess(ex_idx,SEAST)) != NO_SORT ||
        get_neighbor_chess(get_neighbor_chess(ex_idx,NEAST), NEAST) == new_idx ||
        world_get_sort(world, get_neighbor_chess(ex_idx,NEAST)) != NO_SORT) {
        if (world_get_sort(world, new_idx) == NO_SORT) {
            return 1;
        }
    }
  default:
    break;
  }
  return 0;
}

// Simple jump function for the chess world.
void simple_jump_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx, unsigned int new_idx) {
  switch (player)
  {
  case PLAYER_WHITE:
    if (is_allowed_simple_jump_chess(world, player, ex_idx, new_idx)) {
      world_set(world, new_idx, WHITE);
      world_set(world, ex_idx, NO_COLOR);
      world_set_sort(world, ex_idx, NO_SORT);
      world_set_sort(world, new_idx, PAWN);
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;
  case PLAYER_BLACK:
    if (is_allowed_simple_jump_chess(world, player, ex_idx, new_idx)) {
      world_set(world, new_idx, BLACK);
      world_set(world, ex_idx, NO_COLOR);
      world_set_sort(world, ex_idx, NO_SORT);
      world_set_sort(world, new_idx, PAWN);
      update_current_pieces(player, infos, ex_idx, new_idx);
    }
    break;    
  default:
    break;
  }
}


// A bool function which returns if a multiply jump in chess world is allowed or not.
// Black and White can only jump in two possible directions.
int is_allowed_multi_jump_chess(struct world_t* world, enum players player, unsigned int ex_idx) {
  int new_idx = ex_idx;
  // a is a bool true (1) or false (0)
  int a = 1;
  switch (player) {
  case PLAYER_WHITE:
    // We check if two jumps are possible to return true or false.
    for (int b = 0; b < 2; ++b) {
      a = 0;
      // Forward left move: means to jump 2*width-2.
      if (is_allowed_simple_jump_chess(world, PLAYER_WHITE, new_idx, new_idx - (2*WIDTH-2))) {
        a = 1;
        new_idx = new_idx- (2*WIDTH-2);
      }
      // Forward right move: means to jumo 2*width+2.
      else if (is_allowed_simple_jump_chess(world, PLAYER_WHITE, new_idx, new_idx + (2*WIDTH+2))) {
        a = 1;
        new_idx = new_idx + (2*WIDTH+2);
      }
    }
    return a;
    break;
  case PLAYER_BLACK:
    for (int b = 0; b < 2; ++b) {
      a = 0;
      // Forward left move
      if (is_allowed_simple_jump_chess(world, PLAYER_BLACK, ex_idx, ex_idx + (2*WIDTH-2))) {
        a = 1;
        new_idx = new_idx + (2*WIDTH-2);
      }
      // Forward right move
      else if (is_allowed_simple_jump_chess(world, PLAYER_BLACK, new_idx, new_idx- (2*WIDTH+2))) {
        a = 1;
        new_idx = new_idx - (2*WIDTH+2);
      }
    }
    return a;
    break;
  default:
    break;
  }
  return a;
}

// Multiply jump function for chess world. Returns the end position of the multiply jump.
int multi_jump_chess(struct world_t* world, enum players player, struct positions_info* infos, unsigned int ex_idx) {
  int new_idx = ex_idx;
  int a = 1;
  switch (player) {
  case PLAYER_WHITE:
    // Will jump as long as it is possible.
    while (a) {
      a = 0;
      // Forward left move: means to jump 2*width-2.
      if (is_allowed_simple_jump_chess(world, PLAYER_WHITE, new_idx, new_idx - (2*WIDTH-2))) {
        simple_jump_chess(world, PLAYER_WHITE, infos, new_idx, new_idx - (2*WIDTH-2));
        a = 1;
        new_idx = new_idx - (2*WIDTH-2);
      }
      // Forward right move: means to jumo 2*width+2.
      else if (is_allowed_simple_jump_chess(world, PLAYER_WHITE, new_idx, new_idx + (2*WIDTH+2))) {
        simple_jump_chess(world, PLAYER_WHITE, infos, new_idx, new_idx + (2*WIDTH+2));
        a = 1;
        new_idx = new_idx + (2*WIDTH+2);
      }
    }
    break;
  case PLAYER_BLACK:
    while (a) {
      a = 0;
      // Forward move: Is the same as with player white only mirror-inverted. 
      if (is_allowed_simple_jump_chess(world, PLAYER_BLACK, new_idx, new_idx - 4)) {
        simple_jump_chess(world, PLAYER_BLACK, infos, new_idx, new_idx - 4);
        a = 1;
        new_idx = new_idx - 4;
      }
      // Forward left move.
      else if (is_allowed_simple_jump_chess(world, PLAYER_BLACK, new_idx, new_idx + (2*WIDTH-2))) {
        simple_jump_chess(world, PLAYER_BLACK, infos, new_idx, new_idx + (2*WIDTH-2));
        a = 1;
        new_idx = new_idx + (2*WIDTH-2);
      }
      // Forward right move.
      else if (is_allowed_simple_jump_chess(world, PLAYER_BLACK, new_idx, new_idx - (2*WIDTH+2))) {
        simple_jump_chess(world, PLAYER_BLACK, infos, new_idx, new_idx - (2*WIDTH+2));
        a = 1;
        new_idx= new_idx - (2*WIDTH+2);
      }
    }
    break;
  default:
    break;
  }
  return new_idx;
}
