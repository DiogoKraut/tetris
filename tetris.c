/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include <sys/time.h>
#include <time.h>
#include <signal.h>

#include "pieces.h"
#include "screen.h"
#include "game.h"
#include "highscores.h"

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

char fixed_pieces[arena_height][arena_length]; // Mapa das pecas ja fixas

tPiece old_piece, new_piece;     // Variaveis para pecas (atual e preview)
int offi, offj = arena_length/2; // Offset da peca
int piece_color;                 // Cor da peca atual

tScore *SCORE; // Pontuacao
WINDOW *arena, *preview, *info, *score; // Telas para impressao

int main(int argc, char const *argv[]) {
	srand(time(NULL)); // Seed

	/* Inicializacao NCurses */
	initscr();             // inicializa a biblioteca ncurses
	// raw();                 // ler teclas de controle (^C, ^Z, etc)
	keypad(stdscr, TRUE);  // ativa leitura de teclas de setas, Fn, etc
	curs_set(0);           // esconde o cursor do terminal
	start_color();         // ativa modulo de cores

	/* Verifica tamanho do terminal */
	int x, y;
	getmaxyx(stdscr, y, x);
	if(y < MIN_HEIGHT || x < MIN_LENGTH) {
		fprintf(stderr, "Tela do terminal muito pequena!\n");
		abort();
	}

	/* Inicializa SCORE */
	SCORE                   = malloc(sizeof(tScore));
	SCORE->id               = malloc(NAME_SIZE * sizeof(char));
	SCORE->score            = 0;
	SCORE->combo_multiplier = 0;
	getScoreName(SCORE->id); // Le iniciais do jogador

	/* Mais opcoes do ncurses */
	noecho();              // não escreve as teclas lidas na tela
	nodelay(stdscr, TRUE); // leitura não-bloqueante do teclado

	init_color_pairs();  // Define os pares de cores
	init_fixed_pieces(); // Inicia o mapa com 0s

	/* Telas extras usadas na impressao */
	arena   = newwin(arena_height, arena_length, 0, 1);
	preview = newwin(preview_height, preview_length, 0, arena_length + 2);
	score   = newwin(score_height, score_length, preview_height, arena_length + 2);
	info    = newwin(info_height, info_length, 0, arena_length + score_length + 5);


	/* Seleciona as duas primeiras pecas */
	memcpy(old_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));
	memcpy(new_piece, pieces[rand() % NUM_PIECES], sizeof(tPiece));

	/* Boarda, preview, highscores e info soh precisam ser impressos uma vez */
	printArenaBoarder(arena_length, arena_height, stdscr);
	printInfo(info);
	printPreview(preview);

	FILE *highscore = fopen("./highscores.txt", "r+");
	printHighscores(highscore, score);
	fclose(highscore);

	/* Inicializacao dos sinais */
	signal_setup();
	/* Inicilizacao do timer */
	timer_setup();

	int c;
	while(true) {
		printScores(score);

		c = getch();
		switch(c) {
			case KEY_LEFT:
			case KEY_RIGHT:
			case KEY_DOWN:
				movePiece(c);
				break;

			case KEY_UP:
				rotate();
				break;

			case 'q':
				endGame();
		}
	}

	/* Nunca chega ate aqui */
	return 0;
}
