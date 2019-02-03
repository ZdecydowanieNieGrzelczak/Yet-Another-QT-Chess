#ifndef PAWN_H
#define PAWN_H

#include <gamestate.h>

class Pawn : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
public slots:
    void checkForPossibleMoves(GameState *gameState);

};

#endif // PAWN_H
