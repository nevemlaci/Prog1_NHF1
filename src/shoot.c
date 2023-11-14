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

struct shot_node* add_new_shot(struct shot_node* head , double angle, int shipX , int shipY){
    Shot shot;
    shot.angle = angle;
    shot.position.x = shipX + 12; //+16-4
    shot.position.y = shipY + 12;
    shot.position.w=8;
    shot.position.h=8;
    if(head==NULL){
        struct shot_node* uj = (struct shot_node*) malloc(sizeof(struct shot_node));
        uj->shot=shot;
        uj->next = NULL;
        return uj;
    }else{
        struct shot_node* uj = (struct shot_node*) malloc(sizeof(struct shot_node));
        uj->shot=shot;
        uj->next = head;
        return uj;
    }
    return NULL;
}

int render_shots(struct shot_node* head, SDL_Renderer* renderer, SDL_Texture* texture){
    struct shot_node* current = head;
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

int check_hits(struct shot_node** head, node* meteor_head){
    if(*head==NULL || meteor_head==NULL) return -1;

    struct shot_node* current_shot;
    struct shot_node* iw=NULL;
    //struct shot_node* temp;
    node* current_meteor;

    for(current_shot= *head ; current_shot!=NULL ; current_shot=current_shot->next){
        for(current_meteor = meteor_head ; current_meteor!=NULL ; current_meteor=current_meteor->next){
            if(SDL_HasIntersectionF(&current_meteor->meteor.position , &current_shot->shot.position)){
                if(iw==NULL){
                    *head = current_shot->next;
                    free(current_shot);
                    current_shot=*head;
                    deleteFromListIndex(meteor_head , current_meteor->meteor.index);
                    return 0;
                }else{
                    iw->next = current_shot->next;
                    free(current_shot);
                    current_shot=iw;
                    deleteFromListIndex(meteor_head , current_meteor->meteor.index);
                    return 0;
                }
            }
        }
        current_meteor=meteor_head;
        iw=current_shot;
    }
    return 0;

}



int move_shots(struct shot_node* head){
    if(head==NULL) return -1;
    struct shot_node* current = head;
    while(current->next!=NULL){
        current->shot.position.x += cos( current->shot.angle) * SHOT_SPEED;
        current->shot.position.y -= sin(current->shot.angle) * SHOT_SPEED;
        current = current->next;
    }
    current->shot.position.x += cos( current->shot.angle) * SHOT_SPEED;
    current->shot.position.y -= sin(current->shot.angle) * SHOT_SPEED;
    return 0;
}

int delete_shot_list(struct shot_node* head){
    if(head==NULL) return -1;
    struct shot_node* current = head;
    struct shot_node* temp;
    while(current->next != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    free(current);
    return 0;
}