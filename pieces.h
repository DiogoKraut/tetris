/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __PIECES__
#define __PIECES__

#include <ncurses.h>

#define MAX_SHAPE 4  // Toda peca original tem 4 blocos
#define NUM_PIECES 7 // Numero de pecas diferentes (excluindo rotacoes)

typedef struct sPoint {
	int i,j;
} tPoint;

typedef struct sPiece {
	tPoint pos[MAX_SHAPE];
} tPiece;

bool rotate(tPiece *p);
#endif
