#ifndef MAIN_OBJECT__H
#define MAIN_OBJECT__H
#include"Common.h"
#include"BaseObject.h"
struct MainObject:Baseobject
{
    int x_object;
    int y_object;

    MainObject();
    ~MainObject();
    void InputAction(SDL_Event e);
    void move(const int SCREEN_HEIGHT, const int SCREEN_WIDTH);
};
#endif // MAIN_OBECT__H
