#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
using namespace std;
const int SCREEN_WIDTH=1200;
const int SCREEN_HEIGHT=600;
const string WINDOW_TITLE = "SKY WAR";
bool Init();
bool LoadMedia();
void close();
void waitUntilKeyPressed();
void ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y);
SDL_Surface *LoadSurface(std::string path);
SDL_Window *window=NULL;
SDL_Surface *screenSurface=NULL;
SDL_Surface *LoadImage=NULL;
SDL_Surface *Object=NULL;
int main(int argc, char *argv[])
{
    if( !Init() )
	{
		cout << "Failed to initialize!\n" ;
	}
	else
	{
		if( !LoadMedia() )
		{
			cout << "Failed to initialize!\n" ;
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

				}
                SDL_Rect strectchRect;
                strectchRect.x=0;
                strectchRect.y=0;
                strectchRect.w=SCREEN_WIDTH;
                strectchRect.h=SCREEN_HEIGHT;
                SDL_BlitScaled(LoadImage,NULL,screenSurface, &strectchRect);
                Object=LoadSurface("plane80.png");
                if(Object==NULL) return 0;
                ApplySurface(Object,LoadImage,200, 300);
				//Update the surface
				SDL_UpdateWindowSurface( window );
			}
		}
	}

	//Free resources and close SDL
	close();
    return 0;
}

bool Init()
{
    bool success=true;
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
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
            //Initialize PNG loading
            int imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)& imgFlags) )
            {
                cout << "SDL_image could not initialize" << IMG_GetError();
                success=false;
            }
            else{
                screenSurface=SDL_GetWindowSurface(window);
            }
        }
    }
    return success;
}
bool LoadMedia()
{
    bool success=true;
    LoadImage=LoadSurface("bg2.png");
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
SDL_Surface *LoadSurface(std::string path)
{
    SDL_Surface *optimizedSurface=NULL;
    SDL_Surface *loadedSurface=IMG_Load(path.c_str());
    if(loadedSurface==NULL)
    {
        cout << "Unable to load image" << path.c_str() << SDL_GetError();
    }
    else{
        optimizedSurface=SDL_ConvertSurface(loadedSurface,screenSurface->format,0);
        if(optimizedSurface==NULL)
        {
            cout << "Unable to load optimized image" << SDL_GetError();
        }
        SDL_FreeSurface(loadedSurface);
        if (optimizedSurface != NULL)
        {
            Uint32 color_key = SDL_MapRGB(optimizedSurface->format, 0, 0xFF, 0xFF);
            SDL_SetColorKey(optimizedSurface,SDL_TRUE, color_key);
        }
    }
    return optimizedSurface;
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
void ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y)
{
    SDL_Rect set;
    set.x=x;
    set.y=y;
    SDL_BlitSurface(object,NULL,background,&set);
}
