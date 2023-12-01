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
    
    //megk�rj�k a felhaszn�l�t hogy adjon meg egy nevet
    render_GetUsername(app->menuRenderer , app->font , app->username);

    SDL_Rect play_pos = calculatePlayButtonSize(app->menuRenderer , app->font_big);
    SDL_Rect hard_pos = calculateHardButtonSize(app->menuRenderer , app->font_big , &app->hardmode);

    SDL_Event e;
    
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type){
                //Az eg�sz j�t�k bez�r�sa
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        print_Ranglista_to_file(app->ranglista_head);
                        return;
                    }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        //Men�b�l j�t�kba v�lt�s
                        app->latest_score=runGame(app);
                        //Ez a j�t�k v�ge ut�n fut m�r le.
                        resetGame(app);
                    }
                    if(e.key.keysym.scancode == SDL_SCANCODE_H){
                        app->hardmode=!app->hardmode;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(checkPlayButton(&play_pos)){
                        //Men�b�l j�t�kba v�lt�s
                        app->latest_score=runGame(app);
                        //Ez a j�t�k v�ge ut�n fut m�r le.
                        resetGame(app);
                    }
                    if(checkHardButton(&hard_pos)){
                        app->hardmode = !app->hardmode;
                    }
                    break;
            }
        }
        //renderelj�k a men� tartalm�t
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

    //@brief ennyi m�sodpercig tartott a frame
    float deltaTime;
    
    // @brief temp v�ltoz� az adott framen val� kattint�st �s a j�t�kost �sszek�t� szakasz sz�ge 
    double angle;

    // @brief frame sz�ml�l�
    int frames = 0;

    // @brief l�v�s timer spammel�s ellen
    int shot_timer=SHOT_TIME+1;

    // @brief pontsz�m
    int score = 0;
    SDL_Event e;

    //@brief temp meteor amiben az eltal�lt meteor adatai vannak
    Meteor temp_meteor;
    while(app->isGame){
        //�r�k mozgat�sa
        tickGameClock(&app->clock);
        tickSpawnClock(&app->spawn_clock);
        
        deltaTime = calculate_DeltaTime(&app->clock);
        //minden framen 2/1 pont neh�zs�gt�l f�gg�en
        score+= app->hardmode? 2 : 1 ;
        sprintf(pont_szoveg , "%d" , score);
        //shot timer l�ptet�se ha sz�ks�ges
        if(shot_timer<=SHOT_TIME) shot_timer++;
        //ha az el�z� framen men� parancsot ad a j�t�kos akkor kil�p a men�be
        if(app->input.menu == 1){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return score;
        }

        //Meteor spawnol�s
        if(calculate_SpawnTime(&app->spawn_clock) >= (app->hardmode ? BASE_SPAWN_RATE/2 : BASE_SPAWN_RATE)){
            app->meteor_lista_head = spawnMeteors(app->meteor_lista_head, app->screenW , app->screenH);     
            resetSpawnClock(&app->spawn_clock);
        }

        //eventek
        while (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){ //ha bez�rjuk az ablakot visszat�r�nk a men�be(alt+f4)
                        app->isGame=false;
                        app->isMenu=true;
                        SDL_HideWindow(app->gameWindow);
                        SDL_ShowWindow(app->menuWindow);
                        return score;
                    }
                case SDL_KEYDOWN: //billenty�le�t�sek kezel�se
                    keyDown(&app->input , &e.key);
                    break;
                    
                case SDL_KEYUP: //billenty�felenged�sek kezel�se
                    keyUp(&app->input , &e.key);
                    break;
                case SDL_MOUSEBUTTONDOWN: //kattint�s
                    if(shot_timer>SHOT_TIME){
                        angle = calculate_angle_for_shot(app->player.position.x , app->player.position.y);
                        app->shot_lista_head=add_new_shot(app->shot_lista_head , angle , app->player.position.x , app->player.position.y);
                        shot_timer=0;
                        break;                   
                }
            }
        }

        //mozgat� f�ggv�nyek       
        movePlayer(&app->player , app->input , deltaTime , app->screenW , app->screenH);
        moveShots(app->shot_lista_head , deltaTime);
        moveMeteors(app->meteor_lista_head , deltaTime);

        //collision checkek
        checkPlayerMeteorHits(&app->meteor_lista_head , &app->player);

        deleteOutOfBoundsMeteors(&app->meteor_lista_head);
        //meteor kett�v�laszt�sa ha az eltal�lt meteor nem a legkisebb m�ret�(egybe ker�l n�ha 2 meteor de m1)
        temp_meteor=check_hits(&app->shot_lista_head, &app->meteor_lista_head);
        if(temp_meteor.meret>=1){
            app->meteor_lista_head=spawnMeteors_pos(app->meteor_lista_head , temp_meteor.position.x+50 , temp_meteor.position.y+50 , temp_meteor.meret-1);
            app->meteor_lista_head=spawnMeteors_pos(app->meteor_lista_head , temp_meteor.position.x-50 , temp_meteor.position.y-50 , temp_meteor.meret-1);
        }
        //meteor sz�tl�v�s��rt pont
        if(temp_meteor.meret>=0){
            score+=800;
        }
        
        //renderel�s
        SDL_RenderClear(app->gameRenderer);
        SDL_RenderCopy(app->gameRenderer , app->backround , NULL , NULL);
        SDL_RenderCopyF(app->gameRenderer , app->player.texture , NULL , &app->player.position);
        renderMeteors(app->meteor_lista_head , app->gameRenderer, app->meteor_texture);
        render_shots(app->shot_lista_head , app->gameRenderer , app->shot_texture);
        SDL_RenderCopy(app->gameRenderer , text_to_texture_white(app->font , pont_szoveg , app->gameRenderer , &score_pos) , NULL , &score_pos);
        renderReticle(app->gameRenderer , app->reticle);
        SDL_RenderPresent(app->gameRenderer);

        //j�t�kos hal�la, DIE define debug miatt
        if(app->player.health<=0 && DIE != 0){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return score;
        }
        
        //frame sz�ml�l�t l�ptetem
        frames++;
    }
    
    //warning elker�l�se
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