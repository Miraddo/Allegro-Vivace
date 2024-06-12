// init.c
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include "utils/helper.h"
#include "display.h"
#include "keyboard.h"
#include "sprites.h"
#include "audio.h"
#include "fx.h"
#include "shot.h"
#include "ship.h"
#include "alien.h"
#include "stars.h"
#include "hud.h"

// Declare variables for frame rate and timing
const float FPS_30 = 30.0;
const float FPS_60 = 60.0;
float FPS = FPS_60; // Start with 60 FPS

long frames;
long score;
bool key_f_pressed = false; // Add a flag for the 'F' key press

void init()
{

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    disp_init();

    audio_init();

    must_init(al_init_image_addon(), "image");
    sprites_init();

    hud_init();

    must_init(al_init_primitives_addon(), "primitives");

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    keyboard_init();
    fx_init();
    shots_init();
    ship_init();
    aliens_init();
    stars_init();

    frames = 0;
    score = 0;

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                float time_elapsed = 1.0 / FPS;
                fx_update(time_elapsed, FPS);
                shots_update(time_elapsed, FPS);
                stars_update(time_elapsed, FPS);
                ship_update(time_elapsed, FPS);
                aliens_update(time_elapsed, FPS);
                hud_update(time_elapsed, FPS);

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_F)
                {
                    key_f_pressed = true;
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(key_f_pressed)
        {
            if(FPS == FPS_60)
            {
                FPS = FPS_30;
            }
            else
            {
                FPS = FPS_60;
            }
            al_set_timer_speed(timer, 1.0 / FPS);
            key_f_pressed = false;
        }

        if(done)
            break;

        keyboard_update(&event);

        if(redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0,0,0));

            stars_draw();
            aliens_draw();
            shots_draw();
            fx_draw();
            ship_draw();

            hud_draw();

            disp_post_draw();
            redraw = false;
        }
    }

    sprites_deinit();
    hud_deinit();
    audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}