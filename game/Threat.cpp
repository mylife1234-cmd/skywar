#include"Threat.h"
#include"Common.h"
#include"BaseObject.h"
Threat::Threat()
{
    rect.x=SCREEN_WIDTH;
    rect.y=RANGE;
    rect.w=THREAT_WIDTH;
    rect.h=THREAT_HEIGHT;
}
Threat::~Threat()
{

}
  void Threat::GetThreatMove(const int &width, const int& height)
 {
    int SPEED_THREAT=5;
    rect.x-=SPEED_THREAT;
    SPEED_THREAT+=INCREASE_SPEED;
    if(rect.x<0)
    {
        rect.x=1200;
        int randomPreposition=rand()%RANGE;
                if(randomPreposition>RANGE)
                {
                randomPreposition=rect.x*(0.4);
                }
                rect.y=randomPreposition;

    }
 }
 void Threat::resetThreat(const int & width)
 {
        rect.x=width;
        int randomPreposition=rand()%RANGE;
        if(randomPreposition>RANGE)
        {
        randomPreposition=rect.x*(0.4);
        }
        rect.y=randomPreposition;
 }
