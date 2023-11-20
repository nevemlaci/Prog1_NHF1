#include "file.h"


int load_latest_score(char* path){
    FILE* file;
    file = fopen(path , "w+");
    int retval;
    if(fscanf(file,"%d" , &retval)!=1){
        return 0;
    }
    fclose(file);
    return retval;
}

int write_latest_score(char* path , int latest_score){
    FILE* file;
    file = fopen(path , "w");
    if(file==NULL) return -1;
    fprintf(file,"%d" , latest_score);
    fclose(file);
    return 0;
}

ranglista_node* read_ranglista(char* path){
    ranglista_node* head=NULL;
    ranglista_node* prev=NULL;
    FILE* file;
    file = fopen(path, "w+");
    rekord temp;
    if(feof(file)) return head;
    while(!feof(file)){
        if(fscanf(file ,"%s %d" , temp.nev , &temp.pontszam)!=2) return NULL;
            
        head->next=prev;
        prev=head;
    }
    return head;
}


