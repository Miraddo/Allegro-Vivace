//
// Created by miraddo on 6/2/2024.
//

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>

#include "hud.h"
#include "utils/helper.h"
#include "global_variables.h"
#include "sprites.h"
#include "display.h"
#include "ship.h"

extern ALLEGRO_FONT *font;

long score_display;

void hud_init()
{
    font = al_create_builtin_font();
    must_init(font, "font");

    score_display = 0;
}

void hud_deinit()
{
    al_destroy_font(font);
}

void hud_update(float time_elapsed, float fps)
{
    static float frame_accumulator = 0.0f;
    frame_accumulator += time_elapsed * fps;

    // Execute the update logic every 2 frames
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


void hud_draw(float fps)
{
    // Drawing game controls text
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 0, 0, "Arrow keys to move");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 10, 0, "X to shoot");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 20, 0, "Esc to quit");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 30, 0, "Space to pause");
    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 40, 0, "F to toggle the frame rate");

    // Drawing the current frame rate
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

    int spacing = LIFE_W + 1;
    for(int i = 0; i < ship.lives; i++)
        al_draw_bitmap(sprites.life, 1 + (i * spacing), 10, 0);

    if(ship.lives < 0)
        al_draw_text(
            font,
            al_map_rgb_f(1,1,1),
            BUFFER_W / 2, BUFFER_H / 2,
            ALLEGRO_ALIGN_CENTER,
            "G A M E  O V E R"
        );
}