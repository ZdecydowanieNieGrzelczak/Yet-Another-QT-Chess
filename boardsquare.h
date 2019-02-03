#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H


#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>


class ChessPiece;

class BoardSquare : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit BoardSquare(QWidget *parent = nullptr, int xPosition = 0, int yPosition = 0, bool isWhite = false);
    int getxPosition() { return xPosition; }
    int getyPosition() { return yPosition; }
    bool isItWhite() { return isWhite; }
    void setCorrectPixmap();
    void markAsSelected();
    void markAsPossible();
    ChessPiece *pieceOnBoard;
private:

    int xPosition;
    int yPosition;
    bool isWhite;

signals:

public slots:
};

#endif // BOARDSQUARE_H
