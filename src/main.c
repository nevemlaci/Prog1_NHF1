#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include "player.h"
#include "aszteroida.h"
#include "../lib/debugmalloc.h"

typedef struct{
            SDL_Window *menuWindow;
            SDL_Renderer *menuRenderer;
            SDL_Window *gameWindow;
            SDL_Renderer *gameRenderer;
            TTF_Font* font;
            bool isGame;
            bool isMenu;
            Player player;
            Input input;
            SDL_Texture *backround;
            node* meteor_lista_head;
            SDL_Texture* meteor_texture;
        }App;



void runMenu(App* app);

void runGame(App* app);

int main(int argc , char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0 , &dm);

    int screenW , screenH;
    screenW = dm.w;
    screenH = dm.h;

    App app;

    app.menuWindow = SDL_CreateWindow("Menu" , 600 , 300 , 400 , 400, 0);
    app.menuRenderer = SDL_CreateRenderer(app.menuWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.gameWindow = SDL_CreateWindow("" , screenW/2 - 816/2 , screenH/2 - 480/2 , 816 , 480 , 0); //SDL_WINDOW_FULLSCREEN_DESKTOP
    app.gameRenderer = SDL_CreateRenderer(app.gameWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.font = TTF_OpenFont("../materials/font/comic.ttf" , 13);
    app.isGame = false , 
    app.isMenu = true;
    init_player(100 , 100 , 1 , app.gameRenderer , "../materials/images/player.png" , &app.player);
    app.backround = IMG_LoadTexture(app.gameRenderer , "../materials/images/background.jpeg");
    app.meteor_lista_head = init_meteor_list();
    app.meteor_texture = IMG_LoadTexture(app.gameRenderer , "../materials/images/meteor_1.png");

    srand( time(0) );
    SDL_HideWindow(app.gameWindow);
    runMenu(&app);
    SDL_Quit();
    return 0;
}

/**
 * @brief Futtatja a menüt. Meghívja runGame() -t, ha a játékos a játékot indító jelet adja.
 * 
 * @param app a játék törzsét alkotó struktúrára mutató pointer
 */
void runMenu(App* app){
    SDL_ShowWindow(app->menuWindow);
    SDL_Event e;
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                    return;
                }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        app->isGame = true;
                        app->isMenu = false;
                        SDL_ShowWindow(app->gameWindow);
                        SDL_HideWindow(app->menuWindow);
                        runGame(app);
                    }
            }
        }
        SDL_RenderClear(app->menuRenderer);
        SDL_SetRenderDrawColor(app->menuRenderer , 252, 111, 68, 0);
        SDL_RenderPresent(app->menuRenderer);
    }
    
}
/**
 * @brief A játék futtatásáért felelõs. ha a játékos bezárja, visszatérés után a menüben folytatódik a játék.
 * 
 * @param app a játék törzsét alkotó struktúrára mutató pointer
 */
void runGame(App* app){
    int frames = 0;
    int meteorIndex = 0;
    SDL_Event e;
    while(app->isGame){
        if(frames>= 140){
            meteorIndex++;
            spawnMeteors(app->meteor_lista_head , meteorIndex);
            frames=0;
            
        }

        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        app->isGame=false;
                        app->isMenu=true;
                        SDL_HideWindow(app->gameWindow);
                        SDL_ShowWindow(app->menuWindow);
                        return;
                    }
                case SDL_KEYDOWN:
                    keyDown(&app->input , &e.key);
                    break;
                    
                case SDL_KEYUP:
                    keyUp(&app->input , &e.key);
                    break;
            }
        }

        move_player( &app->player , app->input);
        SDL_RenderClear(app->gameRenderer);
        SDL_RenderCopy(app->gameRenderer , app->backround , NULL , NULL);
        SDL_RenderCopy(app->gameRenderer , app->player.texture , NULL , &app->player.position); 
        utkozes_ellenorzese(app->meteor_lista_head , &app->player); 
        renderMeteors(app->meteor_lista_head , app->gameRenderer, app->meteor_texture);
        
        SDL_RenderPresent(app->gameRenderer);
        if(app->player.health<=0){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return;
        }
        SDL_Delay(16);
        frames++;
    }
}

