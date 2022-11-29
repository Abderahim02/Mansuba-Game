#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
const char* place_to_string(enum color_t c, enum sort_t s){
  if ( s == 1 ){
    switch (c){
    case 1:
      return "BLACK";
      break;
    case 2:
      return  "WHITE";
      break;
    case 0:
      return "NO COLOR";
      break;
    case 3:
      return "NO COLOR";
      break;
    }
  }
  else{
    return "NO SORT";
  }
}
const char* dir_to_string(enum dir_t d){
  switch (d){
  case 1:
    return "EAST";
    break;
  case 2:
    return "NEAST";
    break;
  case 3:
    return "NORTH";
    break;
  case 4:
    return "NWEST";
    break;
  case -1 :
    return "WEST";
    break;
  case -2 :
    return "SWEST";
    break;
  case -3 :
    return "SOUTH";
    break;
  case -4:
    return "SEAST";
    break;
  case 9:
    return "EMPTY DIRECTION";
    break;
  case 0 :
    return "NO DIR";
    break;
  default:
    return "NO DIR";
    break;
  }
}

/*
int main(int argc, char *argv[]){
  enum color_t c = WHITE;
  enum sort_t s = PAWN;
  printf("The case is: %s\n",place_to_string(c,s));
  return 0;
}

*/
