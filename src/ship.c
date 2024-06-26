// ship.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// Include the allegro5 header file.
#include <allegro5/allegro_font.h>

// =============================================================================
// Include the necessary header files.
#include "ship.h"
#include "fx.h"
#include "display.h"
#include "keyboard.h"
#include "sprites.h"
#include "shot.h"

// =============================================================================
// Define the ship structure.
SHIP ship;

// =============================================================================
// Define the ship_init function. This function is responsible for initializing
// the ship.
void ship_init()
{
    ship.x = (BUFFER_W / 2) - (SHIP_W / 2);
    ship.y = (BUFFER_H / 2) - (SHIP_H / 2);
    ship.shot_timer = 0;
    ship.lives = 3;
    ship.respawn_timer = 0;
    ship.invincible_timer = 120;
}

// =============================================================================
// Define the ship_update function. This function is responsible for updating
// the ship.
void ship_update(float time_elapsed, float fps)
{
    if(ship.lives < 0)
        return;

    if(ship.respawn_timer)
    {
        ship.respawn_timer -= time_elapsed * fps; // Adjust timer for time elapsed
        if (ship.respawn_timer < 0) ship.respawn_timer = 0; // Ensure timer doesn't go negative
        return;
    }

    if(key[ALLEGRO_KEY_LEFT])
        ship.x -= SHIP_SPEED * time_elapsed * fps; // Adjust movement for time elapsed
    if(key[ALLEGRO_KEY_RIGHT])
        ship.x += SHIP_SPEED * time_elapsed * fps; // Adjust movement for time elapsed
    if(key[ALLEGRO_KEY_UP])
        ship.y -= SHIP_SPEED * time_elapsed * fps; // Adjust movement for time elapsed
    if(key[ALLEGRO_KEY_DOWN])
        ship.y += SHIP_SPEED * time_elapsed * fps; // Adjust movement for time elapsed


    if(ship.x < 0)
        ship.x = 0;
    if(ship.y < 0)
        ship.y = 0;

    if(ship.x > SHIP_MAX_X)
        ship.x = SHIP_MAX_X;
    if(ship.y > SHIP_MAX_Y)
        ship.y = SHIP_MAX_Y;

    if(ship.invincible_timer)
    {

        ship.invincible_timer -= time_elapsed * fps; // Adjust timer for time elapsed
        if (ship.invincible_timer < 0) ship.invincible_timer = 0; // Ensure timer doesn't go negative    else
    }
    else
    {
        if(shots_collide(true, ship.x, ship.y, SHIP_W, SHIP_H))
        {
            int x = ship.x + (SHIP_W / 2);
            int y = ship.y + (SHIP_H / 2);
            fx_add(false, x, y);
            fx_add(false, x+4, y+2);
            fx_add(false, x-2, y-4);
            fx_add(false, x+1, y-5);

            ship.lives--;
            ship.respawn_timer = 90;
            ship.invincible_timer = 180;
        }
    }

    if(ship.shot_timer)
    {
        ship.shot_timer -= time_elapsed * fps; // Adjust timer for time elapsed
        if (ship.shot_timer < 0) ship.shot_timer = 0; // Ensure timer doesn't go negative
    }
    else if(key[ALLEGRO_KEY_X])
    {
        int x = ship.x + (SHIP_W / 2);
        if(shots_add(true, false, x, ship.y))
            ship.shot_timer = 5;
    }
}

// =============================================================================
// Define the ship_draw function. This function is responsible for drawing the
// ship.
void ship_draw()
{
    if(ship.lives < 0)
        return;
    if(ship.respawn_timer)
        return;
    if(((ship.invincible_timer / 2) % 3) == 1)
        return;

    al_draw_bitmap(sprites.ship, ship.x, ship.y, 0);
}