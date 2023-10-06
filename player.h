#include <SDL.h>
#include <SDL_image.h>
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
 * @brief Inicializálja a játékost.
 * 
 * 
 * @param x a játékos kezdõ x koordinátája
 * @param y a játékos kezdõ y koordinátája
 * @param health a játékos kezdõ életereje
 * @param renderer a játék SDL_Renderer -jére mutató pointer
 * @param path a játékos textúrájának elérési útja(char array)
 * @return Player visszatér player-el, értékak inicializálva.
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
 * @brief Játékos mozgatásáért felelõs függvény
 * 
 * @param player inicializált, mozgatandó játékosra mutató pointer
 * @param input bemeneteket kezelõ struct
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


