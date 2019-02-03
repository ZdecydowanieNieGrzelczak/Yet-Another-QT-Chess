#include "bishop.h"

void Bishop::checkForPossibleMoves(GameState *gameState){
    if(!(gameState->getSelectedBoard()->pieceOnBoard == this)){
        return;
    }
    if(!this->isItAlive()){
        return;
    }
    gameState->checkMovesInAllDirection(gameState->getSelectedBoard()->pieceOnBoard, false, true);
}
