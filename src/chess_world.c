#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chess_world.h"
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
                    case TOWER:
                        //printf("\033[0;47m\033[1;31m &  \033[0m");
                        if(world_get(world, j) == WHITE){
                            printf("\033[0;47m\033[1;31m &  \033[0m");
                         }
                         else{
                            printf("\033[0;47m\033[1;32m &  \033[0m");
                         }
                        break;
                    case ELEPHANT:
                        //printf("\033[0;47m\033[1;31m <  \033[0m");
                        if(world_get(world, j) == WHITE){
                            printf("\033[0;47m\033[1;31m >  \033[0m");
                         }
                         else{
                            printf("\033[0;47m\033[1;32m <  \033[0m");
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
                    case TOWER:
                        //printf("\033[0;40m\033[1;31m &  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;40m\033[1;31m &  \033[0m");
                         }
                         else{
                            printf("\033[0;40m\033[1;32m &  \033[0m");
                         }
                        break;
                    case ELEPHANT:
                        //printf("\033[0;40m\033[1;31m <  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;40m\033[1;31m >  \033[0m");
                         }
                         else{
                            printf("\033[0;40m\033[1;32m <  \033[0m");
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
                // printf("\033[0;40m\033[1;31m  \033[0m");
                // printf("\033[0;47m\033[1;31m  \033[0m");
                enum sort_t sort_1 = world_get_sort(world,j);
                switch (sort_1){
                    case PAWN:
                        //printf("\033[0;40m\033[1;31m *  \033[0m");
                        if(world_get(world, j) == WHITE){
                            printf("\033[0;40m\033[1;31m *  \033[0m");
                        }
                        else{
                            printf("\033[0;40m\033[1;32m *  \033[0m");
                        }
                        break;
                    case TOWER:
                        //printf("\033[0;40m\033[1;31m &  \033[0m");
                        if(world_get(world, j) == WHITE){
                            printf("\033[0;40m\033[1;31m &  \033[0m");
                        }
                        else{
                            printf("\033[0;40m\033[1;32m &  \033[0m");
                        }
                        break;
                    case ELEPHANT:
                        //printf("\033[0;40m\033[1;31m <  \033[0m");
                        if(world_get(world, j) == WHITE){
                            printf("\033[0;40m\033[1;31m >  \033[0m");
                        }
                        else{
                            printf("\033[0;40m\033[1;32m <  \033[0m");
                        }
                        break;
                    default:
                        printf("\033[0;40m\033[1;31m    \033[0m");
                        break;
                }
                enum sort_t  sort_2 = world_get_sort(world,j+1);
                switch (sort_2){
                    case PAWN:
                        //printf("\033[0;47m\033[1;31m *  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;47m\033[1;31m *  \033[0m");
                        }
                        else{
                            printf("\033[0;47m\033[1;32m *  \033[0m");
                        }
                        break;

                    case TOWER:
                        //printf("\033[0;47m\033[1;31m &  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;47m\033[1;31m &  \033[0m");
                        }
                        else{
                            printf("\033[0;47m\033[1;32m &  \033[0m");
                        }
                        break;

                    case ELEPHANT:
                        //printf("\033[0;47m\033[1;31m <  \033[0m");
                        if(world_get(world, j+1) == WHITE){
                            printf("\033[0;47m\033[1;31m >  \033[0m");
                        }
                        else{
                            printf("\033[0;47m\033[1;32m <  \033[0m");
                        }
                        break;

                    default:
                        printf("\033[0;47m\033[1;31m    \033[0m");
                        break;
                }
                j=j+2; 
                // id its not playable its color = MAX_color
            }
        }
        start = start + WIDTH ;
        printf("\n");
    } 
  printf("\n");
}