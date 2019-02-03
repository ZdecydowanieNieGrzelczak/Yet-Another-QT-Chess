#include "queen.h"

void Queen::checkForPossibleMoves(GameState *gameState){
    if(!(gameState->getSelectedBoard()->pieceOnBoard == this)){
        return;
    }
    if(!this->isItAlive()){
        return;
    }
    gameState->checkMovesInAllDirection(gameState->getSelectedBoard()->pieceOnBoard, true, true);
}
