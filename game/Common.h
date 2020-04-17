#ifndef COMMON__H
#define COMMON__H
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<SDL_main.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<ctime>
const int A=60;
using namespace std;
SDL_Surface *LoadSurface(std::string path, SDL_Surface *&screenSurface);
namespace func{
    bool Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window*&window, SDL_Surface* &screenSurface);
    bool LoadMedia(SDL_Surface * &LoadImage,SDL_Surface* &screenSurface);
    void close(SDL_Surface * &LoadImage,SDL_Window*&window );
    void waitUntilKeyPressed();
    void ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y);
    bool checkCollision( const SDL_Rect& a,const SDL_Rect& b );
    bool checkCollision1( const SDL_Rect& a, const SDL_Rect & b );
}
#endif // COMMON_H
