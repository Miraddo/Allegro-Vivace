// fx.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// including allegro5 libraries.
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

// =============================================================================
// including the audio header file.
#include "fx.h"
#include "audio.h"
#include "sprites.h"
#include "utils/random.h"

// =============================================================================
// Define the FX struct.
typedef struct FX
{
    int x, y;
    int frame;
    bool spark;
    bool used;
} FX;

// =============================================================================
// Define the FX_N constant. This constant represents the number of FXs (effects) that can
// be displayed on the screen at the same time.
#define FX_N 128
FX fx[FX_N];

// =============================================================================
// fx_init: this function is for initializing the FXs.
void fx_init()
{
    for(int i = 0; i < FX_N; i++)
        fx[i].used = false;
}

// =============================================================================
// fx_add: this is for adding a new FX to the screen.
void fx_add(bool spark, int x, int y)
{
    if(!spark)
    {
        al_play_sample(sample_explode[between(0, 2)], 0.75, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    for(int i = 0; i < FX_N; i++)
    {
        if(fx[i].used)
        {
            continue;
        }

        fx[i].x = x;
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].spark = spark;
        fx[i].used = true;
        return;
    }
}

// =============================================================================
// fx_update: this is for updating the state of each FX in the game.
void fx_update(float time_elapsed, float fps)
{
    for(int i = 0; i < FX_N; i++)
    {
        if(!fx[i].used)
        {
            continue;
        }

        // Increment the frame based on time elapsed and fps.
        fx[i].frame += time_elapsed * fps;

        if((!fx[i].spark && (fx[i].frame == (EXPLOSION_FRAMES * 2)))
        || ( fx[i].spark && (fx[i].frame == (SPARKS_FRAMES * 2)))
        )
            fx[i].used = false;
    }
}

// =============================================================================
// fx_draw: this responsible for drawing each FX on the screen.
void fx_draw()
{
    for(int i = 0; i < FX_N; i++)
    {
        if(!fx[i].used)
            continue;

        int frame_display = fx[i].frame / 2;
        ALLEGRO_BITMAP* bmp =
            fx[i].spark
            ? sprites.sparks[frame_display]
            : sprites.explosion[frame_display]
        ;

        int x = fx[i].x - (al_get_bitmap_width(bmp) / 2);
        int y = fx[i].y - (al_get_bitmap_height(bmp) / 2);
        al_draw_bitmap(bmp, x, y, 0);
    }
}