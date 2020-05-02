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
//BACKGROUND
using namespace std;
const int SCREEN_WIDTH=1200;
const int SCREEN_HEIGHT=685;
const string WINDOW_TITLE = "SKY WAR";
const int LAND=250;
const int SPEED_BACKGROUND=4;
SDL_Surface *LoadSurface(std::string path, SDL_Surface *&screenSurface);
//Threat
const int NUMBER_OF_THREAT=7;
const int SPEED_THREAT=5;
const int INCREASE_SPEED=0.7;
const int THREAT_WIDTH=80;
const int THREAT_HEIGHT=33;
//BOOM FRAME
const int FRAME_WIDTH=660;
const int FRAME_HEIGHT=165;
//BUTLLET
const int SPEED_BUTLLET=80;
const int BUTLLET_WIDTH=35;
const int BUTLLET_HEIGHT=5;
const int X_BUTLLET=65;
const int y_BUTLLET=40;
//MAINOBJECT
const int MOVE_X=20;
const int MOVE_Y=10;
const int LENGTH_OF_PLANE=80;
const int RANGE =400;

namespace func{
   bool Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window*&window, SDL_Surface* &screenSurface,Mix_Chunk *soundBoom[2], Mix_Chunk *soundButllet[2]);
    bool LoadMedia(SDL_Surface * &LoadImage,SDL_Surface* &screenSurface);
    void close(SDL_Surface * &LoadImage,SDL_Window*&window );
    void ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y);
    bool checkCollision( const SDL_Rect& a,const SDL_Rect& b );
    void ApplySurface1(SDL_Surface*object,SDL_Surface*background,SDL_Rect *frame ,int x, int y);
}
#endif // COMMON_H
