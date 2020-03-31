#include<iostream>
#include<SDL.h>
using namespace std;
void logSDLError(ostream& os, const string &msg, bool fatal =false)
{
    os << msg << "Error: " << SDL_GetError() << endl;
    if(fatal)
    {
        SDL_Quit();
        exit(1);
    }
}
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT =600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";
void initSDL(SDL_Window* &window, SDL_Renderer* & renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,         //dung cho may that
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,           // dung cho may ao
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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

int main(int argc, char*argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filledRect;
    filledRect.x=150;
    filledRect.y=150;
    filledRect.h=100;
    filledRect.w=150;
    SDL_SetRenderDrawColor(renderer,255,0,255,255);
    SDL_RenderFillRect(renderer, &filledRect);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;

}
