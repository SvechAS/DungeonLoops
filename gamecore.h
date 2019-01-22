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
#include <QQueue>
#include <QDebug>

#include <dungeonmap.h>
#include <gametime.h>
#include <dungeonstats.h>

class GameCore : public QWidget
{
    Q_OBJECT

public:
    explicit GameCore(QWidget *parent = nullptr);
    ~GameCore();

    struct ActionListMember
    {
        QString name;
        double manaNeed;
        double manaGet;
    };

signals:
    void signalBuildingEnd();

private slots:
    void slotAlarmTickTimer();
    void slotButtonBoostClicked();
    void slotButtonInActionListClicked();
    void slotAddToBuildQueue();

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
                    statsLayout,
                    actionListLayout;

    DungeonMap     *dungeonMap;
    DungeonStats   *dungeonStats;

    GameTime        gameTime;
    QTimer          tickTimer;
    QElapsedTimer   elapsedTime;

    long long lastTime = 0;
    int       timeSpeed = 1;
    int       oldListSize = 1;

    QQueue<ActionListMember> currentActionList;
};

#endif // GAMECORE_H
