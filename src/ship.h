// ship.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the SHIP_HE macro.
#ifndef SHIP_HE
#define SHIP_HE

    // -------------------------------------------------------------------------
    // Declare the constants.
    #define SHIP_SPEED 3
    #define SHIP_MAX_X (BUFFER_W - SHIP_W)
    #define SHIP_MAX_Y (BUFFER_H - SHIP_H)

    // -------------------------------------------------------------------------
    // Declare the global struct.
    typedef struct SHIP
    {
        int x, y;
        int shot_timer;
        int lives;
        int respawn_timer;
        int invincible_timer;
    } SHIP;
    extern SHIP ship;

    // -------------------------------------------------------------------------
    // Declare the functions.
    void ship_init();
    void ship_update(float time_elapsed, float fps);
    void ship_draw();

#endif //SHIP_HE
