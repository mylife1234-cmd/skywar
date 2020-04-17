#ifndef BUTLLET__H
#define BUTLLET__H
#include"BaseObject.h"
struct Butllet :Baseobject
{
    int x_butllet;
    int y_butllet;
    bool move;
    Butllet();
    ~Butllet();
    void InputButlletAction(SDL_Event e);
    void GetButlletMove(const int & width, const int & height);
    bool ButlletMove(){
        return move;
    }
    void setButlletMove(bool _move)
    {
        move = _move;
    }
    void setButlletPreposition(const int &width, const int &height)
    {
        rect.w=width;
        rect.h=height;
    }
};
#endif // BUTLLET__H
