#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"

const char* place_to_string(enum color_t c, enum sort_t s){
  if (s == PAWN) {
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
  return "NO SORT";
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
    return "MAX_DIR";
    break;
  default:
    return "NO_DIR";
    break;
  }
}
