#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

/**
 * @brief sz�veget text�r�v� alak�t
 * 
 * @param font font amivel a sz�veget szeretn�nk ki�rni
 * @param text sz�veg amit ki�runk
 * @param renderer renderer amire ki�rjuk a sz�veget
 * @param pos SDL_Rect* poz�ci� ahov� a sz�veget ki�rjuk
 * @return SDL_Texture* a konvert�l�s v�geredm�nye
 */
SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);
/**
 * @brief sz�veget text�r�v� alak�t feh�r kijelz�shez
 * 
 * @param font font amivel a sz�veget szeretn�nk ki�rni
 * @param text sz�veg amit ki�runk
 * @param renderer renderer amire ki�rjuk a sz�veget
 * @param pos SDL_Rect* poz�ci� ahov� a sz�veget ki�rjuk
 * @return SDL_Texture* a konvert�l�s v�geredm�nye
 */
SDL_Texture* text_to_texture_white(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);

#endif