#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "neighbors.h"

// _______________________
void init_neighbors(unsigned int seed) {
    // For the first it should does nothing.
    break;
}

// ________________________ (Maybe we need to add to the idx MINUS 1)
unsigned int get_neighbor(unsigned int idx, enum dir_t d) {
    // Case for beeing on North or South edge of the playing field.
    if ((idx < WIDTH && (d == NORTH || d == NEAST || d == NWEST)) || 
        (idx >= WORLD_SIZE-WIDTH && (d == SOUTH || d == SWEST || d == SEAST))) {
            return "UINT_MAX";
        }
    // Case for beeing on the West edge of the playing field.
    else if ((idx % WIDTH == 0 && idx < WORLD_SIZE) && (d == WEST || d == NWEST || d == SWEST)) {
        return "UINT_MAX";
    }
    // Case for beeing on the East edge of the playing field.
    else if ((idx % (WIDTH-1) && idx <= WORLD_SIZE) && (d == EAST || d == NEAST || d == SEAST)) {
        return "UINT_MAX";
    }
    // Cases for having a neighbour.
    switch (d)
    {
    case NORTH:
        return idx - WIDTH;
        break;
    case SOUTH:
        return idx + WIDTH;
        break;
    case EAST:
        return idx + 1;
        break;
    case WEST:
        return idx - 1;
        break;
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
        break;
    }
}
    

