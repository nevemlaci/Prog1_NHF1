#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <dirent.h>

#include "player.h"
#include "aszteroida.h"
#include "app.h"
#include "file.h"
#include "../lib/debugmalloc.h"

int main(int argc , char* argv[])
{

    //ha nem létezik saves mappa akkor létrehozzuk
    DIR* dir;
    dir = opendir("../saves");
    if(dir==NULL) system("mkdir \"../saves\"");
    closedir(dir);


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    debugmalloc_log_file("../log/log.txt");

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0 , &dm);

    int screenW , screenH;
    screenW = dm.w;
    screenH = dm.h;
    
    App app = init_App(screenW , screenH);
    app.latest_score = load_latest_score("../saves/latestscores.txt");
    srand(time(0));
    
    runMenu(&app);
    delete_meteor_list(app.meteor_lista_head);
    delete_shot_list(app.shot_lista_head);
    if(write_latest_score("../saves/latestscores.txt" , app.latest_score)==-1) return -1;
    SDL_Quit();
    return 0;
}






