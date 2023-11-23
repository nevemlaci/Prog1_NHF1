#include "menu.h"

int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint){
    SDL_Rect pos;
    SDL_Texture* texture;
    char text[19+REKORD_SIZE+1]; //20 + 59

    //Legutóbbi pontszám szöveg
    pos.x=175;
    pos.y=315;
    sprintf(text , "Legutóbbi pontszám: %d" , latestpoint);
    texture = text_to_texture(font, text , renderer , &pos);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    return 0;
}

void render_get_username(SDL_Renderer* renderer , TTF_Font* font , char* username){
    SDL_Rect pos;
    SDL_Texture* texture;
    pos.x=0;
    pos.y=0;
    texture = text_to_texture(font, "Írj be egy nevet a terminálba! Ne használj ékezetes karaktereket!" , renderer , &pos);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    SDL_RenderPresent(renderer);
    scanf("%s" , username);
}

int renderPlayButton(SDL_Renderer* renderer , TTF_Font* font){
    SDL_Rect pos;
    pos.x = 50;
    pos.y = 50; 
    SDL_RenderCopy(renderer , text_to_texture(font , "PLAY" , renderer , &pos), NULL , &pos);
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

