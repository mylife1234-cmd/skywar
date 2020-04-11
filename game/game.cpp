#include"Common.h"
#include"BaseObject.h"
#include"MainObject.h"
using namespace std;
const int SCREEN_WIDTH=1200;
const int SCREEN_HEIGHT=600;
const string WINDOW_TITLE = "SKY WAR";
SDL_Surface *LoadSurface(std::string path);
SDL_Window *window=NULL;
SDL_Surface *LoadImage=NULL;
SDL_Surface *Object=NULL;
SDL_Surface *screenSurface=NULL;
int main(int argc, char *argv[])
{
    MainObject plane;
    if( !func::Init(SCREEN_WIDTH,SCREEN_HEIGHT,window,screenSurface) )
	{
		cout << "Failed to initialize!\n" ;
	}
	else
	{
		if( !func::LoadMedia(LoadImage,screenSurface) )
		{
			cout << "Failed to initialize!\n" ;
		}
		else
		{
			bool quit = false;
			SDL_Rect strectchRect;
                strectchRect.x=0;
                strectchRect.y=0;
                strectchRect.w=SCREEN_WIDTH;
                strectchRect.h=SCREEN_HEIGHT;
                SDL_BlitScaled(LoadImage,NULL,screenSurface, &strectchRect);
			SDL_Event e;
            plane.setPreposion(400,300);
            bool check=plane.Loading("plane80.png",screenSurface);
            if(check==false){
                return 0;
            }
            plane.showObject(screenSurface);
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					plane.InputAction(e);
				}
				func::ApplySurface(LoadImage,screenSurface,0,0);
				plane.showObject(screenSurface);
				plane.move(SCREEN_HEIGHT, SCREEN_WIDTH);
				SDL_UpdateWindowSurface( window );
			}
		}
	}

	//Free resources and close SDL
	func::close(LoadImage,window);
    return 0;
}

