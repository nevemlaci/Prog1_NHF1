#include "clock.h"

void init_clock(Clock* clock){
    clock->now_tick = SDL_GetPerformanceCounter();
    clock->last_tick = 0;
}

void tick_clock(Clock* clock){
    clock->last_tick=clock->now_tick;
    clock->now_tick = SDL_GetPerformanceCounter();
    return;
}

float calculate_delta_time(Clock* clock){
    return ((clock->now_tick-clock->last_tick)*1.0)/SDL_GetPerformanceFrequency();
}

void init_spawn_clock(Spawn_clock* clock){
    clock->time = SDL_GetPerformanceCounter()*1.0/SDL_GetPerformanceFrequency();
    clock->lastSpawn = clock->time;
}

void tick_spawn_clock(Spawn_clock* clock){
    clock->time = SDL_GetPerformanceCounter()*1.0/SDL_GetPerformanceFrequency();
    return;
}

float calculate_spawn_time(Spawn_clock* clock){
    float retval = (clock->time - clock->lastSpawn);
    return retval;
}

void resetSpawnClock(Spawn_clock* clock){
    clock->lastSpawn = clock->time;
    clock->time = SDL_GetPerformanceCounter()*1.0/SDL_GetPerformanceFrequency();
    return;
}