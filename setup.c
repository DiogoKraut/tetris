#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "pieces.h"
#include "screen.h"
#include "setup.h"

extern const tPiece pieces[NUM_PIECES];
extern tPiece old_piece, new_piece;

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
			if(checkCollision())
				movePieceDown();
			else {
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
			for(j = 0; j < MAX_SHAPE; j++)
				old_piece[1][j]--;
			break;

		case KEY_RIGHT:
			for(j = 0; j < MAX_SHAPE; j++)
				old_piece[1][j]++;
			break;

		case KEY_UP:
		case KEY_DOWN:
			break;
	}
}