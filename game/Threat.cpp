#include"Threat.h"
#include"Common.h"
#include"BaseObject.h"
Threat::Threat()
{
    rect.x=1200;
    rect.y=400;
    rect.w=80;
    rect.h=33;
    x_threat=7;
    y_threat=0;
}
Threat::~Threat()
{

}
  void Threat::GetThreatMove(const int &width, const int& height)
 {
    rect.x-=x_threat;
    if(rect.x<0)
    {
        rect.x=1200;
        int randomPreposition=rand()%400;
                if(randomPreposition>400)
                {
                randomPreposition=rect.x*(0.4);
                }
                rect.y=randomPreposition;

    }
 }
 void Threat::resetThreat(const int & width)
 {
        rect.x=width;
        int randomPreposition=rand()%400;
        if(randomPreposition>400)
        {
        randomPreposition=rect.x*(0.4);
        }
        rect.y=randomPreposition;
 }
