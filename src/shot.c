// shot.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// including allegro5 libraries.
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

// =============================================================================
// including the necessary header files.
#include "audio.h"
#include "utils/random.h"
#include "utils/collision.h"
#include "shot.h"
#include "sprites.h"
#include "display.h"
#include "fx.h"

// =============================================================================
// Define the shot structure.
typedef struct SHOT
{
    int x, y, dx, dy;
    int frame;
    bool ship;
    bool used;
} SHOT;

// =============================================================================
// Define the shots array.
#define SHOTS_N 128
SHOT shots[SHOTS_N];

// =============================================================================
// Define the shots_init function. This function is responsible for initializing
// the shots.
void shots_init()
{
    for(int i = 0; i < SHOTS_N; i++)
        shots[i].used = false;
}

// =============================================================================
// Define the shots_add function. This function is responsible for adding a shot
// to the shots array.
bool shots_add(bool ship, bool straight, int x, int y)
{
    al_play_sample(
        sample_shot,
        0.3,
        0,
        ship ? 1.0 : between_f(1.5, 1.6),
        ALLEGRO_PLAYMODE_ONCE,
        NULL
    );

    for(int i = 0; i < SHOTS_N; i++)
    {
        if(shots[i].used)
            continue;

        shots[i].ship = ship;

        if(ship)
        {
            shots[i].x = x - (SHIP_SHOT_W / 2);
            shots[i].y = y;
        }
        else // alien
        {
            shots[i].x = x - (ALIEN_SHOT_W / 2);
            shots[i].y = y - (ALIEN_SHOT_H / 2);

            if(straight)
            {
                shots[i].dx = 0;
                shots[i].dy = 2;
            }
            else
            {

                shots[i].dx = between(-2, 2);
                shots[i].dy = between(-2, 2);
            }

            // if the shot has no speed, don't bother
            if(!shots[i].dx && !shots[i].dy)
                return true;

            shots[i].frame = 0;
        }

        shots[i].frame = 0;
        shots[i].used = true;

        return true;
    }
    return false;
}

// =============================================================================
// Define the shots_update function. This function is responsible for updating
// the shots.
void shots_update(float time_elapsed, float fps)
{
    for(int i = 0; i < SHOTS_N; i++)
    {
        if(!shots[i].used)
            continue;

        if(shots[i].ship)
        {
            shots[i].y -= 5 * time_elapsed * fps; // Adjust movement for time elapsed

            if(shots[i].y < -SHIP_SHOT_H)
            {
                shots[i].used = false;
                continue;
            }
        }
        else // alien
        {
            shots[i].x += shots[i].dx * time_elapsed * fps; // Adjust movement for time elapsed
            shots[i].y += shots[i].dy * time_elapsed * fps; // Adjust movement for time elapsed


            if((shots[i].x < -ALIEN_SHOT_W)
            || (shots[i].x > BUFFER_W)
            || (shots[i].y < -ALIEN_SHOT_H)
            || (shots[i].y > BUFFER_H)
            ) {
                shots[i].used = false;
                continue;
            }
        }

        shots[i].frame += time_elapsed * fps; // Adjust frame increment for time elapsed
    }
}

// =============================================================================
// Define the shots_collide function. This function is responsible for checking
// if the shots collide.
bool shots_collide(bool ship, int x, int y, int w, int h)
{
    for(int i = 0; i < SHOTS_N; i++)
    {
        if(!shots[i].used)
            continue;

        // don't collide with one's own shots
        if(shots[i].ship == ship)
            continue;

        int sw, sh;
        if(ship)
        {
            sw = ALIEN_SHOT_W;
            sh = ALIEN_SHOT_H;
        }
        else
        {
            sw = SHIP_SHOT_W;
            sh = SHIP_SHOT_H;
        }

        if(collide(x, y, x+w, y+h, shots[i].x, shots[i].y, shots[i].x+sw, shots[i].y+sh))
        {
            fx_add(true, shots[i].x + (sw / 2), shots[i].y + (sh / 2));
            shots[i].used = false;
            return true;
        }
    }

    return false;
}

// =============================================================================
// Define the shots_draw function. This function is responsible for drawing the
// shots.
void shots_draw()
{
    for(int i = 0; i < SHOTS_N; i++)
    {
        if(!shots[i].used)
            continue;

        int frame_display = (shots[i].frame / 2) % 2;

        if(shots[i].ship)
            al_draw_bitmap(sprites.ship_shot[frame_display], shots[i].x, shots[i].y, 0);
        else // alien
        {
            ALLEGRO_COLOR tint =
                frame_display
                ? al_map_rgb_f(1, 1, 1)
                : al_map_rgb_f(0.5, 0.5, 0.5)
            ;
            al_draw_tinted_bitmap(sprites.alien_shot, tint, shots[i].x, shots[i].y, 0);
        }
    }
}