#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "aszteroida.h"
#include "player.h" 

typedef struct{
            SDL_Window *menuWindow;
            SDL_Renderer *menuRenderer;
            SDL_Window *gameWindow;
            SDL_Renderer *gameRenderer;
            TTF_Font* font;
            bool isGame;
            bool isMenu;
            Player player;
            Input input;
            SDL_Texture *backround;
            node* meteor_lista_head;
            SDL_Texture* meteor_texture;
            int latest_score;
        }App;

App init_App(int screenW , int screenH);

/**
 * @brief Futtatja a men�t. Megh�vja runGame() -t, ha a j�t�kos a j�t�kot ind�t� jelet adja.
 * 
 * @param app a j�t�k t�rzs�t alkot� strukt�r�ra mutat� pointer
 */
void runMenu(App* app);

/**
 * @brief A j�t�k futtat�s��rt felel�s. ha a j�t�kos bez�rja, visszat�r�s ut�n a men�ben folytat�dik a j�t�k.
 * 
 * @param app a j�t�k t�rzs�t alkot� strukt�r�ra mutat� pointer
 */
int runGame(App* app);


#endif