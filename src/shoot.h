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

/// @brief egy l�v�s adatait t�rolja
typedef struct{
    /// @brief a l�v�s v�zszinteshez k�pest vett sz�ge
    double angle;
    /// @brief a l�v�s m�rete �s koordin�t�i
    SDL_FRect position;
}Shot;

/// @brief a l�v�sek list�j�nak egy eleme
typedef struct shot_node{
    ///@brief l�v�s adatait t�rolja
    Shot shot;
    /// @brief k�vetkez� listaelem
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
 * @return int: 0 ha sikeres | -1 ha sikertelen
 */
int render_shots(shot_node* head, SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief hozz�ad egy l�v�st a lista elej�hez
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer
 * @param angle l�v�s sz�ge
 * @param shipX j�t�kos X poz�ci�
 * @param shipY j�t�kos Y poz�ci�
 * @return struct shot_node* visszat�r a hozz�adott l�v�s pointerj�vel(dinamikusan foglalt, az eg�sz lista felszabad�t�s�ra van f�ggv�ny)
 */
struct shot_node* add_new_shot(struct shot_node* head , double angle, int shipX , int shipY);

/**
 * @brief ellen�rzi hogy a j�t�kos eltal�lt -e egy meteort a l�v�seivel
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer pointere
 * @param meteor_head meteorok list�j�nak head-j�re mutat� pointer pointere
 * @return Meteor visszat�r az eltal�lt meteor adataival(meret=-1 ha nem volt tal�lat, -2 ha valamelyik head NULL)
 */
Meteor check_hits(shot_node** head, node** meteor_head);

/**
 * @brief l�v�sek mozgat�sa
 * 
 * @param head l�v�sek list�j�nak head-j�re mutat� pointer
 * @return int: -1 ha head==NULL | 0 ha sikeres
 */
int moveShots(struct shot_node* head , float deltaTime);

/**
 * @brief felszabad�tja a l�v�sek list�j�t
 * 
 * @param head l�v�sek list�j�nak head-j�re pointer
 * @return int: -1 ha head==NULL | 0 ha sikeres
 */
int delete_shot_list(struct shot_node* head);

#endif