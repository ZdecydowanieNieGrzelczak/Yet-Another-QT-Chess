#include "pawn.h"

void Pawn::checkForPossibleMoves(GameState *gameState){
    if(gameState->getSelectedBoard()->pieceOnBoard == this){
    }

    if(!this->isItAlive()){
        return;
    }
    int direction; this->isGoingUp ? direction = -1 : direction = 1;
    int currentX = this->getxPosition();
    int currentY = this->getyPosition();
    if(gameState->getChessPieceFromLocation(currentX, currentY + direction) == nullptr){
            gameState->addToPossibleMovesBuffer(currentX, currentY + direction);
    }
    if(gameState->getChessPieceFromLocation(currentX - 1, currentY + direction) != nullptr){
        if(gameState->getChessPieceFromLocation(currentX - 1, currentY + direction)->isItWhite()
                != this->isItWhite()){
                gameState->addToPossibleMovesBuffer(currentX - 1, currentY + direction);
        }
    }
    if(gameState->getChessPieceFromLocation(currentX + 1, currentY + direction) != nullptr){
        if(gameState->getChessPieceFromLocation(currentX + 1, currentY + direction)->isItWhite()
                != this->isItWhite()){
                gameState->addToPossibleMovesBuffer(currentX + 1, currentY + direction);
        }
    }
    if(!isMoved){
        if(gameState->getChessPieceFromLocation(currentX, currentY + direction * 2) == nullptr &&
                gameState->getChessPieceFromLocation(currentX, currentY + direction) == nullptr){
                gameState->addToPossibleMovesBuffer(currentX, currentY + direction * 2);
        }
    }

}
