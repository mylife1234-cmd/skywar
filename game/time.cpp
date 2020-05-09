#include"time.h"
Time::Time()
{
    TimeStart= 0;
    StartTime = false;
}
Time::~Time()
{

}
void Time::start()
{
    //START THE TIMER
    StartTime = true;
    //GET THE CURRENT CLOCK TIME
    TimeStart = SDL_GetTicks();
}
void Time::stop()
{
    //STOP THE TIMER
    StartTime = false;
	//CLEAR TIME
	TimeStart = 0;
}

Uint32 Time::getTicks()
{
	//The actual timer time
	Uint32 time = 0;
    //If the timer is running
    if( StartTime )
    {
        time = SDL_GetTicks() - TimeStart;
    }
    return time;
}

bool Time::Started()
{
	//Timer is running
    return StartTime;
}

