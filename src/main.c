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
#include "app.h"
#include "file.h"
#include "../lib/debugmalloc.h"

int main(int argc , char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0 , &dm);

    int screenW , screenH;
    screenW = dm.w;
    screenH = dm.h;
    
    App app = init_App(screenW , screenH);
    app.latest_score = load_latest_score("../saves/latestscores.txt");
    srand(time(0));
    SDL_HideWindow(app.gameWindow);
    runMenu(&app);

    if(write_latest_score("../saves/latestscores.txt" , app.latest_score)==-1) return -1;

    SDL_Quit();
    return 0;
}






