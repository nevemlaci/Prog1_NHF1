#include "shoot.h"
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
        while(current->next != NULL){
            SDL_RenderCopyF(renderer , texture, NULL, &current->shot.position);
            current=current->next;
        }
        SDL_RenderCopyF(renderer , texture, NULL, &current->shot.position);
        return 0;
    }
    return -1;
}


//int check_hits(struct shot_node* head, node* meteor_head);

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

