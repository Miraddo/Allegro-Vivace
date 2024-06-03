//
// Created by miraddo on 6/2/2024.
//
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "audio.h"
#include "utils/helper.h"

ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    sample_shot = al_load_sample("./assets/audio/shot.flac");
    must_init(sample_shot, "shot sample");

    sample_explode[0] = al_load_sample("./assets/audio/explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample("./assets/audio/explode2.flac");
    must_init(sample_explode[1], "explode[1] sample");
}

void audio_deinit()
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}