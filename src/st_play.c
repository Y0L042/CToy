#include "st_play.h"
#include <raylib.h>
#include <raygui.h>
#include "main.h"

SM_State st_play_state;

void st_play_initialize_state()
{
	sm_register_state(&fsm_game_machine, &st_play_state, "ST_PLAY");
	st_play_state.state_enter = st_play_enter;
	st_play_state.state_update = st_play_update;
	st_play_state.state_physics_update = st_play_physics_update;
	st_play_state.state_draw = st_play_draw;
	st_play_state.state_exit = st_play_exit;
}

void st_play_enter()
{
	printf("Entering PLAY \n");
}

void st_play_update(double delta)
{
}

void st_play_physics_update(double delta)
{
	if (IsKeyDown(KEY_SPACE))
	{
		sm_switch_state(&fsm_game_machine, "ST_STARTMENU");
	}
}

void st_play_draw(double delta)
{
	GuiLabel((Rectangle){ 250, 250, 75, 45 }, "PLAY!");
}

void st_play_exit()
{
	printf("Exiting PLAY \n");
}
