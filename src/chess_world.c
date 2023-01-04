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