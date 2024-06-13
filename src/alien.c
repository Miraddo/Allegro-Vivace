// alien.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// including std libraries.
#include <math.h>

// =============================================================================
// including allegro5 libraries.
#include <allegro5/allegro_font.h>

// =============================================================================
// including the header files.
#include "alien.h"
#include "global_variables.h"
#include "display.h"
#include "shot.h"
#include "sprites.h"
#include "fx.h"
#include "utils/random.h"


// =============================================================================
// Define the alien types.
ALIEN aliens[ALIENS_N];

// =============================================================================
// Define aliens initializations.
void aliens_init()
{
    for(int i = 0; i < ALIENS_N; i++){
        aliens[i].used = false;
    }
}

// =============================================================================
// Alien update function is responsible for updating the state of each alien in
// the game.
void aliens_update(float time_elapsed, float fps)
{
    // ------------------------------------------------------------------------
    // Determine the number of new aliens to spawn based on the current frame count and fps.
    int new_quota;
    if ((int) (frames * time_elapsed * fps) % 120) {
        new_quota = 0;
    } else {
        new_quota = between(2, 4);
    }

    int new_x = between(10, BUFFER_W-50);

    for(int i = 0; i < ALIENS_N; i++)
    {
        if(!aliens[i].used)
        {
            if(new_quota > 0)
            {
                new_x += between(40, 80);
                if(new_x > (BUFFER_W - 60))
                    new_x -= (BUFFER_W - 60);

                aliens[i].x = new_x;

                aliens[i].y = between(-40, -30);
                aliens[i].type = between(0, ALIEN_TYPE_N);
                aliens[i].shot_timer = between(1, 99);
                aliens[i].blink = 0;
                aliens[i].used = true;

                switch(aliens[i].type)
                {
                    case ALIEN_TYPE_BUG:
                        aliens[i].life = 4;
                        break;
                    case ALIEN_TYPE_ARROW:
                        aliens[i].life = 2;
                        break;
                    case ALIEN_TYPE_THICCBOI:
                        aliens[i].life = 12;
                        break;
                    default: ;
                }

                new_quota--;
            }
            continue;
        }

        switch(aliens[i].type)
        {
            case ALIEN_TYPE_BUG:
                // Adjust movement for time elapsed
                if(fmod(frames * time_elapsed * fps, 2) < 1) {
                    aliens[i].y++;
                }

                break;

            case ALIEN_TYPE_ARROW:
                // Adjust movement for time elapsed
                aliens[i].y += time_elapsed * fps;
                break;

            case ALIEN_TYPE_THICCBOI:
                // Adjust movement for time elapsed
                if(fmod(frames * time_elapsed * fps, 4) < 1)  {
                    aliens[i].y++;
                }

                break;

            default: ;
        }

        if(aliens[i].y >= BUFFER_H)
        {
            aliens[i].used = false;
            continue;
        }

        if(aliens[i].blink){
            // Adjust timer for time elapsed
            aliens[i].blink -= time_elapsed * fps;
        }


        if(shots_collide(false, aliens[i].x, aliens[i].y, ALIEN_W[aliens[i].type], ALIEN_H[aliens[i].type]))
        {
            aliens[i].life--;
            aliens[i].blink = 4;
        }

        int cx = aliens[i].x + (ALIEN_W[aliens[i].type] / 2);
        int cy = aliens[i].y + (ALIEN_H[aliens[i].type] / 2);

        if(aliens[i].life <= 0)
        {
            fx_add(false, cx, cy);

            switch(aliens[i].type)
            {
                case ALIEN_TYPE_BUG:
                    score += 200;
                    break;

                case ALIEN_TYPE_ARROW:
                    score += 150;
                    break;

                case ALIEN_TYPE_THICCBOI:
                    score += 800;
                    fx_add(false, cx-10, cy-4);
                    fx_add(false, cx+4, cy+10);
                    fx_add(false, cx+8, cy+8);
                    break;
                default: ;
            }

            aliens[i].used = false;
            continue;
        }

        // Adjust timer for time elapsed.
        aliens[i].shot_timer -= time_elapsed * fps;
        if(aliens[i].shot_timer <= 0)
        {
            switch(aliens[i].type)
            {
                case ALIEN_TYPE_BUG:
                    shots_add(false, false, cx, cy);
                    aliens[i].shot_timer = 150;
                    break;

                case ALIEN_TYPE_ARROW:
                    shots_add(false, true, cx, aliens[i].y);
                    aliens[i].shot_timer = 80;
                    break;

                case ALIEN_TYPE_THICCBOI:
                    shots_add(false, true, cx-5, cy);
                    shots_add(false, true, cx+5, cy);
                    shots_add(false, true, cx-5, cy + 8);
                    shots_add(false, true, cx+5, cy + 8);
                    aliens[i].shot_timer = 200;
                    break;

                default: ;
            }
        }
    }
}


// =============================================================================
// Alien draw function is responsible for drawing the aliens on the screen.
void aliens_draw()
{
    for(int i = 0; i < ALIENS_N; i++)
    {
        if(!aliens[i].used){
            continue;
        }

        if(aliens[i].blink > 2){
            continue;
        }

        al_draw_bitmap(sprites.alien[aliens[i].type], aliens[i].x, aliens[i].y, 0);
    }
}