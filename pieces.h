/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __PIECES__
#define __PIECES__

#include <ncurses.h>

#define MAX_SHAPE 16

typedef sPoint {
	int i,j;
} tPoint;

typedef struct sPiece {
	tPoint point[MAX_SHAPE];

}

#endif
