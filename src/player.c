
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include "aszteroida.h"
#include "player.h"

#define PLAYER_SPEED 3




void init_player(int x , int y, int health , SDL_Renderer *renderer , char* path , Player* player){
    player->health = health;
    player->position.x = x;
    player->position.y = y;
    SDL_Texture *texture = IMG_LoadTexture(renderer , path);
    player->texture = texture;
    player->position.h=32;
    player->position.w=32;
}


void move_player(Player* player , Input input){
    if (input.up == 1) {
			player->position.y -= PLAYER_SPEED;
			
		}
		if (input.down == 1) {
			player->position.y += PLAYER_SPEED;
			
		}
		if (input.left == 1) {
			player->position.x -= PLAYER_SPEED;
			
		}
		if (input.right == 1) {
			player->position.x += PLAYER_SPEED;
			
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
                       
                    default:
                        break;
                }
}

void utkozes_ellenorzese(struct node* head , Player *player){
    struct node* current = head;
    while(current!=NULL){
        if(SDL_HasIntersection(&player->position , &current->meteor.position)){
            player->health--;
            printf("Collision\n");
            deleteFromListIndex(head , current->meteor.index);
            return;
        }

        current = current->next;
    }
}