#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct szoveg{
    SDL_Texture* texture;
    SDL_Rect pos;
}szoveg;

/**
 * @brief szöveget textúrává alakít
 * 
 * @param font font amivel a szöveget szeretnénk kiírni
 * @param text szöveg amit kiírunk
 * @param renderer renderer amire kiírjuk a szöveget
 * @param pos SDL_Rect* pozíció a
 * @return SDL_Texture* 
 */
SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);

#endif