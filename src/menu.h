#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "font.h"
#include "defines.h"
#include <stdio.h>

int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint);

#endif