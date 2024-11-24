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

/// @brief egy eredmény(rekord) adatai a ranglistán
typedef struct rekord{
    /// @brief játékos neve(50 karakter + '\0')
    char nev[51];
    /// @brief elért pontszám
    long long int pontszam;
}rekord;

/// @brief ranglista láncolt listájában egy elem
typedef struct ranglista_node{
    /// @brief adott elem rekordját tartalmazza
    rekord adat;
    /// @brief következõ listaelem
    struct ranglista_node* next;
}ranglista_node;

/// @brief beilleszt egy eredményt a listába, megtartva annak csökkenõ sorrendjét
/// @param head ranglista fej pointer pointere
/// @param nev játékos neve
/// @param pont elért pontszám
void insert_Ranking(ranglista_node** head , char* nev , long long int pont);

/// @brief beolvassa a ranglistát fileból
/// @return a lista legelsõ elemére pointer (az egész lista dinamikusan foglalt, felsazabdítására van külön függvény)
ranglista_node* read_Ranglista_from_file();

/// @brief kiírja a ranglistát fájlba
/// @param head lista legelsõ elemére pointer
/// @return -1 ha a kiírás sikertelen, 0 ha sikeres
int print_Ranglista_to_file(ranglista_node* head);

/// @brief rendereli a listát
/// @param renderer használt renderer
/// @param font használt font
/// @param head lista legelsõ elemére pointer
/// @return -1 ha head==NULL, 0 ha sikeres
int renderRanglista(SDL_Renderer* renderer, TTF_Font* font , ranglista_node* head);

/// @brief felszabadítja az egész ranglistát
/// @param head lista legelsõ elemére pointer
void delete_Ranglista(ranglista_node* head);

#endif