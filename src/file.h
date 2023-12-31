#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <dirent.h>
#include "ranglista.h"

/**
 * @brief bet�lti a legut�bbi sessionben el�rt pontsz�mot
 * 
 * @param path f�jl el�r�si �tja
 * @return int legut�bbi sessionben el�rt pontsz�m
 */
int load_LatestScore(char* path);

/**
 * @brief ki�rja a legut�bbi sessionben el�rt pontsz�mot f�jlba
 * 
 * @param path f�jl el�r�si �tja
 * @param latest_score el�rt pontsz�m
 * @return int | -1 ha nem siker�lt megnyitni a f�jlt, 0 ha sikeres a ki�r�s.
 */
int write_LatestScore(char* path, int latest_score);

///@brief leelen�rzi, hogy l�tezik -e "saves" mappa �s ha nem akkor l�trehozza
///@note (mkdir "../saves"), macOS-en lehets�ges hogy nem fut
void check_for_saves_folder(void);
#endif