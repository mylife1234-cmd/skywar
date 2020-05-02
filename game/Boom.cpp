#include"Common.h"
#include"Boom.h"
Boom::Boom()
{
    fr=0;
}
Boom::~Boom()
{

}
void Boom::SetVideo()
{
    frame[ 0 ].x=0;
    frame[ 0 ].y=0;
    frame[ 0 ].w=165;
    frame[ 0 ].h=165;

    frame[ 1 ].x=FRAME_WIDTH/4;
    frame[ 1 ].y=0;
    frame[ 1 ].w=165;
    frame[ 1 ].h=165;

    frame[ 2 ].x=FRAME_WIDTH/2;
    frame[ 2 ].y=0;
    frame[ 2 ].w=165;
    frame[ 2 ].h=165;

    frame[ 3 ].x=(3*FRAME_WIDTH)/4;
    frame[ 3 ].y=0;
    frame[ 3 ].w=165;
    frame[ 3 ].h=165;

}
void Boom::ShowExplosion(SDL_Surface *&screenSurface)
{
    if(fr>4)
    {
        fr=0;
    }
    func::ApplySurface1(plane,screenSurface,&frame[fr],rect.x,rect.y);
}
