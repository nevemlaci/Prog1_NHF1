#include "font.h"

SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos){
    SDL_Color black = {0, 0, 0};
    SDL_Surface* textsurface = TTF_RenderUTF8_Blended(font , text , black);

    pos->w = textsurface->w;
    pos->h = textsurface->h;
    SDL_Texture* retval = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    return retval;
}

SDL_Texture* text_to_texture_white(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos){
    SDL_Color white = {255, 255, 255};
    SDL_Surface* textsurface = TTF_RenderUTF8_Blended(font , text , white);
    pos->w = textsurface->w;
    pos->h = textsurface->h;
    SDL_Texture* retval = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_FreeSurface(textsurface);
    return retval;
}