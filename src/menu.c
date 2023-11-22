#include "menu.h"

int renderCopyMenuContents(SDL_Renderer* renderer , TTF_Font* font , char* username , int latestpoint){
    SDL_Rect pos;
    SDL_Texture* texture;
    char text[19+REKORD_SIZE+1]; //20 + 59

    //Legut�bbi pontsz�m sz�veg
    pos.x=175;
    pos.y=315;
    sprintf(text , "Legut�bbi pontsz�m: %d" , latestpoint);
    texture = text_to_texture(font, text , renderer , &pos);
    SDL_RenderCopy(renderer , texture , NULL , &pos);
    return 0;
}