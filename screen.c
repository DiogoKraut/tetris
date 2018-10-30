/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "screen.h"

void printArena(int x, int y) {
	int i;

	attron(COLOR_PAIR(4));
	/* Imprime lados */
	for(i = 0; i < y; i++) {
		mvaddch(i, 0, ACS_VLINE);
		mvaddch(i, x + 1, ACS_VLINE);
	}

	/* Imprime cantos inferiores */
	mvaddch(y, 0, ACS_LLCORNER);
	mvaddch(y, x + 1, ACS_LRCORNER);

	/* Imprime chao */
	for(i = 1; i <= x; i++)
		mvaddch(y, i, ACS_HLINE);

	attroff(COLOR_PAIR(4));
}

void printPiece(tPiece p, WINDOW *win) {
		int j, color;
		wclear(win);

		color = (rand() % 3) + 1;
		wattron(win, COLOR_PAIR(color));
		for(j = 0; j < MAX_SHAPE; j++)
			mvwaddch(win, p[0][j], p[1][j], ACS_CKBOARD);
		wrefresh(win);
		wattroff(win, COLOR_PAIR(color));
}