#include "state_machine.h"

SM_State* sm_current_state = NULL;

SM_State* sm_previous_state = NULL;

void sm_switch_state(SM_State* new_state)
{
	if (sm_current_state != NULL && sm_current_state->state_exit != NULL)
	{
		sm_current_state->state_exit();
	}

	sm_previous_state = sm_current_state;
	sm_current_state = new_state;

	if (sm_current_state != NULL && sm_current_state->state_enter != NULL)
	{
		sm_current_state->state_enter();
	}
}

void sm_execute_state_update(double delta)
{
	if (sm_current_state != NULL && sm_current_state->state_update != NULL)
	{
		sm_current_state->state_update(delta);
	}
}

void sm_execute_state_physics_update(double delta)
{
	if (sm_current_state != NULL && sm_current_state->state_physics_update != NULL)
	{
		sm_current_state->state_physics_update(delta);
	}
}

void sm_execute_state_draw(double delta)
{
	if (sm_current_state != NULL && sm_current_state->state_draw != NULL)
	{
		sm_current_state->state_draw(delta);
	}
}
