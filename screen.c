/* DIOGO PARIS KRAUT - GRR20166365 */

#include <ncurses.h>
#include <stdio.h>

#include "pieces.h"
#include "screen.h"
#include "highscores.h"

extern char fixed_pieces[arena_height][arena_length];
extern tPiece old_piece, new_piece;
extern WINDOW *arena;
extern int piece_color;
extern int offi, offj;
extern tScore *SCORE;

void printArenaBoarder(int x, int y, WINDOW *win) {
	int i;

	attron(COLOR_PAIR(MAGENTA));
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

	attroff(COLOR_PAIR(MAGENTA));
	wrefresh(win);
}

void printPiece(tPiece p, WINDOW *win) {
		int i, j;
		wclear(win);

		for(i = 0; i < DIMENTION; i++)
			for(j = 0; j < DIMENTION; j++) // Pecorre peca
				if(old_piece[i][j] == 1)     // Se for bloco, imprime
					mvwaddch(win, i + offi, j + offj, ACS_CKBOARD | COLOR_PAIR(piece_color));

		printFixedPieces();
		wrefresh(win);
}

void printFixedPieces(void) {
	int i, j;

	for(i = 0; i < arena_height; i++)
		for(j = 0; j < arena_length; j++) { // Percorre mapa de pecas fixas
			if(fixed_pieces[i][j] == '1')
				mvwaddch(arena, i, j, ACS_CKBOARD | COLOR_PAIR(RED)); // Imprime
		}
}

void printPreview(WINDOW *win) {
	int i, j;

	wclear(win);

	/* Imprime cabecario */
	wattron(win, COLOR_PAIR(GREEN));
	mvwprintw(win, 0, 0, "PREVIEW");
	wattroff(win, COLOR_PAIR(GREEN));

	/* Imprime caixa do preview */
	wattron(win, COLOR_PAIR(MAGENTA));

	for(i = 2; i < preview_height - 1; i++) // Lado direito
		mvwaddch(win, i, 5, ACS_VLINE);

	for(i = 0; i < 5; i++) { // Teto e chao
		mvwaddch(win, 1, i, ACS_HLINE);
		mvwaddch(win, preview_height -1, i, ACS_HLINE);
	}

	mvwaddch(win, 1, 5, ACS_URCORNER);                  // Canto sup dir
	mvwaddch(win, preview_height - 1, 5, ACS_LRCORNER); // Canto inf dir

	wattroff(win, COLOR_PAIR(MAGENTA));

	/* Imprime peca do preview */
	for(i = 0; i < DIMENTION; i++)
		for(j = 0; j < DIMENTION; j++)
			if(new_piece[i][j] == 1)
				mvwaddch(win, i + 2, j + 1, ACS_CKBOARD | COLOR_PAIR(piece_color));

	wrefresh(win);
}

void printScores(WINDOW *win) {
	wattron(win, COLOR_PAIR(GREEN));
	// Cabecario
	mvwprintw(win, 0, 0, "CURRENT");
	mvwprintw(win, 1, 1, "SCORE");
	wattroff(win, COLOR_PAIR(GREEN));

	wattron(win, A_BLINK);
	mvwprintw(win, 2, 0, "%i", SCORE->score); // Score
	wattroff(win, A_BLINK);


	wrefresh(win);
}

void printInfo(WINDOW *win) {
	wattron(win, COLOR_PAIR(GREEN));

	mvwprintw(win, 0, 5, " _____     _       _     ");
	mvwprintw(win, 1, 5, "|_   _|___| |_ ___|_|___ ");
	mvwprintw(win, 2, 5, "  | | | -_|  _|  _| |_ -|");
	mvwprintw(win, 3, 5, "  |_| |___|_| |_| |_|___|");
	mvwprintw(win, 4, 5, "                         ");

	wattroff(win, COLOR_PAIR(GREEN));

	/* INSTRUCOES */
	wattron(win, A_BOLD | A_UNDERLINE);
	mvwprintw(win, 6, 12, "INSTRUCOES\n");
	wattroff(win, A_BOLD | A_UNDERLINE);

	wprintw(win, "KEY_LEFT  - Move peca para esquerda.\n");
	wprintw(win, "KEY_RIGHT - Move peca para direita.\n");
	wprintw(win, "KEY_DOWN  - Move peca para baixo.\n");
	wprintw(win, "KEY_UP    - Rotaciona a peca.\n");
	wprintw(win, "q         - Salva pontuacao e sai.\n");
	wprintw(win, "^C        - Sai sem salvar.\n");


	wrefresh(win);
}

void printHighscores(FILE *hs, WINDOW *win) {
	int i = 0;
	char s[SCORE_SIZE];

	// Cabecario
	mvwprintw(win, 3, 0, "SCORES\n");

	// High Scores
	/* Enquanto nao tiver impresso 10 score ou fim do arquivo */
	while(i < MAX_SCORES && getHighscore(hs, s)) {
		mvwprintw(win, i + 4, 0, "%s\n", s);
		i++;
	}
	wrefresh(win);
}
