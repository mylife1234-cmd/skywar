#include"Common.h"
#include"font.h"
Font::Font()
{
    rect.x=500;
    rect.y=10;
    color.r=255;
    color.g=255;
    color.b=255;
    rect.w=0;
    rect.h=0;
}
Font::~Font()
{

}
//SET COLOR FOR TEXT
void Font::SetColor(SDL_Color textColor)
{
    color=textColor;
}
//DRAW TEXT ON SCREEN
void Font::drawText(SDL_Surface *background, int size, int x, int y, TTF_Font *&font, std::string fontname)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    font=TTF_OpenFont(fontname.c_str(),size);
    plane=TTF_RenderText_Solid(font, text.c_str(),color);
    if(plane==NULL)
    {
        cout << "Not" << SDL_GetError();
    }
    TTF_SizeText(font,text.c_str(),&offset.w,&offset.h);
    SDL_BlitSurface(plane,NULL,background,&offset);
}


