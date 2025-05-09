#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>


#include "player.h"
#include "aszteroida.h"
#include "app.h"
#include "file.h"
#include "../lib/debugmalloc.h"

int init_sdl(void){

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    debugmalloc_log_file("../log/log.txt");
    if(TTF_Init()< 0) return 2;
    return 0;
}



int main(int argc , char* argv[])
{
    //ha nem l�tezik saves mappa akkor l�trehozzuk
    check_for_saves_folder();
    
    if(init_sdl() != 0) return 1;
    
    App app = init_App(800 , 600);
    if(!app.succesful_init){
        printf("Hiba tortent az alkalmazas inicializalasa kozben!");
        DEFINITELY_AN_ERROR_MESSAGE
        return 69;
    }

    srand(time(0));
    
    runMenu(&app);

    deleteMeteorList(app.meteor_lista_head);
    delete_shot_list(app.shot_lista_head);
    delete_Ranglista(app.ranglista_head);

    if(write_LatestScore("../saves/latestscores.txt" , app.latest_score)==-1) return -1;
    
    SDL_Quit();

    return 0;
}