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
    void move(const int SCREEN_HEIGHT, const int SCREEN_WIDTH);
    //tham khảo cách kết nối đạn vs máy bay ở trang https://phattrienphanmem123az.com/lap-trinh-game-cpp/bai-7-dan-ban-va-xu-ly-chuot.html
    //dòng 12
    void SetListBullet(vector <Butllet*> listButllet_)
    {
        listButllet = listButllet_ ;
    }
    vector <Butllet*> GetListButllet() const{
        return listButllet;
    }
    void RemoveButllet(const int& x_butllet);
};
#endif // MAIN_OBECT__H
