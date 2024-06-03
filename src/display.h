//
// Created by miraddo on 6/2/2024.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#define BUFFER_W 320
#define BUFFER_H 240

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buffer;

void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();

#endif //DISPLAY_H
