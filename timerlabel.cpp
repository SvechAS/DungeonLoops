#include "timerlabel.h"
#include "QPushButton"

TimerLabel::TimerLabel(QWidget *parent)
    : QWidget(parent)
{
    initForm();
    initTimers();
}

TimerLabel::~TimerLabel()
{
}


void TimerLabel::initForm()
{
    // init layout
    layoutPtr = new QBoxLayout(QBoxLayout::LeftToRight);
    // adding time label
    timeLabel.setText(gameClock.getTimeStr());
    timeLabel.setFixedWidth(300);
    layoutPtr -> addWidget(&timeLabel);
    // adding speed control buttons
    for(auto speed : SPEEDS_OF_TIME)
    {
        // init button
        QPushButton *button = new QPushButton((QWidget*) this);
        // creating button's name
        QString name = QString("X").append(std::to_string(speed).c_str());
        // filling up the button
        button->setText(name);
        button->setObjectName(name);
        button->setFixedSize(name.size() * 5 + 15, 20);
        connect(button, SIGNAL(clicked()), &mapper, SLOT(map()));
        mapper.setMapping(button, speed);
        // putting to layout
        layoutPtr -> addWidget(button);
    }
    connect(&mapper, SIGNAL(mapped(int)), this, SLOT(slotButtonSetNewTimeSpeed(int)));
}


void TimerLabel::onTickConnect(QWidget* ptr, const char* slot) {
    connect(&tickTimer, SIGNAL(timeout()), ptr, slot);
}


void TimerLabel::initTimers()
{
    // init tick timer
    tickTimer.setInterval(TICK_INTERVAL);
    tickTimer.start();
    // init clock
    elapsedTime.start();
    lastTickTime = elapsedTime.elapsed();
}

void TimerLabel::slotButtonSetNewTimeSpeed(int newTimeSpeed)
{
    currTimeSpeed = newTimeSpeed;
}

long long TimerLabel::timeElapsed()
{
    long long timeGone = elapsedTime.elapsed() - lastTickTime;
    gameClock.timeTick(int(timeGone * currTimeSpeed));
    lastTickTime += timeGone;
    timeLabel.setText(gameClock.getTimeStr());
    return gameClock.getTimeElapsed();
}

QLayout* TimerLabel::layout() {
    return layoutPtr;
}
