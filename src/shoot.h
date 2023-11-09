#ifndef SHOOT_H
#define SHOOT_H

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "aszteroida.h"

#define SHOT_SPEED 10.0

typedef struct{
    double angle;
    SDL_FRect position;
}Shot;

struct shot_node{
    Shot shot;
    struct shot_node* next;
};

double calculate_angle_for_shot(int shipX , int shipY);

int render_shots(struct shot_node* head, SDL_Renderer* renderer, SDL_Texture* texture);

struct shot_node* add_new_shot(struct shot_node* head , double angle, int shipX , int shipY);

int move_shots(struct shot_node* head);

/**
 * @brief 
 * @todo megcsinálni
 * 
 * @param head 
 * @param meteor_head 
 * @return int 
 */
int check_hits(struct shot_node* head, node* meteor_head);

int move_shots(struct shot_node* head);

#endif