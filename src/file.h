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
 * @return int hibakezeléshez: -1 ha nem sikerült megnyitni a fájlt, 0 ha sikeres a kiírás.
 */
int write_latest_score(char* path, int latest_score);

/**
 * @brief leelenõrzi, hogy létezik e 'saves' mappa, ha nem akkor létrehozza *mkdir "../saves"* paranccsal.
 * 
 */
void check_for_saves_folder(void);
#endif