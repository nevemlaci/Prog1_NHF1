#include "app.h"

App init_App(int screenW , int screenH){
    App app;
    app.menuWindow = SDL_CreateWindow("Menu" , 600 , 300 , 400 , 400, 0);
    app.menuRenderer = SDL_CreateRenderer(app.menuWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.gameWindow = SDL_CreateWindow("" , screenW/2 - 816/2 , screenH/2 - 480/2 , 816 , 480 , SDL_WINDOW_FULLSCREEN_DESKTOP); 
    app.gameRenderer = SDL_CreateRenderer(app.gameWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.font = TTF_OpenFont("../materials/font/comic.ttf" , 13);
    app.isGame = false , 
    app.isMenu = true;
    init_player(100 , 100 , 1 , app.gameRenderer , "../materials/images/player.png" , &app.player);
    app.backround = IMG_LoadTexture(app.gameRenderer , "../materials/images/background.jpeg");
    app.meteor_lista_head = init_meteor_list();
    app.meteor_texture = IMG_LoadTexture(app.gameRenderer , "../materials/images/meteor_1.png");
    app.latest_score = 0;
    return app;
}

void runMenu(App* app){
    SDL_ShowWindow(app->menuWindow);
    SDL_Event e;
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type){
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
                        app->latest_score=runGame(app);
                        delete_meteor_list(app->meteor_lista_head);
                        init_player(100 , 100 , 1 , app->gameRenderer , "../materials/images/player.png" , &app->player);
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
    int frames = 0;
    int meteorIndex = 0;
    int score = 0;
    SDL_Event e;
    while(app->isGame){
        score++;
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
                        return score;
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
            return score;
        }
        SDL_Delay(16);
        frames++;
    }
    return score;
}