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
 * @brief Meteorokat hoz l�tre.
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param index meteorok index�t t�rol� int pointere
 * @param maxX maximum x koordin�ta
 * @param maximum Y koordin�ta
 * \todo ne teremjen k�t meteor egym�son + a j�t�koson(while + collision check)
 */
node* spawnMeteors(struct node* head, int maxX , int maxY);

/**
 * @brief Meteorokat hoz l�tre megadott poz�ci�n
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param index meteorok index�t t�rol� int pointere
 * @param x X poz�ci�
 * @param y Y poz�ci�
 * @param meret meteor m�rete
 */
node* spawnMeteors_pos(struct node* head , int x , int y , int meret);

/**
 * @brief Rendereli a l�ncolt list�ban l�v� meteorokat
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param texture a meteorokhoz haszn�lt text�r�ra mutat� pointer
 */
int renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief kit�rli az eg�sz meteorlist�t
 * 
 * @param head l�ncolt lista els� elem�re mutat� pointer
 */
void delete_meteor_list(node* head);

#endif

