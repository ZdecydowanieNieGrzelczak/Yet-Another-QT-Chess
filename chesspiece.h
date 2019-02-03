#ifndef CHESSPIECE_H
#define CHESSPIECE_H


#define ABSOLUTE_PATH_TO_PIECES "/home/maciek/prgr/qt/chess-qt/Resources/figures/"
#define PIECE_WIDTH 45
#define PIECE_HEIGHT 45
#define BOARD_X_START 200
#define BOARD_Y_START 200
#define BOARD_X_SPACING PIECE_WIDTH
#define BOARD_Y_SPACING PIECE_HEIGHT

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QMouseEvent>
#include <QDrag>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

#include <string.h>
#include <string>


class GameState;

class ChessPiece : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit ChessPiece(QWidget *parent = nullptr, int xPosition = 0, int yPosition = 0, bool isWhite = false, QString imageName = "");

    int getxPosition() { return this->xPosition; }
    int getyPosition() { return this->yPosition; }
    bool isItWhite() { return this->isWhite; }
    bool isItAlive() { return this->isAlive; }
    bool isItGoingUp() { return this->isGoingUp; }

    void setxPosition(int newxPosition) { this->xPosition = newxPosition; }
    void setyPosition(int newyPosition) { this->yPosition = newyPosition; }
    void setDead() { this->isAlive = false; }
    void updatePos();
    void setAsMoved() { this->isMoved = true; }
public slots:
    virtual void checkForPossibleMoves(GameState *gameState);
protected:
     bool isMoved = false;
    int xPosition;
    int yPosition;
    bool isWhite;
    bool isAlive = true;
    bool isGoingUp = false;

signals:

public slots:

private:
    void setDirection(int yPosition);
};

#endif // CHESSPIECE_H
