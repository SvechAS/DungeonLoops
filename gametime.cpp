#include "gametime.h"

GameTime::GameTime()
{
    initTime();
}

long long GameTime::getTimeElapsed()
{
    long long diff = getTimeInt() - notElapsedTime;
    notElapsedTime = getTimeInt();
    return diff;
}

long long GameTime::getTimeInt()
{
    return (((((year * mounthInYear + mounth) * dayInMounth + day) * hourInDay
              + hour) * minInHour + min) * secInMin + sec) * msInSec + ms;
}

QString GameTime::getTimeStr()
{
    QString s;
    s = "Year: "    + QString().number(year) + " Mounth: " + QString().number(mounth)
      + " Day: "    + QString().number(day ) + " Hour: "   + QString().number(hour  )
      + " Minute: " + QString().number(min ) + " Second: " + QString().number(sec   );
    return s;
}

void GameTime::timeTick(int time)
{
    ms += time;
    if(ms >= msInSec)
    {
        overlim(&ms, &sec, msInSec);
        if(sec >= secInMin)
        {
            overlim(&sec, &min, secInMin);
            if(min >= minInHour)
            {
                overlim(&min, &hour, minInHour);
                if(hour >= hourInDay)
                {
                    overlim(&hour, &day, hourInDay);
                    if(day >= dayInMounth)
                    {
                        overlim(&day, &mounth, dayInMounth);
                        if(mounth >= mounthInYear)
                        {
                            overlim(&mounth, &year, mounthInYear);
                        }
                    }
                }
            }
        }
    }
}

void GameTime::overlim(int *num, int *next, int lim)
{
    *next = *next + *num / lim;
    *num = *num % lim;
}

void GameTime::initTime()
{
    ms = 0;
    sec = 0;
    min = 0;
    hour = 0;
    day = 0;
    mounth = 0;
    year = 0;
}
