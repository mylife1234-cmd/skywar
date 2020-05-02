#ifndef BASE_OJECT__H
#define BASE_OJECT__H
struct Baseobject
{
    SDL_Rect rect;
    SDL_Surface *plane;
    SDL_Rect set;
    Baseobject();
    ~Baseobject();
    void SetPreposition(const int& x,const int& y)
    {
        rect.x = x;
        rect.y = y;
    }
    SDL_Rect GetPrePosition() {
        return rect;
    }
    void showObject(SDL_Surface *des);
    bool Loading(std::string path,SDL_Surface*&screenSurface);
};
#endif // BASE_OJECT__H
