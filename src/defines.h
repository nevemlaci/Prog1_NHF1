///@file a konstansok ebben a fájlban vannak definiálva

#ifndef DEFINES_H
#define DEFINES_H

#define PI 3.14159265358

///@brief ennyi másodpercenként spawnol egy meteor
#define BASE_SPAWN_RATE 2
///@brief két lövés közt legalább ennyi idõnek kell eltelnie
#define SHOT_TIME 10
///@brief ha 0 akkor a játékos nem halhat meg
///@note for debug purposes
#define DIE 1
///@brief a lövések sebessége
#define SHOT_SPEED 2100

///@brief a menü ablakának szélessége
#define MENU_W 800
///@brief a menü ablakának magassága
#define MENU_H 400

///@brief ennyi rekord jelenik meg a ranglistáról a menüben
///@note 8 fölé nem érdemes vinni mert belelóg a többi menürészbe
#define RANGLISTA_SIZE 7
///@brief ilyen hosszú maximum egy rekord stringje a ranglistán
#define REKORD_SIZE 59 //50+1+7+1 50= max nev hossza , 1 = szokoz , 7 = INT_MAX karakterszama , 1 = '\0'

///@brief a menü háttérszíne
#define MENU_COLOR 150, 222, 255, 0

///@brief meteorok sebessége
#define METEOR_SPEED 270

///@brief a játékos sebessége
#define PLAYER_SPEED 500

///@brief a játékos szélessége és magassága
///@note a legjobb eredményhez elõnyös 2 hatványára állítani
#define PLAYER_SIZE 64

/// What could this be
#define DEFINITELY_AN_ERROR_MESSAGE system("..\\materials\\Error.url");

#endif