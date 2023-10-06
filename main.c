#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include "player.h"
#include "aszteroida.h"

int main(int argc , char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("" , 50 , 50 , 816 , 480 , 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_Renderer *renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED);
    Player player = init_player(100 , 100 , 10 , renderer , "player.png");
    Input input;

    SDL_Texture *backround = IMG_LoadTexture(renderer , "background.jpeg");

    node* meteor_lista_head = init_meteor_list();
    SDL_Texture* meteor_texture = IMG_LoadTexture(renderer , "meteor_1.png");

    srand( time(0) );

    int frames = 0;
    

    SDL_Event e;
    bool isRunning = true;
    while(isRunning){
        if(frames>= 140){
            spawnMeteors(meteor_lista_head);
            frames=0;
        }

        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_QUIT:
                    isRunning = false;
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
        renderMeteors(meteor_lista_head , renderer, meteor_texture);   
        SDL_RenderPresent(renderer);
        

        SDL_Delay(16);
        frames++;
    }
    return 0;
}