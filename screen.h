/* DIOGO PARIS KRAUT - GRR20166365 */

#include <ncurses.h>
#include "pieces.h"

#define arena_length 15
#define arena_height 20

#define preview_length DIMENTION + 5
#define preview_height DIMENTION + 3

#define score_length preview_length + 7
#define score_height arena_height - preview_height

#define info_length arena_length * 3
#define info_height arena_height

#define MIN_HEIGHT arena_height + 1
#define MIN_LENGTH arena_length + preview_length + info_length + 1

/* Definicoes de cores */
#define RED     1
#define YELLOW  2
#define GREEN   3
#define BLUE    4
#define MAGENTA 5
#define BLACK   6

#define MAX_SCORES 10

void printArenaBoarder(int x, int y, WINDOW *win);
void printPiece(tPiece p, WINDOW *win);
void printFixedPieces(void);
void printPreview(WINDOW *win);
void printScores(WINDOW *win);
void printInfo(WINDOW *win);
void printHighscores(FILE *hs, WINDOW *win);
