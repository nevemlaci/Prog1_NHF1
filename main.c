#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include "SDL2/include/SDL2/SDL.h"
#include "SDL2/include/SDL2/SDL_main.h"


int main(int argc , char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("" , 50 , 50 , 500 , 500 , 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_Renderer *renderer = SDL_CreateRenderer(window , -1 , SDL_RENDERER_ACCELERATED);



    SDL_Event e;
    bool isRunning = true;
    while(isRunning){
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    }
    return 0;
}