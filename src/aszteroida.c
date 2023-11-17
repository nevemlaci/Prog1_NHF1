#include "aszteroida.h"
    

node* spawnMeteors(struct node* head, int maxX , int maxY){
    Meteor meteor;
    meteor.position.x = rand() % (maxX-0+1) + 0;
    meteor.position.y = rand() % (maxY-0+1) + 0;
    meteor.meret = rand() % (2-0+1) + 0;
    meteor.position.h = 32*pow(2 , meteor.meret);
    meteor.position.w = 32*pow(2 , meteor.meret);
    node* uj = (node*) malloc(sizeof(node));
    uj->meteor = meteor;
    uj->next=head;
    return uj;
}

node* spawnMeteors_pos(struct node* head, int x , int y , int meret){
    Meteor meteor;
    meteor.position.x = x;
    meteor.position.y = y;
    meteor.meret = meret;
    meteor.position.h = 32*pow(2 , meteor.meret);
    meteor.position.w = 32*pow(2 , meteor.meret);
    node* uj = (node*) malloc(sizeof(node));
    uj->meteor = meteor;
    uj->next=head;
    return uj;
}

int renderMeteors(node* head , SDL_Renderer* renderer , SDL_Texture* texture){
    if(head==NULL) return -1;
    node* current;
    for(current = head ; current!=NULL ; current = current->next){
        SDL_RenderCopyF(renderer , texture , NULL , &current->meteor.position);
    }
    return 0;
}

void delete_meteor_list(node* head){
    if(head==NULL) return;
    node* current = head;
    node* temp;
    while(current->next != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    free(current);
}