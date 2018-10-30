/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include "pieces.h"
#include "screen.h"
#include "setup.h"


const tPiece pieces[NUM_PIECES] = { // A coordenada do centro aparece por primeiro
	{ // I
		0, 0, 0, 0,
		2, 0, 1, 3,
	},
	{ // L
		1, 0, 2, 2,
		0, 0, 0, 1,
	},
	{ // J
		1, 0, 2, 0,
		0, 0, 0, 1,
	},
	{ // O
		0, 1, 1, 0,
		0, 1 ,0, 1,
	},
	{ // S
		1, 0, 0, 1,
		1, 1, 2, 0,
	},
	{ // T
		1, 1, 1, 2,
		1, 0, 2, 1,
	},
	{ // Z
		1, 0, 0, 1,
		1, 0, 1, 2,
	},
};

tPiece old_piece, new_piece; // Globais pois precisam ser acessadas em signal_handler

int main(int argc, char const *argv[]) {
	srand(time(NULL)); // Seed
	int x, y;

	/* Inicializacao NCurses */
	initscr();             // inicializa a biblioteca ncurses
	//raw();                 // ler teclas de controle (^C, ^Z, etc)
	nodelay(stdscr, TRUE); // leitura não-bloqueante do teclado
	keypad(stdscr, TRUE);  // ativa leitura de teclas de setas, Fn, etc
	noecho();              // não escreve as teclas lidas na tela
	curs_set(0);           // esconde o cursor do terminal
	start_color();         // ativa modulo de cores

	/* Inicializacao dos sinais */
	signal_setup();
	/* Inicilizacao do timer */
	timer_setup();
	/* Check window size */
	getmaxyx(stdscr, y, x);
	if(y < MIN_HEIGHT || x < MIN_LENGTH) {
		fprintf(stderr, "Tela do terminal muito pequena!\n");
		abort();
	}

	/* Inicia pares de cores */
	init_pair(0, COLOR_RED, COLOR_BLACK);     // Cores das pecas ja fixas

	init_pair(1, COLOR_YELLOW, COLOR_BLACK);  /*    Possiveis cores      */
	init_pair(2, COLOR_GREEN, COLOR_BLACK);	  /*       das pecas         */
	init_pair(3, COLOR_BLUE, COLOR_BLACK);    /*       em queda          */

	init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // Cor das paredes da arena

	WINDOW *arena = newwin(20, 15, 0, 1);
	

	printArena(15, 20);
	refresh();
	int c;

	memcpy(old_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));
	memcpy(new_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));
	while(true) {
		c = getch();

		handleInput(c);

		printPiece(old_piece, arena);
	}
	delwin(arena);
	endwin();
	return 0;
}
