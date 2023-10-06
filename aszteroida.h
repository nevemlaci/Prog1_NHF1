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

/**
 * @brief A meteorokat tartalmaz� l�ncolt lista v�g�re illeszt be egy �j elemet(meteort)
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param newMeteor az �j meteort le�ro Meteor t�pus� v�ltoz�t veszi �t
 */
void insertNode(node* head , Meteor newMeteor){
    struct node* current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = (node*) malloc(sizeof(node));
    current->next->meteor = newMeteor;
    current->next->next = NULL;
}

/**
 * @brief Inicializ�lja az els� meteort
 * 
 * @return node* visszat�r az inicializ�lt meteorral
 */
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

/**
 * @brief Rendereli a l�ncolt list�ban l�v� meteorokat
 * 
 * @param head a meteorokat tartalmaz� l�ncolt lista els� elem�re mutat� pointer
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param texture a meteorokhoz haszn�lt text�r�ra mutat� pointer
 */
void renderMeteors(node* head , SDL_Renderer* renderer , SDL_Texture* texture){
    node* current = head;
    while(current!=NULL){
        SDL_RenderCopy(renderer , texture , NULL , &current->meteor.position);
        current = current->next;
    }
}

