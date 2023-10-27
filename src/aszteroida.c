#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "aszteroida.h"



void insertNode(node* head , Meteor newMeteor){
    struct node* current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = (node*) malloc(sizeof(node));
    current->next->meteor = newMeteor;
    current->next->next = NULL;
}

void spawnMeteors(struct node* head , int index){
    Meteor meteor;
    meteor.position.x = rand() % (816-0+1) + 0;
    meteor.position.y = rand() % (480-0+1) + 0;
    meteor.meret = rand() % (2-0+1) + 0;
    meteor.position.h = 32*pow(2 , meteor.meret);
    meteor.position.w = 32*pow(2 , meteor.meret);
    meteor.index=index;
    
    insertNode(head , meteor);
}

void renderMeteors(node* head , SDL_Renderer* renderer , SDL_Texture* texture){
    node* current = head;
    while(current!=NULL){
        SDL_RenderCopy(renderer , texture , NULL , &current->meteor.position);
        current = current->next;
    }
}

void deleteLastFromList(struct node* head){
    node* current = head;
    while(current->next->next!=NULL){
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

void deleteFromListIndex(struct node* head , int index){
    if(index==0){
        node * next_node = head->next;
        free(head);
        head = next_node;
        return;
    }
    node* current = head;
    node* temp = NULL;

    while(current->next->meteor.index!=index){
        if(current->next==NULL){
            break;
        }
        current=current->next;
        
    }
    if (current->next == NULL) {
        deleteLastFromList(head);
        printf("Deleted item with index(last):%d\n" , index);
        return;
    }
    temp = current->next;
    current->next = temp->next;

    free(temp);
    printf("Deleted item with index:%d\n" , index);
}


struct node* init_meteor_list(void){
    Meteor kezdo_meteor;
    kezdo_meteor.meret=0;
    kezdo_meteor.position.x = 3000;
    kezdo_meteor.position.y = 3000;
    kezdo_meteor.position.w = 0;
    kezdo_meteor.position.h = 0;
    kezdo_meteor.index = 0;
    node* head = (node*) malloc(sizeof(node));
    head->meteor = kezdo_meteor;
    head->next = NULL;

    return head;
}

void delete_meteor_list(node* head){
    node* current = head;
    node* temp;
    while(current->next != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    free(current);
}