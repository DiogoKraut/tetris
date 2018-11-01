/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include "highscores.h"

int getHighscore(FILE *hs, char *s) {
	/* Retorna 0 no final do arquivo *
	 * Salva a pontuacao em s        */
	if(fgets(s, SCORE_SIZE, hs) != NULL)
		return 1;
	else
		return 0;
}

void saveScore(tScore *SCORE) {
	FILE *hs = fopen("./highscores.txt", "a+");
	fprintf(hs, "%s - %d\n", SCORE->id, SCORE->score);
	fclose(hs);
}
