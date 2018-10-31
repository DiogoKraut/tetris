/* DIOGO PARIS KRAUT - GRR20166365 */

#include <ncurses.h>
#include "pieces.h"
#include "screen.h"
#include "game.h"

extern char fixed_pieces[arena_height][arena_length];
extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;
extern WINDOW *arena;
extern int piece_color;
extern int offi, offj;

int checkBottomCollision(tPiece p) {
	int i, j;
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++) {
			if(old_piece[i][j] == 1)
				if(i + offi+1 >= arena_height || fixed_pieces[i + offi+1][j + offj] == '1') {
					affixPiece(old_piece);
					return 0;
			}
		}
	return 1;
}

void movePiece(int dir) {
	int i, j, can_move = 1;
		switch(dir) {
			case KEY_LEFT:
				/* Verificar colisao aa esq */
				for(i = 0; i < DIMENTION; i++)
					for(j = 0; j < DIMENTION; j++) // Percorre a peca
						if(old_piece[i][j] == 1)     // Se for um bloco
							/* Se esta no limite esq da arena ou se ha peca fixa */
							if(j + offj-1 < 0 || fixed_pieces[i + offi][j + offj-1] == '1')
								can_move = 0;// Se chegar aqui a peca nao pode ser movida
				if(can_move == 1) {
					offj--;
					printPiece(old_piece, arena);
				}
				break;

			case KEY_RIGHT:
				/* Verificar colisao aa dir */
				for(i = 0; i < DIMENTION; i++)
					for(j = 0; j < DIMENTION; j++) // Percorre a peca
						if(old_piece[i][j] == 1)     // Se for um bloco
							/* Se esta no limite dir da arena ou se ha peca fixa */
							if(j + offj+1 >= arena_length || fixed_pieces[i + offi][j + offj+1] == '1')
								can_move = 0;// Se chegar aqui a peca nao pode ser movida
				if(can_move == 1) {
					offj++;
					printPiece(old_piece, arena);
				}
				break;
			case ' ':
				if(checkBottomCollision(old_piece)) {
					offi++;
					printPiece(old_piece, arena);
				}	else {
					/* Peca nova recebe uma cor aleatoria */
					piece_color = (rand() % 3) + 2;

					/* old_piece = new_piece, new_piece = peca aleatoria da lista de pecas */
					memcpy(old_piece, new_piece, sizeof(tPiece));
					memcpy(new_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));

					offi = 0;
					offj = arena_length/2;

					printPiece(old_piece, arena);
				}
		}
}

void affixPiece(tPiece p) {
	int i, j;
	/* Fixa a peca */
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++)
			if(p[i][j] == 1)
				fixed_pieces[i + offi][j + offj] = '1';

	/* Verifica se uma linha foi completada */
	for(i = 0; i < DIMENTION; i++)
		checkLine(i + offi);
}



void rotate(int dir) {
	int i, j, newi, newj, pi, pj;

	/* Pivos do centro da peca */
	pi = 1;
	pj = 1;

	tPiece aux;
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++)
			aux[i][j] = 0;

	switch(dir) {
		case KEY_UP:
			for(i = 0; i < DIMENTION; i++)
				for(j = 0; j < DIMENTION; j++) {
					newi = j + pi - pj;
					newj = pi + pj - i;

					// old_piece[newi][newj] = old_piece[i][j];
					aux[newi][newj] = old_piece[i][j];
				}
			memcpy(old_piece, aux, sizeof(tPiece));
	}
	printPiece(old_piece, arena);
}
