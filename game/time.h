#ifndef TIME__H
#define TIME__H
#include"Common.h"
struct Time
{
    Uint32 TimeStart;
    //THE TIMER STATUS
    bool StartTime;
    Time();
    ~Time();
    void start();
    void stop();
    Uint32 getTicks();
    bool Started();
};
#endif // TIME__H
