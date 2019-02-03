#include "gamestate.h"

GameState::GameState(bool isWhiteOnBot, QGraphicsScene *scene){
    this->scene = scene;
    this->isWhiteOnBot = isWhiteOnBot;
    selectedBoard = nullptr;
}

void GameState::addToGameTable(int x, int y, BoardSquare *ptr){
    this->gameTable[x][y] = ptr;
}

void GameState::addToActionBuffersAndScene(int x, ChessPiece *ptr){
    if(ptr->isItWhite()){
        this->whiteInAction[x] = ptr;
    }
    else {
     this->blackInAction[x] = ptr;
    }
    this->scene->addItem(ptr);
    putPieceOnBoard(ptr);
}

void GameState::putPieceOnBoard(ChessPiece *ptr){
    int x = ptr->getxPosition();
    int y = ptr->getyPosition();
    this->gameTable[x][y]->pieceOnBoard = ptr;
}

void GameState::deselectTheBoard(){
    selectedBoard->setCorrectPixmap();
    selectedBoard = nullptr;
}

void GameState::setSelectedBoard(int x, int y){
    selectedBoard = gameTable[x][y];
    selectedBoard->markAsSelected();
}

void GameState::addToPossibleMovesBuffer(int x, int y){
    possibleMovesStack[stackIterator] = gameTable[x][y];
    stackIterator++;
}

ChessPiece* GameState::getChessPieceFromLocation(int x, int y){
    if(x < 0 || x > 7 || y < 0 || y > 7){
        return nullptr;
    }
    else {
        //gameTable[x][y]->markAsSelected();
        return gameTable[x][y]->pieceOnBoard;
    }
}

void GameState::markAllPossibilities(){
    for(int iterator = 0; iterator < stackIterator; iterator++){
        if(possibleMovesStack[iterator]->pieceOnBoard != nullptr){
            possibleMovesStack[iterator]->markAsSelected();
        } else {
            possibleMovesStack[iterator]->markAsPossible();
        }
    }
}

void GameState::deselectPossibleMoves(){
    while(stackIterator != 0 ){
        stackIterator -= 1;
        possibleMovesStack[stackIterator]->setCorrectPixmap();
        possibleMovesStack[stackIterator] = nullptr;

    }
}

BoardSquare* GameState::getBoardSquareFromLocation(int x, int y){
    if(x < 0 || x > 7 || y < 0 || y > 7){
        return nullptr;
    }
    else {
        return gameTable[x][y];
    }
}

bool GameState::checkIfIsPossible(BoardSquare *requestedMove){
    if(stackIterator == 0){
        return false;
    }
    return std::find(std::begin(possibleMovesStack), std::end(possibleMovesStack), requestedMove)
            != std::end(possibleMovesStack);
}

void GameState::movePieceFromSelected(int x, int y){
    if(gameTable[x][y]->pieceOnBoard != nullptr){
        setPieceDead(gameTable[x][y]->pieceOnBoard);
    }
    gameTable[x][y]->pieceOnBoard = selectedBoard->pieceOnBoard;
    selectedBoard->pieceOnBoard = nullptr;
    gameTable[x][y]->pieceOnBoard->setxPosition(x);
    gameTable[x][y]->pieceOnBoard->setyPosition(y);
    gameTable[x][y]->pieceOnBoard->updatePos();
    gameTable[x][y]->pieceOnBoard->setAsMoved();
    deselectTheBoard();
    deselectPossibleMoves();
    togglePlayerTurn();
}

void GameState::setPieceDead(ChessPiece *soonToBeDead){

    if(soonToBeDead->isItWhite()){
        whiteGraveyard[whiteGraveyardIterator++] = soonToBeDead;
        updateGraveyard(true);
    }
    else{
        blackGraveyard[blackGraveyardIterator++] = soonToBeDead;
        updateGraveyard(false);
   }
    soonToBeDead->setDead();

}

void GameState::updateGraveyard(bool isWhite){
    int iterator, startingPos;
    float direction;
    ChessPiece **array;
    if(isWhite){
        iterator = whiteGraveyardIterator;
        array = whiteGraveyard;
        startingPos = WHITE_GRAVEYARD_START;
        direction = -1.5;
    } else {
        iterator = blackGraveyardIterator;
        array = blackGraveyard;
        startingPos = BLACK_GRAVEYARD_START;
        direction = 1.5;
    }
    for(int x = 0, y = 0; x < iterator; x++, y++){
        (array[x])->setPos(startingPos, BOARD_Y_START + (y * BOARD_X_SPACING));
        if(x == 7){
            startingPos += direction * BOARD_X_SPACING;
            y -= 8;
        }
    }
}


void GameState::checkMovesInAllDirection(ChessPiece *pieceToCheck, bool isRookLike, bool isBishopLike){
    if(isRookLike){
        checkMovesInOneDirection(pieceToCheck, 1, 0);
        checkMovesInOneDirection(pieceToCheck, -1, 0);
        checkMovesInOneDirection(pieceToCheck, 0, 1);
        checkMovesInOneDirection(pieceToCheck, 0, -1);
    }
    if(isBishopLike){
        checkMovesInOneDirection(pieceToCheck, 1, 1);
        checkMovesInOneDirection(pieceToCheck, 1, -1);
        checkMovesInOneDirection(pieceToCheck, -1, 1);
        checkMovesInOneDirection(pieceToCheck, -1, -1);
    }
}

