#include "shoot.h"
#include "../lib/debugmalloc.h"
#define PI 3.14159265358

double calculate_angle_for_shot(int shipX , int shipY){
    int clickX ,clickY;
    SDL_GetMouseState(&clickX , &clickY);
    double deltaX = clickX - shipX;
    double deltaY = -clickY + shipY;
    double angle = atan(deltaY/deltaX*1.0);
    if(deltaX>=0){
        return angle;
    }else if(deltaX <= 0){
        return angle + PI;
    }
    return -1;
}

shot_node* add_new_shot(shot_node* head , double angle, int shipX , int shipY){
    Shot shot;
    shot.angle = angle;
    shot.position.x = shipX + 12; //+16-4 hajó közepérõl jönnek a lövések
    shot.position.y = shipY + 12;
    shot.position.w=8;
    shot.position.h=8;
    if(head==NULL){
        shot_node* uj = (shot_node*) malloc(sizeof(shot_node));
        uj->shot=shot;
        uj->next = NULL;
        return uj;
    }else{
        shot_node* uj = (shot_node*) malloc(sizeof(shot_node));
        uj->shot=shot;
        uj->next = head;
        return uj;
    }
    return NULL;
}

int render_shots(shot_node* head, SDL_Renderer* renderer, SDL_Texture* texture){
    shot_node* current = head;
    if(head!=NULL){
        while(current!=NULL && current->next != NULL){
            SDL_SetRenderDrawColor(renderer ,255 , 0 , 0 , 255);
            SDL_RenderFillRectF(renderer , &current->shot.position);
            //SDL_RenderCopyF(renderer , texture, NULL, &current->shot.position);
            current=current->next;
        }
        SDL_RenderCopyF(renderer , texture, NULL, &current->shot.position);
        return 0;
    }

    return -1;
}

Meteor check_hits(shot_node** head, node** meteor_head){
    Meteor meteor;
    meteor.meret = -2; 
    if(*head==NULL || meteor_head==NULL) return meteor; //meteor.meret==-2
    shot_node* current_shot;
    shot_node* prev_shot=NULL;
    node* current_meteor;
    node* prev_meteor=NULL;

    for(current_shot= *head ; current_shot!=NULL ; current_shot=current_shot->next){
        for(current_meteor = *meteor_head ; current_meteor!=NULL ; current_meteor=current_meteor->next){
            if(SDL_HasIntersectionF(&current_meteor->meteor.position , &current_shot->shot.position)){
                if(prev_shot==NULL){
                    *head = current_shot->next;
                    free(current_shot);
                    current_shot=*head;
                }else{
                    prev_shot->next = current_shot->next;
                    free(current_shot);
                    current_shot=prev_shot;
                }
                meteor = current_meteor->meteor;
                if(prev_meteor==NULL){
                    *meteor_head = current_meteor->next;
                    free(current_meteor); 
                }else{
                    prev_meteor->next = current_meteor->next;
                    free(current_meteor); 
                }
                return meteor; //törlés történt
            }
            prev_meteor = current_meteor;
        }
        current_meteor=*meteor_head;
        prev_shot=current_shot;
        prev_meteor=NULL;
    }
    meteor.meret = -1;
    return meteor; //meteor.meret==-1 => nem tortent torles

}



int move_shots(shot_node* head){
    if(head==NULL) return -1;
    shot_node* current = head;
    while(current->next!=NULL){
        current->shot.position.x += cos( current->shot.angle) * SHOT_SPEED;
        current->shot.position.y -= sin(current->shot.angle) * SHOT_SPEED;
        current = current->next;
    }
    current->shot.position.x += cos( current->shot.angle) * SHOT_SPEED;
    current->shot.position.y -= sin(current->shot.angle) * SHOT_SPEED;
    return 0;
}

int delete_shot_list(shot_node* head){
    if(head==NULL) return -1;
    shot_node* current = head;
    shot_node* temp;
    while(current->next != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    free(current);
    return 0;
}