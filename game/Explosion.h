#ifndef EXPLOSION__H
#define EXPLOSION__H
#include"Common.h"
#include"BaseObject.h"
struct Explosion:Baseobject
{
    int fr;
    SDL_Rect frame[4];
    Explosion();
    ~Explosion();
    void Set_frame();
    void Set_fr(const int &fr_)
    {
        fr=fr_;
    }
    void showExplosion(SDL_Surface *background);
};
#endif
