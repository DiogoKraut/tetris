/* DIOGO PARIS KRAUT - GRR20166365 */

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "pieces.h"
#include "screen.h"
#include "game.h"
#include "highscores.h"

extern char fixed_pieces[arena_height][arena_length];
extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;
extern WINDOW *arena, *preview;
extern int piece_color;
extern int offi, offj;
extern tScore *SCORE;

int checkBottomCollision(tPiece p) {
	int i, j;

	// Percorre a peca
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++) {
			if(old_piece[i][j] == 1) // Se eh bloco
				if(i + offi+1 >= arena_height || fixed_pieces[i + offi+1][j + offj] == '1') {
				// Se colidir com o fundo ou outra peca
					affixPiece(old_piece); // Fixa a peca
					SCORE->score += AFFIX_SCORE;
					return 0; // Colidiu
			}
		}
	return 1; // Nao colidiu
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
							can_move = 0;// Peca nao pode ser movida
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
							can_move = 0;// Peca nao pode ser movida
			if(can_move == 1) {
				offj++;
				printPiece(old_piece, arena);
			}
			break;
		case KEY_DOWN:
			if(checkBottomCollision(old_piece)) { // Nao colidiu
				offi++;
				printPiece(old_piece, arena);
				SCORE->score += STD_SCORE;
			}	else { // Colidiu
				/* Peca nova recebe uma cor aleatoria */
				piece_color = (rand() % 3) + 2;

				/* old_piece = new_piece, new_piece = peca aleatoria da lista de pecas */
				memcpy(old_piece, new_piece, sizeof(tPiece));
				memcpy(new_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));

				/* Reseta os offsets */
				offi = 0;
				offj = arena_length/2;

				printPreview(preview);
				printPiece(old_piece, arena);
			}
	}
}

void affixPiece(tPiece p) {
	int i, j;

	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++)              // Percorre peca
			if(p[i][j] == 1)                          // Se for bloco
				fixed_pieces[i + offi][j + offj] = '1'; // Fixa peca

	/* Verifica se uma linha foi completada */
	for(i = 0; i < DIMENTION; i++) // Para cada linha da peca
		checkLine(i + offi);

	SCORE->score += SCORE->combo_multiplier;
	SCORE->combo_multiplier = 0.0;
}



void rotate(void) {
	int i, j, newi, newj, pi, pj;

	/* Pivos do centro da peca */
	pi = 1;
	pj = 1;

	tPiece aux;
	/* Zera aux */
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++)
			aux[i][j] = 0;

	/* Rotacao de matriz ao redor de um ponto */
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++) {
			newi = j + pi - pj;
			newj = pi + pj - i;

			aux[newi][newj] = old_piece[i][j];
		}

	/* Se a rotacao foi valida, aplicar aa peca */
	if(checkCollision(&aux) == 1) {
		memcpy(old_piece, aux, sizeof(tPiece));
		printPiece(old_piece, arena);
	}
}

int checkCollision(tPiece *p) {
	int i, j;

	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++) // Percorre a peca
			if(old_piece[i][j] == 1)     // Se for um bloco
				if(i + offi >= arena_height || j + offj >= arena_length || j + offj <= 0 ||
					fixed_pieces[i + offi][j + offj] == '1')
					return 0; // Colidiu
	return 1; // Nao colidiu
}
