#ifndef FILE_H
#define FILE_H
#include <stdio.h>

int load_latest_score(char* path);

int write_latest_score(char* path, int latest_score);
#endif