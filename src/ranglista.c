#include "ranglista.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

void insert_ranking(ranglista_node** head , char* nev , int pont){

    ranglista_node* uj = malloc(sizeof(ranglista_node));
    strcpy(uj->adat.nev , nev);
    uj->adat.pontszam = pont;

    ranglista_node* current;
    ranglista_node* prev = NULL;
    if(*head == NULL){
        uj->next=NULL;
        *head = uj;
        return;
    }
    for(current= *head ; current!=NULL ; current=current->next){
        if(current->adat.pontszam<=pont){
            if(prev==NULL){
                uj->next = *head;
                *head = uj;
                return;
            }else{
                prev->next = uj;
                uj->next = current;
                return;
            }
        }
        prev=current;
    }
    uj->next = NULL;
    prev->next=uj;

}

ranglista_node* read_ranglista_from_file(){
    ranglista_node* head=NULL;
    ranglista_node* uj_node=NULL;
    ranglista_node* vege = head;
    FILE* file;
    file = fopen("../saves/ranglista.txt", "r");
    rekord temp;
    if(feof(file)) return head;
    while(!feof(file)){
        if(fscanf(file ,"%s %d\n" , temp.nev , &temp.pontszam)!=2) return NULL;
        uj_node = (ranglista_node*) malloc(sizeof(ranglista_node));
        uj_node->next = NULL;
        uj_node->adat = temp;
        if(head==NULL){
            head=uj_node;
            vege=head;
        }else{
            vege->next = uj_node;
            vege=vege->next;
        }
    }
    fclose(file);
    return head;
}

int print_ranglista_to_file(ranglista_node* head){
    FILE* file;
    file = fopen("../saves/ranglista.txt" , "w+");
    if(file==NULL) return -1;
    ranglista_node* current;

    for(current= head ; current!=NULL ; current=current->next){
        fprintf(file , "%s %d\n" , current->adat.nev , current->adat.pontszam);
    }
    fclose(file);
    return 0;
}