#include "ranglista.h"
#include "stdlib.h"
#include "string.h"
#include "file.h"

void insert_ranking(ranglista_node** head , char* nev , int pont){

    ranglista_node* uj = malloc(sizeof(ranglista_node));
    strcpy(uj->adat.nev , nev);
    uj->adat.pontszam = pont;

    ranglista_node* current;
    ranglista_node* prev = NULL;
    for(current= *head ; current!=NULL ; current=current->next){
        if(current->adat.pontszam<=pont){
            if(prev==NULL){
                uj->next = *head;
                *head = uj;
            }else{
                prev->next = uj;
                uj->next = current;
            }
        }
    }
}