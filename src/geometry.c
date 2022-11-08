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
  else
    return "NO SORT";
}
int main(int argc, char *argv[]){
  enum color_t c = WHITE;
  enum sort_t s = PAWN;
  printf("The case is: %s\n",place_to_string(c,s));
  return 0;
}
