#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdlib.h>
#include <string.h>

typedef struct {
	char state_name[50];
	void (*state_enter)(void);
	void (*state_update)(double);
	void (*state_physics_update)(double);
	void (*state_draw)(double);
	void (*state_exit)(void);
} SM_State;

extern SM_State* sm_current_state;
extern SM_State* sm_previous_state;

void sm_switch_state(SM_State* new_state);
void sm_execute_state_update(double delta);
void sm_execute_state_physics_update(double delta);
void sm_execute_state_draw(double delta);

#endif // !STATE_MACHINE_H
