// sprites.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the SPRITES_H macro.
#ifndef SPRITES_H
#define SPRITES_H

    // -------------------------------------------------------------------------
    // Define the constants.
    #define SHIP_W 12
    #define SHIP_H 13

    #define SHIP_SHOT_W 2
    #define SHIP_SHOT_H 9

    #define LIFE_W 6
    #define LIFE_H 6

    #define ALIEN_BUG_W      ALIEN_W[0]
    #define ALIEN_BUG_H      ALIEN_H[0]
    #define ALIEN_ARROW_W    ALIEN_W[1]
    #define ALIEN_ARROW_H    ALIEN_H[1]
    #define ALIEN_THICCBOI_W ALIEN_W[2]
    #define ALIEN_THICCBOI_H ALIEN_H[2]

    #define ALIEN_SHOT_W 4
    #define ALIEN_SHOT_H 4

    #define EXPLOSION_FRAMES 4
    #define SPARKS_FRAMES    3

    // -------------------------------------------------------------------------
    // Define the constants.
    extern const int ALIEN_W[];
    extern const int ALIEN_H[];

    // -------------------------------------------------------------------------
    // Declare the sprite structure.
    typedef struct SPRITES
    {
        ALLEGRO_BITMAP* _sheet;

        ALLEGRO_BITMAP* ship;
        ALLEGRO_BITMAP* ship_shot[2];
        ALLEGRO_BITMAP* life;

        ALLEGRO_BITMAP* alien[3];
        ALLEGRO_BITMAP* alien_shot;

        ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
        ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

        ALLEGRO_BITMAP* powerup[4];
    } SPRITES;

    extern SPRITES sprites;

    // -------------------------------------------------------------------------
    // Declare the functions.
    void sprites_init();
    void sprites_deinit();

#endif //SPRITES_H
