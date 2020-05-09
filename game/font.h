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
    void SetText(const std::string &text1)
    {
        text=text1;
    }
    void SetColor(SDL_Color textColor);
    void drawText(SDL_Surface *background, int size, int x, int y, TTF_Font *&font, std::string fontname);
};
#endif // FONT__H

