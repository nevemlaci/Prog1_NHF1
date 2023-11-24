#include "player.h"

void init_player(int x , int y, int health , SDL_Renderer *renderer , char* path , Player* player){
    player->health = health;
    player->position.x = x;
    player->position.y = y;
    SDL_Texture *texture = IMG_LoadTexture(renderer , path);
    player->texture = texture;
    player->position.h=32;
    player->position.w=32;
}

void move_player(Player* player , Input input , float deltaTime , int maxX , int maxY){
            if (input.up == 1 && player->position.y - PLAYER_SPEED*deltaTime > 0) {
                player->position.y -= PLAYER_SPEED*deltaTime;		
            }
            if (input.down == 1 && player->position.y  + PLAYER_SIZE + PLAYER_SPEED*deltaTime < maxY) {
                player->position.y += PLAYER_SPEED*deltaTime;			
            }
            if (input.left == 1 && player->position.x - PLAYER_SPEED*deltaTime > 0) {
                player->position.x -= PLAYER_SPEED*deltaTime;			
            }
            if (input.right == 1 && player->position.x  + PLAYER_SIZE + PLAYER_SPEED*deltaTime < maxX) {
                player->position.x += PLAYER_SPEED*deltaTime;
            }       
}

void keyDown(Input* input , SDL_KeyboardEvent* event){
				switch ( event->keysym.scancode ){
                    case SDL_SCANCODE_W:
                        input->up = 1;
                        break;
                       
                    case SDL_SCANCODE_S:
                        input->down = 1;
                        break;
                       
                    case SDL_SCANCODE_A:
                        input->left = 1;
                        break;
                       
                    case SDL_SCANCODE_D:
                        input->right = 1;
                        break;
                    
                    case SDL_SCANCODE_M:
                        input->menu=1;
                        break;

                    default:
                        break;
                }
}

void keyUp(Input* input , SDL_KeyboardEvent* event){
    
				switch ( event->keysym.scancode ){
                    case SDL_SCANCODE_W:
                        input->up=0;
                        break;
                       
                    case SDL_SCANCODE_S:
                        input->down=0;
                        break;
                       
                    case SDL_SCANCODE_A:
                        input->left=0;
                        break;
                       
                    case SDL_SCANCODE_D:
                        input->right=0;
                        break;
                    
                    case SDL_SCANCODE_M:
                        input->menu=0;
                        break;
                    default:
                        break;
                }
}

void reset_input(Input* input){
    input->up = 0;
    input->down = 0;
    input->left = 0;
    input->right = 0;
    input->menu = 0;
}

Meteor utkozes_ellenorzese(struct node** head , Player *player){
    Meteor meteor;
    struct node* current = *head;
    struct node* prev = NULL;
    while(current!=NULL){
        if(SDL_HasIntersectionF(&player->position , &current->meteor.position)){
            player->health--;
        }
        prev = current;
        current = current->next;
    }
    meteor.meret=-1;
    return meteor;
}