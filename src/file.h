#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <dirent.h>
#include "ranglista.h"


/**
 * @brief betölti a legutóbbi sessionben elért pontszámot
 * 
 * @param path fájl elérési útja
 * @return int legutóbbi sessionben elért pontszám
 */
int load_latest_score(char* path);

/**
 * @brief kiírja a legutóbbi sessionben elért pontszámot fájlba
 * 
 * @param path fájl elérési útja
 * @param latest_score elért pontszám
 * @return int | -1 ha nem sikerült megnyitni a fájlt, 0 ha sikeres a kiírás.
 */
int write_latest_score(char* path, int latest_score);

///@brief leelenõrzi, hogy létezik -e "saves" mappa és ha nem akkor létrehozza
///@note (mkdir "../saves"), macOS-en lehetséges hogy nem fut
void check_for_saves_folder(void);
#endif