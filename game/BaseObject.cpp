#include"Common.h"
#include"BaseObject.h"
Baseobject::Baseobject()
{
    rect.x=0;
    rect.y=0;
    plane=NULL;
}
Baseobject::~Baseobject()
{
    if(plane!=NULL)
    {
        SDL_FreeSurface(plane);
    }
}
bool Baseobject::Loading(std::string path,SDL_Surface*&screenSurface)
{
    plane=LoadSurface(path,screenSurface);
    if(plane==NULL)
    {
        return false;
    }
    return true;
}
void Baseobject::showObject(SDL_Surface*des)
{
    if(plane!=NULL)
    {
        func::ApplySurface(plane,des,rect.x,rect.y);
    }
}
void Baseobject::setPreposion(int x, int y)
{
    rect.x=x;
    rect.y=y;
}
