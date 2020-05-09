#ifndef COMMON__H
#define COMMON__H
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<cstring>
#include<SDL_main.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<ctime>
#include"time.h"
//BACKGROUND
using namespace std;
const int SCREEN_WIDTH=1280;
const int SCREEN_HEIGHT=640;
const string WINDOW_TITLE = "SKY WAR";
const int LAND=140;
const int SPEED_BACKGROUND=10;
SDL_Surface *LoadSurface(std::string path, SDL_Surface *&screenSurface);
//Threat
const int NUMBER_OF_THREAT=100;
const int INCREASE_SPEED=100;
const int THREAT_WIDTH=80;
const int THREAT_HEIGHT=33;
//BOOM FRAME
const int FRAME_WIDTH=660;
const int FRAME_HEIGHT=165;
//BUTLLET
const int SPEED_BUTLLET=100;
const int BUTLLET_WIDTH=35;
const int BUTLLET_HEIGHT=5;
const int X_BUTLLET=65;
const int y_BUTLLET=40;
//MAINOBJECT
const int MOVE_X=20;
const int MOVE_Y=10;
const int PLANE_WIDTH=80;
const int PLANE_HEIGHT=54;
const int RANGE =480;
namespace func{
   bool Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window*&window, SDL_Surface* &screenSurface,Mix_Chunk *soundBoom[2], Mix_Chunk *soundButllet[2]);
    bool LoadMedia(SDL_Surface * &LoadImage,SDL_Surface* &screenSurface);
    void close(SDL_Surface * LoadImage,SDL_Window*window );
    void ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y);
    bool checkCollision( const SDL_Rect& a,const SDL_Rect& b );
    void ApplySurface1(SDL_Surface*object,SDL_Surface*background,SDL_Rect *frame ,int x, int y);
    bool ShowMenu(SDL_Surface*background, TTF_Font *textFont, SDL_Surface *menuScreen,SDL_Window*window,SDL_Surface* LoadImage);
    bool ShowMenu2(SDL_Surface*background,int score, TTF_Font *textFont, SDL_Surface *menuScreen,SDL_Window*window,SDL_Surface* LoadImage);
}
#endif // COMMON_H
