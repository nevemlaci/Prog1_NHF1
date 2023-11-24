#ifndef CLOCK_H
#define CLOCK_H
#include <SDL.h>

/**
 * @brief 
 * 
 * @param last_tick elõzõ frame melyik ticken kezdõdött
 * @param now_tick jelenlegi frame melyik ticken kezdõdött
 */
typedef struct Clock{
    int last_tick;
    int now_tick;
}Clock;

typedef struct Spawn_clock{
    double time;
    double lastSpawn;
}Spawn_clock;

void init_clock(Clock* clock);

void tick_clock(Clock* clock);

float calculate_delta_time(Clock* clock);

void init_spawn_clock(Spawn_clock* clock);

void tick_spawn_clock(Spawn_clock* clock);

float calculate_spawn_time(Spawn_clock* clock);

void resetSpawnClock(Spawn_clock* clock);

#endif