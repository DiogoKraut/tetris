#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "pieces.h"
#include "screen.h"
#include "setup.h"

extern char fixed_pieces[arena_height][arena_length];
extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;
extern WINDOW *arena;
extern int piece_color;

void timer_setup(void) {
	/* Timer define a intensidade da "gravidade". Em intervalos fixos SIGALRM eh
	   elevado sinalizando que a peca deve ser movida                           */
	struct itimerval timer;

	/*  Reseta os membros de timer  */
	timerclear(&timer.it_interval);
	timerclear(&timer.it_value);

	/*  Seta o timer  */
	timer.it_interval.tv_usec = INTERVAL;
	timer.it_value.tv_usec    = INTERVAL;
	setitimer(ITIMER_REAL, &timer, NULL);
}

void signal_setup(void) {
	struct sigaction sa;

	/* Inicializacao da estrutura sa */
	sa.sa_handler = signal_handler;
	sa.sa_flags   = 0;
	sigemptyset(&sa.sa_mask);

	/* Sinais */
	sigaction(SIGINT, &sa, NULL);  // Saida forcada
	sigaction(SIGALRM, &sa, NULL); // Timer
}

void signal_handler(int signum) {
	switch(signum) {
		case SIGALRM: // Move peca para baixo ou gera nova peca
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
			break;

		case SIGINT:
			endwin();
			abort();
	}
}

void handleInput(int c) {
	int j;
	switch(c) {
		case KEY_LEFT:
		case KEY_RIGHT:
		case ' ':
			movePiece(c);
			break;

		case KEY_UP:
		case KEY_DOWN:
			break;
	}
}

void init_color_pairs(void) {
	/* Inicia pares de cores */
	init_pair(1, COLOR_RED, COLOR_BLACK);     // Cores das pecas ja fixas

	init_pair(2, COLOR_YELLOW, COLOR_BLACK);  /*    Possiveis cores      */
	init_pair(3, COLOR_GREEN, COLOR_BLACK);	  /*       das pecas         */
	init_pair(4, COLOR_BLUE, COLOR_BLACK);    /*       em queda          */

	init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // Cor das paredes da arena
}

void init_fixed_pieces(void) {
	int i,j;

	for(i = 0; i < arena_height; i++)
		for(j = 0; j < arena_length; j++)
			fixed_pieces[i][j] = '0';
}
