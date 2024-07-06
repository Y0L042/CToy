#include "st_startmenu.h"
#include <raygui.h>
#include "main.h"

SM_State st_startmenu_state;

void st_startmenu_initialize_state()
{
	sm_register_state(&fsm_game_machine, &st_startmenu_state, "ST_STARTMENU");
	st_startmenu_state.state_draw = st_startmenu_draw;
}

void st_startmenu_draw(double delta)
{
	if (GuiButton((Rectangle){ 250, 205, 150, 45 }, "PLAY"))
	{
		sm_switch_state(&fsm_game_machine, "ST_PLAY");
	}
}
