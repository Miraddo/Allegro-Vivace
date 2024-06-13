// fx.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the FX_H macro.
#ifndef FX_H
#define FX_H

    // -------------------------------------------------------------------------
    // Define the functions.
    void fx_init();
    void fx_add(bool spark, int x, int y);
    void fx_update(float time_elapsed, float fps);
    void fx_draw();

#endif //FX_H
