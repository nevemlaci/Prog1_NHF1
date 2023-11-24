#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "aszteroida.h"
#include "player.h"
#include "shoot.h"
#include "ranglista.h"
#include "defines.h"
#include "font.h"
#include "../lib/debugmalloc.h"
#include "menu.h"
#include "file.h"
#include "clock.h"

typedef struct{
    char username[51];
    SDL_Window *menuWindow;
    SDL_Renderer *menuRenderer;
    SDL_Window *gameWindow;
    SDL_Renderer *gameRenderer;
    int screenW;
    int screenH;
    TTF_Font* font;
    TTF_Font* font_big;
    bool isMenu;
    bool isGame;
    Player player;
    Input input;
    SDL_Texture *backround;
    node* meteor_lista_head;
    SDL_Texture* meteor_texture;
    int latest_score;
    shot_node* shot_lista_head;
    SDL_Texture* shot_texture;
    ranglista_node* ranglista_head;

    Clock clock;
    Spawn_clock spawn_clock;

    int targetFPS;
}App;

/**
 * @brief Inicializ�lja a j�t�kadatok strukt�r�j�t, l�trehozza a renderereket,
 *ablakokat, megnyitja a text�r�kat �s a fontot. Inicializ�lja a l�ncolt list�k fej�t �s
 *a legut�bbi pontsz�mot 0-ra �ll�tja stb.
 * 
 * @param screenW a k�perny� sz�less�ge (nem fullscreen m�k�d�shez sz�ks�ges)
 * @param screenH a k�perny� magass�ga (nem fullscreen m�k�d�shez sz�ks�ges)
 * @return App visszat�r az inicializ�lt strukt�r�val
 */
App init_App(int screenW , int screenH);

/**
 * @brief Futtatja a men�t. Megh�vja runGame() -t, ha a j�t�kos a j�t�kot ind�t� jelet adja.
 * 
 * @param app a j�t�k adatait tartalmaz� strukt�r�ra mutat� pointer 
 */
void runMenu(App* app);

/**
 * @brief A j�t�k futtat�s��rt felel�s. ha a j�t�kos bez�rja, visszat�r�s ut�n a men�ben folytat�dik a j�t�k.
 * 
 * @param app a j�t�k adatait tartalmaz� strukt�r�ra mutat� pointer 
 * 
 * @return visszat�r a j�t�kos adott sessionben el�rt pontsz�m�val
 */
int runGame(App* app);

void resetGame(App* app);

#endif