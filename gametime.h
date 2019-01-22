#ifndef GAMETIME_H
#define GAMETIME_H

#include <QString>

class GameTime
{
public:
    GameTime();

    QString   getTimeStr();
    long long getTimeInt();
    long long getTimeElapsed();

    void      timeTick(int time);


private:
    int sec, min,    hour,
        day, mounth, year,
        ms;

    int secInMin = 60,
        minInHour = 60,
        hourInDay = 24,
        dayInMounth = 30,
        mounthInYear = 12,
        msInSec = 1000;

    long long notElapsedTime = 0;

    void overlim(int *num, int *next, int lim);
    void initTime();
};

#endif // GAMETIME_H
