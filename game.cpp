#include "game.h"

Game::Game(QWidget *parent) : QGraphicsView(parent){
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 800, 600);
    //this->setFocusPolicy(Qt::NoFocus);
    //scene->setFocus(Qt::FocusReason::NoFocusReason);
    gameState = new GameState(true, scene);


    scene->setBackgroundBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));


    addBoardSquares();
    addTimers();


    setStartingLayout(true);
    setStartingLayout(false);



    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    show();
}


void Game::addTimers(){
    whiteTimer = new Timer(true, baseTime, addWithEveryTurn);
    blackTimer = new Timer(false, baseTime, addWithEveryTurn);

    scene->addWidget(blackTimer);
    scene->addWidget(whiteTimer);

    whiteTimer->start();


    whiteTimer->move(BOARD_X_START - TIMER_DISTANCE_FROM_BOARD - 100, 100);
    blackTimer->move(BOARD_X_START + CHESS_BOARD_SIZE * BOARD_X_SPACING
                     + TIMER_DISTANCE_FROM_BOARD, 100);
}

void Game::addBoardSquares(){
    bool isWhite = true;
    for(int x = 0; x < CHESS_BOARD_SIZE; x++){
        for(int y = 0; y < CHESS_BOARD_SIZE; y++){
            if((x + y) % 2 == 0){
                isWhite = true;
            } else {
                isWhite = false;
            }
            BoardSquare *ptr = new BoardSquare(nullptr, x + 1, y + 1, isWhite);
            ptr->setPos(BOARD_X_START + x * BOARD_X_SPACING, BOARD_Y_START + y * BOARD_Y_SPACING);
            scene->addItem(ptr);
            gameState->addToGameTable(x, y, ptr);
        }
    }
}

void Game::setStartingLayout(bool isWhite){
    int startingRow = 7, pawnRow = 6;
    QString color = "White_";
    if(!isWhite){
        color = "Black_";
    }
    bool WOB = gameState->isItWhiteOnBot();
    if((!WOB && isWhite) || (!isWhite && WOB)){
        startingRow = 0;
        pawnRow = 1;
    }
    gameState->addToActionBuffersAndScene(0, new King(nullptr, 4, startingRow, isWhite, color + "king.svg"));
    gameState->addToActionBuffersAndScene(1, new Queen(nullptr, 3, startingRow, isWhite, color + "queen.svg"));
    gameState->addToActionBuffersAndScene(2, new Rook(nullptr, 0, startingRow, isWhite, color + "rook.svg"));
    gameState->addToActionBuffersAndScene(3, new Rook(nullptr, 7, startingRow, isWhite, color + "rook.svg"));
    gameState->addToActionBuffersAndScene(4, new Bishop(nullptr, 2, startingRow, isWhite, color + "bishop.svg"));
    gameState->addToActionBuffersAndScene(5, new Bishop(nullptr, 5, startingRow, isWhite, color + "bishop.svg"));
    gameState->addToActionBuffersAndScene(6, new Knight(nullptr, 1, startingRow, isWhite, color + "knight.svg"));
    gameState->addToActionBuffersAndScene(7, new Knight(nullptr, 6, startingRow, isWhite, color + "knight.svg"));

    for(int iterator = 8; iterator < CHESS_BUFFER_SIZE; iterator++){
        gameState->addToActionBuffersAndScene(iterator, new Pawn(nullptr, iterator - CHESS_BOARD_SIZE,
                                                                 pawnRow, isWhite, color + "pawn.svg"));
    }
}


void Game::mousePressEvent(QMouseEvent *event){
    int x;
    int y;
    if(event->x() >= BOARD_X_START && event->y() >= BOARD_Y_START
            && event->x() <= BOARD_X_START + BOARD_X_SPACING * CHESS_BOARD_SIZE
            && event->y() <= BOARD_Y_START + BOARD_X_SPACING * CHESS_BOARD_SIZE) {
        x = (event->x() - BOARD_X_START) / BOARD_X_SPACING;
        y = (event->y() - BOARD_Y_START) / BOARD_Y_SPACING;
    } else {
        if(gameState->getSelectedBoard() != nullptr){
            gameState->deselectTheBoard();
            gameState->deselectPossibleMoves();
        }
           return;
    }

    if(gameState->getSelectedBoard() != nullptr){
        if(gameState->checkIfIsPossible(gameState->getBoardSquareFromLocation(x, y))){
            toggleTimers();
            gameState->movePieceFromSelected(x, y);


            return;
        } else {
            gameState->deselectTheBoard();
            gameState->deselectPossibleMoves();
        }

    }
    if(gameState->getChessPieceFromLocation(x, y) != nullptr){
        if(gameState->getChessPieceFromLocation(x, y)->isItWhite()
                != gameState->isItWhiteTurn()){
            return;
        }
        gameState->deselectPossibleMoves();
        gameState->setSelectedBoard(x, y);
        gameState->getChessPieceFromLocation(x, y)->checkForPossibleMoves(gameState);
        gameState->markAllPossibilities();
    }
}


void Game::toggleTimers(){
    if(!gameState->isItWhiteTurn()){
        blackTimer->stop();
        whiteTimer->start();
    }
    else {
        whiteTimer->stop();
        blackTimer->start();
    }
}



