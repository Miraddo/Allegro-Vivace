// hud.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the HUD_H macro.
#ifndef HUD_H
#define HUD_H

    // -------------------------------------------------------------------------
    // Define the functions.
    void hud_init();
    void hud_deinit();
    void hud_update(float time_elapsed, float fps);
    void hud_draw(float fps);

#endif //HUD_H
