#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "triangular_world.h"


void print_triangular_world(struct world_t* world){
  printf("\n");
   printf("\n");
  for (int i=0; i< WORLD_SIZE ; ++i){
    enum color_t color = world_get(world, i);
    if( i%HEIGHT == 0 && i != 0 ){
            if( color == WHITE ){ // we use green color for white pieces 
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\n\033[31m* \033[0m"); //we use the symbol * for pawn 
                    break;
                case TOWER:
                    printf("\n\033[31m> \033[0m");//we use the symbol > for white tower 
                    break;
                case ELEPHANT:
                    printf("\n\033[31m& \033[0m"); //we use the symbol & for elephant 
                    break;
                default:
                    break;
                }
            }
            else if(color == BLACK ){ // we use red color for white pieces 
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\n\033[1;32m* \033[0m");
                    break;
                case TOWER:
                    printf("\n\033[1;32m< \033[0m");
                    break;
                case ELEPHANT:
                    printf("\n\033[1;32m& \033[0m");
                    break;
                default:
                    break;
                }
            }
            else if( color == NO_COLOR){
                printf("\n\033[1;37m0 \033[0m");
            }
            else{
                printf("\n\033[1;37m  \033[0m");
            }
         }
    else  {   
            if(color == WHITE ){
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\033[1;31m* \033[0m");
                    break;
                case TOWER:
                    printf("\033[1;31m> \033[0m");
                    break;
                case ELEPHANT:
                    printf("\033[1;31m& \033[0m");
                    break;
                default:
                    break;
                }
                
            }
            else if(world_get(world, i) == BLACK ){
                switch (world_get_sort(world,i)){
                case PAWN:
                    printf("\033[1;32m* \033[0m");
                    break;
                case TOWER:
                    printf("\033[1;32m< \033[0m");
                    break;
                case ELEPHANT:
                    printf("\033[1;32m& \033[0m");
                    break;
                default:
                    break;
                }
            }
            else if(color == NO_COLOR){
                printf("\033[1;37m0 \033[0m");
            }    
            else{
                printf("\033[1;37m  \033[0m");
            }
    }
  }
  printf("\n");
}