#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "pieces.h"
#include "screen.h"
#include "setup.h"

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

	/* Sinal do timer */
	sigaction(SIGALRM, &sa, NULL);
}
