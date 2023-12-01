#ifndef RETICLE_H
#define RETICLE_H

#include <SDL.h>

/// @brief rendereli a célkeresztet a játékban
/// @param renderer játék rendererje
/// @param texture a célkereszt textúrája
void renderReticle(SDL_Renderer* renderer, SDL_Texture* texture);

#endif