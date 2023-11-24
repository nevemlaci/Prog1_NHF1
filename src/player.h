#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "aszteroida.h"
#include "../lib/debugmalloc.h"
#include "defines.h"

//elõre deklaráció(valószínûleg eltávolítható, will fix)
struct node;

/// @brief jtáékos adatait tároló struktúra
typedef struct{
    /// @brief játékos mérete és koordinátái
    SDL_FRect position;
    /// @brief játékos textúrája
    SDL_Texture *texture;
    /// @brief játékos életereje
    /// @note currently partly unused 
    int health;
}Player;

/// @brief a játékbeli bemeneteket tároló struktúra
typedef struct{
    int up , down , left , right , menu;
}Input;

/**
 * 
 * @brief Inicializálja a játékost.
 * 
 * @param x a játékos kezdõ x koordinátája
 * @param y a játékos kezdõ y koordinátája
 * @param health a játékos kezdõ életereje
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param path a játékos textúrájának elérési útja(string)
 * @return Player | visszatér az inicializált játékossal
 */
void init_player(int x , int y, int health , SDL_Renderer *renderer , char* path , Player* player);

/**
 * @brief Játékos mozgatásáért felelõs függvény
 * 
 * @param player inicializált, mozgatandó játékosra mutató pointer
 * @param input bemeneteket tároló struct
 */
void move_player(Player* player , Input input , float deltaTime , int maxX , int maxY);
/**
 * @brief Kezeli a billentyûk lenyomását
 * 
 * @param input bemeneteket kezelõ structra pointer
 * @param event keyboardevent, ez alapján kapjuk meg milyen gomb(ok) lettek lenyomva
 */
void keyDown(Input* input , SDL_KeyboardEvent* event);

/**
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
 * @param head aszteroida lista fejére mutató pointer pointere
 * @param player játékos adatait tároló struktúra pointere
 * @return Meteor visszatér a meteorral ami eltalálta a játékost
 * @note jelenleg sok felesleges dolog van ebben a függvényben de késõbb tervem van velük
 */
Meteor utkozes_ellenorzese(struct node** head , Player *player);

#endif