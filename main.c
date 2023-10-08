#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include "player.h"

typedef struct{
            SDL_Window *menuWindow;
            SDL_Renderer *menuRenderer;
            SDL_Window *gameWindow;
            SDL_Renderer *gameRenderer;;
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

    

    App app;

    app.menuWindow = SDL_CreateWindow("Menu" , 600 , 300 , 400 , 400, 0);
    app.menuRenderer = SDL_CreateRenderer(app.menuWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.gameWindow = SDL_CreateWindow("" , 50 , 50 , 816 , 480 , 0); //SDL_WINDOW_FULLSCREEN_DESKTOP
    app.gameRenderer = SDL_CreateRenderer(app.gameWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.isGame = false , 
    app.isMenu = true;
    init_player(100 , 100 , 10 , app.gameRenderer , "player.png" , &app.player);
    app.backround = IMG_LoadTexture(app.gameRenderer , "background.jpeg");
    app.meteor_lista_head = init_meteor_list();
    app.meteor_texture = IMG_LoadTexture(app.gameRenderer , "meteor_1.png");

    srand( time(0) );
    SDL_HideWindow(app.gameWindow);
    runMenu(&app);
    
    SDL_Quit();
    return 0;
}

void runMenu(App* app){
    SDL_ShowWindow(app->menuWindow);
    SDL_Event e;
    while(app->isMenu){
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                    SDL_DestroyWindow(app->gameWindow);
                    SDL_DestroyWindow(app->menuWindow);
                    return;
                }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        app->isGame = true;
                        app->isMenu = false;
                        app->gameWindow!=NULL ? SDL_ShowWindow(app->gameWindow) : NULL;
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
                        SDL_HideWindow(app->gameWindow);
                        app->isGame=false;
                        app->isMenu=true;
                        SDL_ShowWindow(app->menuWindow);
                        return;
                    }
                    break;
                case SDL_KEYDOWN:
                    keyDown(&app->input , &e.key);
                    break;
                    
                case SDL_KEYUP:
                    keyUp(&app->input , &e.key);
                    break;
            }
        }

        move_player( &app->player , &app->input);
        SDL_RenderClear(app->gameRenderer);
        SDL_RenderCopy(app->gameRenderer , app->backround , NULL , NULL);
        SDL_RenderCopy(app->gameRenderer , app->player.texture , NULL , &app->player.position); 
        utkozes_ellenorzese(app->meteor_lista_head , &app->player); 
        renderMeteors(app->meteor_lista_head , app->gameRenderer, app->meteor_texture);
        
        SDL_RenderPresent(app->gameRenderer);

        SDL_Delay(16);
        frames++;
    }
}