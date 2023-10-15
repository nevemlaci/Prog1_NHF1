#ifndef LISTA_H
#define LISTA_H


#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <math.h>

#include "aszteroida.h"



typedef struct node{
    Meteor meteor;
    struct node *next;
}node;


#endif