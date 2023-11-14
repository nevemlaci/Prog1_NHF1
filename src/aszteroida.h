#ifndef ASZTEROIDA_H
#define ASZTEROIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
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
 * @file
 * @brief Meteorokat hoz létre.
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param index meteorok indexét tároló int pointere
 * @param maxX maximum x koordináta
 * @param maximum Y koordináta
 * \todo ne teremjen két meteor egymáson + a játékoson(while + collision check)
 */
node* spawnMeteors(struct node* head, int maxX , int maxY);

/**
 * @brief Meteorokat hoz létre megadott pozíción
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param index meteorok indexét tároló int pointere
 * @param x X pozíció
 * @param y Y pozíció
 * @param meret meteor mérete
 */
node* spawnMeteors_pos(struct node* head , int x , int y , int meret);

/**
 * @brief Rendereli a láncolt listában lévõ meteorokat
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param texture a meteorokhoz használt textúrára mutató pointer
 */
int renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief kitörli az egész meteorlistát
 * 
 * @param head láncolt lista elsõ elemére mutató pointer
 */
void delete_meteor_list(node* head);

#endif

