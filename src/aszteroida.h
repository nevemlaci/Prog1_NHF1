#ifndef ASZTEROIDA_H
#define ASZTEROIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>


typedef struct Meteor{
    SDL_FRect position;
    int meret;
    int index;
}Meteor;

typedef struct node{
    Meteor meteor;
    struct node *next;
}node;

/**
 * @file
 * @brief A meteorokat tartalmazó láncolt lista végére illeszt be egy új elemet(meteort)
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param newMeteor az új meteort leíro Meteor típusú változót veszi át
 */
void insertNode(struct node* head , Meteor newMeteor);

/**
 * @file
 * @brief Inicializálja az elsõ meteort
 * 
 * @return node* visszatér az inicializált meteorral
 */
struct node* init_meteor_list(void);

/**
 * @file
 * @brief Meteorokat teremt.
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * \todo ne teremjen két meteor egymáson + a játékoson(while + collision check)
 */
void spawnMeteors(struct node* head , int index);

/**
 * @file
 * @brief Rendereli a láncolt listában lévõ meteorokat
 * 
 * @param head a meteorokat tartalmazó láncolt lista elsõ elemére mutató pointer
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param texture a meteorokhoz használt textúrára mutató pointer
 */
void renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief Kitörli az utolsó elemet a lista végérõl
 * 
 * @param head láncolt lista elsõ elemére mutató pointer
 */
void deleteLastFromList(struct node* head);

/**
 * @brief Egy adott indexû elemet töröl ki a listából
 * 
 * @param head láncolt lista elsõ elemére mutató pointer
 * @param index kitörlendõ elem(meteor) indexe
 */
void deleteFromListIndex(struct node* head , int index);

void delete_meteor_list(node* head);

#endif

