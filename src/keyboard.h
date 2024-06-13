// keyboard.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the KEYBAORD_H macro.
#ifndef KEYBAORD_H
#define KEYBAORD_H

    // -------------------------------------------------------------------------
    // Define the constants.
    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    // -------------------------------------------------------------------------
    // Declare the global variables.
    extern unsigned char key[ALLEGRO_KEY_MAX];

    // -------------------------------------------------------------------------
    // Define the functions.
    void keyboard_init();
    void keyboard_update(ALLEGRO_EVENT* event);

#endif //KEYBAORD_H
