//
// Created by miraddo on 6/2/2024.
//
#include <allegro5/allegro_audio.h>

#ifndef AUDIO_H
#define AUDIO_H

extern ALLEGRO_SAMPLE* sample_shot;
extern ALLEGRO_SAMPLE* sample_explode[2];

void audio_init();
void audio_deinit();

#endif //AUDIO_H
