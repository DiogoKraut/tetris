#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "pieces.h"
#include "screen.h"
#include "game.h"

extern char fixed_pieces[arena_height][arena_length];
extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;
extern WINDOW *arena;
extern int piece_color;
extern int SCORE, score_multiplier;

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
	sigaction(SIGINT,  &sa, NULL);  // Saida forcada
	sigaction(SIGALRM, &sa, NULL);  // Timer
	sigaction(SIGUSR1, &sa, NULL);  // Usado para indicar fim de jogo
}

void signal_handler(int signum) {
	switch(signum) {
		case SIGALRM: // Move peca para baixo ou gera nova peca
			movePiece(KEY_DOWN); // ' ' move a peca para baixo
			break;

		case SIGINT:
			endwin();
			abort();

		case SIGUSR1:
			endwin();
			printf("Game Over \n");
			exit(1);
			break;

	}
}

void handleInput(int c) {
	switch(c) {
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_DOWN:
			movePiece(c);
			break;

		case KEY_UP:
			rotate();
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

	init_pair(6, COLOR_BLACK, COLOR_BLACK);
}

void init_fixed_pieces(void) {
	int i,j;

	for(i = 0; i < arena_height; i++)
		for(j = 0; j < arena_length; j++)
			fixed_pieces[i][j] = '0';
}

void checkLine(int line) {
	if(line == 0)
		raise(SIGUSR1); // Peca foi fixada no topo da arena, fim de jogo

	int j, completed = 1;

	/* Verifica se a linha esta completa */
	for(j = 0; j < arena_length; j++)
		if(fixed_pieces[line][j] != '1')
			completed = 0;

	if(completed == 1)
		removeLine(line);
}

void removeLine(int line) {
	int j;
	for(j = 0; j < arena_length; j++)
		fixed_pieces[line][j] = '0';

	score_multiplier += 100;
	wrefresh(arena);
}
