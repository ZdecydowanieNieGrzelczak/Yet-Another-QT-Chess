#ifndef GAMESTATE_H
#define GAMESTATE_H


#define PIECE_WIDTH 45
#define PIECE_HEIGHT 45
#define BOARD_X_START 200
#define BOARD_Y_START 200
#define BOARD_X_SPACING PIECE_WIDTH
#define BOARD_Y_SPACING PIECE_HEIGHT


#define CHESS_BOARD_SIZE 8
#define CHESS_BUFFER_SIZE 16
#define POSSIBLE_MOVES_BUFFER_SIZE 40
#define WHITE_GRAVEYARD_START BOARD_X_START - BOARD_X_SPACING * 2
#define BLACK_GRAVEYARD_START BOARD_X_START + BOARD_X_SPACING * 10


#include <QGraphicsScene>
#include <boardsquare.h>
#include <chesspiece.h>


class GameState
{
public:
    GameState(bool isWhiteOnBot, QGraphicsScene *scene);
    void addToGameTable(int x, int y, BoardSquare *ptr);
    bool isItWhiteOnBot() { return isWhiteOnBot; }
    void addToActionBuffersAndScene(int x, ChessPiece *ptr);
    void putPieceOnBoard(ChessPiece *ptr);
    ChessPiece getPointerToChessPiece(int x, bool isWhite);
    ChessPiece *getChessPieceFromLocation(int x, int y);
    BoardSquare *getSelectedBoard() { return selectedBoard; }
    BoardSquare *getBoardSquareFromLocation(int x, int y);
    void deselectTheBoard();
    void setSelectedBoard(int x, int y);
    void addToPossibleMovesBuffer(int x, int y);
    void markAllPossibilities();
    void deselectPossibleMoves();
    bool checkIfIsPossible(BoardSquare *requestedMove);
    bool isItWhiteTurn(){ return isWhiteTurn; }
    void movePieceFromSelected(int x, int y);
    void checkMovesInAllDirection(ChessPiece *pieceToCheck, bool isRookLike, bool isBishopLike);
    void checkMovesInOneDirection(ChessPiece *pieceToCheck, int xDir, int yDir);
    void togglePlayerTurn() { this->isWhiteTurn = !(this->isWhiteTurn); }
    bool checkForCheck(bool isWhite);
private:
    void setPieceDead(ChessPiece *soonToBeDead);
    void updateGraveyard(bool isWhite);
    bool checkForKnigts(ChessPiece **array, ChessPiece *king);
    bool checkInDirection(int x, int y, bool isBishopLike, ChessPiece **array, ChessPiece *king);
    bool checkForRooks(ChessPiece **array, ChessPiece *king);
    bool checkForBishops(ChessPiece **array, ChessPiece *king);
    bool checkForPawns(ChessPiece **array, ChessPiece *king);
    bool checkForKing(ChessPiece **array, ChessPiece *king);
    BoardSquare *possibleMovesStack[POSSIBLE_MOVES_BUFFER_SIZE];
    int stackIterator = 0;
    int whiteGraveyardIterator = 0;
    int blackGraveyardIterator = 0;
    BoardSquare *gameTable[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE];
    ChessPiece *whiteInAction[CHESS_BUFFER_SIZE];
    ChessPiece *blackInAction[CHESS_BUFFER_SIZE];
    ChessPiece *whiteGraveyard[CHESS_BUFFER_SIZE];
    ChessPiece *blackGraveyard[CHESS_BUFFER_SIZE];
    bool isWhiteOnBot;
    BoardSquare *selectedBoard;
    QGraphicsScene *scene;
    bool isWhiteTurn = true;
};

#endif // GAMESTATE_H
