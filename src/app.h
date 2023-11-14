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

typedef struct{
            SDL_Window *menuWindow;
            SDL_Renderer *menuRenderer;
            SDL_Window *gameWindow;
            SDL_Renderer *gameRenderer;
            int screenW;
            int screenH;
            TTF_Font* font;
            bool isGame;
            bool isMenu;
            Player player;
            Input input;
            SDL_Texture *backround;
            node* meteor_lista_head;
            SDL_Texture* meteor_texture;
            int latest_score;
            struct shot_node* shot_lista_head;
            SDL_Texture* shot_texture;
        }App;

/**
 * @brief Inicializálja a játék fõ struktúráját, létrehozza a renderereket,
 *ablakokat, megnyitja a textúrákat és a fontot. Inicializálja a láncolt listák fejét és
 *a legutóbbi pontszámot 0-ra állítja.
 * 
 * @param screenW a képernyõ szélessége (nem fullscreen mûködéshez szükséges)
 * @param screenH a képernyõ magassága (nem fullscreen mûködéshez szükséges)
 * @return App visszatér az inicializált struktúrával
 */
App init_App(int screenW , int screenH);

/**
 * @brief Futtatja a menüt. Meghívja runGame() -t, ha a játékos a játékot indító jelet adja.
 * 
 * @param app a játék törzsét alkotó struktúrára mutató pointer 
 */
void runMenu(App* app);

/**
 * @brief A játék futtatásáért felelõs. ha a játékos bezárja, visszatérés után a menüben folytatódik a játék.
 * 
 * @param app a játék törzsét alkotó struktúrára mutató pointer
 * 
 * @return visszatér a játékos adott sessionben elért pontszámával
 */
int runGame(App* app);


#endif