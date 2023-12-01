#include "file.h"

int load_LatestScore(char* path) {
    FILE* file;
    file = fopen(path, "r");
    int retval;
    if(fscanf(file,"%d", &retval)!=1) {
        return 0;
    }
    fclose(file);
    return retval;
}

int write_LatestScore(char* path, int latest_score) {


    FILE* file;
    file = fopen(path, "w");
    if(file==NULL) return -1;
    fprintf(file,"%d", latest_score);
    fclose(file);
    return 0;
}

void check_for_saves_folder(void) {
    DIR* dir;
    dir = opendir("../saves");
    if(dir==NULL) system("mkdir \"../saves\"");
    closedir(dir);
}