#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "font.h"
#include "defines.h"
#include <stdio.h>
#include <stdbool.h>

/// @brief rendereli a menü tartalmát amihez nem kell különösen sok adat(pl. latest score)
/// @param renderer menü rendererje
/// @param font használt font
/// @param username a játékos által megadott név
/// @param latestpoint legutóbb elért pontszám
/// @return 0 ha sikeres a konvertálás | -1 ha nem
int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint);

/// @brief rendereli a játékos számára a felhasználónév bekérés üzenetet
/// @param renderer menü rendererje
/// @param font használt font
/// @param username a játékos által megadott nevet tároló char tömb
void render_get_username(SDL_Renderer* renderer , TTF_Font* font , char* username);

/// @brief rendereli a play gombot
/// @param renderer menü rendererje
/// @param font használt font
/// @return 0 ha sikeres
int renderPlayButton(SDL_Renderer* renderer , TTF_Font* font);

/// @brief kiszámolja a play gomb méretét(kattintás ellenõrzéshez szükséges)
/// @param renderer menü rendererje
/// @param font használt font
/// @return SDL_Rect a gombot leíró téglatest 
SDL_Rect calculatePlayButtonSize(SDL_Renderer* renderer , TTF_Font* font);

/// @brief leelenõrzi hogy le lett -e nyomva a play gomb
/// @param play_pos  a gombot leíró téglatest 
/// @return ture ha lenyomták, flase ha nem
bool checkPlayButton(SDL_Rect* play_pos);

#endif