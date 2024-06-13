// keyboard.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// Include the allegro5 header file.
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

// =============================================================================
// Include the keyboard header file.
#include "keyboard.h"

// =============================================================================
// Define the key array.
unsigned char key[ALLEGRO_KEY_MAX];

// =============================================================================
// Define the keyboard_init function. This function is responsible for
// initializing the keyboard.
void keyboard_init()
{
    memset(key, 0, sizeof(key));
}

// =============================================================================
// Define the keyboard_update function. This function is responsible for
// updating the keyboard.
void keyboard_update(ALLEGRO_EVENT* event)
{
    switch(event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
        {
            key[i] &= KEY_SEEN;
        }
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;

    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= KEY_RELEASED;
        break;
    }
}