#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

/** The width (number of columns) of the world */
#ifndef WIDTH
  #define WIDTH 10
#endif
/** The height (number of rows) of the world */
#ifndef HEIGHT
  #define HEIGHT 10
#endif

/** The number of possible places in the world */
#define WORLD_SIZE (WIDTH*HEIGHT)

/** The number of players in a game */
#define MAX_PLAYERS 2

/** Enum defining the possible colors in the world */
enum color_t {
  NO_COLOR  = 0,  // Default color, used to initialize worlds
  BLACK     = 1,
  WHITE     = 2,
  MAX_COLOR = 3,  // Total number of different colors
};

/** Enum defining the possible sorts of pieces in the world */
enum sort_t {
  NO_SORT  = 0,   // Default sort (i.e nothing)
  PAWN     = 1,
  TOWER    = 2,
  ELEPHANT = 3,
  MAX_SORT = 4,   // Total number of different sorts
};

/** Enum defining the possible directions in the world
 Opposite directions correspond to opposite integers
 The directions are all consecutive */
enum dir_t {
  NO_DIR  = 0,    // Default dir (i.e unset)
  EAST    = 1,
  NEAST   = 2,
  NORTH   = 3,
  NWEST   = 4,
  WEST    = -1,
  SWEST   = -2,
  SOUTH   = -3,
  SEAST   = -4,
  MAX_DIR = 9,    // Total number of different directions
};

/** Return a string describing the color `c` and sort `s` */
const char* place_to_string(enum color_t c, enum sort_t s);

/** Return a string describing the direction `d` */
const char* dir_to_string(enum dir_t d);

#endif // __GEOMETRY_H__
