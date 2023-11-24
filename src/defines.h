///@file a konstansok ebben a f�jlban vannak defini�lva

#ifndef DEFINES_H
#define DEFINES_H

///@brief ennyi m�sodpercenk�nt spawnol egy meteor
#define BASE_SPAWN_RATE 4
///@brief k�t l�v�s k�zt legal�bb ennyi id�nek kell eltelnie
#define SHOT_TIME 10
///@brief ha 0 akkor a j�t�kos nem halhat meg
///@note for debug purposes
#define DIE 0
///@brief a l�v�sek sebess�ge
#define SHOT_SPEED 2100

///@brief a men� ablak�nak sz�less�ge
#define MENU_W 800
///@brief a men� ablak�nak magass�ga
#define MENU_H 400

///@brief ennyi rekord jelenik meg a ranglist�r�l a men�ben
#define RANGLISTA_SIZE 5
///@brief ilyen hossz� maximum egy rekord stringje a ranglist�n
#define REKORD_SIZE 59 //50+1+7+1 50= max nev hossza , 1 = szokoz , 7 = INT_MAX karakterszama , 1 = '\0'

///@brief a men� h�tt�rsz�ne
#define MENU_COLOR 150, 222, 255, 0

///@brief meteorok sebess�ge
#define METEOR_SPEED 270

///@brief a j�t�kos sebess�ge
#define PLAYER_SPEED 500

///a j�t�kos sz�less�ge �s magass�ga
#define PLAYER_SIZE 32

#endif