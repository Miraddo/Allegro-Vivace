// audio.h
// Created by milad on 6/2/2024.
//
// =============================================================================
// Define the AUDIO_H macro.
#ifndef AUDIO_H
#define AUDIO_H
    // -------------------------------------------------------------------------
    // Declare the audio variables.
    extern ALLEGRO_SAMPLE* sample_shot;
    extern ALLEGRO_SAMPLE* sample_explode[2];

    // -------------------------------------------------------------------------
    // Declare the functions.
    void audio_init();
    void audio_deinit();

#endif //AUDIO_H
