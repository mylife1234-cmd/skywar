#include"Common.h"

bool func::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window*&window, SDL_Surface* &screenSurface,Mix_Chunk *soundBoom[2], Mix_Chunk *soundButllet[2])
{
    bool success=true;
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
    {
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError();
        success=false;
    }
    else{
        //Create Window
        window=SDL_CreateWindow(WINDOW_TITLE.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL);
        if(window==NULL)
        {
            cout << "Window could not be created! SDL_Error:" << SDL_GetError();
            success=false;
        }
        else{
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
    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)
    {
        success=false;
    }
    soundBoom[0]=Mix_LoadWAV("Explosion+3.wav");
    soundBoom[1]=Mix_LoadWAV("Explosion+6.wav");
    soundButllet[0]=Mix_LoadWAV("Gun+Silencer.wav");
    if(soundBoom[0]==NULL || soundButllet[0]==NULL || soundBoom[1]==NULL)
    {
        success=false;
    }
    if(TTF_Init()==-1)
    {
        return false;
    }
    return success;
}
bool func::LoadMedia(SDL_Surface *&LoadImage,SDL_Surface * &screenSurface)
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
void func::ApplySurface(SDL_Surface*object, SDL_Surface*background, int x, int y)
{
    SDL_Rect set;
    set.x=x;
    set.y=y;
    SDL_BlitSurface(object,NULL,background,&set);
}
bool func::checkCollision( const SDL_Rect& object1, const SDL_Rect & object2 )
{
    int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}
void func::ApplySurface1(SDL_Surface*object,SDL_Surface*background,SDL_Rect *frame, int x, int y)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface(object,frame,background,&offset);
}

