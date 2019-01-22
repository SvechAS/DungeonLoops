#include "dungeonstats.h"

DungeonStats::DungeonStats()
{

}

double     DungeonStats::getManaPool()  { return manaPool; }
double     DungeonStats::getManaLevel() { return mana    ; }

double DungeonStats::spendMana(double want)
{
    double manaReady = want;
    if(manaReady > mana) manaReady = mana;
    if(manaReady > manaFlowLimit) manaReady = manaFlowLimit;
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
    }
}

void DungeonStats::updateStatsLabels()
{
    manaLabel->setText("Mana: " + QString().number(mana) + " / " + QString().number(manaPool));
}
