#include"MainObject.h"
#include"Butllet.h"
#include"BaseObject.h"
Butllet::Butllet()
{
    rect.x=0;
    rect.y=0;
    x_butllet=0;
    y_butllet=0;
    move=false;
}
Butllet::~Butllet(){
}
void Butllet::InputButlletAction(SDL_Event e)
{

}
void Butllet::GetButlletMove(const int& width, const int& height)
{
    rect.x+=SPEED_BUTLLET;
    if(rect.x>=width)
    {
        move=false;
    }
}
