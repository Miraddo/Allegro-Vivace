//
// Created by miraddo on 6/2/2024.
//

#ifndef KEYBAORD_H
#define KEYBAORD_H

#define KEY_SEEN     1
#define KEY_RELEASED 2

extern unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);

#endif //KEYBAORD_H
