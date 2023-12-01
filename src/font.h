#ifndef FONT_H
#define FONT_H

#include <SDL.h>
#include <SDL_ttf.h>

/**
 * @brief szöveget textúrává alakít
 * 
 * @param font font amivel a szöveget szeretnénk kiírni
 * @param text szöveg amit kiírunk
 * @param renderer renderer amire kiírjuk a szöveget
 * @param pos SDL_Rect* pozíció ahová a szöveget kiírjuk
 * @return SDL_Texture* a konvertálás végeredménye
 */
SDL_Texture* text_to_texture(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);
/**
 * @brief szöveget textúrává alakít fehér kijelzéshez
 * 
 * @param font font amivel a szöveget szeretnénk kiírni
 * @param text szöveg amit kiírunk
 * @param renderer renderer amire kiírjuk a szöveget
 * @param pos SDL_Rect* pozíció ahová a szöveget kiírjuk
 * @return SDL_Texture* a konvertálás végeredménye
 */
SDL_Texture* text_to_texture_white(TTF_Font* font, char* text, SDL_Renderer* renderer, SDL_Rect* pos);

#endif