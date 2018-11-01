/* DIOGO PARIS KRAUT - GRR20166365 */

#define SCORE_SIZE 13
#define NAME_SIZE 3
#define COMBO_SCORE 500
#define AFFIX_SCORE 10
#define STD_SCORE 5

typedef struct sScore {
	char *id;
	int score;
	int combo_multiplier; // Aumenta com o numero de linhas destruidas ao mesmo tempo
} tScore;

int getHighscore(FILE *hs, char *s);
void saveScore(tScore *SCORE);
