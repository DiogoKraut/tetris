/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int main(int argc, char const *argv[]) {
	/* Inicializacao NCurses */
	initscr () ;		   	 // inicializa a biblioteca ncurses
	raw () ;		  	  	 // ler teclas de controle (^C, ^Z, etc)
	nodelay (stdscr, TRUE) ; // leitura não-bloqueante do teclado
	keypad (stdscr, TRUE) ;  // ativa leitura de teclas de setas, Fn, etc
	noecho () ;		   	 	 // não escreve as teclas lidas na tela
	curs_set (0) ;	   		 // esconde o cursor do terminal

	if(!has_colors()) {
		endwin();
		fprintf(stderr, "Terminal nao suporta cores!\n");
		exit(1);
	}
	start_color();			 // ativa modulo de cores
	return 0;
}
