#include "aszteroida.h"
    

node* spawnMeteors(struct node* head, int maxX , int maxY){
    Meteor meteor;
    
    meteor.meret = rand() % (2-0+1) + 0;
    maxY -= 32*pow(2 , meteor.meret);
    meteor.position.x = rand() % (maxX-300+1) + 300;
    meteor.position.y = rand() % (maxY-0+1) + 0;
    meteor.angle = rand() % (360-0+1) + 0;
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
    meteor.angle = rand() % (360-0+1) + 0;
    node* uj = (node*) malloc(sizeof(node));
    uj->meteor = meteor;
    uj->next=head;
    return uj;
}

int renderMeteors(node* head , SDL_Renderer* renderer , SDL_Texture* texture){
    if(head==NULL) return -1;
    node* current;
    for(current = head ; current!=NULL ; current = current->next){
        SDL_RenderCopyExF(renderer , texture , NULL , &current->meteor.position , current->meteor.angle , NULL , SDL_FLIP_NONE);
    }
    return 0;
}

int moveMeteors(node* head , float deltaTime){
    if(head==NULL) return -1;
    node* current;
    for(current = head ; current!=NULL ; current = current->next){
        current->meteor.position.x-=METEOR_SPEED*deltaTime;
    }
    return 0;
}

void deleteOutOfBoundsMeteors(node** head){
    node* current = *head;
    node* prev = NULL;
    if(*head == NULL) return;
    for(current = *head ; current!=NULL ; ){
        if(current->meteor.position.x  < -32 * pow(2 , current->meteor.meret))
        {
            if(prev==NULL){
                *head = current->next;
                free(current);
                current = *head;
            }else{
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }else{
            prev=current;
            current=current->next;
        }

    }
}

void deleteMeteorList(node* head){
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