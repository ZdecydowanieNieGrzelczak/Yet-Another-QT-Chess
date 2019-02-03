#ifndef GAME_H
#define GAME_H

#define TIMER_DISTANCE_FROM_BOARD 20
#define CHESS_BUFFER_SIZE 16
#define CHESS_BOARD_SIZE 8

#include "gamestate.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "timer.h"
#include <QGraphicsView>
#include <QWidget>


#include <typeinfo>

class Game: public QGraphicsView{
public:
    Game(QWidget * parent = nullptr);
    QGraphicsScene *scene;

private:
    void setStartingLayout(bool isWhite);
    void deselectBoard();
    void mousePressEvent(QMouseEvent *event);
    void addBoardSquares();
    void addTimers();
    void toggleTimers();

    GameState *gameState;
    Timer *whiteTimer;
    Timer *blackTimer;
    int baseTime = 5;
    int addWithEveryTurn = 0;
};


#endif // GAME_H
