#ifndef BOOM__H
#define BOOM__H
#include"BaseObject.h"
#include"Common.h"
struct Boom:Baseobject
{
    int fr;
    SDL_Rect frame[4];
    Boom();
    ~Boom();
    void SetVideo();
    void SetFrame(int fr1)
    {
        fr=fr1;
    }
    void ShowExplosion(SDL_Surface *&screenSurface);
};
#endif // BOOM__H
