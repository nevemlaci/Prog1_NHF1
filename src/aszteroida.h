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
 * @brief Meteorokat hoz l�tre
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param maxX maximum X poz�ci�
 * @param maxY maximum Y poz�ci�
 * @return node* az �j elemre mutat� pointer 
 */
node* spawnMeteors(struct node* head, int maxX , int maxY);

/**
 * @brief Meteorokat hoz l�tre megadott poz�ci�n �s megadott m�rettel
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param x X poz�ci�
 * @param y Y poz�ci�
 * @param meret meteor m�rete
 * @return node* az �j elemre mutat� pointer
 */
node* spawnMeteors_pos(struct node* head , int x , int y , int meret);

/**
 * @brief Rendereli a l�ncolt list�ban l�v� meteorokat
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param texture a meteorokhoz haszn�lt text�r�ra mutat� pointer
 * @return int hibakezel�shez, -1 ha head==NULL
 */
int renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief kit�rli az eg�sz meteorlist�t
 * 
 * @param head l�ncolt lista els� elem�re mutat� pointer
 */
void delete_meteor_list(node* head);

#endif