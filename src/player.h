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
 * @brief Inicializ�lja a j�t�kost.
 * 
 * 
 * @param x a j�t�kos kezd� x koordin�t�ja
 * @param y a j�t�kos kezd� y koordin�t�ja
 * @param health a j�t�kos kezd� �letereje
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param path a j�t�kos text�r�j�nak el�r�si �tja(char array)
 * @return Player visszat�r player-el, �rt�kak inicializ�lva.
 */
void init_player(int x , int y, int health , SDL_Renderer *renderer , char* path , Player* player);

/**
 * @file
 * @brief J�t�kos mozgat�s��rt felel�s f�ggv�ny
 * 
 * @param player inicializ�lt, mozgatand� j�t�kosra mutat� pointer
 * @param input bemeneteket kezel� struct
 */
void move_player(Player* player , Input input);
/**
 * @file
 * @brief Kezeli a billenty�k lenyom�s�t
 * 
 * @param input 
 * @param event 
 */
void keyDown(Input* input , SDL_KeyboardEvent* event);

/**
 * @file
 * @brief Kezeli a billenty�k felenged�s�t
 * 
 * @param input 
 * @param event 
 */
void keyUp(Input* input , SDL_KeyboardEvent* event);

void reset_input(Input* input);

void utkozes_ellenorzese(struct node* head , Player *player , int* meteorindex);
#endif