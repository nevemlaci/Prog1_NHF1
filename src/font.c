#include "font.h"

SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos){
    SDL_Color black = {0, 0, 0};
    SDL_Surface* textsurface = TTF_RenderText_Blended(font , text , black);
    pos->w = textsurface->w;
    pos->h = textsurface->h;
    SDL_Texture* retval = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    return retval;
}