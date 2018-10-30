/* DIOGO PARIS KRAUT - GRR20166365 */

#include <ncurses.h>
#include "pieces.h"

extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;

void movePieceDown(void) {
	int j;
	for(j= 0; j < MAX_SHAPE; j++)
		old_piece[0][j]++;
}

bool checkCollision(void) {
	return 1;
}