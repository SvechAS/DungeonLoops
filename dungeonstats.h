#ifndef DUNGEONSTATS_H
#define DUNGEONSTATS_H

#include <QLabel>

class DungeonStats
{
public:
    DungeonStats();
    void timePassed(long long ms);
    void updateStatsLabels();
    double spendMana(double want);
    double getManaLevel();
    double getManaPool();
    void setManaLabel(QLabel *label);
    void initStats();
private:
    double calcManaFlowLimit();

    double  manaPool = 1000.0, manaRegen = 0.01,
            mana = 0.0,    manaFlowLimit = 50.0;

    long long timeElapsed = 0;
    QLabel *manaLabel;
};

#endif // DUNGEONSTATS_H
