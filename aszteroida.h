#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <math.h>


typedef struct{
    SDL_Rect position;
    int meret;
}Meteor;

typedef struct node{
    Meteor meteor;
    struct node *next;
}node;

void insertNode(node* head , Meteor newMeteor){
    struct node* current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = (node*) malloc(sizeof(node));
    current->next->meteor = newMeteor;
    current->next->next = NULL;
}




node* init_meteor_list(void){
    Meteor kezdo_meteor;
    kezdo_meteor.meret=0;
    kezdo_meteor.position.x = 10;
    kezdo_meteor.position.y = 10;
    kezdo_meteor.position.w = 32;
    kezdo_meteor.position.h = 32;
    node* head = (node*) malloc(sizeof(node));
    head->meteor = kezdo_meteor;
    head->next = NULL;

    return head;
    
}

/**
 * @brief Meteorokat teremt.
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * \todo ne teremjen k�t meteor egym�son + a j�t�koson(while + collision check)
 */
void spawnMeteors(node* head){
    Meteor meteor;
    meteor.position.x = rand() % (816-0+1) + 0;
    meteor.position.y = rand() % (480-0+1) + 0;
    meteor.meret = rand() % (2-0+1) + 0;
    meteor.position.h = 32*pow(2 , meteor.meret);
    meteor.position.w = 32*pow(2 , meteor.meret);
    
    insertNode(head , meteor);
}

void renderMeteors(node* head , SDL_Renderer* renderer , SDL_Texture* texture){
    node* current = head;
    while(current!=NULL){
        SDL_RenderCopy(renderer , texture , NULL , &current->meteor.position);
        current = current->next;
    }
}

