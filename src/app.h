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
#include "reticle.h"

/// @brief a j�t�k legt�bb helyen haszn�lt v�ltoz�it fogja �ssze
typedef struct App{
    /// @brief j�t�kos �ltal megadott n�v
    char username[51];

    SDL_Surface* icon;

    SDL_Window *menuWindow;

    SDL_Renderer *menuRenderer;

    SDL_Window *gameWindow;

    SDL_Renderer *gameRenderer;

    SDL_Texture* reticle;
    /// @brief a k�perny� sz�less�ge
    int screenW;
    /// @brief a k�perny� magass�ga
    int screenH;
    /// @brief a j�t�kban haszn�lt norm�l m�ret� font
    TTF_Font* font;
    /// @brief a j�t�kban haszn�lt nagy m�ret� font
    TTF_Font* font_big;
    
    bool isMenu;
    
    bool isGame;
    /// @brief j�t�kos adatait tartalmaz� strukt�ra
    Player player;
    /// @brief a bemeneteket t�rol� strukt�ra
    Input input;
    /// @brief h�tt�r text�r�ja
    SDL_Texture *backround;
    /// @brief meteorokat t�rol� l�ncolt lista feje
    node* meteor_lista_head;
    /// @brief meteorok text�r�ja
    SDL_Texture* meteor_texture;
    /// @brief legut�bb el�rt pontsz�m
    int latest_score;
    /// @brief l�v�seket t�rol� lista feje
    shot_node* shot_lista_head;
    /// @brief l�v�s text�r�ja
    SDL_Texture* shot_texture;
    /// @brief ranglista feje
    ranglista_node* ranglista_head;
    /// @brief a j�t�k deltaTime sz�ml�l� �r�ja
    Clock clock;
    /// @brief a j�t�kban meteorok l�trehoz�s�nak id�z�t�s��rt felel�s �ra
    Spawn_clock spawn_clock;
    /// @note nem haszn�lt
    int targetFPS;
    /// @brief neh�z m�d �ll�sa
    bool hardmode;
    /// @brief sikeres inicializ�l�s eset�n true
    bool succesful_init;
}App;

/**
 * @brief Inicializ�lja a j�t�kadatok strukt�r�j�t, l�trehozza a renderereket,
 *ablakokat, megnyitja a text�r�kat �s a fontot. Inicializ�lja a l�ncolt list�k fej�t �s
 *a legut�bbi pontsz�mot 0-ra �ll�tja stb.
 * 
 * @param screenW a k�perny� sz�less�ge
 * @param screenH a k�perny� magass�ga
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

/// @brief alaphelyzetbe �ll�tja a j�t�kot: kit�rli a meteorokat, l�v�seket, visszateszi a j�t�kost a kezd�poz�ci�ra
/// @param app a j�t�k adatait tartalmaz� strukt�r�ra mutat� pointer 
void resetGame(App* app);

/// @brief lek�rdezi majd let�rolja a k�perny� m�ret�t
/// @param w a k�perny� sz�less�g�t t�rol� v�ltoz�ra pointer
/// @param h a k�perny� magass�g�t t�rol� v�ltoz�ra pointer
void getDisplaySize(int* w , int* h);

#endif