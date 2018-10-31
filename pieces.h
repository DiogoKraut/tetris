/* DIOGO PARIS KRAUT - GRR20166365 */

#ifndef __PIECES__
#define __PIECES__

#include <ncurses.h>

#define DIMENTION 2  //
#define MAX_SHAPE 4  // Toda peca original tem 4 blocos
#define NUM_PIECES 7 // Numero de pecas diferentes (excluindo rotacoes)

typedef int tPiece[DIMENTION][MAX_SHAPE];

bool rotate(tPiece *p);
int checkBottomCollision(void);
void movePieceDown(void);
void affixPiece(void);

#endif
