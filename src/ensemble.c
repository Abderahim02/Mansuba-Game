#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "geometry.h"
#include "neighbors.h"
#include "ensemble.h"

// _____________________
struct positions_info { 
  int initial_WHITE[HEIGHT];
  //int allowed_moves_WHITE[HEIGHT];  //à ce pont on  a pas besion de definir le champ mouvements possibles pour chaque joueur 
  int current_pieces_WHITE[HEIGHT]; // les positions des pièces du joieur avec les pieces blahces
  int initial_BLACK[HEIGHT];
  //int allowed_moves_BLACK[HEIGHT];
  int current_pieces_BLACK[HEIGHT]; //les positions des pièces du joueur avec les pieces blahces
};




// _____________________cette fonction initialise le monde avec les positions initales de chaque joueur , on suppose que le joueur avec les pieces blanches occupe les positions latèrales à gauche tants que l'autre joueur occupe celles à droite 

void init_players(struct world_t* b) {
  // struct world_t *world = world_init();
  for (int i = 0; i < WORLD_SIZE; ++i) {
    // In the begin we put the white pieces to the left and the black pieces to the right.
    if (i % WIDTH == 0) {
      world_set(b,i,WHITE);
      world_set_sort(b,i,1);
    }
    else if (i % WIDTH-1 == 0) {
      world_set(b,i,BLACK);
      world_set_sort(b,i,1);       
    }
  }
}
//____________ensemble de fonctions auxiliares :
//la premiere sert à verifier si la case à laquelle on veut se deplacer new_idx est un voisin de la case ex_idx:
int is_newex_neighbor(int ex_idx,int new_idx){
  struct neighbors_t neighbors = get_neighbors(ex_idx);
  for ( int j=0; j < MAX_NEIGHBORS; ++j){
    if(neighbors.n[j].i==new_idx){
      return 1;
    }
  }
  return 0;
}
//cette fct sert à verifier si on a le droit de se deplacer vers cette case:
  
int is_allowed_tomove(struct world_t world, int ex_idx, int new_idx){
  if (is_newex_neighbor(ex_idx, new_idx)){ // si new_idx est un voisin 
    if(world.sorts[new_idx] == 0){
      return 1;
    }
  }
  //a ce stade on effectue que des mouvements simples
  return 0;
}

//une fonction qui met a jour la liste des positions des pieces des joueurs

void update_current_pieces(int player, struct positions_info infos,int ex_idx, int new_idx){
  if(player==0){
    for(int i=0; i < HEIGHT; ++i){
      if( infos.current_pieces_BLACK[i]==ex_idx ){
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

void move_player(struct world_t world, int player,struct positions_info infos, int ex_idx, int new_idx ){
  switch (player){
  case 0 : //player_black_pawns
    if(is_allowed_tomove(world, ex_idx, new_idx)){
      world.colors[new_idx] = BLACK;
      world.colors[ex_idx] = NO_COLOR ;
      world.sorts[ex_idx] = NO_SORT;
      world.sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx);
      //infos.current_pieces_BLACK[new_id] = infos.current_pieces_BLACK[ex_id]; 
    }
  case 1: //player_white_pawn
    if(is_allowed_tomove(world, ex_idx, new_idx)){
      world.colors[new_idx] = BLACK;
      world.colors[ex_idx] = NO_COLOR ;
      world.sorts[ex_idx] = NO_SORT;
      world.sorts[new_idx] = PAWN;
      update_current_pieces(player, infos, ex_idx, new_idx);
      //infos.current_pieces_BLACK[new_id] = infos.current_pieces_BLACK[ex_id]; 
    }
  default:
    break;
  }
}


// ________________________

 

int main() {
  return 0;
}

