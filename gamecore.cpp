#include "gamecore.h"

GameCore::GameCore(QWidget *parent)
    : QWidget(parent)
{
    initForm();
    createMapLayout();
    createActionListLayout();
    createActionsLayout();
    createTimeLayout();
    createStatsLayout();
}

GameCore::~GameCore()
{

}

void GameCore::initForm()
{
    setWindowTitle("Dungeon Loops");
    setFixedSize(1100, 390);
    {
        QPalette Pal(palette());
        Pal.setColor(QPalette::Background, QColor(237, 240, 233));
        setAutoFillBackground(true);
        setPalette(Pal);
    }
    setLayout(&gameLayout);
}

void GameCore::createTimeLayout()
{
    QGridLayout *grid = new QGridLayout();

    {
        timeLabel.setText(gameTime.getTimeStr());
        timeLabel.setFixedWidth(300);
        grid->addWidget(&timeLabel, 0, 0, Qt::AlignLeft);
    }

    int boostSizes[7] = {20, 20, 30, 30, 35, 40, 45};
    QString boostNames[7] = {"X1", "X5", "X10", "X50", "X100", "X1000", "X10000"};
    for(int i = 0; i < 7; i++)
    {
        QPushButton *pbt = new QPushButton(this);
        pbt->setText(boostNames[i]);
        pbt->setFixedSize(boostSizes[i], 20);
        pbt->setObjectName(boostNames[i]);
        connect(pbt, SIGNAL(clicked()), this, SLOT(slotButtonBoostClicked()));
        grid->addWidget(pbt, 0, i + 1);
    }

    gameLayout.addLayout(grid, 0, 0, 1, 4, Qt::AlignLeft);

    tickTimer.setInterval(50);
    connect(&tickTimer, SIGNAL(timeout()), this, SLOT(slotAlarmTickTimer()));

    elapsedTime.start();
    tickTimer.start();
    lastTime = elapsedTime.elapsed();
}

void GameCore::createMapLayout()
{
    QGridLayout *grid = new QGridLayout();

    {
        QLabel *lbl = new QLabel(this);
        lbl->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
        lbl->setText("Map");
        grid->addWidget(lbl, 0, 0, Qt::AlignCenter);
    }

    {
        dungeonMap = new DungeonMap();
        grid->addWidget(dungeonMap, 1, 0);
    }

    {
        QSpacerItem *spe = new QSpacerItem(dungeonMap->width(), this->height());
        grid->addItem(spe, 2, 0);
    }
    grid->setRowStretch(2, 1);
    gameLayout.addLayout(grid, 1, 0, Qt::AlignTop);
}

void GameCore::createActionListLayout()
{
    {
        QLabel *lbl = new QLabel(this);
        lbl->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
        lbl->setText("Action List");
        actionListLayout.addWidget(lbl, 0, 0, Qt::AlignCenter);
    }

    {
        QSpacerItem *spe = new QSpacerItem(200, this->height());
        actionListLayout.addItem(spe, 1, 0);
    }
    actionListLayout.setRowStretch(1, 1);

    gameLayout.addLayout(&actionListLayout, 1, 1, Qt::AlignTop);

    connect(dungeonMap, SIGNAL(signalBuildingStart()), this, SLOT(slotAddToBuildQueue()));
    connect(this, SIGNAL(signalBuildingEnd()), dungeonMap, SLOT(slotBuildingEnd()));
}

void GameCore::createActionsLayout()
{
    QGridLayout *grid = new QGridLayout();

    {
        QLabel *lbl = new QLabel(this);
        lbl->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
        lbl->setText("Actions");
        grid->addWidget(lbl, 0, 0, Qt::AlignCenter);
    }

    {
        QPushButton *btn = new QPushButton(this);
        btn->setText("Create dungeon core");
        btn->setObjectName("DungeonCoreButton");
        connect(btn, SIGNAL(clicked()), this, SLOT(slotButtonInActionListClicked()));
        grid->addWidget(btn, 1, 0, Qt::AlignCenter);
    }

    {
        QSpacerItem *spe = new QSpacerItem(200, this->height());
        grid->addItem(spe, 2, 0);
    }
    grid->setRowStretch(2, 1);
    gameLayout.addLayout(grid, 1, 2, Qt::AlignTop);
}

