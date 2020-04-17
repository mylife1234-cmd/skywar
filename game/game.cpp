#include"Common.h"
#include"BaseObject.h"
#include"MainObject.h"
#include"Butllet.h"
#include"Threat.h"
using namespace std;
const int SCREEN_WIDTH=1200;
const int SCREEN_HEIGHT=600;
const string WINDOW_TITLE = "SKY WAR";
const int NUMBER_OF_THREAT=6;
SDL_Surface *LoadSurface(std::string path);
SDL_Window *window=NULL;
SDL_Surface *LoadImage=NULL;
SDL_Surface *Object=NULL;
SDL_Surface *screenSurface=NULL;
int main(int argc, char *argv[])
{
    MainObject plane;
    int x_background=0;
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
            plane.SetPreposition(400,400);
            bool check=plane.Loading("Fly (1).png",screenSurface);
            if(check==false){
                return 0;
            }
            Threat *NumThreat=new Threat[NUMBER_OF_THREAT];
            for(int i=0; i<NUMBER_OF_THREAT; i++)
            {
                Threat * planeThreat=(NumThreat+i);
                planeThreat->Loading("af1.png",screenSurface);
                int randomPreposition=rand()%400;
                if(randomPreposition>400)
                {
                randomPreposition=SCREEN_HEIGHT*(0.4);
                }
                planeThreat->SetPreposition(SCREEN_WIDTH+i*400, randomPreposition);
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
					plane.InputAction(e,screenSurface);
				}
				x_background-=2;
				func::ApplySurface(LoadImage,screenSurface,x_background,0);
				func::ApplySurface(LoadImage,screenSurface,x_background+SCREEN_WIDTH,0);
				if(x_background<= -SCREEN_WIDTH)
                {
                    x_background=0;
                }
				plane.showObject(screenSurface);
				plane.move(SCREEN_HEIGHT, SCREEN_WIDTH);
				for(int ii=0; ii< plane.GetListButllet().size(); ii++)
                {
                    vector <Butllet*> listButllet = plane.GetListButllet();
                    Butllet* amo= listButllet.at(ii);
                    if(amo!=NULL)
                    {
                        if(amo->ButlletMove())
                        {
                            amo->GetButlletMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                            amo->showObject(screenSurface);
                        }
                        else{
                            if(amo!=NULL)
                            {
                                listButllet.erase(listButllet.begin() + ii);
                                plane.SetListBullet(listButllet);
                                delete amo;
                                amo=NULL;
                            }
                        }
                    }
                }
                int j,k;
                k=j;
                for( j=0; j<NUMBER_OF_THREAT; j++)
                {
                        Threat* planethreat= (NumThreat+j);
                        if(planethreat)
                        {
                            planethreat->GetThreatMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                            planethreat->showObject(screenSurface);
                        }
                }
                for( k=0; k<NUMBER_OF_THREAT; k++)
                {
                    Threat *planethreat=(NumThreat+k);
                     if(planethreat)
                     {
                            bool check1=func::checkCollision(plane.GetPrePosition(),planethreat->GetPrePosition());
                            if(check1==true)
                            {
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Info","Game Over!",NULL);
                                delete []NumThreat;
                                SDL_Quit();
                            }
                            vector <Butllet*> listButllet1=plane.GetListButllet();
                            for(int jj=0; jj<listButllet1.size(); jj++)
                            {
                                Butllet * p_amo=listButllet1.at(jj);
                                bool check2=func::checkCollision1(p_amo->GetPrePosition(),planethreat->GetPrePosition());
                                {
                                    if(check2==true)
                                    {
                                        plane.RemoveButllet(jj);
                                        planethreat->resetThreat(SCREEN_WIDTH + k*400);
                                    }
                                }
                            }
                     }
                }
                SDL_UpdateWindowSurface( window );
			}
		}
	}

	//Free resources and close SDL
	func::close(LoadImage,window);
    return 0;
}

