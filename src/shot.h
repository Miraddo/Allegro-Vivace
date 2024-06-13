// shot.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the SHOT_H macro.
#ifndef SHOT_H
#define SHOT_H

    // -------------------------------------------------------------------------
    // Declare the functions.
    void shots_init();
    bool shots_add(bool ship, bool straight, int x, int y);
    void shots_update(float time_elapsed, float fps);
    bool shots_collide(bool ship, int x, int y, int w, int h);
    void shots_draw();

#endif //SHOT_H
