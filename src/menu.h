#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "font.h"
#include "defines.h"
#include <stdio.h>
#include <stdbool.h>

/// @brief rendereli a men� tartalm�t amihez nem kell k�l�n�sen sok adat(pl. latest score)
/// @param renderer men� rendererje
/// @param font haszn�lt font
/// @param username a j�t�kos �ltal megadott n�v
/// @param latestpoint legut�bb el�rt pontsz�m
/// @return 0 ha sikeres a konvert�l�s | -1 ha nem
int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint);

/// @brief rendereli a j�t�kos sz�m�ra a felhaszn�l�n�v bek�r�s �zenetet
/// @param renderer men� rendererje
/// @param font haszn�lt font
/// @param username a j�t�kos �ltal megadott nevet t�rol� char t�mb
void render_get_username(SDL_Renderer* renderer , TTF_Font* font , char* username);

/// @brief rendereli a play gombot
/// @param renderer men� rendererje
/// @param font haszn�lt font
/// @return 0 ha sikeres
int renderPlayButton(SDL_Renderer* renderer , TTF_Font* font);

/// @brief kisz�molja a play gomb m�ret�t(kattint�s ellen�rz�shez sz�ks�ges)
/// @param renderer men� rendererje
/// @param font haszn�lt font
/// @return SDL_Rect a gombot le�r� t�glatest 
SDL_Rect calculatePlayButtonSize(SDL_Renderer* renderer , TTF_Font* font);

/// @brief leelen�rzi hogy le lett -e nyomva a play gomb
/// @param play_pos  a gombot le�r� t�glatest 
/// @return ture ha lenyomt�k, flase ha nem
bool checkPlayButton(SDL_Rect* play_pos);

#endif