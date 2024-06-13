// display.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the DISPLAY_H macro.
#ifndef DISPLAY_H
#define DISPLAY_H

    // -------------------------------------------------------------------------
    // define the display width and height.
    #define BUFFER_W 320
    #define BUFFER_H 240

    // -------------------------------------------------------------------------
    // define the display scale.
    #define DISP_SCALE 3
    #define DISP_W (BUFFER_W * DISP_SCALE)
    #define DISP_H (BUFFER_H * DISP_SCALE)

    // -------------------------------------------------------------------------
    // Declare the display variables.
    extern ALLEGRO_DISPLAY* disp;
    extern ALLEGRO_BITMAP* buffer;

    // -------------------------------------------------------------------------
    // Declare the functions.
    void disp_init();
    void disp_deinit();
    void disp_pre_draw();
    void disp_post_draw();

#endif //DISPLAY_H
