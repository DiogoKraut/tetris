/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __PIECES__
#define __PIECES__

#include <ncurses.h>

#define DIMENTION 3
#define NUM_PIECES 7 // Numero de pecas diferentes (excluindo rotacoes)

typedef int tPiece[DIMENTION][DIMENTION];

void rotate(void);
int checkBottomCollision(tPiece p);
void movePieceDown(void);
void affixPiece(tPiece p);
void movePiece(int dir);

#endif
