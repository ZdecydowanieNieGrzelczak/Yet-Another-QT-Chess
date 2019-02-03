#ifndef KNIGHT_H
#define KNIGHT_H

#include <gamestate.h>

class Knight : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;

public slots:
    void checkForPossibleMoves(GameState *gameState);
};

#endif // KNIGHT_H
