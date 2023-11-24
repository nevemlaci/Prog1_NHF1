#ifndef CLOCK_H
#define CLOCK_H
#include <SDL.h>

/// @brief a játékban meteorok létrehozásának idõzítéséért felelõs óra
typedef struct Clock{
    /// @brief elõzõ frame ezen a ticken kezdõdött
    int last_tick;
    /// @brief a jelenlegi frame ezen a ticken kezdõdött
    int now_tick;
}Clock;

/// @brief a játékban meteorok létrehozásának idõzítéséért felelõs óra
typedef struct Spawn_clock{
    /// @brief játék kezdete óta eltelt idõ
    double time;
    /// @brief legutóbbi meteor spawn óta eltelt idõ
    double lastSpawn;
}Spawn_clock;

/// @brief inicializálja az órát
/// @param clock inicializálandó óra pointere
void init_clock(Clock* clock);

/// @brief lépteti az órát
/// @param clock léptetett óra pointere
void tick_clock(Clock* clock);

/// @brief kiszámolja az elõzõ frame óta eltelt idõt
/// @param clock óra pointere
/// @return deltaTime másodpercben
float calculate_delta_time(Clock* clock);

/// @brief inicializálja az órát(meteor spawnhoz)
/// @param clock inicializálandó óra pointere
void init_spawn_clock(Spawn_clock* clock);

/// @brief lépteti az órát (de csak time növekszik)
/// @param clock léptetendõ óra pointere
void tick_spawn_clock(Spawn_clock* clock);

/// @brief kiszámolja a legutóbbi meteor spawn óta eltelt idõt
/// @param clock Spawn_clock (amibõl számol)
/// @return legutóbbi spawn óta eltelt idõ másodpercben
float calculate_spawn_time(Spawn_clock* clock);

/// @brief meteor spawnoláskor beállítja lastSpawn-t a jelenlegi idõre
/// @param clock állítandó óra pointere
void resetSpawnClock(Spawn_clock* clock);

#endif