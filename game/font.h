#ifndef FONT__H
#define FONT__H
#include"BaseObject.h"
#include<cstring>
struct Font:Baseobject
{
    std::string text;
    SDL_Color color;
    SDL_Texture *mTexture;
    Font();
    ~Font();
    void SetFont(const string&text1)
    {
        text=text1;
    }
    void SetColor();
    void drawText(SDL_Surface *background, std::string text_, int size, int x, int y, SDL_Color Textcolor,TTF_Font *&font, std::string fontname);
};
#endif // FONT__H

