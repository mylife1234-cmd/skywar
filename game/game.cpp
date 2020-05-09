#include"Common.h"
#include"BaseObject.h"
#include"MainObject.h"
#include"Butllet.h"
#include"Threat.h"
#include"Boom.h"
#include"font.h"
#include"time.h"
using namespace std;
SDL_Window *window=NULL;
SDL_Surface *LoadImage=NULL;
SDL_Surface *screenSurface=NULL;
Mix_Chunk * soundButllet[2];
Mix_Chunk * soundBoom[2];
TTF_Font *fontText= NULL;
SDL_Surface * menuScreen=NULL;
int main(int argc, char *argv[])
{
    MainObject plane;
    int x_background=0;
    Time timer;
    if( !func::Init(SCREEN_WIDTH,SCREEN_HEIGHT,window,screenSurface,soundBoom,soundButllet) ) // Check Init
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
            //Load Plane
            plane.SetPreposition(400,300);
            bool check=plane.Loading("Fly (1).png",screenSurface);
            if(check==false){
                return 0;
            }
            plane.showObject(screenSurface);
            //Load frame explosion between plane and threat
            Boom ex_main;
            bool check3=ex_main.Loading("exp_main.png",screenSurface);
            ex_main.SetVideo();
            if(check3==false)
            {
                return 0;
            }
            //Load frame explosion between butllet and threat
            Boom ex_butllet;
            bool check4=ex_butllet.Loading("exp_main.png", screenSurface);
            if(check4==false)
            {
                return 0;
            }
            ex_butllet.SetVideo();
            //INIT THREAT
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
            unsigned int mark=0;
            bool again=false;
            bool menu_=func::ShowMenu(screenSurface,fontText,menuScreen,window,LoadImage);
            if(menu_ ==true)
            {
                quit=false;
            }
            unsigned int mark_high=0;
			//PUSH EVENT
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    else if(e.type==SDL_KEYDOWN)
                    {
                        if(e.key.keysym.sym==SDLK_SPACE && !timer.Started())
                        {
                            timer.start();
                        }
                        else if(e.key.keysym.sym==SDLK_BACKSPACE && timer.Started())
                        {
                            timer.stop();
                            timer.start();
                        }
                    }
                    plane.InputAction(e,screenSurface,soundButllet);
				}
				//SCROLLING BACKGROUND
				x_background-=3;
				func::ApplySurface(LoadImage,screenSurface,x_background,0);
				func::ApplySurface(LoadImage,screenSurface,x_background+SCREEN_WIDTH,0);
				if(x_background<= -SCREEN_WIDTH)
                {
                    x_background=0;
                }
                Font mark_game;
                Font time;
                Font highScore;
                //SHOW PLANE ON SCREEN
                plane.move(SCREEN_HEIGHT, SCREEN_WIDTH);
				plane.showObject(screenSurface);
				//INIT BUTLLET ON THE SCREEN
				for(int i=0; i< plane.GetListButllet().size(); i++)
                {
                    vector <Butllet*> listButllet = plane.GetListButllet();
                    Butllet* amo= listButllet.at(i);
                    if(amo!=NULL)
                    {
                        if(amo->ButlletMove())
                        {
                            amo->showObject(screenSurface);
                            amo->GetButlletMove(SCREEN_WIDTH,SCREEN_HEIGHT);
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
                //RUN THREAT
                for( int j=0; j<NUMBER_OF_THREAT; j++)
                {
                        Threat* planeThreat=(NumThreat+j);
                        if(planeThreat)
                        {
                            planeThreat->GetThreatMove(SCREEN_WIDTH,SCREEN_HEIGHT);
                            planeThreat->showObject(screenSurface);
                            //Check Collision between plane and threat
                            bool check1=func::checkCollision(plane.GetPrePosition(),planeThreat->GetPrePosition());
                            if(check1==true)
                            {
                                again=true;
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
                                if(again==true)
                                {
                                    //Check play again
                                    bool menu_exit=func::ShowMenu2(screenSurface,mark,fontText,menuScreen,window,LoadImage );
                                    if(menu_exit==true)
                                    {
                                        quit=false;
                                    }
                                     mark_high=mark;
                                     mark=0;
                                     planeThreat->resetThreat(SCREEN_WIDTH + j*RANGE);

                                }else{
                                    delete []NumThreat;
                                    func::close(LoadImage,window);
                                    IMG_Quit();
                                    SDL_Quit();
                                    return 1;
                                }
                            }
                            for(int jj=0; jj<plane.GetListButllet().size(); jj++)
                            {
                                vector <Butllet*> listButllet1 = plane.GetListButllet();
                                Butllet * p_amo=listButllet1.at(jj);
                                if(p_amo!=NULL)
                                {
                                    ////Check Collision between butllet and threat
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
                                         //RESET THREAT AND BUTLLET WHEN COLLISION
                                         planeThreat->resetThreat(SCREEN_WIDTH + j*RANGE);
                                         plane.RemoveButllet(jj);
                                         Mix_PlayChannel(-1,soundBoom[1],0);
                                    }
                                }

                            }
                        }
                }
                //SHOW HIGH SCORE
                string high_score("HIGH SCORE: ");
                string high_score1=to_string(mark_high);
                high_score+=high_score1;
                highScore.SetColor({255,255,0});
                highScore.SetText(high_score);
                highScore.drawText(screenSurface,20,200,40,fontText,"Aller_Bd.ttf");
                //SHOW SCORE
                string mark_score("SCORE: ");
                string mark_score1=to_string(mark);
                mark_score+=mark_score1;
                mark_game.SetColor({255,255,0});
                mark_game.SetText(mark_score);
                mark_game.drawText(screenSurface,20,200,10,fontText,"Aller_Bd.ttf");
                //SHOW TIME
                string timeDown="Time: ";
                string timeUp=to_string(timer.getTicks()/1000);
                timeDown+=timeUp;
                time.SetColor({255,0,0});
                time.SetText(timeDown);
                time.drawText(screenSurface,20,1000,10,fontText,"Aller_Bd.ttf");
                //CHECK PLAY AGAIN
                if(timer.getTicks()/1000==61)
                {
                    again=true;
                    Mix_PlayChannel(-1,soundBoom[0],0);
                    if(again==true)
                    {
                            bool menu_exit=func::ShowMenu2(screenSurface,mark,fontText,menuScreen,window,LoadImage);
                            if(menu_exit==true)
                            {
                                quit=false;
                            }
                            mark_high=mark;
                            mark=0;

                    }
                    else{
                        delete []NumThreat;
                        func::close(LoadImage,window);
                        IMG_Quit();
                        SDL_Quit();
                        return 1;
                    }
                }
                SDL_UpdateWindowSurface( window );
			}
		}
	}
    return 0;
}

