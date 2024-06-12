// init.c
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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
const float fps_30 = 30.0;
const float fps_60 = 60.0;
float fps = fps_60; // Start with 60 fps

long frames;
long score;
bool key_f_pressed = false; // Add a flag for the 'F' key press
bool paused = false; // Add a flag for the paused state
int countdown = 0; // Add a variable for the countdown
ALLEGRO_FONT* font = NULL;

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
    must_init(al_init_font_addon(), "font");
    must_init(al_init_ttf_addon(), "ttf");

    // Load a TTF font with size 48
    font = al_load_ttf_font("./assets/font/Tiny5-Regular.ttf", 92, 0);
    must_init(font, "font");

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
                if (!paused) {
                    float time_elapsed = 1.0 / fps;
                    fx_update(time_elapsed, fps);
                    shots_update(time_elapsed, fps);
                    stars_update(time_elapsed, fps);
                    ship_update(time_elapsed, fps);
                    aliens_update(time_elapsed, fps);
                    hud_update(time_elapsed, fps);

                    frames++;

                    if (key[ALLEGRO_KEY_ESCAPE])
                        done = true;
                }
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if(event.keyboard.keycode == ALLEGRO_KEY_F)
                {
                    key_f_pressed = true;
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
                {
                    if (paused)
                    {
                        countdown = 3; // Start countdown from 3
                    }
                    paused = !paused;
                }

                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(key_f_pressed)
        {
            if(fps == fps_60)
            {
                fps = fps_30;
            }
            else
            {
                fps = fps_60;
            }
            al_set_timer_speed(timer, 1.0 / fps);
            key_f_pressed = false;
        }

        if(done)
            break;

        keyboard_update(&event);

        if(redraw && al_is_event_queue_empty(queue))
        {
            if (paused && countdown > 0)
            {
                // Display the countdown
                al_clear_to_color(al_map_rgb(0, 0, 0));
                char countdown_text[2];
                snprintf(countdown_text, 2, "%d", countdown);
                al_draw_text(font, al_map_rgb(255, 255, 255), 500, 300, ALLEGRO_ALIGN_CENTER, countdown_text);
                al_flip_display();

                // Decrease the countdown every second
                al_rest(1.0);
                countdown--;

                if (countdown == 0)
                {
                    paused = false;
                }
            }
            else if (!paused)
            {
                disp_pre_draw();
                al_clear_to_color(al_map_rgb(0,0,0));

                stars_draw();
                aliens_draw();
                shots_draw();
                fx_draw();
                ship_draw();

                hud_draw(fps);

                disp_post_draw();
            }

            redraw = false;
        }
    }

    al_destroy_font(font);
    sprites_deinit();
    hud_deinit();
    audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}