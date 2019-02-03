#ifndef TIMER_H
#define TIMER_H


#include <QTimer>
#include <QObject>
#include <QLabel>
#include <string>
#include <QGraphicsItem>

class Timer:  public QWidget
{
    Q_OBJECT
public:
    Timer(bool isWhite, int startingTime, int addWithEveryTurn);
    void stopTimer();
    void restartTimer();
    void start();
    void stop();
public slots:
    void updateTime();
private:
    QLabel *timerLabel;
    QTimer *timer;
    int minutesLeft;
    int secondsLeft = 0;
    int addValue;
    bool isWhite;
    bool isOutOfTime = false;
    void initTimer();
    void initNameLabel();
    void initTimerLabel();
    void setLabelStyleAndPos(bool isWhite);
    void setCorrectNumber();
};

#endif // TIMER_H
