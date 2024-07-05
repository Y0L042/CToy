#ifndef ST_STARTMENU_H
#define ST_STARTMENU_H

#include "state_machine.h"

extern SM_State st_startmenu_state;

void st_startmenu_initialize_state();
void st_startmenu_draw(double delta);

#endif // !ST_STARTMENU_H
