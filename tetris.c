/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <ncurses.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>
#include <signal.h>

#include "pieces.h"
#include "screen.h"
#include "game.h"

char fixed_pieces[arena_height][arena_length];
const tPiece pieces[NUM_PIECES] = {
	{{0, 1, 0},
	 {0, 1, 0},
	 {0, 1, 0}}, // I

	{{0, 1, 0},
	 {0, 1, 0},
	 {1, 1, 0}}, // J

	{{0, 1, 0},
	 {0, 1, 0},
	 {0, 1, 1}}, // L

	{{1, 1, 0},
	 {1, 1, 0},
	 {0, 0, 0}}, // O

	{{0, 1, 1},
	 {1, 1, 0},
	 {0, 0, 0}}, // S

	{{1, 1, 1},
	 {0, 1, 0},
	 {0, 0, 0}}, // T

	{{1, 1, 0},
	 {0, 1, 1},
	 {0, 0, 0}} // Z
};

int SCORE = 0;
int score_multiplier = 0;

int offi, offj = arena_length/2;              // Offset da peca
tPiece old_piece, new_piece; // Variaveis para pecas (atual e preview)
WINDOW *arena, *preview, *info, *score;
int piece_color;             // Cor da peca atual

int main(int argc, char const *argv[]) {
	srand(time(NULL)); // Seed
	int x, y;

	/* Inicializacao NCurses */
	initscr();             // inicializa a biblioteca ncurses
	// raw();                 // ler teclas de controle (^C, ^Z, etc)
	nodelay(stdscr, TRUE); // leitura não-bloqueante do teclado
	keypad(stdscr, TRUE);  // ativa leitura de teclas de setas, Fn, etc
	noecho();              // não escreve as teclas lidas na tela
	curs_set(0);           // esconde o cursor do terminal
	start_color();         // ativa modulo de cores
	refresh();
	/* Check window size */
	getmaxyx(stdscr, y, x);
	if(y < MIN_HEIGHT || x < MIN_LENGTH) {
		fprintf(stderr, "Tela do terminal muito pequena!\n");
		abort();
	}
	setlocale(LC_ALL, "");
	init_color_pairs();
	init_fixed_pieces();
	/* Inicializacao dos sinais */
	signal_setup();
	/* Inicilizacao do timer */
	timer_setup();

	arena = newwin(arena_height, arena_length, 0, 1);
	// Telas extras usadas na impressao
	preview = newwin(preview_height, preview_length, 0, arena_length + 2);
	score   = newwin(score_height, score_length, preview_height, arena_length + 2);
	info    = newwin(info_height, info_length, 0, arena_length + preview_length + 10);

	// Arena e info so precisam ser impressos uma vez
	printArena(arena_length, arena_height, stdscr);

	int c;

	// Seleciona as duas primeiras pecas
	memcpy(old_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));
	memcpy(new_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));

	printPreview(preview);
	printInfo(info);
	wrefresh(preview);
	wrefresh(info);
	wrefresh(score);

	while(true) {
		printScores(score);
		c = getch();
		handleInput(c);
	}

	delwin(arena);
	endwin();
	return 0;
}
