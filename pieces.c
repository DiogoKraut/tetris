/* DIOGO PARIS KRAUT - GRR20166365 */

#include <ncurses.h>
#include "pieces.h"
#include "screen.h"

extern char fixed_pieces[arena_height][arena_length];
extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;
extern WINDOW *arena;
extern int piece_color;

void movePieceDown(void) {
	int j;
	for(j= 0; j < MAX_SHAPE; j++)
		old_piece[0][j]++;
}

int checkBottomCollision(void) {
	int j;
	for(j = 0; j < MAX_SHAPE; j++) {
		if(old_piece[0][j] + 1 >= arena_height ||
			 fixed_pieces[old_piece[0][j] + 1] [old_piece[1][j]] == '1') {
				 affixPiece();
				 return 0;
		}
	}
	return 1;
}

void movePiece(int dir) {
	int j, aux = 0;
		switch(dir) {
			case KEY_LEFT:
				for(j = 0; j < MAX_SHAPE; j++)
					if(old_piece[1][j] - 1 < 0 ||
						 fixed_pieces[old_piece[0][j]] [old_piece[1][j] - 1] == '1')
						 aux = 1;
				if(aux == 0) {
					for(j = 0; j < MAX_SHAPE; j++) {
						old_piece[1][j]--;
						printPiece(old_piece, arena);
					}
				}
				break;

			case KEY_RIGHT:
				for(j = 0; j < MAX_SHAPE; j++)
					if(old_piece[1][j] + 1 >= arena_length ||
						 fixed_pieces[old_piece[0][j]] [old_piece[1][j] + 1] == '1')
						 aux = 1;
				if(aux == 0) {
					for(j = 0; j < MAX_SHAPE; j++) {
						old_piece[1][j]++;
						printPiece(old_piece, arena);
					}
				}
				break;
			case ' ':
				if(checkBottomCollision()) {
					movePieceDown();
					printPiece(old_piece, arena);
				}	else {
					/* Peca nova recebe uma cor aleatoria */
					piece_color = (rand() % 3) + 2;

					/* old_piece = new_piece, new_piece = peca aleatoria da lista de pecas */
					memcpy(old_piece, new_piece, sizeof(tPiece));
					memcpy(new_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));
				}
		}
}

void affixPiece(void) {
	int j;
	for(j = 0; j < MAX_SHAPE; j++)
		fixed_pieces[old_piece[0][j]] [old_piece[1][j]] = '1';
}

// void rotate(int dir) {
// 	int j, pi, pj;
//
// 	/* Pivos do centro da peca */
// 	pi = old_piece[0][0];
// 	pj = old_piece[1][0];
//
// 	switch(dir) {
// 		case KEY_UP:
// 			for(j = 0; j < MAX_SHAPE; j++) {
// 				old_piece[0][j] = (old_piece[1][j] + px - 3)
// 			}
// 	}
// }
