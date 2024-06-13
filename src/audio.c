// audio.c
// Created by milad on 6/2/2024.
//
// =============================================================================
// Include the allegro5 header file.
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// =============================================================================
// Include the header files.
#include "audio.h"
#include "utils/helper.h"

// =============================================================================
// Define the audio samples.
ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

// =============================================================================
// Define the audio initialization function.
void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    // Load the audio samples.
    sample_shot = al_load_sample("./assets/audio/shot.flac");
    must_init(sample_shot, "shot sample");

    sample_explode[0] = al_load_sample("./assets/audio/explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample("./assets/audio/explode2.flac");
    must_init(sample_explode[1], "explode[1] sample");
}

// =============================================================================
// Define the audio deinitialization function.
void audio_deinit()
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}