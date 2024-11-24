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

/// @brief a játék legtöbb helyen használt változóit fogja össze
typedef struct App{
    /// @brief játékos által megadott név
    char username[51];

    SDL_Surface* icon;

    SDL_Window *menuWindow;

    SDL_Renderer *menuRenderer;

    SDL_Window *gameWindow;

    SDL_Renderer *gameRenderer;

    SDL_Texture* reticle;
    /// @brief a képernyõ szélessége
    int screenW;
    /// @brief a képernyõ magassága
    int screenH;
    /// @brief a játékban használt normál méretÿ font
    TTF_Font* font;
    /// @brief a játékban használt nagy méretÿ font
    TTF_Font* font_big;
    
    bool isMenu;
    
    bool isGame;
    /// @brief játékos adatait tartalmazó struktúra
    Player player;
    /// @brief a bemeneteket tároló struktúra
    Input input;
    /// @brief háttér textúrája
    SDL_Texture *backround;
    /// @brief meteorokat tároló láncolt lista feje
    meteor_node* meteor_lista_head;
    /// @brief meteorok textúrája
    SDL_Texture* meteor_texture;
    /// @brief legutóbb elért pontszám
    int latest_score;
    /// @brief lövéseket tároló lista feje
    shot_node* shot_lista_head;
    /// @brief lövés textúrája
    SDL_Texture* shot_texture;
    /// @brief ranglista feje
    ranglista_node* ranglista_head;
    /// @brief a játék deltaTime számláló órája
    Clock clock;
    /// @brief a játékban meteorok létrehozásának idõzítéséért felelõs óra
    Spawn_clock spawn_clock;
    /// @note nem használt
    int targetFPS;
    /// @brief nehéz mód állása
    bool hardmode;
    /// @brief sikeres inicializálás esetén true
    bool succesful_init;
}App;

/**
 * @brief Inicializálja a játékadatok struktúráját, létrehozza a renderereket,
 *ablakokat, megnyitja a textúrákat és a fontot. Inicializálja a láncolt listák fejét és
 *a legutóbbi pontszámot 0-ra állítja stb.
 * 
 * @param screenW a képernyõ szélessége
 * @param screenH a képernyõ magassága
 * @return App visszatér az inicializált struktúrával
 */
App init_App(int screenW , int screenH);

/**
 * @brief Futtatja a menÿt. Meghívja runGame() -t, ha a játékos a játékot indító jelet adja.
 * 
 * @param app a játék adatait tartalmazó struktúrára mutató pointer 
 */
void runMenu(App* app);

/**
 * @brief A játék futtatásáért felelõs. ha a játékos bezárja, visszatérés után a menÿben folytatódik a játék.
 * 
 * @param app a játék adatait tartalmazó struktúrára mutató pointer 
 * 
 * @return visszatér a játékos adott sessionben elért pontszámával
 */
int runGame(App* app);

/// @brief alaphelyzetbe állítja a játékot: kitörli a meteorokat, lövéseket, visszateszi a játékost a kezdõpozícióra
/// @param app a játék adatait tartalmazó struktúrára mutató pointer 
void resetGame(App* app);

/// @brief lekérdezi majd letárolja a képernyõ méretét
/// @param w a képernyõ szélességét tároló változóra pointer
/// @param h a képernyõ magasságát tároló változóra pointer
void getDisplaySize(int* w , int* h);

#endif