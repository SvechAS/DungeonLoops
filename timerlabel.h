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

static const int TICK_INTERVAL = 50;

class TimerLabel : public QWidget
{
    Q_OBJECT

public:
    explicit TimerLabel(QWidget *parent = nullptr);
    ~TimerLabel();

    long long timeElapsed();

    QBoxLayout *layout;
    QLabel     timeLabel;
    QTimer          tickTimer;
    QSignalMapper mapper;

signals:
    void buttonClick(int speedUp);
private slots:
    void slotButtonBoostClicked(int speedUp);

private:
    void initForm();

    GameTime        gameTime;
    QString boostNames[7] = {"X1", "X5", "X10", "X50", "X100", "X1000", "X10000"};
    long long lastTime = 0;
    int timeSpeed = 1;
    QElapsedTimer   elapsedTime;
};

#endif // TIMERLABEL_H
