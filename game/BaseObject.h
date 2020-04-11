#ifndef BASE_OJECT__H
#define BASE_OJECT__H

struct Baseobject
{
    SDL_Rect rect;
    SDL_Surface *plane;
    SDL_Rect set;
    Baseobject();
    ~Baseobject();
    Baseobject(const int& x,const int& y)
    {
        rect.x=x;
        rect.y=y;
    }
    void showObject(SDL_Surface *des);
    bool Loading(std::string path,SDL_Surface*&screenSurface);
    void setPreposion(int x, int y);
};
#endif // BASE_OJECT__H
