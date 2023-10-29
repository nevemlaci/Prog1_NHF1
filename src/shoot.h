#ifndef SHOOT_H
#define SHOOT_H

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>



typedef struct{
    int angle;
    SDL_FRect position;
}Shot;

typedef struct{
    Shot shot;
    struct shot_node* next;
}shot_node;

int calculate_angle_for_shot(int shipX , int shipY , int clickX , int clickY);

int init_shot_list(shot_node* head);

int render_shots(shot_node* head, SDL_Renderer* renderer, SDL_Texture* texture);

int add_new_shot(shot_node* head);

#endif