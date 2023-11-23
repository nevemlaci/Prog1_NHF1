#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct szoveg{
    SDL_Texture* texture;
    SDL_Rect pos;
}szoveg;

/**
 * @brief sz�veget text�r�v� alak�t
 * 
 * @param font font amivel a sz�veget szeretn�nk ki�rni
 * @param text sz�veg amit ki�runk
 * @param renderer renderer amire ki�rjuk a sz�veget
 * @param pos SDL_Rect* poz�ci� a
 * @return SDL_Texture* 
 */
SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);

#endif