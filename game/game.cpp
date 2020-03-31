#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const string WINDOW_TITLE = "SKY WAR";
bool Init();
bool LoadMedia();
void close();
void waitUntilKeyPressed();
SDL_Window *window=NULL;
SDL_Surface *screenSurface=NULL;
SDL_Surface *LoadImage=NULL;
int main(int argc, char *argv[])
{
    //Start up SDL and create window
    if(!Init())
    {
        cout << "Failed to initialize";
    }
    else{
        if(!LoadMedia())
        {
            cout << "Failed to load Image";
        }
        else{
            //Apply the image
            SDL_BlitSurface(LoadImage,NULL,screenSurface,NULL);
            //Update the surface
            SDL_UpdateWindowSurface(window);
            waitUntilKeyPressed();
        }
    }
    close();
    return 0;
}

bool Init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError();
        success=false;
    }
    else{
        //Create Window
        window=SDL_CreateWindow(WINDOW_TITLE.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            cout << "Window could not be created! SDL_Error:" << SDL_GetError();
            success=false;
        }
        else{
            //Create Surface
            screenSurface=SDL_GetWindowSurface(window);
        }
    }
    return success;
}
bool LoadMedia()
{
    bool success=true;
    LoadImage=IMG_Load("background.png");
    if(LoadImage==NULL)
    {
        cout << "Unable to load image" << SDL_GetError();
        success=false;
    }
    return success;

}
void close()
{
    //Deallocate surface
    SDL_FreeSurface(LoadImage);
    LoadImage=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
