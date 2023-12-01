#include "reticle.h"

void renderReticle(SDL_Renderer* renderer, SDL_Texture* texture){
    int x, y;
    SDL_GetMouseState(&x , &y);
    SDL_Rect pos = {x-8 , y-8 , 16 , 16};
    SDL_RenderCopy(renderer , texture , NULL, &pos);
}