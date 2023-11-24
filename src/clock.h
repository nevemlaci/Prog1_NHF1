#ifndef CLOCK_H
#define CLOCK_H
#include <SDL.h>

/// @brief a j�t�kban meteorok l�trehoz�s�nak id�z�t�s��rt felel�s �ra
typedef struct Clock{
    /// @brief el�z� frame ezen a ticken kezd�d�tt
    int last_tick;
    /// @brief a jelenlegi frame ezen a ticken kezd�d�tt
    int now_tick;
}Clock;

/// @brief a j�t�kban meteorok l�trehoz�s�nak id�z�t�s��rt felel�s �ra
typedef struct Spawn_clock{
    /// @brief j�t�k kezdete �ta eltelt id�
    double time;
    /// @brief legut�bbi meteor spawn �ta eltelt id�
    double lastSpawn;
}Spawn_clock;

/// @brief inicializ�lja az �r�t
/// @param clock inicializ�land� �ra pointere
void init_clock(Clock* clock);

/// @brief l�pteti az �r�t
/// @param clock l�ptetett �ra pointere
void tick_clock(Clock* clock);

/// @brief kisz�molja az el�z� frame �ta eltelt id�t
/// @param clock �ra pointere
/// @return deltaTime m�sodpercben
float calculate_delta_time(Clock* clock);

/// @brief inicializ�lja az �r�t(meteor spawnhoz)
/// @param clock inicializ�land� �ra pointere
void init_spawn_clock(Spawn_clock* clock);

/// @brief l�pteti az �r�t (de csak time n�vekszik)
/// @param clock l�ptetend� �ra pointere
void tick_spawn_clock(Spawn_clock* clock);

/// @brief kisz�molja a legut�bbi meteor spawn �ta eltelt id�t
/// @param clock Spawn_clock (amib�l sz�mol)
/// @return legut�bbi spawn �ta eltelt id� m�sodpercben
float calculate_spawn_time(Spawn_clock* clock);

/// @brief meteor spawnol�skor be�ll�tja lastSpawn-t a jelenlegi id�re
/// @param clock �ll�tand� �ra pointere
void resetSpawnClock(Spawn_clock* clock);

#endif