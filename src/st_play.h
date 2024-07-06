#ifndef ST_PLAY_H
#define ST_PLAY_H

#include "state_machine.h"

extern SM_State st_play_state;

void st_play_initialize_state();
void st_play_enter();
void st_play_update(double delta);
void st_play_physics_update(double delta);
void st_play_draw(double delta);
void st_play_exit();

#endif // !ST_PLAY_H
