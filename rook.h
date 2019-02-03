#ifndef ROOK_H
#define ROOK_H

#include <gamestate.h>

class Rook : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;

public slots:
    void checkForPossibleMoves(GameState *gameState);

};

#endif // ROOK_H
