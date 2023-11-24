#ifndef ASZTEROIDA_H
#define ASZTEROIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "defines.h"
#include "../lib/debugmalloc.h"


typedef struct Meteor{
    SDL_FRect position;
    int meret;
}Meteor;

typedef struct node{
    Meteor meteor;
    struct node *next;
}node;

/**
 * @brief Meteorokat hoz létre
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param maxX maximum X pozíció
 * @param maxY maximum Y pozíció
 * @return node* az új elemre mutató pointer (új elsõ elem)
 */
node* spawnMeteors(struct node* head, int maxX , int maxY);

/**
 * @brief Meteorokat hoz létre megadott pozíción és megadott mérettel
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param x X pozíció
 * @param y Y pozíció
 * @param meret meteor mérete
 * @return node* az új elemre mutató pointer
 */
node* spawnMeteors_pos(struct node* head , int x , int y , int meret);

/**
 * @brief Rendereli a láncolt listában lévõ meteorokat
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param texture a meteorokhoz használt textúrára mutató pointer
 * @return int hibakezeléshez, -1 ha head==NULL
 */
int renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief mozgatja jobbról balra a meteorokat
 * 
 * @param head meteorok láncolt listájának feje
 * @param deltaTime deltaTime, eddig tartott a frame (s = v*t mozgatás mértékének számításához kell)
 * @return int -1 ha head==NULL
 */
int moveMeteors(node* head , float deltaTime);

/**
 * @brief kitörli a pályán kívülre kerülõ meteorokat
 * 
 * @param head 
 */
void delete_out_of_bounds_meteors(node** head);

/**
 * @brief kitörli az egész meteorlistát
 * 
 * @param head láncolt lista elsõ elemére mutató pointer
 */
void delete_meteor_list(node* head);

#endif