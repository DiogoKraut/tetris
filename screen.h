/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "pieces.h"

#define MIN_HEIGHT 21
#define MIN_LENGTH 35

#define arena_length 15
#define arena_height 20

void printArena(int x, int y, WINDOW *win);
void printPiece(tPiece p, WINDOW *win);
void printFixedPieces(void);