void GameState::checkMovesInOneDirection(ChessPiece *pieceToCheck, int xDir, int yDir){
    int tempX = pieceToCheck->getxPosition() + xDir;
    int tempY = pieceToCheck->getyPosition() + yDir;
    BoardSquare *boardPtr = getBoardSquareFromLocation(tempX, tempY);
    while(boardPtr != nullptr){
        if(boardPtr->pieceOnBoard == nullptr){
            addToPossibleMovesBuffer(tempX, tempY);
        } else if(boardPtr->pieceOnBoard->isItWhite() != pieceToCheck->isItWhite()) {
            addToPossibleMovesBuffer(tempX, tempY);
            return;
        }
        else {
            return;
        }
        tempX += xDir; tempY += yDir;
        boardPtr = getBoardSquareFromLocation(tempX, tempY);
    }
}

bool GameState::checkForCheck(bool isWhite){
    ChessPiece **arrayToCheck;
    ChessPiece *king;
    if(isWhite){
        arrayToCheck = blackInAction;
        king = whiteInAction[0];
    } else {
        arrayToCheck = whiteInAction;
        king = blackInAction[0];
    }
    if(!checkForKnigts(arrayToCheck, king)){
        return false;
    }
    if(!checkForRooks(arrayToCheck, king)){
        return false;
    }
    if(!checkForBishops(arrayToCheck, king)){
        return false;
    }
    if(!checkForPawns(arrayToCheck, king)){
        return false;
    }
    if(!checkForKing(arrayToCheck, king)){
        return false;
    }
    return true;
}

bool GameState::checkForKnigts(ChessPiece **array, ChessPiece *king){
    BoardSquare *currentPointer;
    int currentX = king->getxPosition();
    int currentY = king->getyPosition();
//    printf("current king positions are: x:%d, y:%d\n", currentX, currentY);
    int possibilitiesArray[2][8] = {
        { -2, -1,  1,  2, 2, 1, -1, -2},
        { -1, -2, -2, -1, 1, 2,  2, 1}};
    for(int iterator = 0; iterator < 8; iterator++){
        int tempX = possibilitiesArray[0][iterator] + currentX;
        int tempY = possibilitiesArray[1][iterator] + currentY;
        currentPointer = getBoardSquareFromLocation(tempX, tempY);
        if(currentPointer != nullptr){
            if(currentPointer->pieceOnBoard != nullptr){
                if(currentPointer->pieceOnBoard == array[6] ||
                        currentPointer->pieceOnBoard == array[7]){
                    return false;
                }
            }

        }
    }
    return true;
}

bool GameState::checkForRooks(ChessPiece **array, ChessPiece *king){
    int possibilitiesArray[2][4] = {
        { 1, -1, 0,  0 },
        { 0,  0, 1, -1 } };

    for(int x = 0; x < 4; x++){
        if(!checkInDirection(possibilitiesArray[0][x], possibilitiesArray[1][x],
                            false, array, king)){
            return false;
        }
    }
    return true;
}

bool GameState::checkForBishops(ChessPiece **array, ChessPiece *king){
    int possibilitiesArray[2][4] = {
        { 1, -1, -1,  1 },
        { 1,  1, -1, -1 } };

    for(int x = 0; x < 4; x++){
        if(!checkInDirection(possibilitiesArray[0][x], possibilitiesArray[1][x],
                             true, array, king)){
            return false;
        }
    }
    return true;
}

bool GameState::checkForPawns(ChessPiece **array, ChessPiece *king){
    int xPos = king->getxPosition();
    int yPos = king->getyPosition();

    int upOrDown = -1;
    if(king->isItGoingUp()){
        upOrDown = 1;
    }
//    if((xPos == 0 && king->isItGoingUp()) ||
//            (xPos = 7 && !king->isItGoingUp())){
//        return true;
//    }
    BoardSquare *piece1 = getBoardSquareFromLocation(xPos + 1, yPos + upOrDown);
    BoardSquare *piece2 = getBoardSquareFromLocation(xPos - 1, yPos + upOrDown);
    if(piece1 != nullptr){
        if(piece1->pieceOnBoard != nullptr){
            for(int x = 8; x < 16; x++){
                if(array[x] == piece1->pieceOnBoard){
                    return false;
                }
            }
        }
    }
    if(piece2 != nullptr){
        if(piece2->pieceOnBoard != nullptr){
            for(int x = 8; x < 16; x++){
                if(array[x] == piece2->pieceOnBoard){
                    return false;
                }
            }
        }
    }
    return true;
}

bool GameState::checkInDirection(int x, int y, bool isBishopLike, ChessPiece **array, ChessPiece *king){
    int number = 2;
    if(isBishopLike){
        number = 4;
    }
    int tempx = king->getxPosition() + x;
    int tempy = king->getyPosition() + y;
    BoardSquare *currentBoard = getBoardSquareFromLocation(tempx, tempy);
    while(currentBoard != nullptr){
        if(currentBoard->pieceOnBoard != nullptr){
            if(currentBoard->pieceOnBoard == array[number] ||
                    currentBoard->pieceOnBoard == array[number + 1] ||
                    currentBoard->pieceOnBoard == array[1]){
                return false;
            }
            else {
                return true;
            }
        }
        tempx += x;
        tempy += y;
        currentBoard = getBoardSquareFromLocation(tempx, tempy);

    }
    return true;
}

bool GameState::checkForKing(ChessPiece **array, ChessPiece *king){
    BoardSquare *currentPointer;
    int currentX = king->getxPosition();
    int currentY = king->getyPosition();
    int possibilitiesArray[2][8] = {
        { -1, -1, -1,  0,  0,  1,  1,  1},
        { -1,  0,  1, -1,  1,  1,  0, -1}};
    for(int x = 0; x < 8; x++){
        currentPointer = getBoardSquareFromLocation( currentX + possibilitiesArray[0][x],
                                                    currentY + possibilitiesArray[1][x]);
        if(currentPointer != nullptr){
            if(currentPointer->pieceOnBoard == array[0]){
                return false;
            }
        }
    }
    return true;
}
