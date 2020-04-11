#include"Common.h"
#include"BaseObject.h"
#include"MainObject.h"
MainObject::MainObject()
{
    rect.x=0;
    rect.y=0;
    x_object=0;
    y_object=0;
}
MainObject::~MainObject()
{
    ;
}
void MainObject::InputAction(SDL_Event e)
{
    if(e.type==SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT:
                x_object-=25;
                break;
            case SDLK_DOWN:
                y_object+=20;
                break;
            case SDLK_RIGHT:
                x_object+=25;
                break;
            case SDLK_UP:
                y_object-=20;
                break;
            default:
                break;
        }
    }
    else if(e.type==SDL_KEYUP)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT:
                x_object+=25;
                break;
            case SDLK_DOWN:
                y_object-=20;
                break;
            case SDLK_RIGHT:
                x_object-=25;
                break;
            case SDLK_UP:
                y_object+=20;
                break;
            default:
                break;
        }
    }
}
void MainObject::move(const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
    rect.x+=x_object;
    if(rect.x<0 || rect.x+70 > SCREEN_WIDTH)
    {
        rect.x-=x_object;
    }
    rect.y+=y_object;
    if(rect.y<0 || rect.y+300> SCREEN_HEIGHT )
    {
        rect.y-=y_object;
    }
}
