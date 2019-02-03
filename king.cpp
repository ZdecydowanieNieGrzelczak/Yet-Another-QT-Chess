#include "king.h"


void King::checkForPossibleMoves(GameState *gameState){
    if(gameState->getSelectedBoard()->pieceOnBoard == this){
    }
    BoardSquare *boardToCheck;
    int currentX = this->xPosition;
    int currentY = this->yPosition;
    int possibleArray[2][8] = {
        {  1,  1,  1,  0,  0,  -1, -1, -1 },
        {  0, -1,  1,  1, -1,  1,  0, -1} };
    for(int x = 0; x < 8; x++){
        boardToCheck = gameState->getBoardSquareFromLocation(currentX + possibleArray[0][x],
                currentY + possibleArray[1][x]);
        if(boardToCheck != nullptr){
            if(boardToCheck->pieceOnBoard == nullptr ||
                    boardToCheck->pieceOnBoard->isItWhite() != this->isItWhite()){
                if(willBeChecked(gameState, currentX + possibleArray[0][x],
                                 currentY + possibleArray[1][x])){
                    gameState->addToPossibleMovesBuffer(currentX + possibleArray[0][x],
                            currentY + possibleArray[1][x]);
                }
            }
        }
    }
}

bool King::willBeChecked(GameState *gameState, int x, int y){
    int xForNow = this->xPosition;
    int yForNow = this->yPosition;
    ChessPiece *holdThis = gameState->getBoardSquareFromLocation(x, y)->pieceOnBoard;
    this->xPosition = x;
    this->yPosition = y;
    gameState->getBoardSquareFromLocation(xForNow, yForNow)->pieceOnBoard = nullptr;
    gameState->getBoardSquareFromLocation(x, y)->pieceOnBoard = this;
    bool check = gameState->checkForCheck(this->isWhite);
    gameState->getBoardSquareFromLocation(xForNow, yForNow)->pieceOnBoard = this;
    gameState->getBoardSquareFromLocation(x, y)->pieceOnBoard = holdThis;
    this->xPosition = xForNow;
    this->yPosition = yForNow;
    return check;
}
