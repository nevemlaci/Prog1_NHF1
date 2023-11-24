#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "aszteroida.h"
#include "../lib/debugmalloc.h"
#include "defines.h"

//el�re deklar�ci�(val�sz�n�leg elt�vol�that�, will fix)
struct node;

/// @brief jt��kos adatait t�rol� strukt�ra
typedef struct{
    /// @brief j�t�kos m�rete �s koordin�t�i
    SDL_FRect position;
    /// @brief j�t�kos text�r�ja
    SDL_Texture *texture;
    /// @brief j�t�kos �letereje
    /// @note currently partly unused 
    int health;
}Player;

/// @brief a j�t�kbeli bemeneteket t�rol� strukt�ra
typedef struct{
    int up , down , left , right , menu;
}Input;

/**
 * 
 * @brief Inicializ�lja a j�t�kost.
 * 
 * @param x a j�t�kos kezd� x koordin�t�ja
 * @param y a j�t�kos kezd� y koordin�t�ja
 * @param health a j�t�kos kezd� �letereje
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param path a j�t�kos text�r�j�nak el�r�si �tja(string)
 * @return Player | visszat�r az inicializ�lt j�t�kossal
 */
void init_player(int x , int y, int health , SDL_Renderer *renderer , char* path , Player* player);

/**
 * @brief J�t�kos mozgat�s��rt felel�s f�ggv�ny
 * 
 * @param player inicializ�lt, mozgatand� j�t�kosra mutat� pointer
 * @param input bemeneteket t�rol� struct
 */
void move_player(Player* player , Input input , float deltaTime , int maxX , int maxY);
/**
 * @brief Kezeli a billenty�k lenyom�s�t
 * 
 * @param input bemeneteket kezel� structra pointer
 * @param event keyboardevent, ez alapj�n kapjuk meg milyen gomb(ok) lettek lenyomva
 */
void keyDown(Input* input , SDL_KeyboardEvent* event);

/**
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
 * @param head aszteroida lista fej�re mutat� pointer pointere
 * @param player j�t�kos adatait t�rol� strukt�ra pointere
 * @return Meteor visszat�r a meteorral ami eltal�lta a j�t�kost
 * @note jelenleg sok felesleges dolog van ebben a f�ggv�nyben de k�s�bb tervem van vel�k
 */
Meteor utkozes_ellenorzese(struct node** head , Player *player);

#endif