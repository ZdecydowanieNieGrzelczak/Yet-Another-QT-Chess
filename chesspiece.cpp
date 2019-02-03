#include "chesspiece.h"

ChessPiece::ChessPiece(QWidget *parent, int xPosition, int yPosition, bool isWhite, QString imageName) : QObject(parent)
{
    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->isWhite = isWhite;
    QString imagePath = ABSOLUTE_PATH_TO_PIECES + imageName;
    setPixmap(QPixmap(imagePath).scaled(PIECE_WIDTH, PIECE_HEIGHT));
    updatePos();
    setAcceptedMouseButtons(Qt::LeftButton);
    if(imageName.contains("pawn", Qt::CaseInsensitive)){
        setDirection(yPosition);
    }
}


void ChessPiece::setDirection(int yPosition){
    if(yPosition == 6){
        isGoingUp = true;
    }
}

void ChessPiece::updatePos(){
    setPos(BOARD_X_START + xPosition * BOARD_X_SPACING,
                     BOARD_Y_START + yPosition * BOARD_Y_SPACING);
}

void ChessPiece::checkForPossibleMoves(GameState *gameState){}

