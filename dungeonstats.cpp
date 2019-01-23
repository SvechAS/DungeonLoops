#include "dungeonstats.h"

DungeonStats::DungeonStats()
{

}

double     DungeonStats::getManaPool()  { return manaPool; }
double     DungeonStats::getManaLevel() { return mana    ; }

double DungeonStats::calcManaFlowLimit()
{
    double flowLimit;
    timeElapsed >= 1000 ? flowLimit = manaFlowLimit : flowLimit = manaFlowLimit * timeElapsed / 1000;
    timeElapsed = 0;
    return flowLimit;
}

double DungeonStats::spendMana(double want)
{
    double flowLimit = calcManaFlowLimit();
    double manaReady = want;
    if(manaReady > mana) manaReady = mana;
    if(manaReady > flowLimit) manaReady = flowLimit;
    mana -= manaReady;
    return manaReady;
}

void DungeonStats::setManaLabel(QLabel *label)
{
    manaLabel = label;
}

void DungeonStats::timePassed(long long ms)
{
    if(mana < manaPool)
    {
        mana += ms * manaRegen / 1000;
        if(mana > manaPool)
            mana = manaPool;
        timeElapsed += ms;
    }
}

void DungeonStats::updateStatsLabels()
{
    manaLabel->setText("Mana: " + QString().number(mana) + " / " + QString().number(manaPool));
}

void DungeonStats::initStats()
{

}
