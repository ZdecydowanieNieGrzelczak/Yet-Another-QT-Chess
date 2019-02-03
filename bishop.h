#ifndef BISHOP_H
#define BISHOP_H

#include <gamestate.h>

class Bishop : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;

public slots:
     void checkForPossibleMoves(GameState *gameState);

};

#endif // BISHOP_H
