#ifndef QUEEN_H
#define QUEEN_H

#include <gamestate.h>

class Queen : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
public slots:
    void checkForPossibleMoves(GameState *gameState);
};

#endif // QUEEN_H
