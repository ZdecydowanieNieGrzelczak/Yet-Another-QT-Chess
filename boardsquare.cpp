#include "boardsquare.h"
#include "game.h"


extern Game *game;

BoardSquare::BoardSquare(QWidget *parent, int xPosition, int yPosition, bool isWhite): QObject(parent){

    this->xPosition = xPosition;
    this->yPosition = yPosition;
    this->isWhite = isWhite;
    setCorrectPixmap();
    pieceOnBoard = nullptr;

}
void BoardSquare::setCorrectPixmap(){
    if(this->isItWhite()){
        setPixmap(QPixmap("/home/maciek/prgr/qt/chess-qt/Resources/White_board_noborder.png").scaled(PIECE_WIDTH, PIECE_HEIGHT));
    }
    else{
        setPixmap(QPixmap("/home/maciek/prgr/qt/chess-qt/Resources/Black_board_noborder.png").scaled(PIECE_WIDTH, PIECE_HEIGHT));
    }
}

void BoardSquare::markAsSelected(){
//    printf("should change pixmap");
    setPixmap(QPixmap("/home/maciek/prgr/qt/chess-qt/Resources/Collision.png").scaled(PIECE_WIDTH, PIECE_HEIGHT));
}

void BoardSquare::markAsPossible(){
    setPixmap(QPixmap("/home/maciek/prgr/qt/chess-qt/Resources/Possible_move.png").scaled(PIECE_WIDTH, PIECE_HEIGHT));
}
