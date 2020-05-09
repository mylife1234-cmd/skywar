#ifndef MAIN_OBJECT__H
#define MAIN_OBJECT__H
#include"Common.h"
#include"BaseObject.h"
#include<Vector>
#include"Butllet.h"
using namespace std;
struct MainObject:Baseobject
{
    int x_object;
    int y_object;
    vector <Butllet*> listButllet;
    MainObject();
    ~MainObject();
    void InputAction(SDL_Event e, SDL_Surface* &screenSurface,Mix_Chunk* soundButllet[2]);
    void move(const int &SCREEN_HEIGHT, const int &SCREEN_WIDTH);
    void SetListBullet(vector <Butllet*> listButllet_)
    {
        if (listButllet.size() > 0)
        {
            listButllet.clear();
        }

        listButllet = listButllet_ ;
    }
    vector <Butllet*> GetListButllet() const{
        return listButllet;
    }
    void RemoveButllet(const int& x_butllet);
};
#endif // MAIN_OBECT__H
