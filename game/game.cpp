#include"Common.h"
#include"BaseObject.h"
#include"MainObject.h"
#include"Butllet.h"
#include"Threat.h"
#include"Boom.h"
#include"font.h"
using namespace std;
SDL_Window *window=NULL;
SDL_Surface *LoadImage=NULL;
SDL_Surface *Object=NULL;
SDL_Surface *screenSurface=NULL;
Mix_Chunk * soundButllet[2];
Mix_Chunk * soundBoom[2];
TTF_Font *fontText= NULL;
int main(int argc, char *argv[])
{
    MainObject plane;
    int x_background=0;
    if( !func::Init(SCREEN_WIDTH,SCREEN_HEIGHT,window,screenSurface,soundBoom,soundButllet) )
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
			SDL_Event e;
            plane.SetPreposition(400,300);
            bool check=plane.Loading("Fly (1).png",screenSurface);
            if(check==false){
                return 0;
            }
            Boom ex_main;
            bool check3=ex_main.Loading("exp_main.png",screenSurface);
            ex_main.SetVideo();
            if(check3==false)
            {
                return 0;
            }
            Boom ex_butllet;
            bool check4=ex_butllet.Loading("exp_main.png", screenSurface);
            if(check4==false)
            {
                return 0;
            }
            ex_butllet.SetVideo();
            Threat *NumThreat=new Threat[NUMBER_OF_THREAT];
            for(int i=0; i<NUMBER_OF_THREAT; i++)
            {
                Threat * planeThreat=(NumThreat+i);
                planeThreat->Loading("af1.png",screenSurface);
                int randomPreposition=rand()%RANGE;
                if(randomPreposition>RANGE)
                {
                randomPreposition=SCREEN_HEIGHT*(0.4);
                }
                planeThreat->SetPreposition(SCREEN_WIDTH+i*RANGE, randomPreposition);
            }
            plane.showObject(screenSurface);
            unsigned int mark=0;
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					plane.InputAction(e,screenSurface,soundButllet);
				}
				x_background-=3;
				func::ApplySurface(LoadImage,screenSurface,x_background,0);
				func::ApplySurface(LoadImage,screenSurface,x_background+SCREEN_WIDTH,0);
				if(x_background<= -SCREEN_WIDTH)
                {
                    x_background=0;
                }
                //Mark Game
                Font mark_game;
                mark_game.SetColor();
                plane.move(SCREEN_HEIGHT, SCREEN_WIDTH);
				plane.showObject(screenSurface);
				for(int i=0; i< plane.GetListButllet().size(); i++)
                {
                    vector <Butllet*> listButllet = plane.GetListButllet();
                    Butllet* amo= listButllet.at(i);
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
                                listButllet.erase(listButllet.begin() + i);
                                plane.SetListBullet(listButllet);
                                delete amo;
                                amo=NULL;
                            }
                        }
                    }
                }
                for( int j=0; j<NUMBER_OF_THREAT; j++)
                {
                        Threat* planeThreat= (NumThreat+j);
                        if(planeThreat)
                        {
                            planeThreat->GetThreatMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                            planeThreat->showObject(screenSurface);
                            bool check1=func::checkCollision(plane.GetPrePosition(),planeThreat->GetPrePosition());
                            if(check1==true)
                            {
                                for(int ee=0; ee<4; ee++)
                                {
                                        int x_boom=((plane.GetPrePosition()).x + (planeThreat->GetPrePosition()).w*0.5)-FRAME_HEIGHT*0.5;
                                        int y_boom=((plane.GetPrePosition()).y + (planeThreat->GetPrePosition()).h*0.5)-FRAME_HEIGHT*0.5;
                                        ex_main.SetPreposition(x_boom,y_boom);
                                        ex_main.SetFrame(ee);
                                        SDL_Delay(100);
                                        ex_main.ShowExplosion(screenSurface);
                                        SDL_UpdateWindowSurface( window );

                                }
                                Mix_PlayChannel(-1,soundBoom[0],0);
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Info","Game Over!",NULL);
                                delete []NumThreat;
                                func::close(LoadImage,window);
                                IMG_Quit();
                                SDL_Quit();
                                return 1;
                            }
                            for(int jj=0; jj<plane.GetListButllet().size(); jj++)
                            {
                                vector <Butllet*> listButllet1 = plane.GetListButllet();
                                Butllet * p_amo=listButllet1.at(jj);
                                if(p_amo!=NULL)
                                {
                                    bool check2=func::checkCollision(p_amo->GetPrePosition(),planeThreat->GetPrePosition());
                                    if(check2==true){
                                        mark++;
                                         for(int ee1=0; ee1<4; ee1++)
                                        {
                                            int x_boom1=((p_amo->GetPrePosition()).x + (planeThreat->GetPrePosition()).w*0.5)-FRAME_HEIGHT*0.5;
                                            int y_boom1=((p_amo->GetPrePosition()).y + (planeThreat->GetPrePosition()).h*0.5)-FRAME_HEIGHT*0.5;
                                            ex_butllet.SetPreposition(x_boom1,y_boom1);
                                            ex_butllet.SetFrame(ee1);
                                            ex_butllet.ShowExplosion(screenSurface);
                                            SDL_UpdateWindowSurface( window );

                                        }
                                         planeThreat->resetThreat(SCREEN_WIDTH + j*RANGE);
                                         plane.RemoveButllet(jj);
                                         Mix_PlayChannel(-1,soundBoom[1],0);
                                    }
                                }

                            }
                        }
                }
                string mark_score("Score: ");
                string mark_score1=to_string(mark);
                mark_score+=mark_score1;
                mark_game.SetFont(mark_score);
                SDL_Color color1={255,255,0};
                mark_game.drawText(screenSurface,mark_score,20,500,10,color1,fontText,"Aller_Bd.ttf");
                SDL_UpdateWindowSurface( window );
			}
		}
	}
    return 0;
}

