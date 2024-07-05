#include "st_startmenu.h"
#include <raygui.h>

SM_State st_startmenu_state;

void st_startmenu_initialize_state()
{
	st_startmenu_state.state_draw = st_startmenu_draw;
}

void st_startmenu_draw(double delta)
{
	if (GuiButton((Rectangle){ 250, 205, 150, 45 }, "PLAY"))
	{
	}
}
