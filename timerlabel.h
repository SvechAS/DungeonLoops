#ifndef TIMERLABEL_H
#define TIMERLABEL_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QElapsedTimer>
#include <QPushButton>
#include <QTimer>
#include <QObject>
#include <QSignalMapper>

#include <gametime.h>

const static int TICK_INTERVAL = 50;
const static int SPEEDS_OF_TIME[7] = {1, 5, 10, 50, 100, 1000, 10000};

class TimerLabel : public QWidget
{
    Q_OBJECT

public:
    explicit TimerLabel(QWidget *parent = nullptr);
    ~TimerLabel();

    QLayout* layout();
    long long timeElapsed();
    void onTickConnect(QWidget* ptr, const char* slot);

private:
    void initForm();
    void initTimers();

    GameTime        gameClock;
    long long lastTickTime = 0;
    int currTimeSpeed = 1;

    //layout
    QBoxLayout *layoutPtr;
    QLabel     timeLabel;
    //timers
    QTimer          tickTimer;
    QElapsedTimer   elapsedTime;
    // signals
    QSignalMapper mapper;

private slots:
    void slotButtonSetNewTimeSpeed(int newTimeSpeed);
};

#endif // TIMERLABEL_H
