//
// Created by miraddo on 6/2/2024.
//

#ifndef SHOT_H
#define SHOT_H

void shots_init();
bool shots_add(bool ship, bool straight, int x, int y);
void shots_update();
bool shots_collide(bool ship, int x, int y, int w, int h);
void shots_draw();

#endif //SHOT_H
