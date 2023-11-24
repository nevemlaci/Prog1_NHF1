#ifndef RANGLISTA_H
#define RANGLISTA_H

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "defines.h"
#include "font.h"
#include <SDL_ttf.h>
#include <SDL.h>
#include "../lib/debugmalloc.h"

typedef struct rekord{
    char nev[51];
    int pontszam;
}rekord;

typedef struct ranglista_node{
    rekord adat;
    struct ranglista_node* next;
}ranglista_node;

void insert_ranking(ranglista_node** head , char* nev , int pont);

ranglista_node* read_ranglista_from_file();

int print_ranglista_to_file(ranglista_node* head);

int renderRanglista(SDL_Renderer* renderer, TTF_Font* font , ranglista_node* head);

void delete_ranglista(ranglista_node* head);

#endif