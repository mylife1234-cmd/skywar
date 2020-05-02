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
}
void MainObject::InputAction(SDL_Event e, SDL_Surface* &screenSurface,Mix_Chunk* soundButllet[2])
{
    if(e.type==SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT:
                x_object-=MOVE_X;
                break;
            case SDLK_DOWN:
                y_object+=MOVE_Y;
                break;
            case SDLK_RIGHT:
                x_object+=MOVE_X;
                break;
            case SDLK_UP:
                y_object-=MOVE_Y;
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
                x_object+=MOVE_X;
                break;
            case SDLK_DOWN:
                y_object-=MOVE_Y;
                break;
            case SDLK_RIGHT:
                x_object-=MOVE_X;
                break;
            case SDLK_UP:
                y_object+=MOVE_Y;
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
            listButllet01->Loading("laser.png",screenSurface);
            listButllet01->setButllet(BUTLLET_WIDTH,BUTLLET_HEIGHT);
            Mix_PlayChannel(-1,soundButllet[0],0);
        }
        listButllet01->SetPreposition(this->rect.x+X_BUTLLET, this->rect.y+y_BUTLLET);
        listButllet01->setButlletMove(true);
        listButllet.push_back(listButllet01);
    }
}
void MainObject::move(const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
    rect.x+=x_object;
    if(rect.x<0 || rect.x+LENGTH_OF_PLANE > SCREEN_WIDTH)
    {
        rect.x-=x_object;
    }
    rect.y+=y_object;
    if(rect.y<0 || rect.y+LAND> SCREEN_HEIGHT )
    {
        rect.y-=y_object;
    }
}
void MainObject::RemoveButllet(const int & x_butllet)
{
    for(int iii=0; iii<listButllet.size(); iii++)
    {
            if(x_butllet <listButllet.size())
        {
            Butllet *amo=listButllet.at(x_butllet);
            listButllet.erase(listButllet.begin() + iii);
            if(amo!=NULL)
            {
                delete amo;
                amo=NULL;
            }
        }
    }
}
