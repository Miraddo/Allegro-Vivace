// fx.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// including std libraries.
#include <stdio.h>

// =============================================================================
// including allegro5 libraries.
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// =============================================================================
// including the header files.
#include "hud.h"
#include "utils/helper.h"
#include "global_variables.h"
#include "sprites.h"
#include "display.h"
#include "ship.h"

// =============================================================================
// Declare the font variable and the score display.
extern ALLEGRO_FONT *font;
long score_display;

// =============================================================================
// Define the hud initialization function.
void hud_init()
{
    font = al_create_builtin_font();
    must_init(font, "font");

    score_display = 0;
}

// =============================================================================
// Define the hud deinitialization function. This function is responsible for
// cleaning up the font.
void hud_deinit()
{
    al_destroy_font(font);
}

// =============================================================================
// Define the hud update function. This function is responsible for updating the
// score display.
void hud_update(float time_elapsed, float fps)
{
    static float frame_accumulator = 0.0f;
    frame_accumulator += time_elapsed * fps;

    // ------------------------------------------------------------------------
    // Execute the update logic every 2 frames to make the score incrementation
    // smoother.
    if(frame_accumulator < 2.0f)
        return;

    frame_accumulator -= 2.0f;

    for(long i = 5; i > 0; i--)
    {
        long diff = 1 << i;
        if(score_display <= (score - diff))
            score_display += diff;
    }
}

// =============================================================================
// Define the hud draw function. This function is responsible for drawing the game
// controls text, the current frame rate, the score, and the number of lives.
void hud_draw(float fps)
{
    // ------------------------------------------------------------------------
    // Drawing game controls text and the current frame rate.
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 0, 0, "Arrow keys to move");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 10, 0, "X to shoot");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 20, 0, "Esc to quit");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 30, 0, "Space to pause");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 40, 0, "F to toggle the frame rate");

    // ------------------------------------------------------------------------
    // Drawing the current frame rate and the score.
    char fps_text[20];
    snprintf(fps_text, sizeof(fps_text), "FPS: %.1f", fps);
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 50, 0, fps_text);
    al_draw_textf(
        font,
        al_map_rgb_f(1,1,1),
        1, 1,
        0,
        "%06ld",
        score_display
    );

    // ------------------------------------------------------------------------
    // Drawing the number of lives.
    int spacing = LIFE_W + 1;
    for(int i = 0; i < ship.lives; i++)
    {
        al_draw_bitmap(sprites.life, 1 + (i * spacing), 10, 0);
    }

    // ------------------------------------------------------------------------
    // Drawing the game over text.
    if(ship.lives < 0)
    {
        al_draw_text(
                font,
                al_map_rgb_f(1,1,1),
                BUFFER_W / 2, BUFFER_H / 2,
                ALLEGRO_ALIGN_CENTER,
                "G A M E  O V E R"
        );
    }
}