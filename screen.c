/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "screen.h"

extern char fixed_pieces[arena_height][arena_length];
extern tPiece old_piece, new_piece;
extern WINDOW *arena;
extern int piece_color;

void printArena(int x, int y, WINDOW *win) {
	int i;

	attron(COLOR_PAIR(5));
	/* Imprime lados */
	for(i = 0; i < y; i++) {
		mvwaddch(win, i, 0, ACS_VLINE);
		mvwaddch(win, i, x + 1, ACS_VLINE);
	}

	/* Imprime cantos inferiores */
	mvwaddch(win, y, 0, ACS_LLCORNER);
	mvwaddch(win, y, x + 1, ACS_LRCORNER);

	/* Imprime chao */
	for(i = 1; i <= x; i++)
		mvwaddch(win, y, i, ACS_HLINE);

	attroff(COLOR_PAIR(5));
}

void printPiece(tPiece p, WINDOW *win) {
		int j;
		wclear(win);

		for(j = 0; j < MAX_SHAPE; j++)
			mvwaddch(win, p[0][j], p[1][j], ACS_CKBOARD | COLOR_PAIR(piece_color));

		printFixedPieces();
		wrefresh(win);
}

void printFixedPieces(void) {
	int i, j;
	for(i = 0; i < arena_height; i++)
		for(j = 0; j < arena_length; j++) {
			if(fixed_pieces[i][j] == '1')
				mvwaddch(arena, i, j, ACS_CKBOARD | COLOR_PAIR(1));
		}
}
