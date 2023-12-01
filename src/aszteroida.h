#ifndef ASZTEROIDA_H
#define ASZTEROIDA_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "defines.h"
#include "../lib/debugmalloc.h"


/// @brief egy meteor tulajdons�gait tartalmazza
typedef struct Meteor{
    /// @brief meteor koordin�t�it �s m�reteit t�rolja
    SDL_FRect position;
    /// @brief meteor m�rete: 0-2
    int meret;
    /// @brief beteor k�z�ppont k�r�li elforgat�s�nak sz�ge(random)
    float angle;
}Meteor;

/// @brief meteorok l�ncolt list�j�ban egy elem
typedef struct node{
    /// @brief adott listaelemben t�rolt meteor adatai
    Meteor meteor;
    /// @brief k�vetkez� listaelem
    struct node *next;
}node;

/**
 * @brief Meteorokat hoz l�tre
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param maxX maximum X poz�ci�
 * @param maxY maximum Y poz�ci�
 * @return node* az �j elemre mutat� pointer (�j els� elem lesz)
 */
node* spawnMeteors(struct node* head, int maxX , int maxY);

/**
 * @brief Meteorokat hoz l�tre megadott poz�ci�n �s megadott m�rettel
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param x X poz�ci�
 * @param y Y poz�ci�
 * @param meret az �jmeteor m�rete
 * @return node* az �j elemre mutat� pointer (�j els� elem lesz)
 */
node* spawnMeteors_pos(struct node* head , int x , int y , int meret);

/**
 * @brief A rendererre m�solja a l�ncolt list�ban l�v� meteorokat
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param texture a meteorokhoz haszn�lt text�r�ra mutat� pointer
 * @return int -1 ha head==NULL
 */
int renderMeteors(struct node* head , SDL_Renderer* renderer , SDL_Texture* texture);

/**
 * @brief mozgatja jobbr�l balra a meteorokat
 * 
 * @param head meteorok l�ncolt list�j�nak feje
 * @param deltaTime deltaTime, eddig tartott a frame (s = v*t mozgat�s m�rt�k�nek sz�m�t�s�hoz kell)
 * @return int -1 ha head==NULL
 */
int moveMeteors(node* head , float deltaTime);

/**
 * @brief kit�rli a p�ly�n k�v�lre ker�l� meteorokat
 * 
 * @param head meteorok l�ncolt list�j�nak fej�re mutat� pointer pointere (kell, mivel head is t�rl�sre ker�lhet)
 */
void deleteOutOfBoundsMeteors(node** head);

/**
 * @brief kit�rli az eg�sz meteorlist�t
 * 
 * @param head l�ncolt lista els� elem�re mutat� pointer
 */
void deleteMeteorList(node* head);

#endif