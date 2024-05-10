#pragma once

#define MIN(v1, v2) v1 < v2 ? v1 : v2
#define MIN3(v1, v2, v3) MIN(v1, MIN(v2, v3))
#define MAX(v1, v2) v1 > v2 ? v1 : v2
#define MAX3(v1, v2, v3) MAX(v1, MAX(v2, v3))

typedef enum Direction {
    Left,
    Right,
    Up,
    Down
} Direction;
