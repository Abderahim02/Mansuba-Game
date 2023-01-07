#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complement_ensemble.h"
#include <time.h>
//a function testing if a pièce is prisoner 
int is_prisoner(enum players player, struct positions_info* infos, unsigned int idx ){
  switch (player){
    case PLAYER_WHITE:
        for(int i=0; i<HEIGHT; ++i){ //we must check if its a real current position
          if(infos->current_pieces_WHITE[i] == idx && infos->status_pieces_WHITE[i] == PRISONER ){
              return 1;
          }
        }
        break;
    case PLAYER_BLACK:
        for(int i=0; i<HEIGHT; ++i){
          if(infos->current_pieces_BLACK[i] == idx && infos->status_pieces_BLACK[i] == PRISONER ){
              return 1;
          }
        }
    default:
        break;
  }
  return -1;
}

//  A function testing if  a position idx is an initial position for the player 
int is_initial_position(enum players player, struct positions_info* infos, unsigned int idx){
    switch (player){
        case PLAYER_WHITE:
            for(int i=0; i<HEIGHT; ++i){
                if(infos->initial_WHITE[i] == idx ){
                    return 1;
                }
            }
            break;
        case PLAYER_BLACK:
            for(int i=0; i<HEIGHT; ++i){
                if(infos->initial_BLACK[i] == idx ){
                    return 1;
                }
            }
            break;
    }
    return 0;
}

//make a piece free
void escape_piece(enum players player , struct positions_info* infos, unsigned int idx ){
    switch (player){
        case PLAYER_WHITE:
            for( int i=0; i<HEIGHT;++i ){
                if(infos->current_pieces_WHITE[i]==idx && is_prisoner(PLAYER_WHITE, infos, idx ) == 1){ //we check if its a prisonner position
                    int j = rand()%2; // the piece can escape with a probability of 0.5
                    if(j == 1){
                        infos->status_pieces_WHITE[i] = NON_PRISONER;
                        break;
                    }
                }
            }
            break;
        case PLAYER_BLACK:
             for( int i=0; i<HEIGHT;++i ){
                if(infos->current_pieces_BLACK[i]==idx && is_prisoner(PLAYER_BLACK, infos, idx ) == 1){ //we check if its a prisonner position
                    int j = (rand())%2; // the piece can escape with a probability of 0.5
                    //printf("\nj_rand == %d\n", j);
                    if(j == 1){
                        infos->status_pieces_BLACK[i] = NON_PRISONER;
                        break;
                    }
                }
            }
            break;
    }
}
