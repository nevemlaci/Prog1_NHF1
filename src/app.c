#include "app.h"
#include "shoot.h"
#include "defines.h"

/**
 * @brief Inicializálja a játék fõ struktúráját, létrehozza a renderereket,
 *ablakokat, megnyitja a textúrákat és a fontot. Inicializálja a láncolt listák fejét és
 *a legutóbbi pontszámot 0-ra állítja.
 * 
 * @param screenW a képernyõ szélessége (nem fullscreen mûködéshez szükséges)
 * @param screenH a képernyõ magassága (nem fullscreen mûködéshez szükséges)
 * @return App visszatér az inicializált struktúrával
 */
App init_App(int screenW , int screenH){
    App app;
    app.menuWindow = SDL_CreateWindow("Menu" , 600 , 300 , 400 , 400, 0);
    app.menuRenderer = SDL_CreateRenderer(app.menuWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.gameWindow = SDL_CreateWindow("" , screenW/2 - 816/2 , screenH/2 - 480/2 , 816 , 480 , SDL_WINDOW_FULLSCREEN_DESKTOP); 
    app.gameRenderer = SDL_CreateRenderer(app.gameWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.screenW = screenW;
    app.screenH = screenH;
    app.font = TTF_OpenFont("../materials/font/comic.ttf" , 13);
    app.isGame = false , 
    app.isMenu = true;
    reset_input(&app.input);
    init_player(100 , 100 , 1 , app.gameRenderer , "../materials/images/player.png" , &app.player);
    app.backround = IMG_LoadTexture(app.gameRenderer , "../materials/images/background.jpeg");
    app.meteor_lista_head = init_meteor_list();
    app.meteor_texture = IMG_LoadTexture(app.gameRenderer , "../materials/images/meteor_1.png");
    app.latest_score = 0;
    app.shot_lista_head = NULL;
    app.shot_texture = IMG_LoadTexture(app.gameRenderer , "..//materials/images/shot.png");
    return app;
}

void runMenu(App* app){
    SDL_ShowWindow(app->menuWindow);
    SDL_Event e;
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type){
                //Az egész játék bezárása
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        return;
                    }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        //Menübõl játékba váltás
                        app->isGame = true;
                        app->isMenu = false;
                        SDL_ShowWindow(app->gameWindow);
                        SDL_HideWindow(app->menuWindow);
                        app->latest_score=runGame(app);
                        //Ez a játék vége után fut már le.
                        reset_input(&app->input);
                        delete_meteor_list(app->meteor_lista_head);
                        init_player(100 , 100 , 1 , app->gameRenderer , "../materials/images/player.png" , &app->player);
                        app->meteor_lista_head = init_meteor_list();
                    }
            }
        }
        SDL_RenderClear(app->menuRenderer);
        SDL_SetRenderDrawColor(app->menuRenderer , 252, 111, 68, 0);
        SDL_RenderPresent(app->menuRenderer);
    }
    return;
}

int runGame(App* app){
    // @brief temp változó az adott framen való kattintást és a játékost összekötõ szakasz szöge 
    double angle;
    // @brief frame számláló
    int frames = 0;
    // @brief lövés timer spammelés ellen
    int shot_timer=SHOT_TIME+1;
    // @brief meteorok indexét tárolja(új létrehozásakor növekszik)
    int meteorIndex = 0;
    // @brief pontszám
    int score = 0;
    SDL_Event e;
    while(app->isGame){
        //minden framen 1 pont
        score++;
        //shot timer léptetése ha szükséges
        if(shot_timer<=SHOT_TIME) shot_timer++;
        //ha az elõzõ framen menü parancsot ad a játékos akkor kilép a menübe
        if(app->input.menu == 1){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return score;
        }
        //eventek
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        app->isGame=false;
                        app->isMenu=true;
                        SDL_HideWindow(app->gameWindow);
                        SDL_ShowWindow(app->menuWindow);
                        return score;
                    }
                case SDL_KEYDOWN:
                    keyDown(&app->input , &e.key);
                    break;
                    
                case SDL_KEYUP:
                    keyUp(&app->input , &e.key);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                if(shot_timer>SHOT_TIME){
                    angle = calculate_angle_for_shot(app->player.position.x , app->player.position.y);
                    app->shot_lista_head=add_new_shot(app->shot_lista_head , angle , app->player.position.x , app->player.position.y);
                    shot_timer=0;
                    break;                   
                }
            }
        }
        //mozgató függvények       
        move_player(&app->player , app->input);
        move_shots(app->shot_lista_head);
        //collision checkek
        utkozes_ellenorzese(app->meteor_lista_head , &app->player, &meteorIndex);
        //renderelés
        SDL_RenderClear(app->gameRenderer);
        SDL_RenderCopy(app->gameRenderer , app->backround , NULL , NULL);
        SDL_RenderCopyF(app->gameRenderer , app->player.texture , NULL , &app->player.position);
        renderMeteors(app->meteor_lista_head , app->gameRenderer, app->meteor_texture);
        render_shots(app->shot_lista_head , app->gameRenderer , app->shot_texture);
        SDL_RenderPresent(app->gameRenderer);
        //játékos halála, DIE define debug miatt
        if(app->player.health<=0 && DIE != 0){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return score;
        }
        //Meteor spawnolás
        if(frames >= BASE_SPAWN_RATE){
            meteorIndex++;
            spawnMeteors(app->meteor_lista_head , &meteorIndex , app->screenW , app->screenH);
            frames=0;       
        }
        //16 ms delay -> kb. 60 képkocka / másodperc
        SDL_Delay(16);
        //frame számlálót léptetem
        frames++;
    }
    return score;
}