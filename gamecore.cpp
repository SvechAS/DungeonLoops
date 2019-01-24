#include "gamecore.h"

GameCore::GameCore(QWidget *parent)
    : QWidget(parent), timerLabel(this), actionListLayout()
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
    timerLabel.onTickConnect(this, SLOT(slotAlarmTickTimer()));
    gameLayout.addLayout(timerLabel.layout(), 0, 0, 1, 4, Qt::AlignLeft);
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
    gameLayout.addLayout(actionListLayout.layout(), 1, 1, Qt::AlignTop);

    connect(dungeonMap, SIGNAL(signalBuildingStart()), &actionListLayout, SLOT(slotAddToBuildQueue()));
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

    grid->addWidget(new ActionButton(this, "DungeonCoreButton", "Create dungeon core"), 1, 0, Qt::AlignCenter);

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
    actionListLayout.update();
}

void GameCore::buildFromQueue()
{
    while(actionListLayout.buildFromQueue(dungeonStats))
    {
        emit signalBuildingEnd();
    }
    updateActionListLayout();
}

void GameCore::slotAlarmTickTimer()
{
    long long timeElapsed = timerLabel.timeElapsed();
    dungeonStats->timePassed(timeElapsed);
    dungeonStats->updateStatsLabels();
    dungeonMap->updateScene();

    buildFromQueue();
}

void GameCore::slotButtonInActionListClicked()
{
    ActionButton *btn = qobject_cast<ActionButton*>(sender());
    if(sender()->objectName() == "DungeonCoreButton")
    {
        btn->setEnabled(false);
        dungeonMap->startPlaning();
    }
}
