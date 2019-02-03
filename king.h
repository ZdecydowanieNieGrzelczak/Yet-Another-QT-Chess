#ifndef KING_H
#define KING_H

#include "gamestate.h"


class King : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;

public slots:
    void checkForPossibleMoves(GameState *gameState);
private:
    bool willBeChecked(GameState *gameState, int x, int y);
};

#endif // KING_H
