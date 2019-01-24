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
#include <cmath>

#include <dungeonmap.h>
#include <gametime.h>
#include <dungeonstats.h>
#include <timerlabel.h>
#include <actionbutton.h>

const static double EPS = 0.0000001;

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
        double manaGot;

        ActionListMember() {
            name = "Dungeon Core";
            manaNeed = 2500;
            manaGot = 0;
        }

        double manaNeeds(){
            return manaNeed - manaGot;
        }

        void manaConsume(double mana) {
            manaGot += mana;
        }

        bool manaIsFull() {
            return abs(manaNeeds()) < EPS;
        }

        QString toString() const {
            return "Building: " + name + " | Progress: " + QString::number(manaGot) + " / " + QString::number(manaNeed);
        }
    };

signals:
    void signalBuildingEnd();

private slots:
    void slotAlarmTickTimer();
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

    long long lastTime = 0;
    int       timeSpeed = 1;
    int       oldListSize = 1;

    QQueue<ActionListMember> currentActionList;

    TimerLabel timerLabel;
};

#endif // GAMECORE_H
