#include "clock.h"

void initGameClock(Clock* clock){
    clock->now_tick = SDL_GetPerformanceCounter();
    clock->last_tick = 0;
}

void tickGameClock(Clock* clock){
    clock->last_tick=clock->now_tick;
    clock->now_tick = SDL_GetPerformanceCounter();
    return;
}

float calculate_DeltaTime(Clock* clock){
    return ((clock->now_tick-clock->last_tick)*1.0)/SDL_GetPerformanceFrequency();
}

void initSpawnClock(Spawn_clock* clock){
    clock->time = SDL_GetPerformanceCounter()*1.0/SDL_GetPerformanceFrequency();
    clock->lastSpawn = clock->time;
}

void tickSpawnClock(Spawn_clock* clock){
    clock->time = SDL_GetPerformanceCounter()*1.0/SDL_GetPerformanceFrequency();
    return;
}

float calculate_SpawnTime(Spawn_clock* clock){
    float retval = (clock->time - clock->lastSpawn);
    return retval;
}

void resetSpawnClock(Spawn_clock* clock){
    clock->lastSpawn = clock->time;
    clock->time = SDL_GetPerformanceCounter()*1.0/SDL_GetPerformanceFrequency();
    return;
}