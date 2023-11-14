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
    int index;
}Meteor;

typedef struct node{
    Meteor meteor;
    struct node *next;
}node;

/**
 * @file
 * @brief A meteorokat tartalmaz� l�ncolt lista v�g�re illeszt be egy �j elemet(meteort)
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param newMeteor az �j meteort le�ro Meteor t�pus� v�ltoz�t veszi �t
 */
void insertNode(struct node* head , Meteor newMeteor);

/**
 * @file
 * @brief Inicializ�lja az els� meteort
 * @todo �t�rni �gy a programot, hogy ne kelljen ez a f�ggv�ny
 * 
 * @return node* visszat�r az inicializ�lt meteorral
 */
struct node* init_meteor_list(void);

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
void spawnMeteors(struct node* head , int* index , int maxX , int maxY);

/**
 * @brief Meteorokat hoz l�tre megadott poz�ci�n
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param index meteorok index�t t�rol� int pointere
 * @param x X poz�ci�
 * @param y Y poz�ci�
 * @param meret meteor m�rete
 */
void spawnMeteors_pos(struct node* head , int* index , int x , int y , int meret);

/**
 * @brief Rendereli a l�ncolt list�ban l�v� meteorokat
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param texture a meteorokhoz haszn�lt text�r�ra mutat� pointer
 */
void renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief Kit�rli az utols� elemet a lista v�g�r�l
 * @todo �t�rni �gy, hogy ne kelljen ez a fgv
 * @param head l�ncolt lista els� elem�re mutat� pointer
 */
void deleteLastFromList(struct node* head);

/**
 * @brief Egy adott index� elemet t�r�l ki a list�b�l
 * 
 * @param head l�ncolt lista els� elem�re mutat� pointer
 * @param index kit�rlend� elem(meteor) indexe
 */
void deleteFromListIndex(struct node* head , int index);

/**
 * @brief kit�rli az eg�sz meteorlist�t
 * 
 * @param head l�ncolt lista els� elem�re mutat� pointer
 */
void delete_meteor_list(node* head);

#endif

