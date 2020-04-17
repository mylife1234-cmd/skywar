#include"Common.h"

bool func::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window*&window, SDL_Surface* &screenSurface)
{
    bool success=true;
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
    {
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError();
        success=false;
    }
    else{
        //Create Window
        window=SDL_CreateWindow("Sky War",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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
bool func::LoadMedia(SDL_Surface * &LoadImage,SDL_Surface* &screenSurface)
{
    bool success=true;
    LoadImage=LoadSurface("bg2.png",screenSurface);
    if(LoadImage==NULL)
    {
        cout << "Unable to load image" << SDL_GetError();
        success=false;
    }
    return success;

}
void func::close(SDL_Surface * &LoadImage,SDL_Window*&window )
{
    //Deallocate surface
    SDL_FreeSurface(LoadImage);
    LoadImage=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();
}
SDL_Surface * LoadSurface(std::string path,SDL_Surface *&screenSurface)
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
            Uint32 color_key = SDL_MapRGB(optimizedSurface->format, 0, 255, 255);
            SDL_SetColorKey(optimizedSurface,SDL_TRUE, color_key);
        }
    }
    return optimizedSurface;
}
void func::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void func::ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y)
{
    SDL_Rect set;
    set.x=x;
    set.y=y;
    SDL_BlitSurface(object,NULL,background,&set);
}
bool func::checkCollision( const SDL_Rect& a, const SDL_Rect & b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
//Here is where the collision detection happens. This code calculates the top/bottom and left/right of each of the collison boxes.
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

     if( topA >=bottomB )
    {
        return false;
    }

     if( rightA+A <= leftB )
    {
        return false;
    }

     if( leftA>= rightB )
    {
        return false;
    }

        return true;

    //If none of the sides from A are outside
}
bool func::checkCollision1( const SDL_Rect& a, const SDL_Rect & b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
//Here is where the collision detection happens. This code calculates the top/bottom and left/right of each of the collison boxes.
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >=bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA>= rightB )
    {
        return false;
    }
        return true;

    //If none of the sides from A are outside
}

