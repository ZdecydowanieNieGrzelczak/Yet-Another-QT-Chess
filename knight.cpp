#include "knight.h"

void Knight::checkForPossibleMoves(GameState *gameState){
    BoardSquare *currentPointer;
    int currentX = this->getxPosition();
    int currentY = this->getyPosition();
    int possibilitiesArray[2][8] = {
        { -2, -1,  1,  2, 2, 1, -1, -2},
        { -1, -2, -2, -1, 1, 2,  2, 1}};
    for(int iterator = 0; iterator < 8; iterator++){
        int tempX = possibilitiesArray[0][iterator] + currentX;
        int tempY = possibilitiesArray[1][iterator] + currentY;
        currentPointer = gameState->getBoardSquareFromLocation(tempX, tempY);
        if(currentPointer != nullptr){
            if(currentPointer->pieceOnBoard == nullptr){
                gameState->addToPossibleMovesBuffer(tempX, tempY);
            }
            else if(currentPointer->pieceOnBoard->isItWhite() != this->isItWhite()){
                gameState->addToPossibleMovesBuffer(tempX, tempY);
            }
        }
    }

}
