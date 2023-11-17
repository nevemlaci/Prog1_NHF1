#ifndef SHOOT_H
#define SHOOT_H

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "aszteroida.h"
#include "../lib/debugmalloc.h"

#define SHOT_SPEED 25.0

typedef struct{
    double angle;
    SDL_FRect position;
}Shot;

typedef struct shot_node{
    Shot shot;
    struct shot_node* next;
}shot_node;

/**
 * @brief kisz�molja egy kattint�s �s a j�t�kos k�zti vektor hajl�ssz�g�t
 * 
 * @param shipX j�t�kos X poz�ci�
 * @param shipY j�t�kos Y poz�ci�
 * @return double hajl�sz�g radi�nban x: [-pi/2 ; 3pi/2]
 */
double calculate_angle_for_shot(int shipX , int shipY);

/**
 * @brief l�v�sek m�sol�sa rendererre
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer
 * @param renderer gameRenderer
 * @param texture l�v�sek text�r�ja
 * @return int hibajelz�sre: 0 ha sikeres | -1 ha sikertelen
 */
int render_shots(struct shot_node* head, SDL_Renderer* renderer, SDL_Texture* texture);

/**
 * @brief hozz�ad egy l�v�st a lista elej�hez
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer
 * @param angle l�v�s sz�ge
 * @param shipX j�t�kos X poz�ci�
 * @param shipY j�t�kos Y poz�ci�
 * @return struct shot_node* visszat�r a hozz�adott l�v�s pointerj�vel
 */
struct shot_node* add_new_shot(struct shot_node* head , double angle, int shipX , int shipY);

/**
 * @brief ellen�rzi hogy a j�t�kos eltal�lt -e egy meteort a l�v�seivel
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer pointere
 * @param meteor_head meteorok list�j�nak head-j�re mutat� pointer pointere
 * @return Meteor visszat�r az eltal�lt meteor adataival(meret=-1 ha nem volt tal�lat, -2 ha valamelyik head NULL)
 */
Meteor check_hits(struct shot_node** head, node** meteor_head);

/**
 * @brief l�v�sek mozgat�sa
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer
 * @return int hibajelz�shez: -1 ha head==NULL | 0 ha sikeres
 */
int move_shots(struct shot_node* head);

/**
 * @brief felszabad�tja a l�v�sek list�j�t
 * 
 * @param head l�v�sek list�j�nak head-j�re pointer
 * @return int int hibajelz�shez: -1 ha head==NULL | 0 ha sikeres
 */
int delete_shot_list(struct shot_node* head);

#endif