#include "menu.h"

//nem túl optimális függvények de egy mai gép azért kibírja és cba újraírni most mindent:'D

int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint){
    SDL_Rect pos;
    char text[19+REKORD_SIZE+1]; //20 + 59
    //Legutóbbi pontszám szöveg
    pos.x=175;
    pos.y=315;
    sprintf(text , "Legutóbbi pontszám: %d" , latestpoint);
    SDL_Texture* texture = text_to_texture(font, text , renderer , &pos);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    SDL_DestroyTexture(texture);
    return 0;
}

void render_GetUsername(SDL_Renderer* renderer , TTF_Font* font , char* username){
    SDL_Rect pos;
    pos.x=0;
    pos.y=0;
    SDL_Texture* texture = text_to_texture(font, "Írj be egy nevet a terminálba! Ne használj ékezetes karaktereket!" , renderer , &pos);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
    scanf("%s" , username);
}

int renderPlayButton(SDL_Renderer* renderer , TTF_Font* font){
    SDL_Rect pos;
    pos.x = 50;
    pos.y = 50; 
    SDL_Texture* texture = text_to_texture(font , "PLAY" , renderer , &pos);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    SDL_DestroyTexture(texture);
    return 0;
}

SDL_Rect calculatePlayButtonSize(SDL_Renderer* renderer , TTF_Font* font){
    SDL_Color black = {0, 0, 0};
    SDL_Rect pos;
    pos.x = 50;
    pos.y = 50; 
    SDL_Surface* surf = TTF_RenderText_Blended(font , "PLAY" , black);
    pos.h = surf->h;
    pos.w = surf->w;
    SDL_FreeSurface(surf);
    return pos;
}

bool checkPlayButton(SDL_Rect* play_pos){
    int x , y;
    SDL_GetMouseState(&x , &y);
    SDL_Rect click = {x , y , 1 , 1};
    return SDL_HasIntersection(play_pos , &click);
}

int renderHardButton(SDL_Renderer* renderer , TTF_Font* font , bool* hardmode){
    SDL_Rect pos;
    char text[16]; 
    pos.x=50;
    pos.y=110;
    sprintf(text , "Nehéz mód: %s" , *hardmode? "Igen" : "Nem");
    SDL_Texture* texture = text_to_texture(font, text , renderer , &pos);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    SDL_DestroyTexture(texture);
    return 0;
}

SDL_Rect calculateHardButtonSize(SDL_Renderer* renderer , TTF_Font* font , bool* hardmode){
    SDL_Color black = {0, 0, 0};
    SDL_Rect pos;
    pos.x = 50;
    pos.y = 90; 
    char szoveg[16]; //Nehéz mód: Igen
    sprintf(szoveg , "Nehéz mód: %s" , *hardmode? "Igen" : "Nem");
    SDL_Surface* surf = TTF_RenderText_Blended(font , szoveg , black);
    pos.h = surf->h;
    pos.w = surf->w;
    SDL_FreeSurface(surf);
    return pos;
}

bool checkHardButton(SDL_Rect* hard_pos){
    int x , y;
    SDL_GetMouseState(&x , &y);
    SDL_Rect click = {x , y , 1 , 1};
    return SDL_HasIntersection(hard_pos , &click);
}

