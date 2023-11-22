#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct szoveg{
    SDL_Texture* texture;
    SDL_Rect pos;
}szoveg;

SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);

#endif