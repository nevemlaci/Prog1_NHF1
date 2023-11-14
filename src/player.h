#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_SPEED 3
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
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
 * @param path a játékos textúrájának elérési útja(char array)
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
 * @param input 
 * @param event 
 */
void keyDown(Input* input , SDL_KeyboardEvent* event);

/**
 * @file
 * @brief Kezeli a billentyûk felengedését
 * 
 * @param input 
 * @param event 
 */
void keyUp(Input* input , SDL_KeyboardEvent* event);

void reset_input(Input* input);

void utkozes_ellenorzese(struct node* head , Player *player , int* meteorindex);
#endif