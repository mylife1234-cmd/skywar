#include"Common.h"
#include"font.h"
//FUNTION CHECK AND INIT WINDOW,IMAGE,MUSIC AND FONT
bool func::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Window* &window, SDL_Surface* &screenSurface,Mix_Chunk *soundBoom[2], Mix_Chunk *soundButllet[2])
{
    //************************************
	//	1. Check and initialize window
	//	2. Check and initialize image
	//	3.Check and initialize music
	//	4. Check and initialize font
	//************************************
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
//CHECK AND LOAD BACKGROUND ON THE SCREEN
bool func::LoadMedia(SDL_Surface *&LoadImage,SDL_Surface * &screenSurface)
{
    bool success=true;
    LoadImage=LoadSurface("bg1.png",screenSurface);
    if(LoadImage==NULL)
    {
        cout << "Unable to load image" << SDL_GetError();
        success=false;
    }
    return success;

}
//FREE SURFACE
void func::close(SDL_Surface * &LoadImage,SDL_Window*&window )
{
    //Deallocate surface
    SDL_FreeSurface(LoadImage);
    LoadImage=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();
}
//LOAD OPTIMIZE BACKGROUND
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
//CHECK COLLISION BETWEEN PLANE AND THREAT, BUTLLET AND THREAT
bool func::checkCollision( const SDL_Rect& a, const SDL_Rect & b )
{
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    // Case 1: size object 1 < size object 2
    if (leftA+PLANE_WIDTH > leftB && leftA < rightB)
    {
        if (topA+PLANE_HEIGHT > topB && topA < bottomB)
        {
            return true;
        }
    }

    if (leftA+PLANE_WIDTH > leftB && leftA < rightB)
    {
        if (bottomA > topB && bottomA < bottomB)
        {
          return true;
        }
    }

    if (rightA > leftB && rightA < rightB)
    {
        if (topA > topB && topA < bottomB)
        {
          return true;
        }
    }

    if (rightA > leftB && rightA < rightB)
    {
        if (bottomA > topB && bottomA < bottomB)
        {
          return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (leftB+PLANE_WIDTH > leftA && leftB < rightA)
    {
        if (topB+PLANE_HEIGHT > topA && topB < bottomA)
        {
          return true;
        }
    }

    if (leftB+PLANE_WIDTH > leftA && leftB < rightA)
    {
        if (bottomB > topA && bottomB < bottomA)
        {
          return true;
        }
    }

    if (rightB > leftA && rightB < rightA)
    {
        if (topB > topA && topB < bottomA)
        {
          return true;
        }
    }

    if (rightB > leftA && rightB < rightA)
    {
        if (bottomB > topA && bottomB < bottomA)
        {
          return true;
        }
    }

       // Case 3: size object 1 = size object 2
    if (topA == topB && rightA == rightB && bottomA == bottomB)
    {
        return true;
    }
    return false;
}

//APPLY FRAME ON THE SCREEN
void func::ApplySurface1(SDL_Surface*object,SDL_Surface*background,SDL_Rect *frame, int x, int y)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    SDL_BlitSurface(object,frame,background,&offset);
}
//SHOW MENU START ON THE SCREEN
bool func::ShowMenu(SDL_Surface*background, TTF_Font *textFont,SDL_Surface*menuScreen, SDL_Window *window)
{
    //************************************
	//	1. Set Preposition for menu
	//	2. Input keyboard event
	//	3. If press double space, game start
	//************************************
    menuScreen=LoadSurface("menu.png", background);
    if(menuScreen==NULL)
    {
        return 1;
    }
    SDL_Rect menuItem;
    menuItem.x=150;
    menuItem.y=550;

    Font textMenu;
    textMenu.SetText("PRESS DOUBLE SPACE TO START");
    textMenu.SetColor({255,255,0});
    SDL_Event e;
    while(true){
        func::ApplySurface(menuScreen,background,0,0);
        textMenu.drawText(background,70,menuItem.x,menuItem.y,textFont,"Aller_Bd.ttf");
        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_KEYDOWN)
            {

                if(e.key.keysym.sym==SDLK_SPACE)
                {
                    return true;
                }
                else if(e.key.keysym.sym==SDLK_ESCAPE)
                {
                    return 0;
                }


            }
            if(e.type==SDL_QUIT)
            {
                return 0;
            }
        }
        SDL_UpdateWindowSurface(window);
    }
    return false;
}
//SHOW MENU PLAY AGAIN WHEN YOU LOSE
bool func::ShowMenu2(SDL_Surface*background,int score, TTF_Font *textFont, SDL_Surface *menuScreen,SDL_Window*window,SDL_Surface*LoadImage)
{
    //************************************
	//	1. Set Preposition for menu
	//	2. Input keyboard event
	//	3. If press double backspace, game start
	//************************************
    menuScreen=LoadSurface("EXIT.png", background);
    if(menuScreen==NULL)
    {
        return 1;
    }
    SDL_Rect menuItem;

    menuItem.x=350;
    menuItem.y=300;
    Font textMenu;
    std::string highscore("YOUR HIGH SCORE: ");
    std::string highscore1=to_string(score);
    highscore+=highscore1;
    textMenu.SetText(highscore);
    textMenu.SetColor({255,255,0});
    SDL_Rect playAgain;
    playAgain.x=80;
    playAgain.y=550;
    Font play;
    play.SetText("PRESS DOUBLE BACKSPACE TO PLAY AGAIN");
    SDL_Event e;
    while(true){
        func::ApplySurface(menuScreen,background,0,0);
        textMenu.drawText(background,60,menuItem.x,menuItem.y,textFont,"Aller_Bd.ttf");
        play.drawText(background,60,playAgain.x, playAgain.y, textFont,"Aller_Bd.ttf");
        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_KEYDOWN)
            {
                if(e.key.keysym.sym==SDLK_BACKSPACE)
                {

                    return true;
                }
                if(e.key.keysym.sym==SDLK_ESCAPE)
                {

                    return 0;
                }
            }

            if(e.type==SDL_QUIT)
            {
                func::close(LoadImage,window);
                    TTF_Quit();
                    IMG_Quit();
                    SDL_Quit();
                return 0;
            }
        }
        SDL_UpdateWindowSurface(window);
    }
}
