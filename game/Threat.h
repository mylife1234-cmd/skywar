#ifndef THREAT__H
#define THREAT__H
#include"Common.h"
#include"BaseObject.h"
struct Threat :Baseobject
{
    Threat();
    ~Threat();
    void GetThreatMove(const int & width, const int & height);
    void resetThreat(const int & xThreat);
};
#endif // THREAT__H
