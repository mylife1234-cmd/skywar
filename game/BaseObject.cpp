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
//LOAD OBJECT
bool Baseobject::Loading(std::string path,SDL_Surface*&screenSurface)
{
    plane=LoadSurface(path,screenSurface);
    if(plane==NULL)
    {
        return false;
    }
    return true;
}
//SHOW OJECT ON SCREEN
void Baseobject::showObject(SDL_Surface*background)
{
    if(plane!=NULL)
    {
        func::ApplySurface(plane,background,rect.x,rect.y);
    }
}

