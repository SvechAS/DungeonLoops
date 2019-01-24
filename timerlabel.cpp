#include "timerlabel.h"
#include "QPushButton"

TimerLabel::TimerLabel(QWidget *parent)
    : QWidget(parent)
{
    initForm();
}

TimerLabel::~TimerLabel()
{

}


void TimerLabel::initForm()
{

    layout = new QBoxLayout(QBoxLayout::LeftToRight);
    timeLabel.setText(gameTime.getTimeStr());
    timeLabel.setFixedWidth(300);
    layout -> addWidget(&timeLabel);

    int boostSpeeds[7] = {1, 5, 10, 50, 100, 1000, 10000};
    for(int i = 0; i < 7; i++)
    {
        QPushButton *pbt = new QPushButton((QWidget*) this);
        QString name = QString("X").append(std::to_string(boostSpeeds[i]).c_str());
        pbt->setText(name);
        pbt->setObjectName(name);
        pbt->setFixedSize(name.size() * 5 + 15, 20);

        connect(pbt, SIGNAL(clicked()), &mapper, SLOT(map()));
        mapper.setMapping(pbt, boostSpeeds[i]);
        layout -> addWidget(pbt);
    }

    connect(&mapper, SIGNAL(mapped(int)), this, SLOT(slotButtonBoostClicked(int)));
    tickTimer.setInterval(TICK_INTERVAL);
    //connect(&tickTimer, SIGNAL(timeout()), parent, SLOT(slotAlarmTickTimer()));

    elapsedTime.start();
    tickTimer.start();
    lastTime = elapsedTime.elapsed();
}

void TimerLabel::slotButtonBoostClicked(int speedUp)
{
    timeSpeed = speedUp;
    lastTime = elapsedTime.elapsed();
}

long long TimerLabel::timeElapsed()
{
    long long timeGone = elapsedTime.elapsed() - lastTime;
    gameTime.timeTick(int(timeGone * timeSpeed));
    lastTime += timeGone;
    timeLabel.setText(gameTime.getTimeStr());
    return gameTime.getTimeElapsed();
}
