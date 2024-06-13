// stars.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// Include the allegro5 header file.
#include <allegro5/allegro_font.h>

// =============================================================================
// Include the necessary header files.
#include "stars.h"
#include "utils/random.h"
#include "display.h"

// =============================================================================
// Define the star structure.
typedef struct STAR
{
    float y;
    float speed;
} STAR;

#define STARS_N ((BUFFER_W / 2) - 1)
STAR stars[STARS_N];

// =============================================================================
// Define the stars_init function. This function is responsible for initializing
// the stars.
void stars_init()
{
    for(int i = 0; i < STARS_N; i++)
    {
        stars[i].y = between_f(0, BUFFER_H);
        stars[i].speed = between_f(0.1, 1);
    }
}

// =============================================================================
// Define the stars_update function. This function is responsible for updating
// the stars.
void stars_update(float time_elapsed, float fps)
{
    for(int i = 0; i < STARS_N; i++)
    {
        stars[i].y += stars[i].speed * time_elapsed * fps; // Adjust movement for time elapsed
        if(stars[i].y >= BUFFER_H)
        {
            stars[i].y = 0;
            stars[i].speed = between_f(0.1, 1);
        }
    }
}

// =============================================================================
// Define the stars_draw function. This function is responsible for drawing
// the stars.
void stars_draw()
{
    float star_x = 1.5;
    for(int i = 0; i < STARS_N; i++)
    {
        float l = stars[i].speed * 0.8;
        al_draw_pixel(star_x, stars[i].y, al_map_rgb_f(l,l,l));
        star_x += 2;
    }
}