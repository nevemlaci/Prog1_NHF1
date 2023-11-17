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
 * @brief Inicializ�lja a j�t�kost.
 * 
 * 
 * @param x a j�t�kos kezd� x koordin�t�ja
 * @param y a j�t�kos kezd� y koordin�t�ja
 * @param health a j�t�kos kezd� �letereje
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param path a j�t�kos text�r�j�nak el�r�si �tja(string)
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
 * @param input bemeneteket kezel� structra pointer
 * @param event keyboardevent, ez alapj�n kapjuk meg milyen gomb(ok) lettek lenyomva
 */
void keyDown(Input* input , SDL_KeyboardEvent* event);

/**
 * @file
 * @brief Kezeli a billenty�k felenged�s�t
 * 
 * @param input bemeneteket kezel� structra pointer
 * @param event keyboardevent, ez alapj�n kapjuk meg milyen gomb(ok) lettek felengedve
 */
void keyUp(Input* input , SDL_KeyboardEvent* event);

/**
 * @brief alaphelyzetbe �ll�tja a bemenetet t�rol� strukt�r�t
 * 
 * @param input bemenetet t�rol� strukt�r�ra pointer
 */
void reset_input(Input* input);

/**
 * @brief ellen�rzi hogy a j�t�kost eltal�lja -e egy aszteroida
 * 
 * @param head aszteroida lista fej�re mutat� pointer pointere (a f�ggv�ny v�ltoztathatja head-et)
 * @param player j�t�kos adatait t�rol� strukt�ra pointere 
 * @return Meteor visszat�r a meteorral ami eltal�lta a j�t�kost
 */
Meteor utkozes_ellenorzese(struct node** head , Player *player);
#endif