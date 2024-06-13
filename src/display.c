// display.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Including allegro5 libraries.
#include <allegro5/allegro_font.h>

// =============================================================================
// Including the header files.
#include "utils/helper.h"
#include "display.h"

// =============================================================================
// Declare variables for the display and buffer.
ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

// =============================================================================
// Declare the display initialization function.
void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

// =============================================================================
// Display deinitialization function is for cleaning up the display
// and bitmap buffer when they are no longer needed.
void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

// =============================================================================
// Display pre draw function is called before drawing operations are performed.
void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
}

// =============================================================================
// Display post draw function is called after all drawing operations are completed.
void disp_post_draw()
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}