/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "pieces.h"

#define MIN_HEIGHT 21
#define MIN_LENGTH 35

#define arena_length 15
#define arena_height 20

#define preview_length DIMENTION + 5
#define preview_height DIMENTION + 3

#define score_length preview_length
#define score_height arena_height - preview_height

#define info_length arena_length * 3
#define info_height arena_height

void printArena(int x, int y, WINDOW *win);
void printPiece(tPiece p, WINDOW *win);
void printFixedPieces(void);
void printPreview(WINDOW *win);
void printScores(WINDOW *win);
void printInfo(WINDOW *win);
