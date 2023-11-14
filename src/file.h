#ifndef FILE_H
#define FILE_H
#include <stdio.h>

/**
 * @brief bet�lti a legut�bbi sessionben el�rt pontsz�mot
 * 
 * @param path f�jl el�r�si �tja
 * @return int legut�bbi sessionben el�rt pontsz�m
 */
int load_latest_score(char* path);

/**
 * @brief ki�rja a legut�bbi sessionben l�rt pontsz�mot f�jlba
 * 
 * @param path 
 * @param latest_score 
 * @return int 
 */
int write_latest_score(char* path, int latest_score);
#endif