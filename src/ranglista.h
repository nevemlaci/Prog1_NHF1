#ifndef RANGLISTA_H
#define RANGLISTA_H



typedef struct rekord{
    char nev[50];
    int pontszam;
}rekord;

typedef struct ranglista_node{
    rekord adat;
    struct ranglista_node* next;
}ranglista_node;

void insert_ranking(ranglista_node** head , char* nev , int pont);

ranglista_node* read_ranglista_from_file();

int print_ranglista_to_file(ranglista_node* head);

#endif