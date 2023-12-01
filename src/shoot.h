#ifndef SHOOT_H
#define SHOOT_H

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "aszteroida.h"
#include "../lib/debugmalloc.h"
#include "defines.h"

/// @brief egy lövés adatait tárolja
typedef struct{
    /// @brief a lövés vízszinteshez képest vett szöge
    double angle;
    /// @brief a lövés mérete és koordinátái
    SDL_FRect position;
}Shot;

/// @brief a lövések listájának egy eleme
typedef struct shot_node{
    ///@brief lövés adatait tárolja
    Shot shot;
    /// @brief következõ listaelem
    struct shot_node* next;
}shot_node;

/**
 * @brief kiszámolja egy kattintás és a játékos közti vektor hajlásszögét
 * 
 * @param shipX játékos X pozíció
 * @param shipY játékos Y pozíció
 * @return double hajlászög radiánban x: [-pi/2 ; 3pi/2]
 */
double calculate_angle_for_shot(int shipX , int shipY);

/**
 * @brief lövések másolása rendererre
 * 
 * @param head lövések listájának head-jére mutató pointer
 * @param renderer gameRenderer
 * @param texture lövések textúrája
 * @return int: 0 ha sikeres | -1 ha sikertelen
 */
int render_shots(shot_node* head, SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief hozzáad egy lövést a lista elejéhez
 * 
 * @param head lövések listájának head-jére mutató pointer
 * @param angle lövés szöge
 * @param shipX játékos X pozíció
 * @param shipY játékos Y pozíció
 * @return struct shot_node* visszatér a hozzáadott lövés pointerjével(dinamikusan foglalt, az egész lista felszabadítására van függvény)
 */
struct shot_node* add_new_shot(struct shot_node* head , double angle, int shipX , int shipY);

/**
 * @brief ellenõrzi hogy a játékos eltalált -e egy meteort a lövéseivel
 * 
 * @param head lövések listájának head-jére mutató pointer pointere
 * @param meteor_head meteorok listájának head-jére mutató pointer pointere
 * @return Meteor visszatér az eltalált meteor adataival(meret=-1 ha nem volt találat, -2 ha valamelyik head NULL)
 */
Meteor check_hits(shot_node** head, node** meteor_head);

/**
 * @brief lövések mozgatása
 * 
 * @param head lövések listájának head-jére mutató pointer
 * @return int: -1 ha head==NULL | 0 ha sikeres
 */
int moveShots(struct shot_node* head , float deltaTime);

/**
 * @brief felszabadítja a lövések listáját
 * 
 * @param head lövések listájának head-jére pointer
 * @return int: -1 ha head==NULL | 0 ha sikeres
 */
int delete_shot_list(struct shot_node* head);

#endif