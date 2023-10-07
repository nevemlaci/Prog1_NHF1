#include <SDL.h>
#include <SDL_image.h>
#include "aszteroida.h"
#include <stdbool.h>
#define PLAYER_SPEED 3


typedef struct{
    SDL_Rect position;
    SDL_Texture *texture;
    int health;
}Player;

typedef struct{
    int up , down , left , right;
}Input;

/**
 * @file
 * @brief Inicializ�lja a j�t�kost.
 * 
 * 
 * @param x a j�t�kos kezd� x koordin�t�ja
 * @param y a j�t�kos kezd� y koordin�t�ja
 * @param health a j�t�kos kezd� �letereje
 * @param renderer a j�t�k SDL_Renderer -j�re mutat� pointer
 * @param path a j�t�kos text�r�j�nak el�r�si �tja(char array)
 * @return Player visszat�r player-el, �rt�kak inicializ�lva.
 */
Player init_player(int x , int y, int health , SDL_Renderer *renderer , char* path){
    Player player;
    player.health = health;
    player.position.x = x;
    player.position.y = y;
    SDL_Texture *texture = IMG_LoadTexture(renderer , path);
    player.texture = texture;
    player.position.h=32;
    player.position.w=32;
    return player;
}

/**
 * @file
 * @brief J�t�kos mozgat�s��rt felel�s f�ggv�ny
 * 
 * @param player inicializ�lt, mozgatand� j�t�kosra mutat� pointer
 * @param input bemeneteket kezel� struct
 */
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
/**
 * @file
 * @brief Kezeli a billenty�k lenyom�s�t
 * 
 * @param input 
 * @param event 
 */
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

/**
 * @file
 * @brief Kezeli a billenty�k felenged�s�t
 * 
 * @param input 
 * @param event 
 */
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

void utkozes_ellenorzese(node* head , Player *player){
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