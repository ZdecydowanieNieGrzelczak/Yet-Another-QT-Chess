#include "timer.h"

Timer::Timer(bool isWhite, int startingTime, int addWithEveryTurn){
    minutesLeft = startingTime;
    addValue = addWithEveryTurn;
    this->isWhite = isWhite;
    secondsLeft = -addValue;
    initTimer();
    initTimerLabel();
    initNameLabel();



}

void Timer::initTimer(){
    timer = new QTimer;
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);
    timer->stop();
    this->setGeometry(0, 0, 100, 40);
}

void Timer::initTimerLabel(){
    timerLabel = new QLabel(this);

    this->timerLabel->setGeometry(0, 20, 100, 20);
    this->timerLabel->show();
    timerLabel->setStyleSheet("QLabel { background-color : black; color: white; }");
    timerLabel->setText(QString::number(minutesLeft) + ":" + "00");
}

void Timer::setCorrectNumber(){
    QString seconds;
    if(secondsLeft < 10){
        seconds = "0" + QString::number(secondsLeft);
    }
    else {
        seconds = QString::number(secondsLeft);
    }
    timerLabel->setText(QString::number(minutesLeft) + ":" + seconds);
}

void Timer::initNameLabel(){
    QLabel *nameLabel = new QLabel(this);
    nameLabel->setGeometry(0, 0, 100, 20);
    if(isWhite){
        nameLabel->setText("White player:");
    } else {
        nameLabel->setText("Black player:");
    }
}

void Timer::start(){
    secondsLeft += addValue;
    while(secondsLeft > 60){
        secondsLeft -= 60;
        if(minutesLeft < 59){
            minutesLeft++;
        }
    }
    setCorrectNumber();
    timer->start(1000);
}

void Timer::stop(){
    timer->stop();
}

void Timer::updateTime(){
    secondsLeft--;
    if(minutesLeft == 0 && secondsLeft == 0){
        isOutOfTime = true;
        return;
    }
    if(secondsLeft == -1){
        minutesLeft--;
        secondsLeft = 59;
    }
    setCorrectNumber();
}