void GameCore::createStatsLayout()
{
    QGridLayout *grid = new QGridLayout();

    {
        QLabel *lbl = new QLabel(this);
        lbl->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
        lbl->setText("Stats");
        grid->addWidget(lbl, 0, 0, Qt::AlignCenter);
    }

    {
        dungeonStats = new DungeonStats();
        QLabel *lbl = new QLabel("Mana: 0 / 0", this);
        dungeonStats->setManaLabel(lbl);
        grid->addWidget(lbl, 1, 0, Qt::AlignLeft);
    }

    {
        QSpacerItem *spe = new QSpacerItem(300, this->height());
        grid->addItem(spe, 2, 0);
    }
    grid->setRowStretch(2, 1);
    gameLayout.addLayout(grid, 1, 3, Qt::AlignCenter);
}

void GameCore::updateActionListLayout()
{
    int i;
    for(i = 0; i < currentActionList.size(); i++)
    {
        QLabel *lbl = qobject_cast<QLabel*>(actionListLayout.itemAtPosition(i + 1, 0)->widget());
        lbl->setText("Building: " + currentActionList.at(i).name + " | Progress: "
                                  + QString::number(currentActionList.at(i).manaGet) + " / "
                                  + QString::number(currentActionList.at(i).manaNeed));
    }
}

void GameCore::slotAddToBuildQueue()
{
    ActionListMember *tmp = new ActionListMember;
    tmp->name = "Dungeon Core";
    tmp->manaNeed = 2500;
    tmp->manaGet = 0;
    currentActionList.enqueue(*tmp);

    QLayoutItem *target = actionListLayout.takeAt(actionListLayout.indexOf(actionListLayout.itemAtPosition(oldListSize, 0)));
    actionListLayout.addItem(target, currentActionList.size() + 1, 0);

    oldListSize = currentActionList.size() + 1;

    QLabel *lbl = new QLabel(this);
    actionListLayout.addWidget(lbl, currentActionList.size(), 0, Qt::AlignCenter);
}

void GameCore::buildFromQueue()
{
    if(!currentActionList.isEmpty())
    {
        currentActionList.head().manaGet += dungeonStats->spendMana(currentActionList.head().manaNeed -
                                                                    currentActionList.head().manaGet);
        if(currentActionList.head().manaGet >= currentActionList.head().manaNeed)
        {
            currentActionList.dequeue();
            QLayoutItem *target = actionListLayout.takeAt(actionListLayout.indexOf(
                                                          actionListLayout.itemAtPosition(1, 0)));
            delete target->widget();

            target = actionListLayout.takeAt(actionListLayout.indexOf(actionListLayout.itemAtPosition(oldListSize, 0)));
            actionListLayout.addItem(target, currentActionList.size() + 1, 0);

            oldListSize = currentActionList.size() + 1;

            emit signalBuildingEnd();
        }

        updateActionListLayout();
    }
}

void GameCore::slotAlarmTickTimer()
{
    long long timeGone = elapsedTime.elapsed() - lastTime;
    gameTime.timeTick(int(timeGone * timeSpeed));
    lastTime += timeGone;
    timeLabel.setText(gameTime.getTimeStr());

    long long timeElapsed = gameTime.getTimeElapsed();
    dungeonStats->timePassed(timeElapsed);
    dungeonStats->updateStatsLabels();
    dungeonMap->updateScene();

    buildFromQueue();
}

void GameCore::slotButtonInActionListClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(sender()->objectName() == "DungeonCoreButton")
    {
        btn->setEnabled(false);
        dungeonMap->startPlaning();
    }
}

void GameCore::slotButtonBoostClicked()
{
    int boostSpeeds[7] = {1, 5, 10, 50, 100, 1000, 10000};
    QString boostNames[7] = {"X1", "X5", "X10", "X50", "X100", "X1000", "X10000"};
    QString str = sender()->objectName();
    for(int i = 0; i < 7; i++)
        if(str == boostNames[i])
            timeSpeed = boostSpeeds[i];
    lastTime = elapsedTime.elapsed();
}
