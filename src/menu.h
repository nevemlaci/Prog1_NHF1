#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "font.h"
#include "defines.h"
#include <stdio.h>
#include <stdbool.h>

int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint);

void render_get_username(SDL_Renderer* renderer , TTF_Font* font , char* username);

int renderPlayButton(SDL_Renderer* renderer , TTF_Font* font);

SDL_Rect calculatePlayButtonSize(SDL_Renderer* renderer , TTF_Font* font);

bool checkPlayButton(SDL_Rect* play_pos);

#endif