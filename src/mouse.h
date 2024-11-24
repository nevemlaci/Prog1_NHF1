#pragma once

typedef struct mouse {
    int x, y;
} mouse;

void UpdateMousePos(mouse* m);