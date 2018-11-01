/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#include "screen.h"
#include "game.h"
#include "highscores.h"

extern char fixed_pieces[arena_height][arena_length];
extern WINDOW *arena, *preview, *info, *score;
extern tScore *SCORE;

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
	sa.sa_handler = signal_handler; // Funcao para tratar sinais
	sa.sa_flags   = 0;
	sigemptyset(&sa.sa_mask);

	/* Sinais */
	sigaction(SIGINT,  &sa, NULL);  // Saida forcada
	sigaction(SIGALRM, &sa, NULL);  // Timer
	sigaction(SIGUSR1, &sa, NULL);  // Usado para indicar fim de jogo
}

void signal_handler(int signum) {
	switch(signum) {
		case SIGALRM: // Move peca para baixo
			movePiece(KEY_DOWN);
			break;

		case SIGINT: // Parada forcada
			endwin();
			abort();

		case SIGUSR1: // Fim de jogo
			gameOver();
			break;
	}
}

void init_color_pairs(void) {
	/* Inicia pares de cores */
	init_pair(RED, COLOR_RED, COLOR_BLACK);     // Cores das pecas ja fixas

	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);  /*    Possiveis cores      */
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);	   /*       das pecas         */
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);      /*       em queda          */

	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK); // Cor das paredes da arena

	init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
}

void init_fixed_pieces(void) {
	int i,j;
	/* Inicializa mapa de pecas fixas */
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
	/* Apaga linha do mapa de pecas fixas */
	for(j = 0; j < arena_length; j++)
		fixed_pieces[line][j] = '0';

	SCORE->combo_multiplier += COMBO_SCORE; // Aumenta a pontuacao
	wrefresh(arena);
}

void getScoreName(char *s) {
	printw("Digite suas iniciais (3 caracteres): ");
	refresh();
	scanw("%3s", s);
	clear();
	refresh();
}

void gameOver(void) {
	wclear(info);
	nodelay(stdscr, FALSE);
	wattron(info, A_BLINK | COLOR_PAIR(RED));

	mvwprintw(info, 4, 0, "_____                  _____              ");
	mvwprintw(info, 5, 0, "|   __|___ _____ ___   |     |_ _ ___ ___ ");
	mvwprintw(info, 6, 0, "|  |  | .'|     | -_|  |  |  | | | -_|  _|");
	mvwprintw(info, 7, 0, "|_____|__,|_|_|_|___|  |_____|\\_/|___|_|  ");

	wrefresh(info);
	wattroff(info, A_BLINK | COLOR_PAIR(RED));

	sleep(5);
	endGame();
}

void endGame(void) {
	saveScore(SCORE);

	free(SCORE->id);
	free(SCORE);
	delwin(score);
	delwin(info);
	delwin(arena);
	endwin();
	exit(1);
}

void cascadeLines()
