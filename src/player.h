#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_SPEED 15
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "aszteroida.h"
#include "../lib/debugmalloc.h"

struct node;

typedef struct{
    SDL_FRect position;
    SDL_Texture *texture;
    int health;
}Player;

typedef struct{
    int up , down , left , right , menu;
}Input;
/**
 * @file
 * @brief Inicializálja a játékost.
 * 
 * 
 * @param x a játékos kezdõ x koordinátája
 * @param y a játékos kezdõ y koordinátája
 * @param health a játékos kezdõ életereje
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param path a játékos textúrájának elérési útja(string)
 * @return Player visszatér player-el, értékak inicializálva.
 */
void init_player(int x , int y, int health , SDL_Renderer *renderer , char* path , Player* player);

/**
 * @file
 * @brief Játékos mozgatásáért felelõs függvény
 * 
 * @param player inicializált, mozgatandó játékosra mutató pointer
 * @param input bemeneteket kezelõ struct
 */
void move_player(Player* player , Input input);
/**
 * @file
 * @brief Kezeli a billentyûk lenyomását
 * 
 * @param input bemeneteket kezelõ structra pointer
 * @param event keyboardevent, ez alapján kapjuk meg milyen gomb(ok) lettek lenyomva
 */
void keyDown(Input* input , SDL_KeyboardEvent* event);

/**
 * @file
 * @brief Kezeli a billentyûk felengedését
 * 
 * @param input bemeneteket kezelõ structra pointer
 * @param event keyboardevent, ez alapján kapjuk meg milyen gomb(ok) lettek felengedve
 */
void keyUp(Input* input , SDL_KeyboardEvent* event);

/**
 * @brief alaphelyzetbe állítja a bemenetet tároló struktúrát
 * 
 * @param input bemenetet tároló struktúrára pointer
 */
void reset_input(Input* input);

/**
 * @brief ellenõrzi hogy a játékost eltalálja -e egy aszteroida
 * 
 * @param head aszteroida lista fejére mutató pointer pointere (a függvény változtathatja head-et)
 * @param player játékos adatait tároló struktúra pointere 
 * @return Meteor visszatér a meteorral ami eltalálta a játékost
 */
Meteor utkozes_ellenorzese(struct node** head , Player *player);
#endif