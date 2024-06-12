//
// Created by miraddo on 6/2/2024.
//

#ifndef SHIP_HE
#define SHIP_HE

#define SHIP_SPEED 3
#define SHIP_MAX_X (BUFFER_W - SHIP_W)
#define SHIP_MAX_Y (BUFFER_H - SHIP_H)

typedef struct SHIP
{
    int x, y;
    int shot_timer;
    int lives;
    int respawn_timer;
    int invincible_timer;
} SHIP;
extern SHIP ship;

void ship_init();
void ship_update(float time_elapsed, float fps);
void ship_draw();

#endif //SHIP_HE
