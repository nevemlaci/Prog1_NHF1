#ifndef ASZTEROIDA_H
#define ASZTEROIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "defines.h"
#include "../lib/debugmalloc.h"


/// @brief egy meteor tulajdonságait tartalmazza
typedef struct Meteor{
    /// @brief meteor koordinátáit és méreteit tárolja
    SDL_FRect position;
    /// @brief meteor mérete: 0-2
    int meret;
    /// @brief beteor középpont körüli elforgatásának szöge(random)
    float angle;
}Meteor;

/// @brief meteorok láncolt listájában egy elem
typedef struct meteor_node{
    /// @brief adott listaelemben tárolt meteor adatai
    Meteor meteor;
    /// @brief következõ listaelem
    struct meteor_node *next;
}meteor_node;

/**
 * @brief Meteorokat hoz létre
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param maxX maximum X pozíció
 * @param maxY maximum Y pozíció
 * @return node* az új elemre mutató pointer (új elsõ elem lesz)
 */
meteor_node* spawnMeteors(struct meteor_node* head, int maxX , int maxY);

/**
 * @brief Meteorokat hoz létre megadott pozíción és megadott mérettel
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param x X pozíció
 * @param y Y pozíció
 * @param meret az újmeteor mérete
 * @return node* az új elemre mutató pointer (új elsõ elem lesz)
 */
meteor_node* spawnMeteors_pos(struct meteor_node* head , int x , int y , int meret);

/**
 * @brief A rendererre másolja a láncolt listában lévõ meteorokat
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param texture a meteorokhoz használt textúrára mutató pointer
 * @return int -1 ha head==NULL
 */
int renderMeteors(struct meteor_node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief mozgatja jobbról balra a meteorokat
 * 
 * @param head meteorok láncolt listájának feje
 * @param deltaTime deltaTime, eddig tartott a frame (s = v*t mozgatás mértékének számításához kell)
 * @return int -1 ha head==NULL
 */
int moveMeteors(meteor_node* head , float deltaTime);

/**
 * @brief kitörli a pályán kívülre kerülõ meteorokat
 * 
 * @param head meteorok láncolt listájának fejére mutató pointer pointere (kell, mivel head is törlésre kerülhet)
 */
void deleteOutOfBoundsMeteors(meteor_node** head);

/**
 * @brief kitörli az egész meteorlistát
 * 
 * @param head láncolt lista elsõ elemére mutató pointer
 */
void deleteMeteorList(meteor_node* head);

#endif