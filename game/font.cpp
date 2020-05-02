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
void Font::SetColor()
{
    SDL_Color textColor ={255,255,0};
    color=textColor;
}
void Font::drawText(SDL_Surface *background, std::string text_, int size, int x, int y, SDL_Color Textcolor, TTF_Font *&font, std::string fontname)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;
    font=TTF_OpenFont(fontname.c_str(),size);
    plane=TTF_RenderText_Solid(font, text_.c_str(),Textcolor);
    if(plane==NULL)
    {
        cout << "Not" << SDL_GetError();
    }
    TTF_SizeText(font,text_.c_str(),&rect.w,&rect.h);
    SDL_BlitSurface(plane,NULL,background,&offset);
}


