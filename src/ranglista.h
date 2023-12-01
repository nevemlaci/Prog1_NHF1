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

/// @brief egy eredm�ny(rekord) adatai a ranglist�n
typedef struct rekord{
    /// @brief j�t�kos neve(50 karakter + '\0')
    char nev[51];
    /// @brief el�rt pontsz�m
    int pontszam;
}rekord;

/// @brief ranglista l�ncolt list�j�ban egy elem
typedef struct ranglista_node{
    /// @brief adott elem rekordj�t tartalmazza
    rekord adat;
    /// @brief k�vetkez� listaelem
    struct ranglista_node* next;
}ranglista_node;

/// @brief beilleszt egy eredm�nyt a list�ba, megtartva annak cs�kken� sorrendj�t
/// @param head ranglista fej pointer pointere
/// @param nev j�t�kos neve
/// @param pont el�rt pontsz�m
void insert_Ranking(ranglista_node** head , char* nev , int pont);

/// @brief beolvassa a ranglist�t fileb�l
/// @return a lista legels� elem�re pointer (az eg�sz lista dinamikusan foglalt, felsazabd�t�s�ra van k�l�n f�ggv�ny)
ranglista_node* read_Ranglista_from_file();

/// @brief ki�rja a ranglist�t f�jlba
/// @param head lista legels� elem�re pointer
/// @return -1 ha a ki�r�s sikertelen, 0 ha sikeres
int print_Ranglista_to_file(ranglista_node* head);

/// @brief rendereli a list�t
/// @param renderer haszn�lt renderer
/// @param font haszn�lt font
/// @param head lista legels� elem�re pointer
/// @return -1 ha head==NULL, 0 ha sikeres
int renderRanglista(SDL_Renderer* renderer, TTF_Font* font , ranglista_node* head);

/// @brief felszabad�tja az eg�sz ranglist�t
/// @param head lista legels� elem�re pointer
void delete_Ranglista(ranglista_node* head);

#endif