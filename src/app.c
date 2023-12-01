#include "app.h"

App init_App(int screenW , int screenH){
    
    App app;
    app.succesful_init=false;

    app.icon = IMG_Load("..\\materials\\images\\player.png");

    if(!app.icon){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    SDL_Texture* play_button;
    app.menuWindow = SDL_CreateWindow("Asteroids - Menu" , (screenW/2) - (MENU_W/2) , (screenH/2) - (MENU_H/2) , MENU_W , MENU_H, 0);
    if(!app.menuWindow){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    SDL_SetWindowIcon(app.menuWindow , app.icon);
    app.menuRenderer = SDL_CreateRenderer(app.menuWindow , -1 , SDL_RENDERER_ACCELERATED);
    if(!app.menuRenderer){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.gameWindow = SDL_CreateWindow("" , screenW/2 - 816/2 , screenH/2 - 480/2 , 816 , 480 , SDL_WINDOW_FULLSCREEN_DESKTOP); 
    if(!app.gameWindow){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    SDL_SetWindowIcon(app.gameWindow , app.icon);
    app.gameRenderer = SDL_CreateRenderer(app.gameWindow , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!app.gameRenderer){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.reticle = IMG_LoadTexture(app.gameRenderer , "../materials/images/reticle.png");
    if(!app.reticle){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.screenW = screenW;
    app.screenH = screenH;
    app.font = TTF_OpenFont("../materials/font/comic.ttf" , 25);
    if(!app.font){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.font_big = TTF_OpenFont("../materials/font/comic.ttf" , 55);
    if(!app.font_big){
        printf("%s\n" , TTF_GetError()); 
        return app;
    }
    app.isGame = false , 
    app.isMenu = true;
    init_Input(&app.input);
    init_Player(100 , 100 , 1 , app.gameRenderer , "../materials/images/player.png" , &app.player);
    if(!app.player.texture){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.backround = IMG_LoadTexture(app.gameRenderer , "../materials/images/background.jpeg");
    if(!app.backround){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.meteor_lista_head = NULL;
    app.meteor_texture = IMG_LoadTexture(app.gameRenderer , "../materials/images/meteor_2.png");
    if(!app.meteor_texture){
        printf("%s\n" , SDL_GetError());
        return app;
    }
    app.latest_score = 0;
    app.shot_texture=IMG_LoadTexture(app.gameRenderer , "../materials/images/shot.png");
    app.shot_lista_head = NULL;
    app.ranglista_head = read_Ranglista_from_file();
    app.latest_score = load_LatestScore("../saves/latestscores.txt");
    SDL_SetRenderDrawColor(app.menuRenderer , MENU_COLOR);

    initGameClock(&app.clock);

    app.hardmode = false;

    app.succesful_init=true;
    return app;
}

void runMenu(App* app){
    SDL_HideWindow(app->gameWindow);
    SDL_ShowWindow(app->menuWindow);
    
    //megkérjük a felhasználót hogy adjon meg egy nevet
    render_GetUsername(app->menuRenderer , app->font , app->username);

    SDL_Rect play_pos = calculatePlayButtonSize(app->menuRenderer , app->font_big);
    SDL_Rect hard_pos = calculateHardButtonSize(app->menuRenderer , app->font_big , &app->hardmode);

    SDL_Event e;
    
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type){
                //Az egész játék bezárása
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        print_Ranglista_to_file(app->ranglista_head);
                        return;
                    }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        //Menübõl játékba váltás
                        app->latest_score=runGame(app);
                        //Ez a játék vége után fut már le.
                        resetGame(app);
                    }
                    if(e.key.keysym.scancode == SDL_SCANCODE_H){
                        app->hardmode=!app->hardmode;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(checkPlayButton(&play_pos)){
                        //Menübõl játékba váltás
                        app->latest_score=runGame(app);
                        //Ez a játék vége után fut már le.
                        resetGame(app);
                    }
                    if(checkHardButton(&hard_pos)){
                        app->hardmode = !app->hardmode;
                    }
                    break;
            }
        }
        //rendereljük a menü tartalmát
        SDL_RenderClear(app->menuRenderer);
        renderPlayButton(app->menuRenderer , app->font_big);
        renderHardButton(app->menuRenderer , app->font_big , &app->hardmode);
        renderRanglista(app->menuRenderer , app->font, app->ranglista_head);
        renderCopyMenuContents(app->menuRenderer , app->font , app->username , app->latest_score);
        SDL_RenderPresent(app->menuRenderer);
    }
    return;
}

int runGame(App* app){
    SDL_ShowCursor(SDL_DISABLE);
    initSpawnClock(&app->spawn_clock);
    app->isGame = true;
    app->isMenu = false;
    SDL_ShowWindow(app->gameWindow);
    SDL_HideWindow(app->menuWindow);
    SDL_Rect score_pos = {3 ,3 ,0 ,0};
    char pont_szoveg[8];

    //@brief ennyi másodpercig tartott a frame
    float deltaTime;
    
    // @brief temp változó az adott framen való kattintást és a játékost összekötõ szakasz szöge 
    double angle;

    // @brief frame számláló
    int frames = 0;

    // @brief lövés timer spammelés ellen
    int shot_timer=SHOT_TIME+1;

    // @brief pontszám
    int score = 0;
    SDL_Event e;

    //@brief temp meteor amiben az eltalált meteor adatai vannak
    Meteor temp_meteor;
    while(app->isGame){
        //órák mozgatása
        tickGameClock(&app->clock);
        tickSpawnClock(&app->spawn_clock);
        
        deltaTime = calculate_DeltaTime(&app->clock);
        //minden framen 2/1 pont nehézségtõl függõen
        score+= app->hardmode? 2 : 1 ;
        sprintf(pont_szoveg , "%d" , score);
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

        //Meteor spawnolás
        if(calculate_SpawnTime(&app->spawn_clock) >= (app->hardmode ? BASE_SPAWN_RATE/2 : BASE_SPAWN_RATE)){
            app->meteor_lista_head = spawnMeteors(app->meteor_lista_head, app->screenW , app->screenH);     
            resetSpawnClock(&app->spawn_clock);
        }

        //eventek
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){ //ha bezárjuk az ablakot visszatérünk a menübe(alt+f4)
                        app->isGame=false;
                        app->isMenu=true;
                        SDL_HideWindow(app->gameWindow);
                        SDL_ShowWindow(app->menuWindow);
                        return score;
                    }
                case SDL_KEYDOWN: //billentyûleütések kezelése
                    keyDown(&app->input , &e.key);
                    break;
                    
                case SDL_KEYUP: //billentyûfelengedések kezelése
                    keyUp(&app->input , &e.key);
                    break;
                case SDL_MOUSEBUTTONDOWN: //kattintás
                    if(shot_timer>SHOT_TIME){
                        angle = calculate_angle_for_shot(app->player.position.x , app->player.position.y);
                        app->shot_lista_head=add_new_shot(app->shot_lista_head , angle , app->player.position.x , app->player.position.y);
                        shot_timer=0;
                        break;                   
                }
            }
        }

        //mozgató függvények       
        movePlayer(&app->player , app->input , deltaTime , app->screenW , app->screenH);
        moveShots(app->shot_lista_head , deltaTime);
        moveMeteors(app->meteor_lista_head , deltaTime);

        //collision checkek
        checkPlayerMeteorHits(&app->meteor_lista_head , &app->player);

        deleteOutOfBoundsMeteors(&app->meteor_lista_head);
        //meteor kettéválasztása ha az eltalált meteor nem a legkisebb méretû(egybe kerül néha 2 meteor de m1)
        temp_meteor=check_hits(&app->shot_lista_head, &app->meteor_lista_head);
        if(temp_meteor.meret>=1){
            app->meteor_lista_head=spawnMeteors_pos(app->meteor_lista_head , temp_meteor.position.x+50 , temp_meteor.position.y+50 , temp_meteor.meret-1);
            app->meteor_lista_head=spawnMeteors_pos(app->meteor_lista_head , temp_meteor.position.x-50 , temp_meteor.position.y-50 , temp_meteor.meret-1);
        }
        //meteor szétlövéséért pont
        if(temp_meteor.meret>=0){
            score+=800;
        }
        
        //renderelés
        SDL_RenderClear(app->gameRenderer);
        SDL_RenderCopy(app->gameRenderer , app->backround , NULL , NULL);
        SDL_RenderCopyF(app->gameRenderer , app->player.texture , NULL , &app->player.position);
        renderMeteors(app->meteor_lista_head , app->gameRenderer, app->meteor_texture);
        render_shots(app->shot_lista_head , app->gameRenderer , app->shot_texture);
        SDL_RenderCopy(app->gameRenderer , text_to_texture_white(app->font , pont_szoveg , app->gameRenderer , &score_pos) , NULL , &score_pos);
        renderReticle(app->gameRenderer , app->reticle);
        SDL_RenderPresent(app->gameRenderer);

        //játékos halála, DIE define debug miatt
        if(app->player.health<=0 && DIE != 0){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return score;
        }
        
        //frame számlálót léptetem
        frames++;
    }
    
    //warning elkerülése
    return score;
}

void resetGame(App* app){
    SDL_ShowCursor(SDL_ENABLE);
    insert_Ranking(&app->ranglista_head , app->username , app->latest_score);
    init_Input(&app->input);
    deleteMeteorList(app->meteor_lista_head);
    app->meteor_lista_head=NULL;
    delete_shot_list(app->shot_lista_head);
    app->shot_lista_head=NULL;
    init_Player(100 , 100 , 1 , app->gameRenderer , "../materials/images/player.png" , &app->player);
    initGameClock(&app->clock);
}

void getDisplaySize(int* w , int* h){
    
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0 , &dm);
    *w= dm.w;
    *h= dm.h;
}