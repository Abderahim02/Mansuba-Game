#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensemble.h"
/*
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
*/

// _____________________
struct world_t{ 
  enum color_t colors[WORLD_SIZE];
  enum sort_t sorts[WORLD_SIZE];
};


enum players{
  PLAYER_WHITE = 2,
  PLAYER_BLACK = 1 ,
};
struct positions_info { 
  int initial_WHITE[HEIGHT];
  /*  à ce pont on  a pas besion de definir le champ mouvements possibles pour chaque joueur */
  int current_pieces_WHITE[HEIGHT]; // les positions des pièces du joieur avec les pieces blahces
  int initial_BLACK[HEIGHT];
  int current_pieces_BLACK[HEIGHT]; //les positions des pièces du joueur avec les pieces blahces
};


// _____________________cette fonction initialise le monde avec les positions initales de chaque joueur , on suppose que le joueur avec les pieces blanches occupe les positions latèrales à gauche tants que l'autre joueur occupe celles à droite 

// ____________
/*void add_to_current_piece(struct positions_info positions_info, unsigned int ex_idx, unsigned int new_idx){
  for(int i=0 ; i < HEIGHT; ++i ){
    if (positions_info)
  }
  }
}____*/
//cette fonction initialise les informations sur les joueurs NB: les tableaux sont remplis initialement par WORLD_SIZE partout)
struct positions_info init_infos(){
  struct positions_info infos;
  for (int i=0; i < HEIGHT ; ++i){
    infos.current_pieces_BLACK[i] = WORLD_SIZE;
    infos.current_pieces_WHITE[i] = WORLD_SIZE;
  }
  return infos;
}
void add_to_current_piece(struct positions_info positions_info, enum players player, unsigned int idx){
  switch (player){
  case PLAYER_WHITE:
        for (int i=0; i < HEIGHT; ++i){
              if(positions_info.current_pieces_WHITE[i] != WORLD_SIZE){
                      positions_info.current_pieces_WHITE[i] = idx;
                      break;
           }
        }
        break;
    case PLAYER_BLACK:
        for (int i=0; i < HEIGHT; ++i){
              if(positions_info.current_pieces_BLACK[i] != WORLD_SIZE){
                      positions_info.current_pieces_BLACK[i] = idx;
                      break;
           }
        }
        break;
      default:
        break;
  }
}
void init_players(struct world_t* b, struct positions_info positions_info) {
    //struct positions_info positions_info;
    for (int i = 0; i < WORLD_SIZE; ++i) {
        // In the begin we put the white pieces to the left and the black pieces to the right.
        if (i % WIDTH == 0) {
            world_set(b,i,WHITE);
            world_set_sort(b,i,1);
            add_to_current_piece(positions_info, PLAYER_WHITE, i);
            //positions_info.initial_WHITE[i] = 1;
            //positions_info.current_pieces_WHITE[i] = 1;
        }
        else if ((i% WIDTH)  == WIDTH - 1 ) {
            world_set(b, i, BLACK);
            world_set_sort(b, i, 1);
            add_to_current_piece(positions_info, PLAYER_BLACK, i);
            //positions_info.initial_BLACK[i] = 1;
            //positions_info.current_pieces_BLACK[i] = 1;
        }
    }
}

//____________ensemble de fonctions auxiliares :
//la premiere sert à verifier si la case à laquelle on veut se deplacer new_idx est un voisin de la case ex_idx:

int is_new_ex_neighbor(unsigned int ex_idx, unsigned int new_idx){
  struct neighbors_t neighbors = get_neighbors(ex_idx);
  for ( int j=0; j < MAX_NEIGHBORS; ++j){
    if(neighbors.n[j].i == new_idx){
      return 1;
    }
  }
  return 0;
}
//cette fct sert à verifier si on a le droit de se deplacer vers cette case:
  
int is_allowed_to_move(struct world_t* world, unsigned int ex_idx, unsigned int new_idx){
  if (is_new_ex_neighbor(ex_idx, new_idx)){ // si new_idx est un voisin 
    if( world->sorts[new_idx] == 0){
      return 1;
    }
  }
  //a ce stade on effectue que des mouvements simples
  return 0;
}

//une fonction qui met a jour la liste des positions des pieces des joueurs

void update_current_pieces(enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx){
  if( player == 1){
    for(int i=0; i < HEIGHT; ++i){
      if( infos.current_pieces_BLACK[i]== ex_idx ){
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
// c'est la fonction qui fait un mouvement d'une piece si c'est possible

void move_player(struct world_t* world, enum players player, struct positions_info infos, unsigned int ex_idx, unsigned int new_idx ){
  switch (player){
  case PLAYER_BLACK : //player_black_pawns
    if(is_allowed_to_move(world, ex_idx, new_idx)){
      world->colors[new_idx] = BLACK;
      world->colors[ex_idx] = NO_COLOR ;
      world->sorts[ex_idx] = NO_SORT;
      world->sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx);
      //infos.current_pieces_BLACK[new_id] = infos.current_pieces_BLACK[ex_id]; 
    }
    break;
  case PLAYER_WHITE: //player_white_pawn
    if(is_allowed_to_move(world, ex_idx, new_idx)){
      world->colors[new_idx] = BLACK;
      world->colors[ex_idx] = NO_COLOR ;
      world->sorts[ex_idx] = NO_SORT;
      world->sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx);

      
      //infos.current_pieces_BLACK[new_id] = infos.current_pieces_BLACK[ex_id]; 
    }
    break;
  default:
    break;
  }
}
void print_world( struct world_t* world ){
  for (int i=0; i< WORLD_SIZE ; ++i){
    if( i%HEIGHT == 0 && i != 0 ){
      printf("\n%d ", world->colors[i]);    
    }
    else {
      printf("%d ", world->colors[i]);
    
    }
  }
}

int main() {
  struct world_t* world = world_init();
  struct positions_info positions = init_infos();
  init_players(world, positions);
  printf("First round: \n");
  print_world(world);
  printf("\n");
  move_player(world, PLAYER_WHITE, positions, 0, 2);
  printf("Second round:\n");
  print_world(world);
  printf("\n");
  return 0;
}
