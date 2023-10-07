#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include "player.h"
#include "aszteroida.h"

void runMenu(SDL_Renderer* menuRenderer , SDL_Window* menuWindow , bool* isRunning , SDL_Window* window){
    SDL_ShowWindow(menuWindow);
    SDL_Event e;
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                    SDL_Quit();
                    break;
                }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        *isRunning = true;
                        window!=NULL ? SDL_ShowWindow(window) : NULL;
                        SDL_HideWindow(menuWindow);
                        return;
                    }
            }
        }
        SDL_RenderClear(menuRenderer);
        SDL_SetRenderDrawColor(menuRenderer , 252, 111, 68, 0);
        SDL_RenderPresent(menuRenderer);
    }
    
}

int main(int argc , char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_Window *menuWindow = SDL_CreateWindow("Menu" , 600 , 300 , 400 , 400, 0);
    SDL_Renderer *menuRenderer = SDL_CreateRenderer(menuWindow , -1 , SDL_RENDERER_ACCELERATED);


    bool isRunning = false;

    runMenu(menuRenderer , menuWindow , &isRunning ,NULL);

    SDL_Window *window = SDL_CreateWindow("" , 50 , 50 , 816 , 480 , 0); //SDL_WINDOW_FULLSCREEN_DESKTOP
    SDL_Renderer *renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED);

    Player player = init_player(100 , 100 , 10 , renderer , "player.png");
    Input input;

    SDL_Texture *backround = IMG_LoadTexture(renderer , "background.jpeg");

    node* meteor_lista_head = init_meteor_list();
    SDL_Texture* meteor_texture = IMG_LoadTexture(renderer , "meteor_1.png");

    srand( time(0) );

    int frames = 0;
    int meteorIndex = 0;
     
    SDL_Event e;
    while(isRunning){
        if(frames>= 140){
            meteorIndex++;
            spawnMeteors(meteor_lista_head , meteorIndex);
            frames=0;
            
        }

        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        SDL_HideWindow(window);
                        isRunning=false;
                        runMenu(menuRenderer , menuWindow , &isRunning, window);
                    }
                    break;
                case SDL_KEYDOWN:
                    keyDown(&input , &e.key);
                    break;
                    
                case SDL_KEYUP:
                    keyUp(&input , &e.key);
                    break;
            }
        }

        move_player( &player , input);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer , backround , NULL , NULL);
        SDL_RenderCopy(renderer , player.texture , NULL , &player.position); 
        utkozes_ellenorzese(meteor_lista_head , &player); 
        renderMeteors(meteor_lista_head , renderer, meteor_texture);
        
        SDL_RenderPresent(renderer);
        if(player.health<=0){
            ;
        }

        SDL_Delay(16);
        frames++;
    }
    return 0;
}