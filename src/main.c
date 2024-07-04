#include "raylib.h"

#include "memory.h"
#include "cvec.h"
#include "uuid.h"
#include "ttcard.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

CVecVoid TTCard_allTTCards = { 0 };
int cards_read = 0;

extern int add(int a, int b);

void ready();
void update(double delta);
void physics_update(double delta);
void draw(double delta);



enum State {
	ST_START_MENU,
	ST_PLAY
};
enum State current_state = ST_START_MENU;
enum State previous_state = ST_START_MENU;
void switch_state(enum State new_state);
void state_enter();
void state_update();
void state_update(double delta);
void state_physics_update(double delta);
void state_draw(double delta);
void state_exit();

void st_startmenu_draw(double delta);



int main()
{
	

	int result = add(1, 2);
	
	printf("Result: %d \n", result);

	const int screenWidth = 1280;
	const int screenHeight = 720;
	

	InitWindow(screenWidth, screenHeight, "Triple Triad");
	SetTargetFPS(60);             

	ready();

	while (!WindowShouldClose())    
	{
		
		double frame_time = GetFrameTime();
		update(frame_time);
		physics_update(frame_time);
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw(frame_time);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void ready()
{
	ttcard_read_data_json(&TTCard_allTTCards, "./data/cards.json");
	printf("Cards read from JSON...\n");
	cards_read = 1;

	printf("Capacity: %d\n", TTCard_allTTCards.capacity);
	printf("Count: %d\n", TTCard_allTTCards.count);
}

void update(double delta)
{
	state_update(delta);
}

void physics_update(double delta)
{
	state_physics_update(delta);
}

void draw(double delta)
{
	state_draw(delta);
}



/*
* State Machine
*/

void switch_state(enum State new_state)
{
	state_exit();
	previous_state = current_state;
	current_state = new_state;
	state_enter();
}

void state_enter()
{
	switch (current_state)
	{
	case ST_START_MENU:
		break;
	case ST_PLAY:
		break;
	default:
		break;
	}
}

void state_update(double delta)
{
	switch (current_state)
	{
	case ST_START_MENU:
		break;
	case ST_PLAY:
		break;
	default:
		break;
	}
}

void state_physics_update(double delta)
{
	switch (current_state)
	{
	case ST_START_MENU:
		break;
	case ST_PLAY:
		break;
	default:
		break;
	}
}

void state_draw(double delta)
{
	switch (current_state)
	{
	case ST_START_MENU:
		st_startmenu_draw(delta);
		break;
	case ST_PLAY:
		break;
	default:
		break;
	}
}

void state_exit()
{
	switch (current_state)
	{
	case ST_START_MENU:
		break;
	case ST_PLAY:
		break;
	default:
		break;
	}
}

/*------------------------------------------------------*/



void st_startmenu_draw(double delta)
{
	if (cards_read == 1)
	{
		ttcard_draw((TTCard*)TTCard_allTTCards.data[0], 25, 25);
	}
}