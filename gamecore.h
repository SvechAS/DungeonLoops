#ifndef GAMECORE_H
#define GAMECORE_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QWidget>
#include <QSpacerItem>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>
#include <cmath>

#include <dungeonmap.h>
#include <gametime.h>
#include <dungeonstats.h>
#include <timerlabel.h>
#include <actionbutton.h>
#include <actionlistlayout.h>

class GameCore : public QWidget
{
    Q_OBJECT

public:
    explicit GameCore(QWidget *parent = nullptr);
    ~GameCore();

signals:
    void signalBuildingEnd();

private slots:
    void slotAlarmTickTimer();
    void slotButtonInActionListClicked();

private:
    void initForm();
    void createMapLayout();
    void createActionsLayout();
    void createTimeLayout();
    void createStatsLayout();
    void createActionListLayout();
    void updateActionListLayout();
    void buildFromQueue();

    QLabel          timeLabel;
    QGridLayout     gameLayout,
                    timeLayout,
                    statsLayout;
    ActionListLayout actionListLayout;

    DungeonMap     *dungeonMap;
    DungeonStats   *dungeonStats;

    long long lastTime = 0;
    int       timeSpeed = 1;
    int       oldListSize = 1;


    TimerLabel timerLabel;
};

#endif // GAMECORE_H
