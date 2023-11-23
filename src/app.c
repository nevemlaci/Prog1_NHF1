#include "app.h"




App init_App(int screenW , int screenH){
    App app;
    SDL_Texture* play_button;
    app.menuWindow = SDL_CreateWindow("Asteroids - Menu" , (screenW/2) - (MENU_W/2) , (screenH/2) - (MENU_H/2) , MENU_W , MENU_H, 0);
    app.menuRenderer = SDL_CreateRenderer(app.menuWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.gameWindow = SDL_CreateWindow("" , screenW/2 - 816/2 , screenH/2 - 480/2 , 816 , 480 , SDL_WINDOW_FULLSCREEN_DESKTOP); 
    app.gameRenderer = SDL_CreateRenderer(app.gameWindow , -1 , SDL_RENDERER_ACCELERATED);
    app.screenW = screenW;
    app.screenH = screenH;
    app.font = TTF_OpenFont("../materials/font/comic.ttf" , 25);
    app.font_big = TTF_OpenFont("../materials/font/comic.ttf" , 55);
    app.isGame = false , 
    app.isMenu = true;
    reset_input(&app.input);
    init_player(100 , 100 , 1 , app.gameRenderer , "../materials/images/player.png" , &app.player);
    app.backround = IMG_LoadTexture(app.gameRenderer , "../materials/images/background.jpeg");
    app.meteor_lista_head = NULL;
    app.meteor_texture = IMG_LoadTexture(app.gameRenderer , "../materials/images/meteor_1.png");
    app.latest_score = 0;
    app.shot_lista_head = NULL;
    app.shot_texture = IMG_LoadTexture(app.gameRenderer , "..//materials/images/shot.png");
    app.ranglista_head = read_ranglista_from_file();
    app.latest_score = load_latest_score("../saves/latestscores.txt");
    SDL_SetRenderDrawColor(app.menuRenderer , MENU_COLOR);
    return app;
}

void runMenu(App* app){
    SDL_HideWindow(app->gameWindow);
    SDL_ShowWindow(app->menuWindow);
    
    //megk�rj�k a felhaszn�l�t hogy adjon meg egy nevet
    render_get_username(app->menuRenderer , app->font , app->username);

    SDL_Rect play_pos = calculatePlayButtonSize(app->menuRenderer , app->font_big);

    SDL_Event e;
    
    while(true){
        while (SDL_PollEvent(&e)){
            switch (e.type){
                //Az eg�sz j�t�k bez�r�sa
                case SDL_WINDOWEVENT:
                    if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                        print_ranglista_to_file(app->ranglista_head);
                        return;
                    }
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode == SDL_SCANCODE_T){
                        //Men�b�l j�t�kba v�lt�s
                        app->latest_score=runGame(app);
                        //Ez a j�t�k v�ge ut�n fut m�r le.
                        resetGame(app);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(checkPlayButton(&play_pos)){
                        //Men�b�l j�t�kba v�lt�s
                        app->latest_score=runGame(app);
                        //Ez a j�t�k v�ge ut�n fut m�r le.
                        resetGame(app);
                    }
                    break;
            }
        }
        //renderelj�k a men� tartalm�t
        SDL_RenderClear(app->menuRenderer);
        renderPlayButton(app->menuRenderer , app->font_big);
        renderRanglista(app->menuRenderer , app->font, app->ranglista_head);
        renderCopyMenuContents(app->menuRenderer , app->font , app->username , app->latest_score);
        SDL_RenderPresent(app->menuRenderer);
    }
    return;
}

int runGame(App* app){
    
    app->isGame = true;
    app->isMenu = false;
    SDL_ShowWindow(app->gameWindow);
    SDL_HideWindow(app->menuWindow);

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
        //minden framen 1 pont
        score++;
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
        if(frames >= BASE_SPAWN_RATE){
            app->meteor_lista_head = spawnMeteors(app->meteor_lista_head, app->screenW , app->screenH);
            frames=0;       
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
        move_player(&app->player , app->input);
        move_shots(app->shot_lista_head);
        moveMeteors(app->meteor_lista_head);

        //collision checkek
        utkozes_ellenorzese(&app->meteor_lista_head , &app->player);

        //meteor kett�v�laszt�sa ha az eltal�lt meteor nem a legkisebb m�ret�(egybe ker�l n�ha 2 meteor de m1)
        temp_meteor=check_hits(&app->shot_lista_head, &app->meteor_lista_head);
        if(temp_meteor.meret>=1){
            
            app->meteor_lista_head=spawnMeteors_pos(app->meteor_lista_head , temp_meteor.position.x+50 , temp_meteor.position.y+50 , temp_meteor.meret-1);
            app->meteor_lista_head=spawnMeteors_pos(app->meteor_lista_head , temp_meteor.position.x-50 , temp_meteor.position.y-50 , temp_meteor.meret-1);
        }
        if(temp_meteor.meret>=0){
            score+=200;
        }
        
        //renderel�s
        SDL_RenderClear(app->gameRenderer);
        SDL_RenderCopy(app->gameRenderer , app->backround , NULL , NULL);
        SDL_RenderCopyF(app->gameRenderer , app->player.texture , NULL , &app->player.position);
        renderMeteors(app->meteor_lista_head , app->gameRenderer, app->meteor_texture);
        render_shots(app->shot_lista_head , app->gameRenderer , app->shot_texture);
        SDL_RenderPresent(app->gameRenderer);

        //j�t�kos hal�la, DIE define debug miatt
        if(app->player.health<=0 && DIE != 0){
            app->isGame=false;
            app->isMenu=true;
            SDL_HideWindow(app->gameWindow);
            SDL_ShowWindow(app->menuWindow);
            return score;
        }

        //16 ms delay -> kb. 60 k�pkocka / m�sodperc
        SDL_Delay(16);
        
        //frame sz�ml�l�t l�ptetem
        frames++;
    }
    
    //warning elker�l�se
    return score;
}

void resetGame(App* app){
    insert_ranking(&app->ranglista_head , app->username , app->latest_score);
    reset_input(&app->input);
    delete_meteor_list(app->meteor_lista_head);
    app->meteor_lista_head=NULL;
    delete_shot_list(app->shot_lista_head);
    app->shot_lista_head=NULL;
    init_player(100 , 100 , 1 , app->gameRenderer , "../materials/images/player.png" , &app->player);
}