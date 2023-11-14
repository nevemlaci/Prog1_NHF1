#ifndef FILE_H
#define FILE_H
#include <stdio.h>

/**
 * @brief betölti a legutóbbi sessionben elért pontszámot
 * 
 * @param path fájl elérési útja
 * @return int legutóbbi sessionben elért pontszám
 */
int load_latest_score(char* path);

/**
 * @brief kiírja a legutóbbi sessionben lért pontszámot fájlba
 * 
 * @param path 
 * @param latest_score 
 * @return int 
 */
int write_latest_score(char* path, int latest_score);
#endif