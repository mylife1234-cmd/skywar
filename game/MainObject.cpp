#include"Common.h"
#include"BaseObject.h"
#include"MainObject.h"
#include"Butllet.h"
MainObject::MainObject()
{
    rect.x=0;
    rect.y=0;
    x_object=0;
    y_object=0;
    plane=NULL;
}
MainObject::~MainObject()
{
    ;
}
void MainObject::InputAction(SDL_Event e, SDL_Surface* &screenSurface)
{
    if(e.type==SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT:
                x_object-=20;
                break;
            case SDLK_DOWN:
                y_object+=10;
                break;
            case SDLK_RIGHT:
                x_object+=20;
                break;
            case SDLK_UP:
                y_object-=10;
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
                x_object+=20;
                break;
            case SDLK_DOWN:
                y_object-=10;
                break;
            case SDLK_RIGHT:
                x_object-=20;
                break;
            case SDLK_UP:
                y_object+=10;
                break;
            default:
                break;
        }
    }
    //dòng 61 đến dòng 73 tham khảo thuật toán tại https://phattrienphanmem123az.com/lap-trinh-game-cpp/bai-7-dan-ban-va-xu-ly-chuot.html
    else if(e.type==SDL_MOUSEBUTTONDOWN)
    {
        Butllet* listButllet01 =new Butllet();
        if(e.button.button==SDL_BUTTON_LEFT)
        {
            listButllet01->setButlletPreposition(35,5);
            listButllet01->Loading("laser.png",screenSurface);
        }
        listButllet01->SetPreposition(this->rect.x+65, this->rect.y+40);
        listButllet01->setButlletMove(true);
        listButllet.push_back(listButllet01);
    }
}
void MainObject::move(const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
    rect.x+=x_object;
    if(rect.x<0 || rect.x+60 > SCREEN_WIDTH)
    {
        rect.x-=x_object;
    }
    rect.y+=y_object;
    if(rect.y <0 || rect.y+200> SCREEN_HEIGHT )
    {
        rect.y-=y_object;
    }
}
void MainObject::RemoveButllet(const int & x_butllet)
{
    for(int i=0; i<listButllet.size(); i++)
    {
        if(x_butllet <listButllet.size())
        {
            Butllet *amo=listButllet.at(x_butllet);
            listButllet.erase(listButllet.begin() + i);
            if(amo!=NULL)
            {
                delete amo;
                amo=NULL;
            }
        }
    }
}
