// alien.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the ALIEN_HE macro.
#ifndef ALIEN_HE
#define ALIEN_HE
    // -------------------------------------------------------------------------
    // Define the type of the alien.
    typedef enum ALIEN_TYPE
    {
        ALIEN_TYPE_BUG = 0,
        ALIEN_TYPE_ARROW,
        ALIEN_TYPE_THICCBOI,
        ALIEN_TYPE_N
    } ALIEN_TYPE;

    // Define the alien structure.
    typedef struct ALIEN
    {
        int x, y;
        ALIEN_TYPE type;
        int shot_timer;
        int blink;
        int life;
        bool used;
    } ALIEN;

    // -------------------------------------------------------------------------
    // Define the number of aliens.
    #define ALIENS_N 16

    // -------------------------------------------------------------------------
    // Declare the functions.
    void aliens_init();
    void aliens_update(float time_elapsed, float fps);
    void aliens_draw();

#endif //ALIEN_HE
